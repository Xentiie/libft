/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gzip.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 22:00:12 by reclaire          #+#    #+#             */
/*   Updated: 2024/05/21 22:22:22 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_int.h"

static void write_gzip_header(file fd)
{
	const U8 header[] = {0x1f, 0x8b, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03};
	ft_fwrite(fd, (char*)header, sizeof(header));
}
static void write_gzip_footer(file fd, U32 crc, U32 size)
{
	ft_fwrite(fd, (char*)&crc, sizeof(U32));
	ft_fwrite(fd, (char*)&size, sizeof(U32));
}

#define BLOCK_UNCOMPRESSED 0
#define BLOCK_TYPE_1 1
#define BLOCK_TYPE_2 2

static void create_block(t_bitstream *stream, bool is_last, S32 block_type, U8 *data, U64 data_size, U32 *crc)
{
	U8 block_header = 0;
	block_header |= (is_last & 1);
	block_header |= ((block_type & 0x3) << 1);
	ft_bstrm_write_byte(stream, block_header);

	switch (block_type)
	{
	case BLOCK_UNCOMPRESSED:;
		U16 size = data_size;
		ft_bstrm_write_bytes(stream, 2, (U8*)&size);
		ft_bstrm_write_bytes(stream, 2, (U8*)&(U16){~size});

		ft_bstrm_write_bytes(stream, size, data);
		break;
	default:
		return;
	}

	*crc = ft_crc32_u(data, data_size, *crc);
}

void ft_make_gzip(U8 *data, U64 len, string out_file)
{
	file fd = ft_fopen(out_file, "w+");
	if (fd == (file)-1)
		return;

	U32 crc = 0;
	U32 out_size = 0;
	U64 n = 0;

	write_gzip_header(fd);

	U8 buffer[32768 * 4];
	t_bitstream stream = FT_BITSTREAM_INIT(buffer, sizeof(buffer));
	
	U64 to_compress = sizeof(buffer) / 1.5;
	while (n < len)
	{
		create_block(&stream, (n + to_compress) < len, BLOCK_UNCOMPRESSED, data + n, MIN(to_compress, len - n), &crc);
		U64 to_write = ft_bstrm_flush_bytes(&stream);
		out_size += to_write;
		
		while (to_write)
			to_write -= ft_fwrite(fd, (char*)buffer, to_write);

		n += to_compress;
	}

	write_gzip_footer(fd, crc, out_size);
	ft_fclose(fd);
}
