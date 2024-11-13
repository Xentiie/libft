/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fixed_codes_generator.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 15:13:49 by reclaire          #+#    #+#             */
/*   Updated: 2024/11/10 22:52:39 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// make -C ../.. && gcc -g -I../ -I../../ -L../../ -DFT_DEFLATE_CODES_GENERATOR ./fixed_codes_generator.c -lft -lz -lm
#if defined(FT_DEFLATE_CODES_GENERATOR)

#include "libft/io.h"
#include <stdlib.h>

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

// 
const U16 fixed_ll_codes[] = {
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

const struct
{
	U16 min;
	U16 max;
	U16 mask;
	U8 extra_bits;
} gen_ll_table[] = {
	{3, 3, 0x0, 0}, {4, 4, 0x0, 0}, {5, 5, 0x0, 0}, {6, 6, 0x0, 0}, {7, 7, 0x0, 0}, {8, 8, 0x0, 0}, {9, 9, 0x0, 0}, {10, 10, 0x0, 0},

	{11, 12, 0x1, 1}, {13, 14, 0x1, 1}, {15, 16, 0x1, 1}, {17, 18, 0x1, 1}, {19, 22, 0x3, 2},
	{23, 26, 0x3, 2}, {27, 30, 0x3, 2}, {31, 34, 0x3, 2}, {35, 42, 0x7, 3}, {43, 50, 0x7, 3},
	{51, 58, 0x7, 3}, {59, 66, 0x7, 3}, {67, 82, 0xF, 4}, {83, 98, 0xF, 4}, {99, 114, 0xF, 4},
	{115, 130, 0xF, 4}, {131, 162, 0x1F, 5}, {163, 194, 0x1F, 5}, {195, 226, 0x1F, 5}, {227, 257, 0x1F, 5},
	{258, 258, 0x0, 0}};

const struct
{
	U16 min;
	U16 max;
	U16 mask;
	U8 extra_bits;
} gen_offset_table[] = {
	{1, 1, 0x0, 0}, {2, 2, 0x0, 0}, {3, 3, 0x0, 0}, {4, 4, 0x0, 0}, {5, 6, 0x1, 1}, {7, 8, 0x1, 1}, {9, 12, 0x3, 2},
	{13, 16, 0x3, 2}, {17, 24, 0x7, 3}, {25, 32, 0x7, 3}, {33, 48, 0xF, 4}, {49, 64, 0xF, 4}, {65, 96, 0x1F, 5},
	{97, 128, 0x1F, 5}, {129, 192, 0x3F, 6}, {193, 256, 0x3F, 6}, {257, 384, 0x7F, 7}, {385, 512, 0x7F, 7}, {513, 768, 0xFF, 8},
	{769, 1024, 0xFF, 8}, {1025, 1536, 0x1FF, 9}, {1537, 2048, 0x1FF, 9}, {2049, 3072, 0x3FF, 10}, {3073, 4096, 0x3FF, 10},
	{4097, 6144, 0x7FF, 11}, {6145, 8192, 0x7FF, 11}, {8193, 12288, 0xFFF, 12}, {12289, 16384, 0xFFF, 12}, {16385, 24576, 0x1FFF, 13},
	{24577, 32768, 0x1FFF, 13}, {0, 0, 0, 0}, {0, 0, 0, 0}};

struct s_fixed_code
{
	U8 op;
	U8 nbits;
	U16 val;
};

int main()
{
	struct s_fixed_code ll_codes[512] = {[0 ... 511] = {0, 0, 0}};
	struct s_fixed_code dist_codes[32] = {[0 ... 31] = {0, 0, 0}};

	struct s_fixed_code e;
	int i;

	{ /* ll codes */
		i = 0;
		while (i <= 143)
		{
			if (ll_codes[fixed_ll_codes[i]].nbits != 0 ||
				ll_codes[fixed_ll_codes[i] | 0x100].nbits != 0)
			{
				ft_printf("ERROR\n");
				exit(1);
			}
			e = (struct s_fixed_code){.op = 0x80, .nbits = 8, .val = i};
			ll_codes[fixed_ll_codes[i]] = e;
			ll_codes[fixed_ll_codes[i] | 0x100] = e;
			i++;
		}

		while (i <= 255)
		{
			if (ll_codes[fixed_ll_codes[i]].nbits != 0)
			{
				ft_printf("ERROR\n");
				exit(1);
			}
			e = (struct s_fixed_code){.op = 0x80, .nbits = 9, .val = i};
			ll_codes[fixed_ll_codes[i]] = e;
			i++;
		}

		e = (struct s_fixed_code){.op = 0x20, .nbits = 7, .val = 0};
		ll_codes[0] = e;
		ll_codes[0x80] = e;
		ll_codes[0x100] = e;
		ll_codes[0x180] = e;
		i++;

		while (i <= 279)
		{
			if (ll_codes[fixed_ll_codes[i]].nbits != 0 ||
				ll_codes[fixed_ll_codes[i] | 0x80].nbits != 0 ||
				ll_codes[fixed_ll_codes[i] | 0x100].nbits != 0 ||
				ll_codes[fixed_ll_codes[i] | 0x180].nbits != 0)
			{
				ft_printf("ERROR\n");
				exit(1);
			}
			e = (struct s_fixed_code){.op = 0x40 | gen_ll_table[i - 257].extra_bits,
									  .nbits = 7,
									  .val = gen_ll_table[i - 257].min};
			ll_codes[fixed_ll_codes[i]] = e;
			ll_codes[fixed_ll_codes[i] | 0x80] = e;
			ll_codes[fixed_ll_codes[i] | 0x100] = e;
			ll_codes[fixed_ll_codes[i] | 0x180] = e;
			i++;
		}

		while (i <= 287)
		{
			if (ll_codes[fixed_ll_codes[i]].nbits != 0 ||
				ll_codes[fixed_ll_codes[i] | 0x100].nbits != 0)
			{
				ft_printf("ERROR\n");
				exit(1);
			}
			e = (struct s_fixed_code){.op = 0x40 | gen_ll_table[i - 257].extra_bits, .nbits = 8, .val = gen_ll_table[i - 257].min};
			ll_codes[fixed_ll_codes[i]] = e;
			ll_codes[fixed_ll_codes[i] | 0x100] = e;
			i++;
		}
	}

	{ /* dist codes */
		e = (struct s_fixed_code){.op = 0x80, .nbits = 5, .val = i};
		i = 0;
		for (; i < 32; i++)
		{
			U8 code = reverse_5_bits((U8)i);
			dist_codes[code] = (struct s_fixed_code){.op = 0x80 | gen_offset_table[i].extra_bits, .nbits = 5, .val = gen_offset_table[i].min};
		}
	}

	filedesc fd = ft_fopen("./DEFLATE/fixed_codes.h", "w+");

	ft_dprintf(fd, "#if !defined(FT_FIXED_CODES_H)\n");
	ft_dprintf(fd, "#define FT_FIXED_CODES_H\n");
	ft_dprintf(fd, "#include \"libft/std.h\"\n\n");

	ft_dprintf(fd, "struct s_code {\n\tU8 op;\n\tU8 nbits;\n\tU16 val;\n};\n\n");

	ft_dprintf(fd, "static const struct s_code fixed_ll_codes[] = {\n\t");
	i = 0;
	for (; i < 512; i++)
	{
		ft_dprintf(fd, "{%u, %u, %u}, ", ll_codes[i].op, ll_codes[i].nbits, ll_codes[i].val);
		if ((i + 1) % 10 == 0)
			ft_dprintf(fd, "\n\t");
	}
	ft_dprintf(fd, "\n};\n");
	
	ft_dprintf(fd, "static const struct s_code fixed_dist_codes[] = {\n\t");
	i = 0;
	for (; i < 32; i++)
	{
		ft_dprintf(fd, "{%u, %u, %u}, ", dist_codes[i].op, dist_codes[i].nbits, dist_codes[i].val);
		if ((i + 1) % 10 == 0)
			ft_dprintf(fd, "\n\t");
	}
	ft_dprintf(fd, "\n};\n");
	
	ft_dprintf(fd, "#endif\n");

	ft_fclose(fd);

	static const struct
	{
		unsigned char op;	/* operation, extra bits, table bits */
		unsigned char bits; /* bits in this part of the code */
		unsigned short val; /* offset in table or code value */
	} lenfix[512] = {
		{96, 7, 0}, {0, 8, 80}, {0, 8, 16}, {20, 8, 115}, {18, 7, 31}, {0, 8, 112}, {0, 8, 48}, {0, 9, 192}, {16, 7, 10}, {0, 8, 96}, {0, 8, 32}, {0, 9, 160}, {0, 8, 0}, {0, 8, 128}, {0, 8, 64}, {0, 9, 224}, {16, 7, 6}, {0, 8, 88}, {0, 8, 24}, {0, 9, 144}, {19, 7, 59}, {0, 8, 120}, {0, 8, 56}, {0, 9, 208}, {17, 7, 17}, {0, 8, 104}, {0, 8, 40}, {0, 9, 176}, {0, 8, 8}, {0, 8, 136}, {0, 8, 72}, {0, 9, 240}, {16, 7, 4}, {0, 8, 84}, {0, 8, 20}, {21, 8, 227}, {19, 7, 43}, {0, 8, 116}, {0, 8, 52}, {0, 9, 200}, {17, 7, 13}, {0, 8, 100}, {0, 8, 36}, {0, 9, 168}, {0, 8, 4}, {0, 8, 132}, {0, 8, 68}, {0, 9, 232}, {16, 7, 8}, {0, 8, 92}, {0, 8, 28}, {0, 9, 152}, {20, 7, 83}, {0, 8, 124}, {0, 8, 60}, {0, 9, 216}, {18, 7, 23}, {0, 8, 108}, {0, 8, 44}, {0, 9, 184}, {0, 8, 12}, {0, 8, 140}, {0, 8, 76}, {0, 9, 248}, {16, 7, 3}, {0, 8, 82}, {0, 8, 18}, {21, 8, 163}, {19, 7, 35}, {0, 8, 114}, {0, 8, 50}, {0, 9, 196}, {17, 7, 11}, {0, 8, 98}, {0, 8, 34}, {0, 9, 164}, {0, 8, 2}, {0, 8, 130}, {0, 8, 66}, {0, 9, 228}, {16, 7, 7}, {0, 8, 90}, {0, 8, 26}, {0, 9, 148}, {20, 7, 67}, {0, 8, 122}, {0, 8, 58}, {0, 9, 212}, {18, 7, 19}, {0, 8, 106}, {0, 8, 42}, {0, 9, 180}, {0, 8, 10}, {0, 8, 138}, {0, 8, 74}, {0, 9, 244}, {16, 7, 5}, {0, 8, 86}, {0, 8, 22}, {64, 8, 0}, {19, 7, 51}, {0, 8, 118}, {0, 8, 54}, {0, 9, 204}, {17, 7, 15}, {0, 8, 102}, {0, 8, 38}, {0, 9, 172}, {0, 8, 6}, {0, 8, 134}, {0, 8, 70}, {0, 9, 236}, {16, 7, 9}, {0, 8, 94}, {0, 8, 30}, {0, 9, 156}, {20, 7, 99}, {0, 8, 126}, {0, 8, 62}, {0, 9, 220}, {18, 7, 27}, {0, 8, 110}, {0, 8, 46}, {0, 9, 188}, {0, 8, 14}, {0, 8, 142}, {0, 8, 78}, {0, 9, 252}, {96, 7, 0}, {0, 8, 81}, {0, 8, 17}, {21, 8, 131}, {18, 7, 31}, {0, 8, 113}, {0, 8, 49}, {0, 9, 194}, {16, 7, 10}, {0, 8, 97}, {0, 8, 33}, {0, 9, 162}, {0, 8, 1}, {0, 8, 129}, {0, 8, 65}, {0, 9, 226}, {16, 7, 6}, {0, 8, 89}, {0, 8, 25}, {0, 9, 146}, {19, 7, 59}, {0, 8, 121}, {0, 8, 57}, {0, 9, 210}, {17, 7, 17}, {0, 8, 105}, {0, 8, 41}, {0, 9, 178}, {0, 8, 9}, {0, 8, 137}, {0, 8, 73}, {0, 9, 242}, {16, 7, 4}, {0, 8, 85}, {0, 8, 21}, {16, 8, 258}, {19, 7, 43}, {0, 8, 117}, {0, 8, 53}, {0, 9, 202}, {17, 7, 13}, {0, 8, 101}, {0, 8, 37}, {0, 9, 170}, {0, 8, 5}, {0, 8, 133}, {0, 8, 69}, {0, 9, 234}, {16, 7, 8}, {0, 8, 93}, {0, 8, 29}, {0, 9, 154}, {20, 7, 83}, {0, 8, 125}, {0, 8, 61}, {0, 9, 218}, {18, 7, 23}, {0, 8, 109}, {0, 8, 45}, {0, 9, 186}, {0, 8, 13}, {0, 8, 141}, {0, 8, 77}, {0, 9, 250}, {16, 7, 3}, {0, 8, 83}, {0, 8, 19}, {21, 8, 195}, {19, 7, 35}, {0, 8, 115}, {0, 8, 51}, {0, 9, 198}, {17, 7, 11}, {0, 8, 99}, {0, 8, 35}, {0, 9, 166}, {0, 8, 3}, {0, 8, 131}, {0, 8, 67}, {0, 9, 230}, {16, 7, 7}, {0, 8, 91}, {0, 8, 27}, {0, 9, 150}, {20, 7, 67}, {0, 8, 123}, {0, 8, 59}, {0, 9, 214}, {18, 7, 19}, {0, 8, 107}, {0, 8, 43}, {0, 9, 182}, {0, 8, 11}, {0, 8, 139}, {0, 8, 75}, {0, 9, 246}, {16, 7, 5}, {0, 8, 87}, {0, 8, 23}, {64, 8, 0}, {19, 7, 51}, {0, 8, 119}, {0, 8, 55}, {0, 9, 206}, {17, 7, 15}, {0, 8, 103}, {0, 8, 39}, {0, 9, 174}, {0, 8, 7}, {0, 8, 135}, {0, 8, 71}, {0, 9, 238}, {16, 7, 9}, {0, 8, 95}, {0, 8, 31}, {0, 9, 158}, {20, 7, 99}, {0, 8, 127}, {0, 8, 63}, {0, 9, 222}, {18, 7, 27}, {0, 8, 111}, {0, 8, 47}, {0, 9, 190}, {0, 8, 15}, {0, 8, 143}, {0, 8, 79}, {0, 9, 254}, {96, 7, 0}, {0, 8, 80}, {0, 8, 16}, {20, 8, 115}, {18, 7, 31}, {0, 8, 112}, {0, 8, 48}, {0, 9, 193}, {16, 7, 10}, {0, 8, 96}, {0, 8, 32}, {0, 9, 161}, {0, 8, 0}, {0, 8, 128}, {0, 8, 64}, {0, 9, 225}, {16, 7, 6}, {0, 8, 88}, {0, 8, 24}, {0, 9, 145}, {19, 7, 59}, {0, 8, 120}, {0, 8, 56}, {0, 9, 209}, {17, 7, 17}, {0, 8, 104}, {0, 8, 40}, {0, 9, 177}, {0, 8, 8}, {0, 8, 136}, {0, 8, 72}, {0, 9, 241}, {16, 7, 4}, {0, 8, 84}, {0, 8, 20}, {21, 8, 227}, {19, 7, 43}, {0, 8, 116}, {0, 8, 52}, {0, 9, 201}, {17, 7, 13}, {0, 8, 100}, {0, 8, 36}, {0, 9, 169}, {0, 8, 4}, {0, 8, 132}, {0, 8, 68}, {0, 9, 233}, {16, 7, 8}, {0, 8, 92}, {0, 8, 28}, {0, 9, 153}, {20, 7, 83}, {0, 8, 124}, {0, 8, 60}, {0, 9, 217}, {18, 7, 23}, {0, 8, 108}, {0, 8, 44}, {0, 9, 185}, {0, 8, 12}, {0, 8, 140}, {0, 8, 76}, {0, 9, 249}, {16, 7, 3}, {0, 8, 82}, {0, 8, 18}, {21, 8, 163}, {19, 7, 35}, {0, 8, 114}, {0, 8, 50}, {0, 9, 197}, {17, 7, 11}, {0, 8, 98}, {0, 8, 34}, {0, 9, 165}, {0, 8, 2}, {0, 8, 130}, {0, 8, 66}, {0, 9, 229}, {16, 7, 7}, {0, 8, 90}, {0, 8, 26}, {0, 9, 149}, {20, 7, 67}, {0, 8, 122}, {0, 8, 58}, {0, 9, 213}, {18, 7, 19}, {0, 8, 106}, {0, 8, 42}, {0, 9, 181}, {0, 8, 10}, {0, 8, 138}, {0, 8, 74}, {0, 9, 245}, {16, 7, 5}, {0, 8, 86}, {0, 8, 22}, {64, 8, 0}, {19, 7, 51}, {0, 8, 118}, {0, 8, 54}, {0, 9, 205}, {17, 7, 15}, {0, 8, 102}, {0, 8, 38}, {0, 9, 173}, {0, 8, 6}, {0, 8, 134}, {0, 8, 70}, {0, 9, 237}, {16, 7, 9}, {0, 8, 94}, {0, 8, 30}, {0, 9, 157}, {20, 7, 99}, {0, 8, 126}, {0, 8, 62}, {0, 9, 221}, {18, 7, 27}, {0, 8, 110}, {0, 8, 46}, {0, 9, 189}, {0, 8, 14}, {0, 8, 142}, {0, 8, 78}, {0, 9, 253}, {96, 7, 0}, {0, 8, 81}, {0, 8, 17}, {21, 8, 131}, {18, 7, 31}, {0, 8, 113}, {0, 8, 49}, {0, 9, 195}, {16, 7, 10}, {0, 8, 97}, {0, 8, 33}, {0, 9, 163}, {0, 8, 1}, {0, 8, 129}, {0, 8, 65}, {0, 9, 227}, {16, 7, 6}, {0, 8, 89}, {0, 8, 25}, {0, 9, 147}, {19, 7, 59}, {0, 8, 121}, {0, 8, 57}, {0, 9, 211}, {17, 7, 17}, {0, 8, 105}, {0, 8, 41}, {0, 9, 179}, {0, 8, 9}, {0, 8, 137}, {0, 8, 73}, {0, 9, 243}, {16, 7, 4}, {0, 8, 85}, {0, 8, 21}, {16, 8, 258}, {19, 7, 43}, {0, 8, 117}, {0, 8, 53}, {0, 9, 203}, {17, 7, 13}, {0, 8, 101}, {0, 8, 37}, {0, 9, 171}, {0, 8, 5}, {0, 8, 133}, {0, 8, 69}, {0, 9, 235}, {16, 7, 8}, {0, 8, 93}, {0, 8, 29}, {0, 9, 155}, {20, 7, 83}, {0, 8, 125}, {0, 8, 61}, {0, 9, 219}, {18, 7, 23}, {0, 8, 109}, {0, 8, 45}, {0, 9, 187}, {0, 8, 13}, {0, 8, 141}, {0, 8, 77}, {0, 9, 251}, {16, 7, 3}, {0, 8, 83}, {0, 8, 19}, {21, 8, 195}, {19, 7, 35}, {0, 8, 115}, {0, 8, 51}, {0, 9, 199}, {17, 7, 11}, {0, 8, 99}, {0, 8, 35}, {0, 9, 167}, {0, 8, 3}, {0, 8, 131}, {0, 8, 67}, {0, 9, 231}, {16, 7, 7}, {0, 8, 91}, {0, 8, 27}, {0, 9, 151}, {20, 7, 67}, {0, 8, 123}, {0, 8, 59}, {0, 9, 215}, {18, 7, 19}, {0, 8, 107}, {0, 8, 43}, {0, 9, 183}, {0, 8, 11}, {0, 8, 139}, {0, 8, 75}, {0, 9, 247}, {16, 7, 5}, {0, 8, 87}, {0, 8, 23}, {64, 8, 0}, {19, 7, 51}, {0, 8, 119}, {0, 8, 55}, {0, 9, 207}, {17, 7, 15}, {0, 8, 103}, {0, 8, 39}, {0, 9, 175}, {0, 8, 7}, {0, 8, 135}, {0, 8, 71}, {0, 9, 239}, {16, 7, 9}, {0, 8, 95}, {0, 8, 31}, {0, 9, 159}, {20, 7, 99}, {0, 8, 127}, {0, 8, 63}, {0, 9, 223}, {18, 7, 27}, {0, 8, 111}, {0, 8, 47}, {0, 9, 191}, {0, 8, 15}, {0, 8, 143}, {0, 8, 79}, {0, 9, 255}};

	for (int i = 0; i < 512; i++)
	{
		// Les seuls qui restent qui sont pas pareil c'est les codes avec le deuxieme bit dans .op de set (invalid code)
		if (lenfix[i].bits != ll_codes[i].nbits)
			ft_printf("on est triste: %d (%u - %u)\n", i, lenfix[i].bits, ll_codes[i].nbits);
		if (lenfix[i].val != ll_codes[i].val)
			ft_printf("on est triste: %d (%u - %u) %#x\n", i, lenfix[i].val, ll_codes[i].val, lenfix[i].op);
	}
}

#endif