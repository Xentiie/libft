/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 17:28:55 by reclaire          #+#    #+#             */
/*   Updated: 2023/09/26 21:05:56 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#ifdef FT_FILE_IO
S32	handle_d(S32 i)
{
	string	out;
	U64		l;

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