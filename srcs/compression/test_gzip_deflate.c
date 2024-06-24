/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_gzip_deflate.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 15:15:36 by reclaire          #+#    #+#             */
/*   Updated: 2024/06/24 22:30:16 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/compression/deflate.h"
#include "libft/io.h"
#include <stdio.h>
#include <stdlib.h>

extern const struct s_code fixed_ll_codes[];

U64 compress_data(U8 *data_out, U64 out_size)
{
	U8 buff_in[2048];
	U64 in_size;

	{
		file fd = ft_fopen("./test_gzip_deflate_old.c", "r");
		in_size = ft_fread(fd, (char *)buff_in, sizeof(buff_in));
	}

	t_deflate_stream deflate_stream = ft_deflate_init_stream(buff_in, in_size, data_out, out_size);
	ft_deflate_next_block(&deflate_stream, 4096, 1, 1);
	return deflate_stream.out_used;
}

int main2()
{
	U8 buff_in[4096];
	U64 in_size = compress_data(buff_in, sizeof(buff_in));
	U8 buff_out[4096] = {0};

	t_deflate_stream2 stream;
	ft_inflate_init(&stream);

	stream.in = buff_in;
	stream.in_size = 10;
	stream.out = buff_out;
	stream.out_size = 10;

	U64 in_used = 0;
	U64 out_used = 0;

	while (1)
	{
		S32 ret = ft_inflate2(&stream);
		if (ret == FT_INFLATE_RET_NOT_DONE)
		{
			out_used += stream.out_used;
			stream.out += stream.out_used;
			stream.out_used = 0;

			in_used += stream.in_used;
			stream.in += stream.in_used;
			stream.in_used = 0;
		}
		if (ret < 0)
		{
			printf("inflate error: %d\n", ret);
			break;
		}
		if (ret == FT_INFLATE_RET_DONE)
		{
			in_used += stream.in_used;
			out_used += stream.out_used;
			printf("inflate done\n");
			break;
		}
	}

	printf("IN USED: %lu\n", in_used);
	printf("OUT USED: %lu\n", out_used);
	printf("%.*s\n", (int)out_used, buff_out);
}

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
	struct s_fixed_code {
		U16 code;
		U16 index;
		U8 nbits;
	} codes[512] = {0};

	int i = 0;
	while (i <= 143)
	{
		if (codes[fixed_codes[i]].nbits != 0 || codes[fixed_codes[i] | 0x100].nbits != 0)
		{
			printf("ERROR\n");
			exit(1);
		}

		codes[fixed_codes[i]] = (struct s_fixed_code){.code = fixed_codes[i], .index = i, .nbits = 8};
		codes[fixed_codes[i] | 0x100] = (struct s_fixed_code){.code = fixed_codes[i], .index = i, .nbits = 8};
		i++;
	}

	while (i <= 255)
	{
		if (codes[fixed_codes[i]].nbits != 0)
		{
			printf("ERROR\n");
			exit(1);
		}
		codes[fixed_codes[i]] = (struct s_fixed_code){.code = fixed_codes[i], .index = i, .nbits = 9};
		i++;
	}

	while (i <= 279)
	{
		if (codes[fixed_codes[i]].nbits != 0 || codes[fixed_codes[i] | 0x80].nbits != 0 || codes[fixed_codes[i] | 0x100].nbits != 0 || codes[fixed_codes[i] | 0x180].nbits != 0)
		{
			printf("ERROR\n");
			exit(1);
		}
		codes[fixed_codes[i]] = (struct s_fixed_code){.code = fixed_codes[i], .index = i, .nbits = 7};
		codes[fixed_codes[i] | 0x80] = (struct s_fixed_code){.code = fixed_codes[i], .index = i, .nbits = 7};
		codes[fixed_codes[i] | 0x100] = (struct s_fixed_code){.code = fixed_codes[i], .index = i, .nbits = 7};
		codes[fixed_codes[i] | 0x180] = (struct s_fixed_code){.code = fixed_codes[i], .index = i, .nbits = 7};
		i++;
	}

	while (i <= 287)
	{
		if (codes[fixed_codes[i]].nbits != 0 || codes[fixed_codes[i] | 0x100].nbits != 0)
		{
			printf("ERROR\n");
			exit(1);
		}
		codes[fixed_codes[i]] = (struct s_fixed_code){.code = fixed_codes[i], .index = i, .nbits = 8};
		codes[fixed_codes[i] | 0x100] = (struct s_fixed_code){.code = fixed_codes[i], .index = i, .nbits = 8};
		i++;
	}


	file fd = ft_fopen("./fixed_codes.c", "w+");

	ft_dprintf(fd, "#include \"libft/std.h\"\n\n");

	ft_dprintf(fd, "struct s_code {\n\tU16 code;\n\tU16 index;\n\tU8 nbits;\n};\n\n");
	ft_dprintf(fd, "const struct s_code fixed_ll_codes[] = {\n\t");

	i = 0;
	for (; i < 512; i++)
	{
		ft_dprintf(fd, "{%u, %u, %u}, ", codes[i].code, codes[i].index, codes[i].nbits);
		if ((i + 1) % 10 == 0)
			ft_dprintf(fd, "\n\t");
	}

	ft_dprintf(fd, "\n};\n");

	ft_fclose(fd);
}
