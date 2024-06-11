/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inflate.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 11:07:21 by reclaire          #+#    #+#             */
/*   Updated: 2024/06/08 21:30:16 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "deflate_int.h"
#include <stdio.h>

#define __FTINFLATEERR(_ret, _inflate_err, _errno) \
	do                                             \
	{                                              \
		if (err)                                   \
			*err = _inflate_err;                   \
		__FTRETURN_ERR(_ret, _errno);              \
	} while (0)

static t_huffman_node *huffman_add_node(t_huffman_node *root, U8 code, U8 code_len, int symbol)
{
	if (code_len == 0)
	{
		if (root != NULL)
			return NULL;
		t_huffman_node *out = malloc(sizeof(t_huffman_node));
		out->left = NULL;
		out->right = NULL;
		out->byte = symbol;
		out->nbits = code_len;
		out->huffman_coding = code;
		return out;
	}
	else
	{
		U8 bit = (code >> (code_len - 1)) & 0x1;
		if (root == NULL)
		{
			root = malloc(sizeof(t_huffman_node));
			ft_bzero(root, sizeof(t_huffman_node));
			root->byte = U8_MAX;
		}
		if (bit == 0)
			root->left = huffman_add_node(root->left, code, code_len - 1, symbol);
		else
			root->right = huffman_add_node(root->right, code, code_len - 1, symbol);
		return root;
	}
}

static t_huffman_node *mk_huffman(U8 *data, U64 len)
{
	t_huffman_node *root = NULL;
	for (U64 i = 0; i < len; i++)
	{
		U8 num_bits = data[i * 2];
		U8 code_bits = data[i * 2 + 1];
		if (num_bits == 0)
			continue;

		root = huffman_add_node(root, code_bits, num_bits, i);
		if (root == NULL)
		{
			printf("Symbol 0x%02lx (code ", i);
			for (int i = 0; i < 8; i++)
				printf("%u", code_bits >> i);
			printf(") terminates at an internal node\n");
		}
	}
	return root;
}

#define code_length_to_code_table(code_lengths, code_lengths_len, max_code_length, code_table_out)   \
	do                                                                                               \
	{                                                                                                \
		U8 *code_table = a_malloc(sizeof(U8) * 2 * code_lengths_len);                                \
		if (code_table == NULL)                                                                      \
			__FTRETURN_ERR(FALSE, FT_EOMEM);                                                         \
		(*code_table_out) = code_table;                                                              \
		{                                                                                            \
			U16 *next_code = a_malloc(sizeof(U16) * max_code_length + sizeof(U8) * max_code_length); \
			if (next_code == NULL)                                                                   \
			{                                                                                        \
				a_free(code_table);                                                                  \
				__FTRETURN_ERR(FALSE, FT_EOMEM);                                                     \
			}                                                                                        \
			U8 *lengths_count = next_code + sizeof(U16) * max_code_length;                           \
			for (U64 i = 0; i < code_lengths_len; i++)                                               \
				lengths_count[code_lengths[i]]++;                                                    \
                                                                                                     \
			ft_bzero(code_table, sizeof(U8) * 2 * code_lengths_len);                                 \
			U32 code = 0;                                                                            \
			lengths_count[0] = 0;                                                                    \
			for (U8 bits = 1; bits < (max_code_length + 1); bits++)                                  \
			{                                                                                        \
				code = (code + lengths_count[bits - 1]) << 1;                                        \
				next_code[bits] = code;                                                              \
			}                                                                                        \
                                                                                                     \
			for (U64 i = 0; i < code_lengths_len; i++)                                               \
			{                                                                                        \
				U16 length = code_lengths[i];                                                        \
				if (length != 0)                                                                     \
				{                                                                                    \
					code_table[i * 2] = length;                                                      \
					code_table[i * 2 + 1] = next_code[length];                                       \
					next_code[length]++;                                                             \
				}                                                                                    \
			}                                                                                        \
			a_free(next_code);                                                                       \
		}                                                                                            \
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
		U8 block_header = (*(U16 *)(data_stream->in + data_stream->in_used) >> data_stream->bit_offset) & 0x7;
		last = block_header & 0x1;
		block_type = (block_header & 0x6) >> 1;

		data_stream->bit_offset += 3;
	}

	printf("Reading block:\n");
	printf("	is last: %s\n", last ? "TRUE" : "FALSE");
	printf("	block type: %d\n", block_type);

	U64 out_sv = data_stream->out_used;
	switch (block_type)
	{
	case DEFLATE_BLOCK_TYPE_0:;
		U16 size;
		if (data_stream->bit_offset != 0)
		{
			data_stream->in_used++;
			data_stream->bit_offset = 0;
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
	case DEFLATE_BLOCK_TYPE_1:; // Block type are reversed

		U16 code = 0;
		while (TRUE)
		{
			U64 curr = *(U64 *)(data_stream->in + data_stream->in_used);
			code = getcode(curr, &data_stream->bit_offset);
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
					extra_length = (*(U32 *)(data_stream->in + data_stream->in_used) >> data_stream->bit_offset) & length_code.mask;
					data_stream->bit_offset += length_code.extra_bits;
				}

				{ // Read distance code + read extra distance bits
					dist_code = (curr >> data_stream->bit_offset) & 0x1F;
					distance_code = offset_table[dist_code];
					data_stream->bit_offset += 5;

					extra_distance = (*(U32 *)(data_stream->in + data_stream->in_used) >> data_stream->bit_offset) & distance_code.mask;
					data_stream->bit_offset += distance_code.extra_bits;
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

			data_stream->in_used += data_stream->bit_offset / 8;
			data_stream->bit_offset %= 8;
		}
		break;

	case DEFLATE_BLOCK_TYPE_2:; // Block type are reversed
		U32 header = *(U32 *)(data_stream->in + data_stream->in_used) >> data_stream->bit_offset;
		U16 num_ll_code = (header & 0x1f) + 257;
		U8 num_dist_code = ((header & 0x3e0) >> 5) + 1;
		U8 num_cl_code = ((header & 0x3c00) >> 10) + 4;

		printf("\n	Num ll code: %u\n	Num dist code: %u\n	Num cl code: %u\n", num_ll_code, num_dist_code, num_cl_code);

		data_stream->bit_offset += 14;
		data_stream->in_used += data_stream->bit_offset / 8;
		data_stream->bit_offset %= 8;

		const U8 cl_code_length_encoding_i[] = {16, 17, 18, 0, 8, 7, 9, 6, 10, 5, 11, 4, 12, 3, 13, 2, 14, 1, 15};
		U8 cl_code_length[19] = {0};
#define cl_code_length_len (sizeof(cl_code_length) / sizeof(cl_code_length[0]))
		U8 cl_code_length_max = 0;
		for (U8 i = 0; i < num_cl_code; i++)
		{
			U8 v = ((*(U16 *)(data_stream->in + data_stream->in_used)) >> data_stream->bit_offset) & 0x7;
			cl_code_length[cl_code_length_encoding_i[i]] = v;
			cl_code_length_max = MAX(v, cl_code_length_max);

			data_stream->bit_offset += 3;
			data_stream->in_used += data_stream->bit_offset / 8;
			data_stream->bit_offset %= 8;
		}

		printf("	CL code lengths (0 - 18): %u", cl_code_length[0]);
		for (U64 i = 1; i < cl_code_length_len; i++)
			printf(" %u", cl_code_length[i]);
		printf("\n");

		U8 *cl_codes;
		{
			U8 *code_table;
			U16 next_code[7] = {0};
			U8 lengths_count[7] = {0};
			for (U64 i = 0; i < cl_code_length_len; i++)
				lengths_count[cl_code_length[i]]++;

			code_table = a_malloc(sizeof(U8) * 2 * cl_code_length_len);
			ft_bzero(code_table, sizeof(U8) * 2 * cl_code_length_len);
			if (code_table == NULL)
				__FTRETURN_ERR(FALSE, FT_EOMEM);

			U16 code = 0;
			lengths_count[0] = 0;
			for (U8 bits = 1; bits < (cl_code_length_max + 1); bits++)
			{
				code = (code + lengths_count[bits - 1]) << 1;
				next_code[bits] = code;
			}

			for (U8 i = 0; i < cl_code_length_len; i++)
			{
				U8 length = cl_code_length[i];
				if (length != 0)
				{
					code_table[i * 2] = length;
					code_table[i * 2 + 1] = next_code[length];
					next_code[length]++;
				}
			}
			cl_codes = code_table;
		}

		printf("	CL Codes:\n");
		for (U64 i = 0; i < cl_code_length_len; i++)
		{
			U8 length = cl_codes[i * 2];
			U8 encoded_bits = cl_codes[i * 2 + 1];
			if (length == 0)
				continue;
			printf("		%ld:", i);
			for (int i = length - 1; i >= 0; i--)
				printf("%c", ((encoded_bits & (1 << i)) != 0) ? '1' : '0');
			printf("\n");
		}

		t_huffman_node *root = mk_huffman(cl_codes, cl_code_length_len);

		U16 ll_code_lengths[288] = {0};
		U16 dist_code_lengths[32] = {0};
		U16 dist_ll_code_lengths_max = 0;
		{

			t_huffman_node *node = root;
			if (node == NULL)
				goto block2_end;

			U64 codes_read = 0;
			int last_symbol = -1;
			while (codes_read < num_ll_code + num_dist_code)
			{
				U8 b = (*(data_stream->in + data_stream->in_used) >> data_stream->bit_offset) & 0x1;
				data_stream->bit_offset++;
				data_stream->in_used += data_stream->bit_offset / 8;
				data_stream->bit_offset %= 8;

				node = b == 0 ? node->left : node->right;
				if (node->byte == U8_MAX)
					continue;
				int symbol = node->byte;
				node = root;
				if (symbol < 0 || symbol > 18)
				{
					printf("symbol error\n");
				}

				U8 repeat_count;
				switch (symbol)
				{
				case 16:;
					repeat_count = 3 + ((*(U16 *)(data_stream->in + data_stream->in_used) >> data_stream->bit_offset) & 0x3);
					data_stream->bit_offset += 2;
					data_stream->in_used += data_stream->bit_offset / 8;
					data_stream->bit_offset %= 8;

					if (last_symbol == -1)
						printf("Repeat code (16) used for first CL code value");
					printf("Symbol 16 (repeat count %d, repeating %d)\n", repeat_count, last_symbol);
					for (int i = 0; i < repeat_count; i++)
					{
						if (codes_read >= num_ll_code)
							dist_code_lengths[codes_read - num_ll_code] = last_symbol;
						else
							ll_code_lengths[codes_read] = last_symbol;
						codes_read++;
					}
					break;
				case 17:;
					repeat_count = 3 + ((*(U16 *)(data_stream->in + data_stream->in_used) >> data_stream->bit_offset) & 0x7);
					data_stream->bit_offset += 3;
					data_stream->in_used += data_stream->bit_offset / 8;
					data_stream->bit_offset %= 8;

					printf("Symbol 17 (repeat count %d)\n", repeat_count);
					for (int i = 0; i < repeat_count; i++)
					{
						if (codes_read >= num_ll_code)
							dist_code_lengths[codes_read - num_ll_code] = 0;
						else
							ll_code_lengths[codes_read] = 0;
						codes_read++;
					}
					last_symbol = 0;
					break;
				case 18:;
					repeat_count = 11 + ((*(U16 *)(data_stream->in + data_stream->in_used) >> data_stream->bit_offset) & 0x7f);
					data_stream->bit_offset += 7;
					data_stream->in_used += data_stream->bit_offset / 8;
					data_stream->bit_offset %= 8;

					printf("Symbol 18 (repeat count %d)\n", repeat_count);
					for (int i = 0; i < repeat_count; i++)
					{
						if (codes_read >= num_ll_code)
							dist_code_lengths[codes_read - num_ll_code] = 0;
						else
							ll_code_lengths[codes_read] = 0;
						codes_read++;
					}
					last_symbol = 0;
					break;
				default:
					if (codes_read >= num_ll_code)
						dist_code_lengths[codes_read - num_ll_code] = symbol;
					else
						ll_code_lengths[codes_read] = symbol;
					codes_read += 1;
					last_symbol = symbol;
					dist_ll_code_lengths_max = MAX(dist_ll_code_lengths_max, symbol);
					break;
				}
			}

			for (U64 i = 0; i < sizeof(ll_code_lengths) / sizeof(ll_code_lengths[0]); i++)
				printf("%u, ", ll_code_lengths[i]);
			printf("\n");
			U8 *ll_codes;
			code_length_to_code_table(ll_code_lengths, (sizeof(ll_code_lengths) / sizeof(ll_code_lengths[0])), dist_ll_code_lengths_max, &ll_codes);
			printf("LL codes:\n");
			for (U64 i = 0; i < sizeof(ll_code_lengths) / sizeof(ll_code_lengths[0]); i++)
			{
				U8 length = ll_codes[i * 2];
				U8 bits = ll_codes[i * 2 + 1];
				if (length == 0)
					continue;
				printf("		%lu:", i);
				for (int i = length - 1; i >= 0; i--)
					printf("%c", ((bits & (1 << i)) != 0) ? '1' : '0');
				printf("\n");
			}
		}

	block2_end:
		a_free(code_table);
		break;
	}

	data_stream->crc32 = ft_crc32_u(data_stream->out + out_sv, data_stream->out_used - out_sv, data_stream->crc32);

	if (err)
		*err = FT_OK;
	return !last;
}

struct s_inflate_error_entry
{
	S32 err;
	string name;
	string desc;
};

#define ENT(X, desc) {X, #X, desc},
#define ENTRIES_LEN ((S32)(sizeof(entries) / sizeof(struct s_inflate_error_entry) - 1))

static struct s_inflate_error_entry entries[] = {
	ENT(FT_OK, "No error")
		ENT(FT_INFLATE_EOMEM, "Not enough space in output buffer")
			ENT(FT_INFLATE_EBLOCKSIZE, "Invalid (size/~size) in block type 0")
				ENT(FT_INFLATE_EINV_LENGTH_CODE, "Invalid length code")
					ENT(FT_INFLATE_EINV_DISTANCE, "Invalid distance. Not enough characters in buffer to process back-reference")};

const_string ft_inflate_strerror(S32 err)
{
	if (err < 0)
		__FTRETURN_ERR((NULL), FT_ERANGE);
	if (err >= ENTRIES_LEN)
		__FTRETURN_ERR((NULL), FT_ENOENT);
	return entries[err].desc;
}

const_string ft_inflate_errortostr(S32 err)
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
