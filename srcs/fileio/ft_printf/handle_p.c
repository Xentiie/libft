/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_p.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 17:28:55 by reclaire          #+#    #+#             */
/*   Updated: 2024/02/11 20:26:07 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	convert(U64 num, S32 *i)
{
	string	hexa = "0123456789abcdef";

	if (num >= 16)
	{
		convert(num / 16, i);
		convert(num % 16, i);
	}
	else
	{
		if (num >= '0' && num <= '9')
			ft_putchar_fd(hexa[num], ft_stdout);
		else
			ft_putchar_fd(hexa[num], ft_stdout);
		(*i)++;
	}
}

S32	handle_p(U64 p)
{
	S32	i;

	i = 0;
	ft_putstr_fd("0x", ft_stdout);
	convert(p, &i);
	return (i + 2);
}
