/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deflate.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 03:49:46 by reclaire          #+#    #+#             */
/*   Updated: 2024/05/28 02:49:45 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_int.h"
#include <stdio.h>

/*
Le boug de la vidéo parle d'un truc SUPER IMPORTANT sur l'ordre des bits:
https://youtu.be/SJPvNi4HrWQ?t=1403
Rule#1
Donc en gros quand on push un NOMBRE dans le stream, toujours least significant bit
Quand on a un byte entier, on le reverse et ca pars


Deflate:
https://youtu.be/SJPvNi4HrWQ?t=2891

1 block:
	IS_LAST  BTYPE   BITSTREAM...
	1 bit   2 bits

Plusieurs types de blocks:
Type 0: non-compressé
	IS_LAST  BTYPE   PADDING    SIZE    ~SIZE   BITSTREAM...
	1 bit   2 bits   5 bits   16 bits  16 bits

Type 1: back references

De ce que j'ai compris jusque la:
On se balade dans le stream de donné, tant qu'on trouve une séquence de charactères
qu'on n'a jamais vu, et on envoie tout dans le bitstream (pas rule#1 car pas nombre)

Quand on trouve une séquence qu'on connait, on fout a la place une back-reference:
on rentre la taille de la séquence connue (RULE#1 !!) (jsp sur cb de bytes/bits) puis
la distance (RULE#1 !!) a laquelle on a vu la séquence

La taille est entre 1-258 et la distance 1-32768 en arrière
Prefix codes:
Je crois qu'on assigne a chaque back reference un "prefix code", un code unique qui représente
une back ref. Pour determiner le code on utilise un code tree (??? voir huffman (sauf que dans la vidéo il dit
c'est pas huffman mais nsm))

Ce que fait deflate pour réduire le nombre de codes utilisé c'est que chaque charactères a un code,
et chaque LENGTH d'une back ref en a un aussi, donc si on croise un code pour une back ref, on
sait que derriere on a la distance, et boum pas besoin d'avoir un code unique pour chaque
combinaison length/distance


A partir de la je commence a plus suivre
LL CODES TABLE
https://youtu.be/SJPvNi4HrWQ?t=4077



https://youtu.be/SJPvNi4HrWQ?t=4652
*/

