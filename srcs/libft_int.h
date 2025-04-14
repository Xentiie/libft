/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_int.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 19:57:38 by reclaire          #+#    #+#             */
/*   Updated: 2025/04/14 20:21:06 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(LIBFT_INT_H)
# define LIBFT_INT_H

#define _FT_RETURN

# include "libft/libft.h"
# include "libft/std.h"

# define MAX(x, y) (x > y ? x : y)
# define MIN(x, y) (x < y ? x : y)

#define _FT_EXTENDED_ALIAS
#if defined(_FT_EXTENDED_ALIAS)
#include "libft/macros.h"
#define __extended_alias_dummy(x) x
#define __extended_alias_dummy2(y, x) x
#define EXTENDED_ALIAS(function_name, priority, cpuid_flags_lst, os_flags_lst) __attribute__((annotate("ft_extended_alias:" function_name ":" #priority ":" FT_MACRO_FOR_EACH_sep(__extended_alias_dummy, ",", FT_DEPAREN(cpuid_flags_lst) ":" FT_MACRO_FOR_EACH_sep_arg(__extended_alias_dummy2, ",",, FT_DEPAREN(os_flags_lst))))))
#endif

#endif