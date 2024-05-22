/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitstream.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 23:44:59 by reclaire          #+#    #+#             */
/*   Updated: 2024/05/21 22:20:42 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_int.h"

/*in*/
U8 ft_bstrm_read_bit(t_bitstream *stream)
{
	if (stream->bits_read / 8 > stream->buffer_max_len)
		__FTRETURN_ERR((U8)-1, FT_ERANGE);
	U64 byte_idx = stream->bits_read / 8;
	U64 bit_idx = stream->bits_read % 8;
	stream->bits_read++;
	stream->total_bits_read++;
	__FTRETURN_OK((stream->buffer[byte_idx] >> bit_idx) & 1);
}

U8 ft_bstrm_read_bits(t_bitstream *stream, U8 n)
{
	if (n > 64)
		__FTRETURN_ERR((U8)-1, FT_ERANGE);
	U8 b = 0;
	for (U8 i = 0; i < n; i++)
	{
		b |= (ft_bstrm_read_bit(stream) << i);
		if (ft_errno != FT_OK)
			__FTRETURN_ERR(-1, ft_errno);
	}
	__FTRETURN_OK(b);
}

U8 ft_bstrm_read_byte(t_bitstream *stream)
{
	U64 n = ft_bstrm_read_bits(stream, 8);
	if (ft_errno != FT_OK)
		__FTRETURN_ERR((U8)-1, ft_errno);
	__FTRETURN_OK((U8)n);
}

void ft_bstrm_read_bytes(t_bitstream *stream, U64 n, U8 *out)
{
	for (U64 i = 0; i < n; i++)
	{
		*out = ft_bstrm_read_byte(stream);
		out++;
		if (ft_errno != FT_OK)
			__FTRETURN_ERR(, ft_errno);
	}
	__FTRETURN_OK();
}

/*out*/
void ft_bstrm_write_bit(t_bitstream *stream, U8 bit)
{
	if (stream->bits_read / 8 > stream->buffer_max_len)
		__FTRETURN_ERR(, FT_ERANGE);
	U64 byte_idx = stream->bits_read / 8;
	U64 bit_idx = stream->bits_read % 8;
	stream->bits_read++;
	stream->total_bits_read++;
	stream->buffer[byte_idx] |= ((bit & 1) << (bit_idx));
	__FTRETURN_OK();
}

void ft_bstrm_write_bits(t_bitstream *stream, U64 n, U8 *bits)
{
	for (U64 i = 0; i < n; i++)
	{
		ft_bstrm_write_bit(stream, bits[i]);
		if (ft_errno != FT_OK)
			__FTRETURN_ERR(,ft_errno);
	}
	__FTRETURN_OK();
}

void ft_bstrm_write_byte(t_bitstream *stream, U8 byte)
{
	for (U8 i = 0; i < 8; i++)
		ft_bstrm_write_bit(stream, byte >> i);
}

void ft_bstrm_write_bytes(t_bitstream *stream, U64 n, U8 *bytes)
{
	for (U64 i = 0; i < n; i++)
		ft_bstrm_write_byte(stream, bytes[i]);
}

void ft_bstrm_write_0(t_bitstream *stream)
{
	ft_bstrm_write_byte(stream, 0);
}

U64 ft_bstrm_flush_bytes(t_bitstream *stream)
{
	U64 out = stream->bits_read / 8;
	stream->bits_read %= 8;
	return out;
}
