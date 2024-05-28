/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gzip.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 22:00:12 by reclaire          #+#    #+#             */
/*   Updated: 2024/05/27 20:53:26 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_int.h"
#include <stdio.h>

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

static U64 create_block(t_bitstream *stream, bool is_last, S32 block_type, U8 *data, U64 data_size, U32 *crc)
{
	U64 out;

	ft_bstrm_write_bit(stream, is_last);
	ft_bstrm_write_bit(stream, block_type & 1);
	ft_bstrm_write_bit(stream, block_type & 2);

	switch (block_type)
	{
	case BLOCK_UNCOMPRESSED:;
		while (stream->bit_offset != 0)
			ft_bstrm_write_bit(stream, 0);
		U16 size = data_size;
		ft_bstrm_write_u16_little_endian(stream, size);
		ft_bstrm_write_u16_little_endian(stream, ~((U16)size));

		ft_bstrm_write_bytes(stream, size, data);
		out = data_size;
		break;
	case BLOCK_TYPE_1:
		ft_deflate(data, data_size, stream);
		out = data_size;
		break;

	default:
		return 0;
	}

	*crc = ft_crc32_u(data, data_size, *crc);
	return out;
}

void ft_make_gzip(U8 *data, U64 len, string out_file)
{
	file fd = ft_fopen(out_file, "w+");
	if (fd == (file)-1)
		return;

	U8 buffer[8192];
	U32 crc = 0;
	U32 out_size = 0;

	t_bitstream stream = FT_BITSTREAM_INIT(buffer, sizeof(buffer));

	write_gzip_header(fd);

	U64 to_compress = sizeof(buffer) / 1.5;
	U64 n = 0;
	while (n < len)
	{
		bool is_last = (n + to_compress) > len;
		out_size += create_block(&stream, is_last, BLOCK_TYPE_1, data + n, MIN(to_compress, len - n), &crc);

		while (is_last && stream.bit_offset != 0)
			ft_bstrm_write_bit(&stream, 0);

		U64 to_write = stream.byte_offset;
		while (to_write)
			to_write -= ft_fwrite(fd, (char*)buffer, to_write);
		ft_bstrm_reset_counter(&stream);

		n += to_compress;
	}

	write_gzip_footer(fd, crc, out_size);
	ft_fclose(fd);
}

