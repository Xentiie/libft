/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_int.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 19:57:38 by reclaire          #+#    #+#             */
/*   Updated: 2025/01/22 17:09:41 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(LIBFT_INT_H)
# define LIBFT_INT_H

#define _FT_RETURN

# include "libft/libft.h"
# include "libft/std.h"

# if !defined(LIBFT_AVOID_ALLOCA)
#  if defined(FT_OS_WIN) || defined(FT_OS_WIN_WSL)
#   include <malloc.h>
#  else
#   include <alloca.h>
#  endif
#  define ft_alloca(...) alloca(__VA_ARGS__)
#  define ft_afree(...)
# endif

# define MAX(x, y) (x > y ? x : y)
# define MIN(x, y) (x < y ? x : y)

#endif