/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deflate.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 03:49:46 by reclaire          #+#    #+#             */
/*   Updated: 2024/06/04 16:06:51 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "deflate_int.h"

//#define DEFLATE_VERBOSE

static U8 reverse(U8 b)
{
	b = (b & 0xF0) >> 4 | (b & 0x0F) << 4;
	b = (b & 0xCC) >> 2 | (b & 0x33) << 2;
	b = (b & 0xAA) >> 1 | (b & 0x55) << 1;
	return b;
}

static inline void write_block_header(t_deflate_stream *stream, bool last, U8 block_type)
{
	*(U16 *)(stream->out + stream->out_used) |= ((last | (block_type << 1)) << stream->s.bit_offset);
	if (stream->s.bit_offset > 5)
	{
		stream->s.bit_offset = (stream->s.bit_offset + 3) % 8;
		stream->out_used++;
	}
	else
		stream->s.bit_offset += 3;
}

#define LOOKAHEAD_SIZE 1024
#define WINDOW_SIZE 32768

#define out_remaining_size(stream) (stream->out_size - stream->out_used)
#define out_remaining_bits(stream) (out_remaining_size(stream) * 8 - stream->s.bit_offset)
#define in_remaining_size(stream) (stream->in_size - stream->in_used)

#define min_type_0_size (                      \
	3	 /* 3 bits pour le header */           \
	+ 32 /* 32 bits pour la taille du block */ \
	+ 8	 /* 8 bits pour 1 byte */              \
)

#define min_type_1_size (             \
	3	/* 3 bits pour le header */   \
	+ 8 /* 8 bits pour un code */     \
	+ 7 /* 7 bits pour le code 256 */ \
)

static void find_backref_linear(t_deflate_stream *stream, U64 n, U64 to_compress, U64 window_size, U16 *out_length, U16 *out_distance)
{
	U64 wn = 1;

	to_compress = 1024;
	n = 0;

	*out_length = 0;
	*out_distance = 0;

	while (wn < window_size + 1)
	{
		U64 i = 0;
		while (i < 258 &&
			   (i + n) < to_compress &&
			   *(stream->in + stream->in_used + i - wn) == *(stream->in + stream->in_used + i))
		{
			i++;
		}

		if (i > *out_length)
		{
			*out_distance = wn;
			*out_length = i;
		}
		wn++;
	}
}

