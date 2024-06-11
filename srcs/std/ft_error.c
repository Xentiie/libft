/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 17:27:54 by reclaire          #+#    #+#             */
/*   Updated: 2024/06/07 17:31:39 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_int.h"
#include <stdarg.h>

void ft_error(S32 retcode, string fmt, ...)
{
	va_list args;

	ft_dprintf(ft_stderr, "%s: ", ft_argv[0]);
	va_start(args, fmt);
	ft_vdprintf(ft_stderr, fmt, args);
	va_end(args);

	if (retcode > 0)
		exit(retcode);
}
