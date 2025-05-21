/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   attributes_defines.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 18:57:30 by reclaire          #+#    #+#             */
/*   Updated: 2025/05/18 01:20:43 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(FT_BITS_ATTRIBUTES_DEFINES_H)
#define FT_BITS_ATTRIBUTES_DEFINES_H

#if defined(__has_attribute)
#define FT_HAS_ATTRIBUTE(x) __has_attribute(x)
#else
#pragma warn "No FT_HAS_ATTRIBUTE"
#define FT_HAS_ATTRIBUTE(x) FALSE
#endif

#if !FT_HAS_ATTRIBUTE(constructor)
#pragma error "No __attribute__((constructor))"
#endif

#if FT_HAS_ATTRIBUTE(hot)
#define FUNCTION_HOT __attribute__((hot))
#else
#define FUNCTION_HOT
#endif

#if FT_HAS_ATTRIBUTE(cold)
#define FUNCTION_COLD __attribute__((cold))
#else
#define FUNCTION_COLD
#endif

#if FT_HAS_ATTRIBUTE(pure)
#define FUNCTION_PURE __attribute__((pure))
#else
#define FUNCTION_PURE
#endif

#if FT_HAS_ATTRIBUTE(unused)
#define MAYBE_UNUSED __attribute__((unused))
#else
#define MAYBE_UNUSED
#endif

#if FT_HAS_ATTRIBUTE(aligned)
#define ALIGNED(X) __attribute__((aligned(X)))
#else
// TODO: check for SSE functions that requires alignement
#pragma warn "Careful: no __attribute__((aligned)), will break stuff"
#define ALIGNED(X)
#endif

#if FT_HAS_ATTRIBUTE(__always_inline__)
#define ALWAYS_INLINE __attribute__((__always_inline__))
#else
#pragma warn "No attribute __always_inline__ :("
#define ALWAYS_INLINE
#endif

#endif
