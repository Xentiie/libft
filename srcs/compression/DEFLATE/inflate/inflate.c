/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inflate.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 11:07:21 by reclaire          #+#    #+#             */
/*   Updated: 2024/06/24 22:34:21 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_INFLATE_FIXED_CODES_GENERATOR

#include "inflate_int.h"

// clang-format off
enum e_inf_state {
	BLK_HEAD,
		RD_UNCOMPRESS,
			UNCOMPRESS_CPY,

		RD_CODE,

		LIT,

		RD_EXTRA_LEN,
		RD_DIST,
		RD_EXTRA_DIST,

		CPY_BACKREF
};

extern const struct {
	U16 code;
	U16 index;
	U8 nbits;
} fixed_ll_codes[];

/*
const struct s_code fixed_ll_codes[] = {
	// 8 bits (0 - 143)
	{ 12, 8}, {140, 8}, { 76, 8}, {204, 8}, { 44, 8}, {172, 8}, {108, 8}, {236, 8}, { 28, 8}, {156, 8}, 
	{ 92, 8}, {220, 8}, { 60, 8}, {188, 8}, {124, 8}, {252, 8}, {  2, 8}, {130, 8}, { 66, 8}, {194, 8}, 
	{ 34, 8}, {162, 8}, { 98, 8}, {226, 8}, { 18, 8}, {146, 8}, { 82, 8}, {210, 8}, { 50, 8}, {178, 8}, 
	{114, 8}, {242, 8}, { 10, 8}, {138, 8}, { 74, 8}, {202, 8}, { 42, 8}, {170, 8}, {106, 8}, {234, 8}, 
	{ 26, 8}, {154, 8}, { 90, 8}, {218, 8}, { 58, 8}, {186, 8}, {122, 8}, {250, 8}, {  6, 8}, {134, 8}, 
	{ 70, 8}, {198, 8}, { 38, 8}, {166, 8}, {102, 8}, {230, 8}, { 22, 8}, {150, 8}, { 86, 8}, {214, 8}, 
	{ 54, 8}, {182, 8}, {118, 8}, {246, 8}, { 14, 8}, {142, 8}, { 78, 8}, {206, 8}, { 46, 8}, {174, 8}, 
	{110, 8}, {238, 8}, { 30, 8}, {158, 8}, { 94, 8}, {222, 8}, { 62, 8}, {190, 8}, {126, 8}, {254, 8}, 
	{  1, 8}, {129, 8}, { 65, 8}, {193, 8}, { 33, 8}, {161, 8}, { 97, 8}, {225, 8}, { 17, 8}, {145, 8}, 
	{ 81, 8}, {209, 8}, { 49, 8}, {177, 8}, {113, 8}, {241, 8}, {  9, 8}, {137, 8}, { 73, 8}, {201, 8}, 
	{ 41, 8}, {169, 8}, {105, 8}, {233, 8}, { 25, 8}, {153, 8}, { 89, 8}, {217, 8}, { 57, 8}, {185, 8}, 
	{121, 8}, {249, 8}, {  5, 8}, {133, 8}, { 69, 8}, {197, 8}, { 37, 8}, {165, 8}, {101, 8}, {229, 8}, 
	{ 21, 8}, {149, 8}, { 85, 8}, {213, 8}, { 53, 8}, {181, 8}, {117, 8}, {245, 8}, { 13, 8}, {141, 8}, 
	{ 77, 8}, {205, 8}, { 45, 8}, {173, 8}, {109, 8}, {237, 8}, { 29, 8}, {157, 8}, { 93, 8}, {221, 8}, 
	{ 61, 8}, {189, 8}, {125, 8}, {253, 8},
	
	// 9 bits (144 - 255)
	{ 19, 9}, {275, 9}, {147, 9}, {403, 9}, { 83, 9}, {339, 9}, {211, 9}, {467, 9}, { 51, 9}, {307, 9}, 
	{179, 9}, {435, 9}, {115, 9}, {371, 9}, {243, 9}, {499, 9}, { 11, 9}, {267, 9}, {139, 9}, {395, 9}, 
	{ 75, 9}, {331, 9}, {203, 9}, {459, 9}, { 43, 9}, {299, 9}, {171, 9}, {427, 9}, {107, 9}, {363, 9}, 
	{235, 9}, {491, 9}, { 27, 9}, {283, 9}, {155, 9}, {411, 9}, { 91, 9}, {347, 9}, {219, 9}, {475, 9}, 
	{ 59, 9}, {315, 9}, {187, 9}, {443, 9}, {123, 9}, {379, 9}, {251, 9}, {507, 9}, {  7, 9}, {263, 9}, 
	{135, 9}, {391, 9}, { 71, 9}, {327, 9}, {199, 9}, {455, 9}, { 39, 9}, {295, 9}, {167, 9}, {423, 9}, 
	{103, 9}, {359, 9}, {231, 9}, {487, 9}, { 23, 9}, {279, 9}, {151, 9}, {407, 9}, { 87, 9}, {343, 9}, 
	{215, 9}, {471, 9}, { 55, 9}, {311, 9}, {183, 9}, {439, 9}, {119, 9}, {375, 9}, {247, 9}, {503, 9}, 
	{ 15, 9}, {271, 9}, {143, 9}, {399, 9}, { 79, 9}, {335, 9}, {207, 9}, {463, 9}, { 47, 9}, {303, 9}, 
	{175, 9}, {431, 9}, {111, 9}, {367, 9}, {239, 9}, {495, 9}, { 31, 9}, {287, 9}, {159, 9}, {415, 9}, 
	{ 95, 9}, {351, 9}, {223, 9}, {479, 9}, { 63, 9}, {319, 9}, {191, 9}, {447, 9}, {127, 9}, {383, 9}, 
	{255, 9}, {511, 9}, 

	// 7 bits (256 - 279)
	{  0, 7}, { 64, 7}, { 32, 7}, { 96, 7}, { 16, 7}, { 80, 7}, { 48, 7}, {112, 7}, {  8, 7}, { 72, 7}, 
	{ 40, 7}, {104, 7}, { 24, 7}, { 88, 7}, { 56, 7}, {120, 7}, {  4, 7}, { 68, 7}, { 36, 7}, {100, 7}, 
	{ 20, 7}, { 84, 7}, { 52, 7}, {116, 7}, 

	// 8 bits (280 - 287)
	{  3, 8}, {131, 8}, { 67, 8}, {195, 8}, { 35, 8}, {163, 8}, { 99, 8}, {227, 8},

	// + 2 codes fantomes (288, 289)
};
#define fixed_ll_codes_len (sizeof(fixed_ll_codes)/sizeof(fixed_ll_codes[0]))
*/

