/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloca.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 20:02:03 by reclaire          #+#    #+#             */
/*   Updated: 2025/04/14 20:05:06 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(FT_BITS_ALLOCA_H)
#define FT_BITS_ALLOCA_H

/* Define _FT_AVOID_ALLOCA to remove all use of alloca */
# if !defined(_FT_AVOID_ALLOCA)

#  include "libft/bits/os_defines.h"
#  if FT_OS_WINDOWS
#   include <malloc.h>
#  else
#   include <alloca.h>
#  endif

#  define ft_alloca(...) alloca(__VA_ARGS__)
#  define ft_afree(...)

# else /* defined(_FT_AVOID_ALLOCA) */
#  define ft_alloca(...) malloc(__VA_ARGS__)
#  define ft_afree(...) free(__VA_ARGS__)
# endif

#endif