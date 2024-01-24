/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_i.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 17:28:55 by reclaire          #+#    #+#             */
/*   Updated: 2023/09/26 21:06:01 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#ifdef FT_FILEIO
S32	handle_i(S32 i)
{
	string	out;
	S32		l;

	if (i == 0)
	{
		ft_putchar_fd('0', 1);
		return (1);
	}
	out = ft_itoa(i);
	l = ft_strlen(out);
	ft_putstr_fd(out, 1);
	free(out);
	return (l);
}
#endif