/*
const struct s_table_entry ll_table[] = {
	{3, 3, 0x0, 0}, {4, 4, 0x0, 0}, {5, 5, 0x0, 0}, {6, 6, 0x0, 0},
	{7, 7, 0x0, 0}, {8, 8, 0x0, 0}, {9, 9, 0x0, 0}, {10, 10, 0x0, 0},
	
	{11, 12, 0x1, 1}, {13, 14, 0x1, 1}, {15, 16, 0x1, 1}, {17, 18, 0x1, 1},
	{19, 22, 0x3, 2}, {23, 26, 0x3, 2}, {27, 30, 0x3, 2}, {31, 34, 0x3, 2},
	{35, 42, 0x7, 3}, {43, 50, 0x7, 3}, {51, 58, 0x7, 3}, {59, 66, 0x7, 3},
	{67, 82, 0xF, 4}, {83, 98, 0xF, 4}, {99, 114, 0xF, 4}, {115, 130, 0xF, 4},
	{131, 162, 0x1F, 5}, {163, 194, 0x1F, 5}, {195, 226, 0x1F, 5}, {227, 257, 0x1F, 5},
	{258, 258, 0x0, 0}
};
#define ll_table_size sizeof(ll_table) / sizeof(ll_table[0]);
*/

const struct s_table_entry dist_table[] = {
	{1, 1, 0x0, 0}, {2, 2, 0x0, 0}, {3, 3, 0x0, 0}, {4, 4, 0x0, 0},
	{5, 6, 0x1, 1}, {7, 8, 0x1, 1},
	{9, 12, 0x3, 2}, {13, 16, 0x3, 2},
	{17, 24, 0x7, 3}, {25, 32, 0x7, 3},
	{33, 48, 0xF, 4}, {49, 64, 0xF, 4},
	{65, 96, 0x1F, 5}, {97, 128, 0x1F, 5},
	{129, 192, 0x3F, 6}, {193, 256, 0x3F, 6},
	{257, 384, 0x7F, 7}, {385, 512, 0x7F, 7},
	{513, 768, 0xFF, 8}, {769, 1024, 0xFF, 8},
	{1025, 1536, 0x1FF, 9}, {1537, 2048, 0x1FF, 9},
	{2049, 3072, 0x3FF, 10}, {3073, 4096, 0x3FF, 10},
	{4097, 6144, 0x7FF, 11}, {6145, 8192, 0x7FF, 11},
	{8193, 12288, 0xFFF, 12}, {12289, 16384, 0xFFF, 12},
	{16385, 24576, 0x1FFF, 13}, {24577, 32768, 0x1FFF, 13}
};
#define dist_table_size sizeof(dist_table) / sizeof(dist_table[0]);

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
// clang-format on

