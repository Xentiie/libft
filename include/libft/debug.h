/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 19:59:45 by reclaire          #+#    #+#             */
/*   Updated: 2025/04/15 01:50:41 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(LIBFT_DEBUG_H)
#define LIBFT_DEBUG_H

#include "libft/libft.h"

#if defined(DEBUG)
#define FT_IFDEBUG(...) __VA_ARGS__
#define FT_NIFDEBUG(...)
#else
#define FT_IFDEBUG(...)
#define FT_NIFDEBUG(...) __VA_ARGS__
#endif

#define FT_DEBUG_FALSE 0
#define FT_DEBUG_VALGRIND 1
#define FT_DEBUG_TRUE 2

void ft_debug_break();
S8 ft_is_debugger();

#if defined(FT_MEMCHECK)
extern bool ft_check_leaks();
extern void ft_memcheck_init(const_string *argv, bool threaded);

extern void *_malloc(U64 size, char *file, int line);
extern void _free(void *p, char *file, int line);
#define malloc(X) _malloc(X, __FILE__, __LINE__)
#define free(X) _free(X, __FILE__, __LINE__)
#endif /* FT_MEMCHECK */

#endif