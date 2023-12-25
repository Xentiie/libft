/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 16:43:53 by reclaire          #+#    #+#             */
/*   Updated: 2023/09/27 21:11:42 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdarg.h>
#ifdef FT_FILE_IO
S64	ft_printf(const_string fmt, ...)
{
	U64			i;
	va_list		args;
	S64			c_count;

	va_start(args, fmt);
	i = 0;
	c_count = 0;
	while (fmt[i])
	{
		if (fmt[i] == '%')
		{
			if (fmt[i+1] == '%')
				c_count += write(1, "%", 1);
			else if (fmt[i+1] == 'c')
				c_count += handle_c(va_arg(args, U32)); //U8 pas supporté par va_args
			else if (fmt[i+1] == 'd')
				c_count += handle_d(va_arg(args, S32));
			else if (fmt[i+1] == 'i')
				c_count += handle_i(va_arg(args, S32));
			else if (fmt[i+1] == 'p')
				c_count += handle_p(va_arg(args, U64));
			else if (fmt[i+1] == 's')
				c_count += handle_s(va_arg(args, string));
			else if (fmt[i+1] == 'u')
				c_count += handle_u(va_arg(args, U64));
			else if (fmt[i+1] == 'X')
				c_count += handle_ux(va_arg(args, U64));
			else if (fmt[i+1] == 'x')
				c_count += handle_x(va_arg(args, U64));
			else if (fmt[i+1] == 'v')
			{
				if (fmt[i+2] && fmt[i+3] == 'i')
				{
					if (fmt[i+2] == '2')
						{c_count += handle_vec2i(va_arg(args, t_iv2)); i+= 2;}
					else if (fmt[i+2] == '3')
						{c_count += handle_vec3i(va_arg(args, t_iv3)); i+= 2;}
					else if (fmt[i+2] == '4')
						{c_count += handle_vec4i(va_arg(args, t_iv4)); i+= 2;}
				}
				else
				{
					if (fmt[i+2] == '2')
						{c_count += handle_vec2(va_arg(args, t_v2)); i+= 2;}
					else if (fmt[i+2] == '3')
						{c_count += handle_vec3(va_arg(args, t_v3)); i+= 2;}
					else if (fmt[i+2] == '4')
						{c_count += handle_vec4(va_arg(args, t_v4)); i+= 2;}
				}
			}
			i++;
		}
		else
		{
			c_count++;
			ft_putchar_fd(fmt[i], 1);
		}
		i++;
	}
	va_end(args);
	return (c_count);
}
#endif