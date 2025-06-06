/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_int.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 16:55:27 by reclaire          #+#    #+#             */
/*   Updated: 2024/11/22 09:24:34 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(FT_PRINTF_INT_H)
#define FT_PRINTF_INT_H

#define _FT_IPRINTF
#include "libft_int.h"
#include "libft/io.h"
#include "../file_private.h"

#include <stdarg.h>

#define FL_ALT (1 << 1)
#define FL_ZEROPAD (1 << 2)
#define FL_SPACEPAD (1 << 3)
#define FL_LEFTJUST (1 << 4)
#define FL_SHOWSIGN (1 << 5)
#define FL_SPACESIGN (1 << 6)

#define FL_T_LONG (1 << 7)
#define FL_T_LONGLONG (1 << 8)
#define FL_T_SHORT (1 << 9)

#define FL_UNSIGNED (1 << 10)
#define FL_NUMBER (1 << 11)
#define FL_FP (1 << 12)
#define FL_HEX (1 << 13)
#define FL_HEX_M (1 << 14)
#define FL_BINARY (1 << 15)

typedef S64 (*t_fmtwr_i)(const_string str, U64 str_len, void *data);
bool __ftprintf_build_arg_table(const_string fmt, va_list vaargs, U64 **args);
S32 __ftprintf_parse_flags(const_string *_fmt);
S32 __ftprintf_parse_specifier_n(const_string *_fmt);
S32 __ftprintf_parse_width(const_string *_fmt, S32 *arg_n, S32 *nextarg);
S32 __ftprintf_parse_prec(const_string *_fmt, S32 *arg_n, S32 *nextarg);
S32 __ftprintf_parse_size_flags(const_string *_fmt);
#endif