struct s_ll_code
{
	U8 bit_n;
	U16 code;
} const ll_codes[] = {
	{8, 48},
	{8, 49},
	{8, 50},
	{8, 51},
	{8, 52},
	{8, 53},
	{8, 54},
	{8, 55},
	{8, 56},
	{8, 57},
	{8, 58},
	{8, 59},
	{8, 60},
	{8, 61},
	{8, 62},
	{8, 63},
	{8, 64},
	{8, 65},
	{8, 66},
	{8, 67},
	{8, 68},
	{8, 69},
	{8, 70},
	{8, 71},
	{8, 72},
	{8, 73},
	{8, 74},
	{8, 75},
	{8, 76},
	{8, 77},
	{8, 78},
	{8, 79},
	{8, 80},
	{8, 81},
	{8, 82},
	{8, 83},
	{8, 84},
	{8, 85},
	{8, 86},
	{8, 87},
	{8, 88},
	{8, 89},
	{8, 90},
	{8, 91},
	{8, 92},
	{8, 93},
	{8, 94},
	{8, 95},
	{8, 96},
	{8, 97},
	{8, 98},
	{8, 99},
	{8, 100},
	{8, 101},
	{8, 102},
	{8, 103},
	{8, 104},
	{8, 105},
	{8, 106},
	{8, 107},
	{8, 108},
	{8, 109},
	{8, 110},
	{8, 111},
	{8, 112},
	{8, 113},
	{8, 114},
	{8, 115},
	{8, 116},
	{8, 117},
	{8, 118},
	{8, 119},
	{8, 120},
	{8, 121},
	{8, 122},
	{8, 123},
	{8, 124},
	{8, 125},
	{8, 126},
	{8, 127},
	{8, 128},
	{8, 129},
	{8, 130},
	{8, 131},
	{8, 132},
	{8, 133},
	{8, 134},
	{8, 135},
	{8, 136},
	{8, 137},
	{8, 138},
	{8, 139},
	{8, 140},
	{8, 141},
	{8, 142},
	{8, 143},
	{8, 144},
	{8, 145},
	{8, 146},
	{8, 147},
	{8, 148},
	{8, 149},
	{8, 150},
	{8, 151},
	{8, 152},
	{8, 153},
	{8, 154},
	{8, 155},
	{8, 156},
	{8, 157},
	{8, 158},
	{8, 159},
	{8, 160},
	{8, 161},
	{8, 162},
	{8, 163},
	{8, 164},
	{8, 165},
	{8, 166},
	{8, 167},
	{8, 168},
	{8, 169},
	{8, 170},
	{8, 171},
	{8, 172},
	{8, 173},
	{8, 174},
	{8, 175},
	{8, 176},
	{8, 177},
	{8, 178},
	{8, 179},
	{8, 180},
	{8, 181},
	{8, 182},
	{8, 183},
	{8, 184},
	{8, 185},
	{8, 186},
	{8, 187},
	{8, 188},
	{8, 189},
	{8, 190},
	{8, 191},
	{9, 400},
	{9, 401},
	{9, 402},
	{9, 403},
	{9, 404},
	{9, 405},
	{9, 406},
	{9, 407},
	{9, 408},
	{9, 409},
	{9, 410},
	{9, 411},
	{9, 412},
	{9, 413},
	{9, 414},
	{9, 415},
	{9, 416},
	{9, 417},
	{9, 418},
	{9, 419},
	{9, 420},
	{9, 421},
	{9, 422},
	{9, 423},
	{9, 424},
	{9, 425},
	{9, 426},
	{9, 427},
	{9, 428},
	{9, 429},
	{9, 430},
	{9, 431},
	{9, 432},
	{9, 433},
	{9, 434},
	{9, 435},
	{9, 436},
	{9, 437},
	{9, 438},
	{9, 439},
	{9, 440},
	{9, 441},
	{9, 442},
	{9, 443},
	{9, 444},
	{9, 445},
	{9, 446},
	{9, 447},
	{9, 448},
	{9, 449},
	{9, 450},
	{9, 451},
	{9, 452},
	{9, 453},
	{9, 454},
	{9, 455},
	{9, 456},
	{9, 457},
	{9, 458},
	{9, 459},
	{9, 460},
	{9, 461},
	{9, 462},
	{9, 463},
	{9, 464},
	{9, 465},
	{9, 466},
	{9, 467},
	{9, 468},
	{9, 469},
	{9, 470},
	{9, 471},
	{9, 472},
	{9, 473},
	{9, 474},
	{9, 475},
	{9, 476},
	{9, 477},
	{9, 478},
	{9, 479},
	{9, 480},
	{9, 481},
	{9, 482},
	{9, 483},
	{9, 484},
	{9, 485},
	{9, 486},
	{9, 487},
	{9, 488},
	{9, 489},
	{9, 490},
	{9, 491},
	{9, 492},
	{9, 493},
	{9, 494},
	{9, 495},
	{9, 496},
	{9, 497},
	{9, 498},
	{9, 499},
	{9, 500},
	{9, 501},
	{9, 502},
	{9, 503},
	{9, 504},
	{9, 505},
	{9, 506},
	{9, 507},
	{9, 508},
	{9, 509},
	{9, 510},
	{9, 511},
	{7, 0},
	{7, 1},
	{7, 2},
	{7, 3},
	{7, 4},
	{7, 5},
	{7, 6},
	{7, 7},
	{7, 8},
	{7, 9},
	{7, 10},
	{7, 11},
	{7, 12},
	{7, 13},
	{7, 14},
	{7, 15},
	{7, 16},
	{7, 17},
	{7, 18},
	{7, 19},
	{7, 20},
	{7, 21},
	{7, 22},
	{7, 23},
	{8, 192},
	{8, 193},
	{8, 194},
	{8, 195},
	{8, 196},
	{8, 197},
	{8, 198},
	{8, 199}};