/* Load registers with state in inflate() for speed */
#define LOAD()                                             \
	do                                                     \
	{                                                      \
		if (UNLIKELY(stream->in_used > stream->in_size))   \
			return FT_INFLATE_RET_INVALID_IN_SIZE;         \
		if (UNLIKELY(stream->out_used > stream->out_used)) \
			return FT_INFLATE_RET_INVALID_OUT_SIZE;        \
		have = stream->in_size - stream->in_used;          \
		left = stream->out_size - stream->out_used;        \
		next = stream->in + stream->in_used;               \
		hold = inf_data->hold;                             \
		bits = stream->bits;                               \
	} while (0)

/* Restore stream from registers in inflate() */
#define RESTORE()                                                         \
	do                                                                    \
	{                                                                     \
		stream->in_used += (stream->in_size - stream->in_used) - have;    \
		stream->out_used += (stream->out_size - stream->out_used) - left; \
		inf_data->hold = hold;                                            \
		stream->bits = bits;                                              \
	} while (0)

/* Clear the input bit accumulator */
#define INITBITS() \
	do             \
	{              \
		hold = 0;  \
		bits = 0;  \
	} while (0)

/* Get a byte of input into the bit accumulator, or return from inflate()
   if there is no input available. */
#define PULLBYTE()                                \
	do                                            \
	{                                             \
		if (have == 0)                            \
			goto inflate_leave;                   \
		have--;                                   \
		hold += (unsigned long)(*next++) << bits; \
		bits += 8;                                \
	} while (0)

/* Assure that there are at least n bits in the bit accumulator.  If there is
   not enough available input to do that, then return from inflate(). */
#define NEEDBITS(n)                  \
	do                               \
	{                                \
		while (bits < (unsigned)(n)) \
			PULLBYTE();              \
	} while (0)

/* Return the low n bits of the bit accumulator (n < 16) */
#define BITS(n) \
	((unsigned)hold & ((1U << (n)) - 1))

/* Remove n bits from the bit accumulator */
#define DROPBITS(n)            \
	do                         \
	{                          \
		hold >>= (n);          \
		bits -= (unsigned)(n); \
	} while (0)

/* Remove zero to seven bits as needed to go to a byte boundary */
#define BYTEBITS()         \
	do                     \
	{                      \
		hold >>= bits & 7; \
		bits -= bits & 7;  \
	} while (0)

