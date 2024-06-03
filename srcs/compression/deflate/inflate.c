/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inflate.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 11:07:21 by reclaire          #+#    #+#             */
/*   Updated: 2024/06/02 23:00:58 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "deflate_int.h"

#define __FTINFLATEERR(_ret, _inflate_err, _errno) \
	do                                             \
	{                                              \
		if (err)                                   \
			*err = _inflate_err;                   \
		__FTRETURN_ERR(_ret, _errno);              \
	} while (0)

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

bool ft_inflate_next_block(t_deflate_stream *data_stream, S32 *err)
{
	U8 last, block_type;

	{ // Read block header (block type is inverted: block type 1 <=> block type 2)
		U8 block_header = (*(U16 *)(data_stream->in + data_stream->in_used) >> data_stream->s.bit_offset) & 0x7;
		last = block_header & 0x1;
		block_type = block_header & 0x6;

		data_stream->s.bit_offset += 3;
	}

	U64 out_sv = data_stream->out_used;

	switch (block_type)
	{
	case DEFLATE_BLOCK_TYPE_0:;
		U16 size;
		if (data_stream->s.bit_offset != 0)
		{
			data_stream->in_used++;
			data_stream->s.bit_offset = 0;
		}

		{ // Read size and check ~size
			size = *(U16 *)(data_stream->in + data_stream->in_used);
			U16 nsize = *(U16 *)(data_stream->in + data_stream->in_used + 2);
			if (UNLIKELY(size != ((~nsize) & 0xffff)))
				__FTINFLATEERR(FALSE, FT_INFLATE_EBLOCKSIZE, FT_EINVOP); // ERROR: INVALID SIZE ~SIZE
			data_stream->in_used += 4;
		}

		if (UNLIKELY(data_stream->out_size - data_stream->out_used < size))
			__FTINFLATEERR(FALSE, FT_INFLATE_EOMEM, FT_EINVOP); // ERROR: NOT ENOUGH SPACE

		ft_memcpy(data_stream->out + data_stream->out_used, data_stream->in + data_stream->in_used, size);
		data_stream->in_used += size;
		data_stream->out_used += size;

		break;
	case DEFLATE_BLOCK_TYPE_2:; // Block type are reversed

		U16 code = 0;
		while (TRUE)
		{
			U64 curr = *(U64 *)(data_stream->in + data_stream->in_used);
			code = getcode(curr, &data_stream->s.bit_offset);
			if (UNLIKELY(code == U16_MAX))
				__FTINFLATEERR(FALSE, FT_INFLATE_EINV_LENGTH_CODE, FT_EINVOP); // ERROR: INVALID CODE
			if (code < 256)
			{
				*(data_stream->out + data_stream->out_used) = (U8)code;
				data_stream->out_used++;
			}
			else if (code == 256)
				break;
			else
			{
				struct s_table_entry length_code, distance_code;
				U16 extra_length, extra_distance;
				U16 total_length, total_distance;
				U8 dist_code;

				{ // Get length_code + read extra length bits
					length_code = ll_table[code - 257];
					extra_length = (*(U32 *)(data_stream->in + data_stream->in_used) >> data_stream->s.bit_offset) & length_code.mask;
					data_stream->s.bit_offset += length_code.extra_bits;
				}

				{ // Read distance code + read extra distance bits
					dist_code = (curr >> data_stream->s.bit_offset) & 0x1F;
					distance_code = offset_table[dist_code];
					data_stream->s.bit_offset += 5;

					extra_distance = (*(U32 *)(data_stream->in + data_stream->in_used) >> data_stream->s.bit_offset) & distance_code.mask;
					data_stream->s.bit_offset += distance_code.extra_bits;
				}

				total_length = length_code.min + extra_length;
				total_distance = distance_code.min + extra_distance;

				if (UNLIKELY(total_distance > data_stream->out_used))
					__FTINFLATEERR(FALSE, FT_INFLATE_EINV_DISTANCE, FT_EINVOP); // ERROR: DIST > N CHARS IN BUFFER
				if (UNLIKELY(data_stream->out_used + total_length > data_stream->out_size))
					__FTINFLATEERR(FALSE, FT_INFLATE_EOMEM, FT_EINVOP); // ERROR: NOT ENOUGH SPACE

				for (U16 i = 0; i < total_length; i++)
					*(data_stream->out + data_stream->out_used) = *(data_stream->out + data_stream->out_used - total_distance + i);
				data_stream->out_used += total_length;
			}

			data_stream->in_used += data_stream->s.bit_offset / 8;
			data_stream->s.bit_offset %= 8;
		}
		break;

	case DEFLATE_BLOCK_TYPE_1:; // Block type are reversed
		break;
	}

	data_stream->crc32 = ft_crc32_u(data_stream->out + out_sv, data_stream->out_used - out_sv, data_stream->crc32);

	if (err)
		*err = FT_OK;
	return !last;
}





struct s_inflate_error_entry
{
	S32	err;
	string			name;
	string			desc;
};

# define ENT(X, desc) { X, #X, desc },
# define ENTRIES_LEN ((S32)(sizeof(entries)/sizeof(struct s_inflate_error_entry) - 1))

static struct s_inflate_error_entry entries[] = {
	ENT(FT_OK, "No error")
	ENT(FT_INFLATE_EOMEM, "Not enough space in output buffer")
	ENT(FT_INFLATE_EBLOCKSIZE, "Invalid (size/~size) in block type 0")
	ENT(FT_INFLATE_EINV_LENGTH_CODE, "Invalid length code")
	ENT(FT_INFLATE_EINV_DISTANCE, "Invalid distance. Not enough characters in buffer to process back-reference")
};


const_string	ft_inflate_strerror(S32 err)
{
	if (err < 0)
		__FTRETURN_ERR((NULL), FT_ERANGE);
	if (err >= ENTRIES_LEN)
		__FTRETURN_ERR((NULL), FT_ENOENT);
	return entries[err].desc;
}

const_string	ft_inflate_errortostr(S32 err)
{
	if (err < 0)
		__FTRETURN_ERR((NULL), FT_ERANGE);
	if (err >= ENTRIES_LEN)
		__FTRETURN_ERR((NULL), FT_ENOENT);
	return entries[err].name;
}

S32 ft_inflate_strtoerror(const_string name)
{
	if (name == NULL)
		__FTRETURN_ERR((-1), FT_EINVPTR);
	S32 i = 0;
	while (i < ENTRIES_LEN)
	{
		if (!ft_strcmp(name, entries[i].name))
			break;
		i++;
	}
	if (i == ENTRIES_LEN)
		__FTRETURN_ERR((-1), FT_ENOENT);
	__FTRETURN_OK(i);
}
