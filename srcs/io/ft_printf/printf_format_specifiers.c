/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_format_specifiers.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 01:17:13 by reclaire          #+#    #+#             */
/*   Updated: 2025/03/31 01:36:48 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/bits/printf_format_specifiers.h"

struct s_fmt_flag *ft_printf_format_specifiers()
{
	static const struct s_fmt_flag specifiers[] = {
		{.type = FMT_FLAG, .c = '#', .flag = FL_ALT},
		{.type = FMT_FLAG, .c = '0', .flag = FL_ZEROPAD},
		{.type = FMT_FLAG, .c = ' ', .flag = FL_SPACEPAD},
		{.type = FMT_FLAG, .c = '-', .flag = FL_LEFTJUST},
		{.type = FMT_FLAG, .c = '+', .flag = FL_SHOWSIGN},
		{.type = FMT_FLAG, .c = '\'', .flag = 0},
		{.type = FMT_FLAG, .c = 'I', .flag = 0},

		{.type = FMT_SIZE, .c = 'h', .flag = FL_T_SHORT},
		{.type = FMT_SIZE, .c = 'l' + 127, .flag = FL_T_LONG},
		{.type = FMT_SIZE, .c = 'j', .flag = FL_T_LONGLONG},
		{.type = FMT_SIZE, .c = 'z', .flag = FL_T_LONGLONG},
		{.type = FMT_SIZE, .c = 'Z', .flag = FL_T_LONGLONG},
		{.type = FMT_SIZE, .c = 't', .flag = FL_T_LONGLONG},
		{.type = FMT_SIZE, .c = 'L', .flag = FL_T_LONGLONG},
		{.type = FMT_SIZE, .c = 'q', .flag = FL_T_LONGLONG},

		{.type = FMT_SPEC, .c = 'n', .flag = 0},
		{.type = FMT_SPEC, .c = 'c', .flag = 0},
		{.type = FMT_SPEC, .c = 's', .flag = 0},
	
		{.type = FMT_SPEC, .c = 'D', .flag = FL_T_LONG | FL_SPEC_NUMBER},
		{.type = FMT_SPEC, .c = 'd', .flag = FL_SPEC_NUMBER},
		{.type = FMT_SPEC, .c = 'i', .flag = FL_SPEC_NUMBER},
	
		{.type = FMT_SPEC, .c = 'e', .flag = FL_SPEC_FLOATING_POINT},
		{.type = FMT_SPEC, .c = 'E', .flag = FL_SPEC_FLOATING_POINT},
		{.type = FMT_SPEC, .c = 'f', .flag = FL_SPEC_FLOATING_POINT},
		{.type = FMT_SPEC, .c = 'g', .flag = FL_SPEC_FLOATING_POINT},
		{.type = FMT_SPEC, .c = 'G', .flag = FL_SPEC_FLOATING_POINT},
	
		{.type = FMT_SPEC, .c = 'X', .flag = FL_SPEC_HEX_U | FL_SPEC_UNSIGNED | FL_SPEC_NUMBER},
		{.type = FMT_SPEC, .c = 'x', .flag = FL_SPEC_UNSIGNED | FL_SPEC_NUMBER}, /* | FL_SPEC_HEX if FL_ALT */

		{.type = FMT_SPEC, .c = 'U', .flag = FL_T_LONGLONG | FL_SPEC_UNSIGNED | FL_SPEC_NUMBER},
		{.type = FMT_SPEC, .c = 'u', .flag = FL_SPEC_UNSIGNED | FL_SPEC_NUMBER},

		{.type = FMT_SPEC, .c = 'O', .flag = FL_T_LONGLONG | FL_SPEC_UNSIGNED | FL_SPEC_NUMBER},
		{.type = FMT_SPEC, .c = 'o', .flag = FL_SPEC_UNSIGNED | FL_SPEC_NUMBER},

		{.type = FMT_SPEC, .c = 'p', .flag = FL_T_LONG | FL_SPEC_UNSIGNED | FL_SPEC_NUMBER | FL_SPEC_HEX},

		{0},
	};

	return specifiers;
}