// ll_code: index + 257
struct s_ll_table_entry
{
	U16 min;
	U16 max;
	U8 extra_bits;
} const ll_table[] = {
	{3, 3, 0}, {4, 4, 0}, {5, 5, 0}, {6, 6, 0}, {7, 7, 0}, {8, 8, 0}, {9, 9, 0}, {10, 10, 0}, {11, 12, 1}, {13, 14, 1}, {15, 16, 1}, {17, 18, 1}, {19, 22, 2}, {23, 26, 2}, {27, 30, 2}, {31, 34, 2}, {35, 42, 3}, {43, 50, 3}, {51, 58, 3}, {59, 66, 3}, {67, 82, 4}, {83, 98, 4}, {99, 114, 4}, {115, 130, 4}, {131, 162, 5}, {163, 194, 5}, {195, 226, 5}, {227, 257, 5}, {258, 258, 0}};
const U8 ll_table_size = sizeof(ll_table) / sizeof(ll_table[0]);

struct s_offset_table_entry
{
	U16 min;
	U16 max;
	U8 extra_bits;
} const offset_table[] = {
	{1, 1, 0}, {2, 2, 0}, {3, 3, 0}, {4, 4, 0}, {5, 6, 1}, {7, 8, 1}, {9, 12, 2}, {13, 16, 2}, {17, 24, 3}, {25, 32, 3}, {33, 48, 4}, {49, 64, 4}, {65, 96, 5}, {97, 128, 5}, {129, 192, 6}, {193, 256, 6}, {257, 384, 7}, {385, 512, 7}, {513, 768, 8}, {769, 1024, 8}, {1025, 1536, 9}, {1537, 2048, 9}, {2049, 3072, 10}, {3073, 4096, 10}, {4097, 6144, 11}, {6145, 8192, 11}, {8193, 12288, 12}, {12289, 16384, 12}, {16385, 24576, 13}, {24577, 32768, 13}};
const U8 offset_table_size = sizeof(offset_table) / sizeof(offset_table[0]);

#define BLOCK_UNCOMPRESSED 0
#define BLOCK_TYPE_1 1
#define BLOCK_TYPE_2 2

#define LOOKAHEAD_SIZE 1024
#define WINDOW_SIZE 32768

void ft_inflate(U8 *data, U64 size, U64 *output, U64 output_len)
{
	U64 n = 0;
	t_bitstream stream = FT_BITSTREAM_INIT(data, size);

read_block:;
	U8 last_block = ft_bstrm_read_bit(&stream);
	U64 block_type = ft_bstrm_read_bits(&stream, 2);

	switch (block_type)
	{
	case BLOCK_UNCOMPRESSED:
		ft_bstrm_read_align_byte(&stream);

		U16 len = ft_bstrm_read_u16_little_endian(&stream);
		U16 nlen = ft_bstrm_read_u16_little_endian(&stream);
		if (len != ((~nlen) & 0xffff))
			return; // ERROR

		for (U16 i = 0; i < len; i++)
			output[n++] = ft_bstrm_read_byte(&stream);
		break;
	case BLOCK_TYPE_1:

		break;
	case BLOCK_TYPE_2:
		break;
	}

	if (!last_block)
		goto read_block;
}

static void write_code(struct s_ll_code code, t_bitstream *stream)
{
	for (U8 j = 0; j < code.bit_n; j++)
		ft_bstrm_write_bit(stream, code.code >> (code.bit_n - 1 - j));
}

typedef struct s_deflate_stream
{
	U8 *in;
	U64 available_in;
	U64 total_compressed_in;

	U8 *out;
	U64 available_out;
	U64 total_out;
} t_deflate_stream;

typedef struct s_deflate_bitstream
{
	U8 *buffer;
	U64 buffer_max_len;

	U8 bit_offset;
	U64 byte_offset;
}	t_deflate_bitstream;

