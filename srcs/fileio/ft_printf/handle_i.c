/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_i.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 17:28:55 by reclaire          #+#    #+#             */
/*   Updated: 2024/02/11 20:23:45 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

S32	handle_i(S32 i)
{
	string	out;
	S32		l;

	if (i == 0)
	{
		ft_putchar_fd('0', ft_stdout);
		return (1);
	}
	out = ft_itoa(i);
	l = ft_strlen(out);
	ft_putstr_fd(out, ft_stdout);
	free(out);
	return (l);
}
