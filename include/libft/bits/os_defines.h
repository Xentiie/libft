/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   os_defines.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 16:16:11 by reclaire          #+#    #+#             */
/*   Updated: 2025/04/14 20:20:44 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(FT_OS_DEFINES_H)
#define FT_OS_DEFINES_H

/*
https://web.archive.org/web/20140625123925/http://nadeausoftware.com/articles/2012/01/c_c_tip_how_use_compiler_predefined_macros_detect_operating_system
*/

#define _FT_PRIVATE_BITS
#include "libft/bits/private/bool_defines.h"
#undef _FT_PRIVATE_BITS

#if !defined(FT_OS_LINUX) \
	&& !defined(FT_OS_BSD) \
	&& !defined(FT_OS_BSD_DRAGONFLY) \
	&& !defined(FT_OS_BSD_FREEBSD) \
	&& !defined(FT_OS_BSD_NETBSD) \
	&& !defined(FT_OS_BSD_OPENBSD) \
	&& !defined(FT_OS_SOLARIS) \
	&& !defined(FT_OS_APPLE) \
	&& !defined(FT_OS_APPLE_XCODE) \
	&& !defined(FT_OS_APPLE_IOS) \
	&& !defined(FT_OS_APPLE_OSX) \
	&& !defined(FT_OS_WINDOWS) \
	&& !defined(FT_OS_WINDOWS32) \
	&& !defined(FT_OS_WINDOWS64) \
	&& !defined(FT_OS_CYGWIN) \
	&& !defined(FT_OS_CYGWIN_POSIX) \
	&& !defined(FT_OS_MINGW) \
	&& !defined(FT_OS_MINGW32) \
	&& !defined(FT_OS_MINGW64) \
	&& !defined(FT_OS_UNIX) \
	&& !defined(FT_OS_POSIX) \
	&& !defined(FT_OS_ANDROID)

/* === DEFAULT CONFIG === */
/* Any Linux */
#define FT_OS_LINUX FALSE

/* Any BSD */
#define FT_OS_BSD FALSE
/* DragonFly BSD */
#define FT_OS_BSD_DRAGONFLY FALSE
/* FreeBSD */
#define FT_OS_BSD_FREEBSD FALSE
/* NetBSD */
#define FT_OS_BSD_NETBSD FALSE
/* OpenBSD */
#define FT_OS_BSD_OPENBSD FALSE

/* Solaris */
#define FT_OS_SOLARIS FALSE

/* Any Apple */
#define FT_OS_APPLE FALSE
/* Xcode simulator */
#define FT_OS_APPLE_XCODE FALSE
/* IOS device */
#define FT_OS_APPLE_IOS FALSE
/* OSX device */
#define FT_OS_APPLE_OSX FALSE

/* Any Windows */
#define FT_OS_WINDOWS FALSE
/* 32 bits Windows */
#define FT_OS_WINDOWS32 FALSE
/* 64 bits Windows */
#define FT_OS_WINDOWS64 FALSE

/* Cygwin */
#define FT_OS_CYGWIN FALSE
/* Cygwin POSIX */
#define FT_OS_CYGWIN_POSIX FALSE

/* MingW */
#define FT_OS_MINGW FALSE
/* 32 bits MingW */
#define FT_OS_MINGW32 FALSE
/* 64 bits MingW */
#define FT_OS_MINGW64 FALSE

/* Unix */
#define FT_OS_UNIX FALSE

/* Posix */
#define FT_OS_POSIX FALSE

/* Android */
#define FT_OS_ANDROID FALSE

/* IDE */
#define FT_IDE_INTELLISENSE FALSE

/* === LINUX === */
#if defined(__linux__)
# define FT_OS_LINUX TRUE
#endif

/* === BSD === */
#if defined(__unix__) || (defined(__APPLE__) && defined(__MACH__))
# include <sys/param.h>
# if defined(BSD)
#  define FT_OS_BSD TRUE
#  if defined(__DragonFly__)
#   define FT_OS_BSD_DRAGONFLY TRUE
#  endif
#  if defined(__FreeBSD__)
#   define FT_OS_BSD_FREEBSD TRUE
#  endif
#  if defined(__NetBSD__)
#   define FT_OS_BSD_NETBSD TRUE
#  endif
#  if defined(__OpenBSD__)
#   define FT_OS_BSD_OPENBSD TRUE
#  endif
# endif
#endif

/* === SOLARIS === */
#if defined(__sun) && (defined(__SVR4) || defined(__svr4))
# define FT_OS_SOLARIS TRUE
#endif

/* === APPLE === */
#if defined(__APPLE__) && defined(__MACH__)
# define FT_OS_APPLE TRUE
# include <TargetConditionals.h>
# if TARGET_IPHONE_SIMULATOR == 1
# define FT_OS_APPLE_XCODE TRUE
# elif TARGET_OS_IPHONE == 1
# define FT_OS_APPLE_IOS TRUE
# elif TARGET_OS_MAC == 1
# define FT_OS_APPLE_OSX TRUE
# endif
#endif

/* === WINDOWS === */
#if defined(_WIN32)
# define FT_OS_WINDOWS TRUE
# define FT_OS_WINDOWS32 TRUE
#elif defined(_WIN64)
# define FT_OS_WINDOWS TRUE
# define FT_OS_WINDOWS64 TRUE
#endif

/* === CYGWIN === */
#if defined(__CYGWIN__)
# define FT_OS_CYGWIN TRUE
# if !defined(_WIN32)
#  define FT_OS_CYGWIN_POSIX TRUE
# endif
#endif

/* === MINGW === */
#if defined(__MINGW32__)
# define FT_OS_MINGW TRUE
# define FT_OS_MINGW32 TRUE
#elif defined(__MINGW64__)
# define FT_OS_MINGW TRUE
# define FT_OS_MINGW64 TRUE
#endif

/* === UNIX === */
#if !defined(_WIN32) && (defined(__unix__) || defined(__unix) || (defined(__APPLE__) && defined(__MACH__)))
# define FT_OS_UNIX TRUE
#endif

/* === POSIX === */
#if FT_OS_UNIX
#include <unistd.h>
#if defined(_POSIX_VERSION)
# define FT_OS_POSIX TRUE
#endif
#endif

/* === ANDROID === */
#if defined(__ANDROID__)
#define FT_OS_ANDROID FALSE
#endif

#endif

#if __INTELLISENSE__
#define FT_IDE_INTELLISENSE TRUE
#endif

#endif