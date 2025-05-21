/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extended_aliases.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 20:36:02 by reclaire          #+#    #+#             */
/*   Updated: 2025/05/20 04:02:48 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(FT_BITS_EXTENDED_ALIASES_H)
#define FT_BITS_EXTENDED_ALIASES_H

#include "libft/macros.h"
#define __extended_alias_dummy(x) x
#define __extended_alias_dummy2(y, x) x
#define EXTENDED_ALIAS(function_name, priority, cpuid_flags_lst, os_flags_lst) __attribute__((annotate("ft_extended_alias:" function_name ":" #priority ":" FT_MACRO_FOR_EACH_sep(__extended_alias_dummy, ",", FT_DEPAREN(cpuid_flags_lst) ":" FT_MACRO_FOR_EACH_sep_arg(__extended_alias_dummy2, ",",, FT_DEPAREN(os_flags_lst))))))

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wattributes"
#pragma GCC diagnostic ignored "-Wunknown-pragmas"

#endif