/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 17:27:54 by reclaire          #+#    #+#             */
/*   Updated: 2024/11/27 15:36:55 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_int.h"
#include "libft/io.h"
#include "libft/strings.h"

#include <stdlib.h>
#include <stdarg.h>

void ft_error(S32 retcode, string fmt, ...)
{
	va_list args;

	ft_fprintf(ft_fstderr, "%s: ", ft_argv[0]);
	va_start(args, fmt);
	ft_vfprintf(ft_fstderr, fmt, args);
	va_end(args);

	if (retcode > 0)
		exit(retcode);
}

void ft_error_errno(S32 retcode, string fmt, ...)
{
	va_list args;

	ft_fprintf(ft_fstderr, "%s: (%d)%s: ", ft_argv[0], ft_errno, ft_strerror(ft_errno));
	
	va_start(args, fmt);
	ft_vfprintf(ft_fstderr, fmt, args);
	va_end(args);
	
	if (retcode > 0)
		exit(retcode);
}

void ft_error_errno2(S32 retcode, string fmt, ...)
{
	va_list args;

	ft_fprintf(ft_fstderr, "%s: (%d)%s: ", ft_argv[0], ft_errno, ft_strerror2());
	va_start(args, fmt);
	ft_vfprintf(ft_fstderr, fmt, args);
	va_end(args);

	if (retcode > 0)
		exit(retcode);
}
