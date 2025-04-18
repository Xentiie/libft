/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_format_specifiers.h                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 01:18:01 by reclaire          #+#    #+#             */
/*   Updated: 2025/04/15 02:33:04 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(FT_BITS_PRINTF_FORMAT_SPECIFIERS_H)
#define FT_BITS_PRINTF_FORMAT_SPECIFIERS_H

#include "libft/bits/format_specifiers.h"

#define FL_ALT (1 << 0)
#define FL_ZEROPAD (1 << 1)
#define FL_SPACEPAD (1 << 2)
#define FL_LEFTJUST (1 << 3)
#define FL_SHOWSIGN (1 << 4)
#define FL_SPACESIGN (1 << 5)

#define FL_T_SHORT (1 << 7)
#define FL_T_LONG (1 << 8)
#define FL_T_LONGLONG (1 << 9)

#define FL_SPEC_NUMBER (1 << 10)
#define FL_SPEC_UNSIGNED (1 << 11)
#define FL_SPEC_HEX (1 << 12)
#define FL_SPEC_HEX_U (1 << 13)
#define FL_SPEC_FLOATING_POINT (1 << 14)

const struct s_fmt_flag *ft_printf_format_specifiers();

#endif
