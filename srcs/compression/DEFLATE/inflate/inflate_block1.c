/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inflate_block1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 21:08:00 by reclaire          #+#    #+#             */
/*   Updated: 2024/06/18 21:28:20 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inflate_int.h"

static U8 reverse_5_bits(U8 x)
{
    static const U8 table[] = {
        0x00, 0x10, 0x08, 0x18,
		0x04, 0x14, 0x0c, 0x1c,
		0x02, 0x12, 0x0a, 0x1a,
		0x06, 0x16, 0x0e, 0x1e,
		0x01, 0x11, 0x09, 0x19,
		0x05, 0x15, 0x0d, 0x1d,
		0x03, 0x13, 0x0b, 0x1b,
		0x07, 0x17, 0x0f, 0x1f,
    };
    return table[x];
}

static U16 getcode(U64 d, U8 *bit_offset)
{
	U64 v = d >> *bit_offset;
	U16 i = 0;

	for (; i < 144; i++)
	{
		if ((v & 0xFF) == ll_codes[i])
		{
			*bit_offset += 8;
			return i;
		}
	}
	for (; i < 256; i++)
	{
		if ((v & 0x1FF) == ll_codes[i])
		{
			*bit_offset += 9;
			return i;
		}
	}
	for (; i < 280; i++)
	{
		if ((v & 0x7F) == ll_codes[i])
		{
			*bit_offset += 7;
			return i;
		}
	}
	for (; i < 288; i++)
	{
		if ((v & 0xFF) == ll_codes[i])
		{
			*bit_offset += 8;
			return i;
		}
	}

	return U16_MAX;
}

#define block_type_1_save_state()                                          \
	{                                                                      \
		stream->bit_offset = bit_offset_sv;                                \
		stream->save_state.type1.working_bytes = curr;                     \
	}

bool inflate_block_type1(t_deflate_stream *stream, S32 *err, bool load_save)
{
	U16 code = 0;

	if (UNLIKELY(load_save))
	{
		if (CHK_OUT_SIZE(4))
			__FTINFLATEERR(FT_INFLATE_E_OUT_OMEM);
		*((U64 *)(stream->out + stream->out_used)) = stream->save_state.type1.working_bytes;
	}

	while (TRUE)
	{
		if (CHK_IN_SIZE(8))
			__FTINFLATEERR(FT_INFLATE_E_IN_OMEM);

		/*
		getcode: max 9 bits
		ll code extra bits: max 5 bits
		dist code: 5 bits
		dist code extra bits: max 13 bits
		total: 32 bits
		+ bit offset: max 10
		total: 42 bits
		*/

		U8 bit_offset_sv = stream->bit_offset;

		U64 curr = *(U64 *)(stream->in + stream->in_used);

		code = getcode(curr, &stream->bit_offset);
		if (UNLIKELY(code == U16_MAX))
			__FTINFLATEERR(FT_INFLATE_EINV_LENGTH_CODE); // ERROR: INVALID CODE
		if (UNLIKELY(stream->out_used == stream->out_size))
		{
			IFDEBUG(printf("	/!\\ Not enough space remaining in buffer\n");)
			block_type_1_save_state();
			__FTINFLATEERR(FT_INFLATE_E_OUT_OMEM); // ERROR: NO MORE SPACE
		}

		if (code < 256)
		{
			IFDEBUG(if (ft_isprint(code)) printf("	Litteral: %c\n", (U8)code); else printf("	Litteral: %#x\n", (U8)code);)
			*(stream->out + stream->out_used) = (U8)code;
			stream->out_used++;
		}
		else if (code == 256)
		{
			IFDEBUG(printf("	End of block marker found\n");)
			break;
		}
		else
		{
			IFDEBUG(
				printf("	Backref:\n");
				printf("		ll code: %u\n", code);)
			struct s_table_entry length_code, distance_code;
			U16 extra_length, extra_distance;
			U16 total_length, total_distance;
			U8 dist_code;

			{										// Get length_code + read extra length bits
				length_code = ll_table[code - 257]; // max extra bits: 5
				extra_length = (curr >> stream->bit_offset) & length_code.mask;
				stream->bit_offset += length_code.extra_bits;
				IFDEBUG(
					printf("		Length table entry: { min: %u, max: %u, extra bits: %u }\n", length_code.min, length_code.max, length_code.extra_bits);
					printf("		Extra length: %u\n", extra_length);)
			}

			{ // Read distance code + read extra distance bits
				dist_code = reverse_5_bits((curr >> stream->bit_offset) & 0x1F);
				distance_code = offset_table[dist_code];
				stream->bit_offset += 5;

				extra_distance = (curr >> stream->bit_offset) & distance_code.mask;
				stream->bit_offset += distance_code.extra_bits;
				IFDEBUG(
					printf("		Dist code: %u\n", dist_code);
					printf("		Dist table entry: { min: %u, max: %u, extra bits: %u }\n", distance_code.min, distance_code.max, distance_code.extra_bits);
					printf("		Extra dist: %u\n", extra_distance));
			}

			total_length = length_code.min + extra_length;
			total_distance = distance_code.min + extra_distance;
			IFDEBUG(
				printf("		Total length/distance: %u/%u\n", total_length, total_distance);)

			if (UNLIKELY(total_distance > stream->out_used))
				__FTINFLATEERR(FT_INFLATE_EINV_DISTANCE); // ERROR: DIST > N CHARS IN BUFFER

			if (UNLIKELY(stream->out_used + total_length > stream->out_size))
			{
				block_type_1_save_state();
				__FTINFLATEERR(FT_INFLATE_E_OUT_OMEM); // ERROR: NOT ENOUGH SPACE
			}

			for (U16 i = 0; i < total_length; i++)
				*(stream->out + stream->out_used + i) = *(stream->out + stream->out_used - total_distance + i);
			stream->out_used += total_length;
		}

		stream->in_used += stream->bit_offset / 8;
		stream->bit_offset %= 8;
	}

	return TRUE;
}
