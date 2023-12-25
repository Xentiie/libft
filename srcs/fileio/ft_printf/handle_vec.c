/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_vec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 14:38:23 by reclaire          #+#    #+#             */
/*   Updated: 2023/09/27 21:09:58 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>
#ifdef FT_FILE_IO
#define do_vec(v, type, size, conv)					\
	U64	total_size = 0;								\
	ft_putchar_fd('(', 1);							\
	for (int __i = 0; __i < size; __i++)			\
	{												\
		string __istr = conv(((type*)&v)[__i]);		\
		ft_putstr_fd(__istr, 1);					\
		total_size += ft_strlen(__istr);			\
		free(__istr);								\
		if (__i != size - 1)						\
			ft_putchar_fd(',', 1);					\
	}												\
	ft_putchar_fd(')', 1);							\
	return (total_size);

S32	handle_vec2i(t_iv2 c)	{ do_vec(c, int, 2, ft_itoa); }
S32	handle_vec3i(t_iv3 c)	{ do_vec(c, int, 3, ft_itoa); }
S32	handle_vec4i(t_iv4 c)	{ do_vec(c, int, 4, ft_itoa); }
S32	handle_vec2(t_v2 c)		{ do_vec(c, float, 2, ft_ftoa); }
S32	handle_vec3(t_v3 c)		{ do_vec(c, float, 3, ft_ftoa); }
S32	handle_vec4(t_v4 c)		{ do_vec(c, float, 4, ft_ftoa); }

#endif