S32 ft_inflate2(t_deflate_stream2 *stream)
{
#define blk_12 inf_data->blk_data.type12
#define GET_LENGTH() ll_table[inf_data->blk_data.type12.length_code_i - 257].min
#define GET_DIST() dist_table[inf_data->blk_data.type12.dist_code].min

	U64 hold;		// bit accumulator
	U64 have, left; // remaining in, remaining out
	U8 bits;		// bit counter
	U8 *next;
	U64 i; // counter
	struct s_inflate_data *inf_data = &stream->inflate;

	LOAD();

	if (inf_data->window == NULL)
	{
		inf_data->window = malloc(sizeof(U8) * FT_DEFLATE_WINDOW_SIZE);
		if (UNLIKELY(inf_data->window == NULL))
			return FT_INFLATE_RET_OMEM;
		inf_data->window_size = 0;
		inf_data->win_next = inf_data->window;
	}

	while (TRUE)
	{
		switch (inf_data->state)
		{
		case BLK_HEAD:
			IFDEBUG(printf("Reading block:\n"))
			NEEDBITS(3);

			inf_data->last = BITS(1);
			IFDEBUG(printf("	last: %s\n", inf_data->last ? "yes" : "no"))

			DROPBITS(1);
			switch (BITS(2))
			{
			case 0:
				IFDEBUG(printf("	block type: uncompressed\n"))
				inf_data->state = RD_UNCOMPRESS;
				break;

			case 1:
				IFDEBUG(printf("	block type: fixed\n"))
				blk_12.ll_codes = fixed_ll_codes;
				inf_data->state = RD_CODE;
				break;

			case 2:
				IFDEBUG(printf("	block type: dynamic\n"))
				inf_data->state = 0; // TODO
				break;

			case 3:
				IFDEBUG(printf("	block type: INVALID\n"))
				// TODO
				DROPBITS(2);
				goto inflate_leave;
			}
			DROPBITS(2);
			break;

		case RD_UNCOMPRESS:
			BYTEBITS();
			NEEDBITS(32);

			if ((hold & 0xFFFF) != ((hold >> 16) ^ 0xFFFF))
			{
				// TODO
				IFDEBUG(printf("	invalid size/~size\n"))
				goto inflate_leave;
			}
			inf_data->blk_data.type0.length = hold & 0xFFFF;
			IFDEBUG(printf("	size: %u\n", inf_data->blk_data.type0.length))
			inf_data->state = UNCOMPRESS_CPY;
			/* fallthrough */

		case UNCOMPRESS_CPY:;
			U16 to_cpy = inf_data->blk_data.type0.length;
			if (to_cpy)
			{
				if (to_cpy > have)
					to_cpy = have;
				if (to_cpy > left)
					to_cpy = left;
				if (to_cpy == 0)
					goto inflate_leave;
				IFDEBUG(printf("	copying %u bytes\n", to_cpy))
				ft_memcpy(stream->out + stream->out_used, next, to_cpy);

				have -= to_cpy;
				left -= to_cpy;
				inf_data->blk_data.type0.length -= to_cpy;

				next += to_cpy;
				stream->out_used += to_cpy;
				break;
			}
			inf_data->state = BLK_HEAD;
			break;

		case RD_CODE:
			// Boucle a travers tout les codes
			blk_12.length_code_i = 0;

			NEEDBITS(7);
			while (TRUE)
			{
				if (fixed_ll_codes[BITS(9)].nbits <= bits)
					break;
				PULLBYTE();
			}

			if (blk_12.length_code_i < 256)
			{
				inf_data->state = LIT;
				break;
			}
			else if (blk_12.length_code_i == 256)
			{
				IFDEBUG(printf("	End of block marker found\n"))
				inf_data->state = BLK_HEAD;
				break;
			}
			else
			{
				IFDEBUG(printf("	backref:\n		base length: %u\n", GET_LENGTH()))
				inf_data->state = RD_EXTRA_LEN;
			}
			/* fallthrough */
		case RD_EXTRA_LEN:
			NEEDBITS(ll_table[blk_12.length_code_i - 257].extra_bits);
			blk_12.extra_length = BITS(ll_table[blk_12.length_code_i - 257].extra_bits);
			IFDEBUG(printf("		extra length: %u\n", blk_12.extra_length))
			DROPBITS(ll_table[blk_12.length_code_i - 257].extra_bits);
			inf_data->state = RD_DIST;
			/* fallthrough */

		case RD_DIST:
			NEEDBITS(5);
			printf("		raw dist code: %u\n", BITS(5));
			blk_12.dist_code = reverse_5_bits(BITS(5));
			IFDEBUG(printf("		dist code: %u\n", blk_12.dist_code))
			IFDEBUG(printf("		dist: %u\n", GET_DIST()))
			DROPBITS(5);
			inf_data->state = RD_EXTRA_DIST;
			/* fallthrough */

		case RD_EXTRA_DIST:
			NEEDBITS(dist_table[blk_12.dist_code].extra_bits);
			blk_12.extra_dist = BITS(dist_table[blk_12.dist_code].extra_bits);
			IFDEBUG(printf("		extra dist: %u\n", blk_12.extra_dist))
			IFDEBUG(printf("		total: %u/%u\n", GET_LENGTH() + blk_12.extra_length, GET_DIST() + blk_12.extra_dist))
			DROPBITS(dist_table[blk_12.dist_code].extra_bits);
			inf_data->state = CPY_BACKREF;
			/* fallthrough */

		case CPY_BACKREF:
			return FT_INFLATE_RET_DONE;
			

		case LIT:
			if (have == 0)
				goto inflate_leave;

			if (inf_data->win_next - inf_data->window >= FT_DEFLATE_WINDOW_SIZE)
				inf_data->win_next = inf_data->window;

			*inf_data->win_next++ = (U8)blk_12.length_code_i;
			inf_data->window_size++;
			*next++ = (U8)blk_12.length_code_i;

			IFDEBUG(
				if (ft_isprint(blk_12.length_code_i))
					printf("	lit: %#x : %c\n", blk_12.length_code_i, blk_12.length_code_i);
				else printf("	lit: %#x\n", blk_12.length_code_i);)
			inf_data->state = RD_CODE;
			break;

		default:
			goto inflate_leave;
		}

		if (inf_data->state == BLK_HEAD && inf_data->last)
		{
			RESTORE();
			return FT_INFLATE_RET_DONE;
		}
	}

inflate_leave:
	RESTORE();
	return FT_INFLATE_RET_NOT_DONE;
}

