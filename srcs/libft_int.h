/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_int.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 19:57:38 by reclaire          #+#    #+#             */
/*   Updated: 2025/06/08 02:33:44 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(LIBFT_INT_H)
#define LIBFT_INT_H

#include "libft/bits/ft_return.h"

#include "libft/libft.h"
#include "libft/std.h"

#include "libft/bits/globals.h"

typedef void * (*f_ft_allocator)(U64 size);
typedef void (*f_ft_free)(void *);

_FT_GLOBAL_VAR_DEC(f_ft_allocator, ftalloc)
_FT_GLOBAL_VAR_DEC(f_ft_free, ftfree)

#if FT_CUSTOM_ALLOCATORS
#define ftalloc _FT_GLOBAL_VAR(ftalloc)
#define ftfree _FT_GLOBAL_VAR(ftfree)
#else
#define ftalloc malloc
#define ftfree free
#endif

#endif