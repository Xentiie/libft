/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:24:33 by reclaire          #+#    #+#             */
/*   Updated: 2025/04/14 20:34:24 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(FT_BITS_GLOBALS_H)
#define FT_BITS_GLOBALS_H

#if !defined(_FT_NO_GLOBALS)
#define _FT_NO_GLOBALS 1
#endif

#if _FT_NO_GLOBALS
#define _FT_GLOBAL_VAR_DEC(type, name) type *__global_##name();
#define _FT_GLOBAL_VAR_DEF(type, name, ...)             \
	type *__global_##name()                             \
	{                                                   \
		static type __##name __VA_OPT__(= __VA_ARGS__); \
		return &__##name;                               \
	}
#define _FT_GLOBAL_VAR_DEF_THREADLOCAL(type, name, ...)             \
	type *__global_##name()                                         \
	{                                                               \
		static threadlocal type __##name __VA_OPT__(= __VA_ARGS__); \
		return &__##name;                                           \
	}
#define _FT_GLOBAL_VAR(name) (*(__global_##name()))
#else
#define _FT_GLOBAL_VAR_DEC(type, name) extern type name;
#define _FT_GLOBAL_VAR_DEF(type, name, ...) type name __VA_OPT__(= __VA_ARGS__);
#define _FT_GLOBAL_VAR(name) (name)
#endif

#endif