void ft_inflate_init(t_deflate_stream2 *stream)
{
	ft_memset(stream, 0, sizeof(t_deflate_stream2));
}




#else /* #ifndef FT_INFLATE_FIXED_CODES_GENERATOR */

#include "libft/io.h"

const U16 fixed_codes[] = {
	// 8 bits (0 - 143)
	12, 140, 76, 204, 44, 172, 108, 236, 28, 156, 
	92, 220, 60, 188, 124, 252, 2, 130, 66, 194, 
	34, 162, 98, 226, 18, 146, 82, 210, 50, 178, 
	114, 242, 10, 138, 74, 202, 42, 170, 106, 234, 
	26, 154, 90, 218, 58, 186, 122, 250, 6, 134, 
	70, 198, 38, 166, 102, 230, 22, 150, 86, 214, 
	54, 182, 118, 246, 14, 142, 78, 206, 46, 174, 
	110, 238, 30, 158, 94, 222, 62, 190, 126, 254, 
	1, 129, 65, 193, 33, 161, 97, 225, 17, 145, 
	81, 209, 49, 177, 113, 241, 9, 137, 73, 201, 
	41, 169, 105, 233, 25, 153, 89, 217, 57, 185, 
	121, 249, 5, 133, 69, 197, 37, 165, 101, 229, 
	21, 149, 85, 213, 53, 181, 117, 245, 13, 141, 
	77, 205, 45, 173, 109, 237, 29, 157, 93, 221, 
	61, 189, 125, 253,
	
	// 9 bits (144 - 255)
	19, 275, 147, 403, 83, 339, 211, 467, 51, 307, 
	179, 435, 115, 371, 243, 499, 11, 267, 139, 395, 
	75, 331, 203, 459, 43, 299, 171, 427, 107, 363, 
	235, 491, 27, 283, 155, 411, 91, 347, 219, 475, 
	59, 315, 187, 443, 123, 379, 251, 507, 7, 263, 
	135, 391, 71, 327, 199, 455, 39, 295, 167, 423, 
	103, 359, 231, 487, 23, 279, 151, 407, 87, 343, 
	215, 471, 55, 311, 183, 439, 119, 375, 247, 503, 
	15, 271, 143, 399, 79, 335, 207, 463, 47, 303, 
	175, 431, 111, 367, 239, 495, 31, 287, 159, 415, 
	95, 351, 223, 479, 63, 319, 191, 447, 127, 383, 
	255, 511, 

	// 7 bits (256 - 279)
	0, 64, 32, 96, 16, 80, 48, 112, 8, 72, 
	40, 104, 24, 88, 56, 120, 4, 68, 36, 100, 
	20, 84, 52, 116, 

	// 8 bits (280 - 287)
	3, 131, 67, 195, 35, 163, 99, 227,

	// + 2 codes fantomes (288, 289)
};

int main()
{
	struct s_code codes[512] = {0};

	file fd = ft_fopen("./fixed_codes.c", "w+");

	ft_dprintf(fd, "#include \"libft/std.h\"\n\n");

	ft_dprintf(fd, "/*\nList of fixed codes. Generated with:");

	ft_dprintf(fd, "struct s_code {\n\tU16 code;\n\tU8 nbits;\n\tU16 index;\n};\n\n");
	ft_dprintf(fd, "const struct s_code fixed_ll_codes[] = {\n\t");

	for (int i = 0; i < 144; i++)
	{
		ft_dprintf(fd, "{%u, 8, %d}, ", fixed_codes[i], i);
		ft_dprintf(fd, "{%u, 8, %d}, ", fixed_codes[i] | 0x100, i);

		if (codes[fixed_codes[i]].nbits != 0 || codes[fixed_codes[i] | 0x100].nbits != 0)
		{
			printf("ERROR\n");
			exit(1);
		}

		codes[fixed_codes[i]] = (struct s_code){.code = fixed_codes[i], .nbits = 8};
		codes[fixed_codes[i] | 0x100] = (struct s_code){.code = fixed_codes[i], .nbits = 8};

		if ((i + 1) % 5 == 0)
			ft_dprintf(fd, "\n\t");
	}
	ft_dprintf(fd, "\n};\n");

	ft_fclose(fd);
}

#endif
