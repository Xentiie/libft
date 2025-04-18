/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   os_defines.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 16:16:11 by reclaire          #+#    #+#             */
/*   Updated: 2025/04/15 02:15:28 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(FT_BITS_OS_DEFINES_H)
#define FT_BITS_OS_DEFINES_H

/*
https://web.archive.org/web/20140625123925/http://nadeausoftware.com/articles/2012/01/c_c_tip_how_use_compiler_predefined_macros_detect_operating_system
*/

#include "libft/bits/bool_defines.h"

// clang-format off
/* === DEFAULT CONFIG === */
/* Any Linux */
#undef FT_OS_LINUX
#define FT_OS_LINUX FALSE

/* Any BSD */
#undef FT_OS_BSD
#define FT_OS_BSD FALSE
/* DragonFly BSD */
#undef FT_OS_BSD_DRAGONFLY
#define FT_OS_BSD_DRAGONFLY FALSE
/* FreeBSD */
#undef FT_OS_BSD_FREEBSD
#define FT_OS_BSD_FREEBSD FALSE
/* NetBSD */
#undef FT_OS_BSD_NETBSD
#define FT_OS_BSD_NETBSD FALSE
/* OpenBSD */
#undef FT_OS_BSD_OPENBSD
#define FT_OS_BSD_OPENBSD FALSE

/* Solaris */
#undef FT_OS_SOLARIS
#define FT_OS_SOLARIS FALSE

/* Any Apple */
#undef FT_OS_APPLE
#define FT_OS_APPLE FALSE
/* Xcode simulator */
#undef FT_OS_APPLE_XCODE
#define FT_OS_APPLE_XCODE FALSE
/* IOS device */
#undef FT_OS_APPLE_IOS
#define FT_OS_APPLE_IOS FALSE
/* OSX device */
#undef FT_OS_APPLE_OSX
#define FT_OS_APPLE_OSX FALSE

/* Any Windows */
#undef FT_OS_WINDOWS
#define FT_OS_WINDOWS FALSE
/* 32 bits Windows */
#undef FT_OS_WINDOWS32
#define FT_OS_WINDOWS32 FALSE
/* 64 bits Windows */
#undef FT_OS_WINDOWS64
#define FT_OS_WINDOWS64 FALSE

/* Cygwin */
#undef FT_OS_CYGWIN
#define FT_OS_CYGWIN FALSE
/* Cygwin POSIX */
#undef FT_OS_CYGWIN_POSIX
#define FT_OS_CYGWIN_POSIX FALSE

/* MingW */
#undef FT_OS_MINGW
#define FT_OS_MINGW FALSE
/* 32 bits MingW */
#undef FT_OS_MINGW32
#define FT_OS_MINGW32 FALSE
/* 64 bits MingW */
#undef FT_OS_MINGW64
#define FT_OS_MINGW64 FALSE

/* Unix */
#undef FT_OS_UNIX
#define FT_OS_UNIX FALSE

/* Posix */
#undef FT_OS_POSIX
#define FT_OS_POSIX FALSE

/* Android */
#undef FT_OS_ANDROID
#define FT_OS_ANDROID FALSE

/* IDE */
#undef FT_IDE_INTELLISENSE
#define FT_IDE_INTELLISENSE FALSE

/* === LINUX === */
#if defined(__linux__)
# undef FT_OS_LINUX
# undef FT_OS_LINUX
# define FT_OS_LINUX TRUE
#endif

/* === BSD === */
#if defined(__unix__) || (defined(__APPLE__) && defined(__MACH__))
# include <sys/param.h>
# if defined(BSD)
#  undef FT_OS_BSD
#  define FT_OS_BSD TRUE
#  if defined(__DragonFly__)
#   undef FT_OS_BSD_DRAGONFLY
#   define FT_OS_BSD_DRAGONFLY TRUE
#  endif
#  if defined(__FreeBSD__)
#   undef FT_OS_BSD_FREEBSD
#   define FT_OS_BSD_FREEBSD TRUE
#  endif
#  if defined(__NetBSD__)
#   undef FT_OS_BSD_NETBSD
#   define FT_OS_BSD_NETBSD TRUE
#  endif
#  if defined(__OpenBSD__)
#   undef FT_OS_BSD_OPENBSD
#   define FT_OS_BSD_OPENBSD TRUE
#  endif
# endif
#endif

/* === SOLARIS === */
#if defined(__sun) && (defined(__SVR4) || defined(__svr4))
# undef FT_OS_SOLARIS
# define FT_OS_SOLARIS TRUE
#endif

/* === APPLE === */
#if defined(__APPLE__) && defined(__MACH__)
# undef FT_OS_APPLE
# define FT_OS_APPLE TRUE
# include <TargetConditionals.h>
# if TARGET_IPHONE_SIMULATOR == 1
# undef FT_OS_APPLE_XCODE
# define FT_OS_APPLE_XCODE TRUE
# elif TARGET_OS_IPHONE == 1
# undef FT_OS_APPLE_IOS
# define FT_OS_APPLE_IOS TRUE
# elif TARGET_OS_MAC == 1
# undef FT_OS_APPLE_OSX
# define FT_OS_APPLE_OSX TRUE
# endif
#endif

/* === WINDOWS === */
#if defined(_WIN32)
# undef FT_OS_WINDOWS
# define FT_OS_WINDOWS TRUE
# undef FT_OS_WINDOWS32
# define FT_OS_WINDOWS32 TRUE
#elif defined(_WIN64)
# undef FT_OS_WINDOWS
# define FT_OS_WINDOWS TRUE
# undef FT_OS_WINDOWS64
# define FT_OS_WINDOWS64 TRUE
#endif

/* === CYGWIN === */
#if defined(__CYGWIN__)
# undef FT_OS_CYGWIN
# define FT_OS_CYGWIN TRUE
# if !defined(_WIN32)
#  undef FT_OS_CYGWIN_POSIX
#  define FT_OS_CYGWIN_POSIX TRUE
# endif
#endif

/* === MINGW === */
#if defined(__MINGW32__)
# undef FT_OS_MINGW
# define FT_OS_MINGW TRUE
# undef FT_OS_MINGW32
# define FT_OS_MINGW32 TRUE
#elif defined(__MINGW64__)
# undef FT_OS_MINGW
# define FT_OS_MINGW TRUE
# undef FT_OS_MINGW64
# define FT_OS_MINGW64 TRUE
#endif

/* === UNIX === */
#if !defined(_WIN32) && (defined(__unix__) || defined(__unix) || (defined(__APPLE__) && defined(__MACH__)))
# undef FT_OS_UNIX
# define FT_OS_UNIX TRUE
#endif

/* === POSIX === */
#if FT_OS_UNIX
#include <unistd.h>
#if defined(_POSIX_VERSION)
# undef FT_OS_POSIX
# define FT_OS_POSIX TRUE
#endif
#endif

/* === ANDROID === */
#if defined(__ANDROID__)
#undef FT_OS_ANDROID
#define FT_OS_ANDROID FALSE
#endif

#else /*  */
#endif

#if __INTELLISENSE__
#undef FT_IDE_INTELLISENSE
#define FT_IDE_INTELLISENSE TRUE
#endif

// clang-format on
