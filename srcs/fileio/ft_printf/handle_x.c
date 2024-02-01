/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_x.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 17:28:55 by reclaire          #+#    #+#             */
/*   Updated: 2024/01/10 11:19:34 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>
#ifdef FT_FILEIO
static void	add_to_char_buff(string buf, U8 c)
{
	static int	i = 0;

	if (!buf)
	{
		i = 0;
		return ;
	}
	buf[i] = c;
	i++;
}

static void	convert(U64 num, string out)
{
	string	hexa;

	hexa = "0123456789abcdef";
	if (num >= 16)
	{
		convert(num / 16, out);
		convert(num % 16, out);
	}
	else
		add_to_char_buff(out, hexa[num]);
}

S32	handle_x(U64 i)
{
	U8		out[8];
	S32		ret;

	ft_bzero(out, sizeof(U8) * 8);
	if (i == 0)
		add_to_char_buff((string)out, '0');
	else
		convert(i, (string)out);
	ret = ft_fwrite(ft_stdout, out, ft_strlen((string)out));
	add_to_char_buff(NULL, '0');
	return (ret);
}
#endif