static void block_type_1(U8 *data, U64 data_len, t_bitstream *out_stream)
{
	if (data_len == 0)
		return;

	U64 window = 0;

	U64 n = 0;
	while (n < data_len)
	{
		U64 offset = 0;
		U64 size = 0;
		U64 wn = 1;

		while (wn < window + 1)
		{
			U64 i = 0;
			U8 *curr = data - wn;

			while (i < LOOKAHEAD_SIZE &&
				   i + n < data_len &&
				   *(curr + i) == data[i])
				i++;

			if (i > size)
			{
				offset = wn;
				size = i;
			}
			wn++;
		}

		U64 incr = 1;
		if (offset > 0 && size >= 3)
		{
			incr = size;

			for (U8 i = 0; i < ll_table_size; i++)
			{
				struct s_ll_table_entry ent = ll_table[i];

				if (ent.min <= size && ent.max >= size)
				{
					write_code(ll_codes[i + 257], out_stream);

					U16 length_extra = size - ent.min;
					for (U8 j = 0; j < ent.extra_bits; j++)
						ft_bstrm_write_bit(out_stream, length_extra >> j);
					break;
				}
			}

			for (U8 i = 0; i < offset_table_size; i++)
			{
				if (offset_table[i].min <= offset && offset_table[i].max >= offset)
				{
					for (U8 j = 0; j < 5; j++)
						ft_bstrm_write_bit(out_stream, i >> (4 - j));
					U16 offset_extra = offset - offset_table[i].min;
					for (U8 j = 0; j < offset_table[i].extra_bits; j++)
						ft_bstrm_write_bit(out_stream, offset_extra >> j);
					break;
				}
			}
		}
		else
			write_code(ll_codes[*data], out_stream);

		if (window < WINDOW_SIZE)
			window = MIN(WINDOW_SIZE, incr + window);
		data += incr;
		n += incr;
	}

	write_code(ll_codes[256], out_stream);
}

static U64 block_type_0(U8 *data, U64 data_len, t_bitstream *out_stream)
{
	if (out_stream->bit_offset != 0)
	{
		out_stream->bit_offset = 0;
		out_stream->byte_offset++;
	} //Skip current byte

	U16 size = data_len;
	*(U16*)(out_stream->buffer + out_stream->byte_offset) = size;
	*(U16*)(out_stream->buffer + out_stream->byte_offset + 2) = ~size;

	//ft_bstrm_write_u16_little_endian(out_stream, size);
	//ft_bstrm_write_u16_little_endian(out_stream, ~((U16)size));

	ft_bstrm_write_bytes(out_stream, size, data);
}

static void create_block(t_bitstream *stream, bool is_last, S32 block_type, U8 *data, U64 data_size)
{
	ft_bstrm_write_bit(stream, is_last);
	ft_bstrm_write_bit(stream, block_type & 1);
	ft_bstrm_write_bit(stream, block_type & 2);
	if (ft_errno == FT_ERANGE)
		return;

	switch (block_type)
	{
	case BLOCK_UNCOMPRESSED:;
		block_type_0(data, data_size, stream);
		break;
	case BLOCK_TYPE_1:
		block_type_1(data, data_size, stream);
		break;
	}
}

bool ft_deflate(t_deflate_stream *data_stream, U64 block_max_size)
{
	t_bitstream out_stream = FT_BITSTREAM_INIT(data_stream->out, data_stream->available_out);

	U64 n = 0;

	data_stream->total_compressed_in = 0;
	data_stream->total_out = 0;

	while (data_stream->available_in > 0)
	{
		bool is_last = block_max_size >= data_stream->available_in;
		//bool is_last = 1;

		create_block(&out_stream, is_last, BLOCK_TYPE_1, data_stream->in, MIN(block_max_size, data_stream->available_in));

		while (is_last && stream.bit_offset != 0)
			ft_bstrm_write_bit(&stream, 0);

		U64 to_write = stream.byte_offset;
		while (to_write)
			to_write -= ft_fwrite(fd, (char*)buffer, to_write);
		ft_bstrm_reset_counter(&stream);

		n += to_compress;
	}
}
