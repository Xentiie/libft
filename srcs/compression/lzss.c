/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lzss.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 02:27:57 by reclaire          #+#    #+#             */
/*   Updated: 2024/05/19 16:53:15 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_int.h"
#include <stdlib.h>

static U8 add_bit(U8 bit, U8 *data)
{
	static U8 b;
	static U8 n = 0;

	b |= (bit & 1) << n++;
	if (n == 8)
	{
		*data = b;
		b = 0;
		n = 0;
		return 1;
	}
	return 0;
}

static U64 add_byte(U8 byte, U8 *data)
{
	U64 out = 0;
	for (U8 n = 0; n < 8; n++)
		out += add_bit(byte >> n, data + out);
	return out;
}

U8 *ft_lzss(U8 *data, U64 len, U64 window_size, U64 lookahead)
{
	U8 buffer[1024];
	U8 *buf = buffer;

	//buf += add_byte(255, buf);
}

