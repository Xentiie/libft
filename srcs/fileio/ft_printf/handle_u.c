/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_u.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 17:28:55 by reclaire          #+#    #+#             */
/*   Updated: 2024/02/11 20:27:31 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

S32	handle_u(U64 i)
{
	string	out;
	U64		l;

	out = ft_uitoa(i);
	l = ft_strlen(out);
	ft_putstr_fd(out, ft_stdout);
	free(out); //TODO: probably a better way to do this not using the heap
	return (l);
}
