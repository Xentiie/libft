/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_defines.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 18:57:09 by reclaire          #+#    #+#             */
/*   Updated: 2025/04/14 20:09:43 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(FT_BITS_BUILTINS_DEFINES_H)
#define FT_BITS_BUILTINS_DEFINES_H

#ifdef __has_builtin
#define FT_HAS_BUILTIN(x) __has_builtin(x)
#else
#pragma warn "No FT_HAS_BUILTIN"
#define FT_HAS_BUILTIN(x) FALSE
#endif

#if !FT_HAS_BUILTIN(__builtin_expect) || defined(_FT_NO_IF_PREDICT)
# if !defined(_FT_NO_IF_PREDICT)
#  pragma warn "No IF_PREDICT"
# endif
# define IF_PREDICT(cond, expect) (cond)
# define IF_PREDICT_B(cond, expect) (cond)
#else
# define IF_PREDICT(cond, expect) __builtin_expect((cond), expect)
# define IF_PREDICT_B(cond, expect) __builtin_expect(!!(cond), expect)
#endif

#if FT_HAS_BUILTIN(__builtin_bswap16)
#define ft_bswap16(x) __builtin_bswap16(x)
#endif

#if FT_HAS_BUILTIN(__builtin_bswap32)
#define ft_bswap32(x) __builtin_bswap32(x)
#endif

#if FT_HAS_BUILTIN(__builtin_bswap64)
#define ft_bswap64(x) __builtin_bswap64(x)
#endif

#endif
