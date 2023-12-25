/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_uX.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 17:28:55 by reclaire          #+#    #+#             */
/*   Updated: 2023/09/26 21:06:21 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#ifdef FT_FILE_IO
static void	convert(U64 num, S32 *i)
{
	string	hexa;

	hexa = "0123456789ABCDEF";
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

S32	handle_ux(U64 i)
{
	S32	j;

	j = 0;
	if (i == 0)
		return (write(1, "0", 1));
	else
		convert(i, &j);
	return (j);
}
#endif