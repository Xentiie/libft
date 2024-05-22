/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitstreams.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 23:45:18 by reclaire          #+#    #+#             */
/*   Updated: 2024/05/21 22:09:03 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_BITSTREAMS_H
#define LIBFT_BITSTREAMS_H

typedef struct s_bitstream
{
	U8 *buffer;
	U64 buffer_max_len;

	U64 bits_read;
	U64 total_bits_read;
} t_bitstream;

#define FT_BITSTREAM_INIT(buf, max_len) ((t_bitstream){.buffer = buf, .buffer_max_len = max_len, .bits_read = 0, .total_bits_read = 0})
#define FT_BITSTREAM_CPY(stream) ((t_bitstream){.buffer = stream.buffer, .buffer_max_len = stream.buffer_max_len, .bits_read = 0, .total_bits_read = 0})
#define FT_BITSTREAM_RESET(stream) do { stream.bits_read = 0; stream.total_bits_read = 0; } while (0)

U8 ft_bstrm_read_bit(t_bitstream *stream);
U8 ft_bstrm_read_bits(t_bitstream *stream, U8 n);
U8 ft_bstrm_read_byte(t_bitstream *stream);
void ft_bstrm_read_bytes(t_bitstream *stream, U64 n, U8 *out);

void ft_bstrm_write_bit(t_bitstream *stream, U8 bit);
void ft_bstrm_write_bits(t_bitstream *stream, U64 n, U8 *bits);
void ft_bstrm_write_byte(t_bitstream *stream, U8 byte);
void ft_bstrm_write_bytes(t_bitstream *stream, U64 n, U8 *bytes);
//Appends a 0 byte at the end of the stream, to byte-align it
void ft_bstrm_write_0(t_bitstream *stream);
//Returns the number of bytes written in the stream, and sets internal counter to 0 bytes (keeps current written bits that needs to be filled)
U64 ft_bstrm_flush_bytes(t_bitstream *stream);

#endif