bool ft_deflate_next_block(t_deflate_stream *data_stream, U64 block_max_size, U8 is_last, U8 block_type)
{
	if (UNLIKELY(in_remaining_size(data_stream) == 0) || UNLIKELY(out_remaining_size(data_stream) == 0))
		__FTRETURN_ERR(FALSE, FT_EINVOP);

	U64 to_compress = UNLIKELY(in_remaining_size(data_stream) < block_max_size) ? in_remaining_size(data_stream) : block_max_size;
	switch (block_type)
	{
	case DEFLATE_BLOCK_TYPE_0:; // TODO: 65,535 max size
		to_compress = MIN(to_compress, (out_remaining_bits(data_stream) - (min_type_0_size - 8)) / 8);

		{ // Error checks
			if (UNLIKELY(to_compress > U16_MAX))
				__FTRETURN_ERR(FALSE, FT_EINVVAL); // ERROR: BLOCK SIZE OVERFLOW
			if (UNLIKELY(min_type_0_size > out_remaining_bits(data_stream)))
				__FTRETURN_ERR(FALSE, FT_EINVOP); // ERROR: PAS ASSEZ DE PLACE PR UN BLOCK
			if (UNLIKELY(to_compress == 0))
				__FTRETURN_ERR(FALSE, FT_EINVOP); // ERROR: BLOCK DE 0 DE SIZE
		}

		write_block_header(data_stream, is_last, block_type);

		// Skip current byte
		if (LICKELY(data_stream->s.bit_offset != 0))
		{
			data_stream->s.bit_offset = 0;
			data_stream->out_used++;
		}

		{ // Write size ~size
			U16 size = to_compress;
			*(U16 *)(data_stream->out + data_stream->out_used) = size;
			*(U16 *)(data_stream->out + data_stream->out_used + 2) = ~size;
			data_stream->out_used += 4;
		}

		ft_memcpy(
			data_stream->out + data_stream->out_used,
			data_stream->in + data_stream->in_used,
			to_compress);

		data_stream->crc32 = ft_crc32_u(data_stream->in + data_stream->in_used, to_compress, data_stream->crc32);
		data_stream->out_used += to_compress;
		data_stream->in_used += to_compress;
		break;

	case DEFLATE_BLOCK_TYPE_1:;
		if (UNLIKELY(min_type_1_size > out_remaining_bits(data_stream)))
			__FTRETURN_ERR(FALSE, FT_EINVOP); // ERROR: PAS ASSEZ DE PLACE PR UN BLOCK

		to_compress = MIN(to_compress, (out_remaining_bits(data_stream) - (min_type_1_size - 8)) / 8);
		if (UNLIKELY(to_compress == 0))
			__FTRETURN_ERR(FALSE, FT_EINVOP); // ERROR: BLOCK DE 0 DE SIZE

		write_block_header(data_stream, is_last, block_type);

		U64 in_i_sv = data_stream->in_used;
		U64 window = 0, n = 0;

#define step_stream                                             \
	{                                                           \
		data_stream->out_used += data_stream->s.bit_offset / 8; \
		data_stream->s.bit_offset %= 8;                         \
	}

		while (n < to_compress)
		{
			U16 length, distance;
			find_backref_linear(data_stream, n, to_compress, window, &length, &distance);

			U64 incr = 1;
			if (distance > 0 && length >= 3)
			{
				incr = length;
				U16 llcode, distancecode;

				{ // Find length code and distance code
					for (llcode = 0; llcode < ll_table_size; llcode++)
						if (ll_table[llcode].min <= length && ll_table[llcode].max >= length)
							break;
					for (distancecode = 0; distancecode < offset_table_size; distancecode++)
						if (offset_table[distancecode].min <= distance && offset_table[distancecode].max >= distance)
							break;
				}

				U8 llcode_size = ll_codes_bits[(llcode + 257) / 8];

				U8 code_size =
					llcode_size +						   // llcode bits				max 9
					ll_table[llcode].extra_bits +		   // llcode extra bits			max 5
					5 +									   // offset code bits			max 5
					offset_table[distancecode].extra_bits; // offset code extra bits	max 13

				// + 7 pour le code de fin de block (256)
				if ((U8)(code_size + 7) > out_remaining_bits(data_stream))
					__FTRETURN_ERR(FALSE, FT_EINVOP); // ERROR: PLUS DE PLACE

				// Le code entier tiens dans 32 bits (9 + 5 + 5 + 13 = 32)
				// clang-format off
				//U32 full_code = 0
				//	| ll_codes[llcode + 257]
				//	| (((U16)(length - ll_table[llcode].min)) << (llcode_size))
				//	| ((reverse(distancecode) >> 3) << (llcode_size + ll_table[llcode].extra_bits + 1))
				//	| ((distance - offset_table[distancecode].min) << (llcode_size + ll_table[llcode].extra_bits + 6));
				U32 full_code = 0
					| ll_codes[llcode + 257]
					| (((U16)(length - ll_table[llcode].min)) << (llcode_size))
					| ((reverse(distancecode) >> 3) << (llcode_size + ll_table[llcode].extra_bits))
					| ((distance - offset_table[distancecode].min) << (llcode_size + ll_table[llcode].extra_bits + 5));
				// clang-format on

				*(U64 *)(data_stream->out + data_stream->out_used) |= full_code << data_stream->s.bit_offset;
				data_stream->s.bit_offset += code_size;
				step_stream;

#ifdef DEFLATE_VERBOSE
				printf("backref: %u:%u\n", length, distance);
#endif
			}
			else
			{
				U8 c = *(data_stream->in + data_stream->in_used);
#ifdef DEFLATE_VERBOSE
				if (ft_isprint(c))
					printf("lit: %d -> %c\n", c, c);
				else
					printf("lit: %d\n", c);
#endif

				*(U16 *)(data_stream->out + data_stream->out_used) |= ll_codes[c] << data_stream->s.bit_offset;
				data_stream->s.bit_offset += ll_codes_bits[c / 8];
				step_stream;
			}

			if (window < WINDOW_SIZE)
				window = MIN(WINDOW_SIZE, incr + window);
			data_stream->in_used += incr;
			n += incr;
		}

		//  Code 256: 0000000, donc juste bit_offset+=7
		data_stream->s.bit_offset += 7;
		step_stream;

		data_stream->crc32 = ft_crc32_u(data_stream->in + in_i_sv, data_stream->in_used - in_i_sv, data_stream->crc32);
		break;
	}

	__FTRETURN_OK(TRUE);
}

bool ft_deflate_end(t_deflate_stream *stream)
{
	if (LICKELY(stream->s.bit_offset != 0))
	{
		stream->out_used++;
		if (UNLIKELY(stream->out_used > stream->out_size))
			__FTRETURN_ERR(FALSE, FT_EINVOP);
		stream->s.bit_offset = 0;
	}
	__FTRETURN_OK(TRUE);
}
