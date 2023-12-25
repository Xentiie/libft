/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_p.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 17:28:55 by reclaire          #+#    #+#             */
/*   Updated: 2023/09/26 21:06:08 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#ifdef FT_FILE_IO
static void	convert(U64 num, S32 *i)
{
	string	hexa;

	hexa = "0123456789abcdef";
	if (num >= 16)
	{
		convert(num / 16, i);
		convert(num % 16, i);
	}
	else
	{
		if (num >= '0' && num <= '9')
			ft_putchar_fd(hexa[num], 1);
		else
			ft_putchar_fd(hexa[num], 1);
		(*i)++;
	}
}

S32	handle_p(U64 p)
{
	S32	i;

	i = 0;
	ft_putstr_fd("0x", 1);
	convert(p, &i);
	return (i + 2);
}
#endif