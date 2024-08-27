/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _libft.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 19:56:09 by reclaire          #+#    #+#             */
/*   Updated: 2024/08/15 23:55:04 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _LIBFT_H
# define _LIBFT_H

/*
#define LIBFT_AVOID_ALLOCA -> replace alloca by malloc/free

*/

# if defined(FT_OS_UNKNOWN) || (!defined(FT_OS_WIN) && !defined(FT_APPLE) && !defined(FT_OS_LINUX))

#  if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#   define FT_OS_WIN
#   define WIN32_LEAN_AND_MEAN 
#   ifdef _WIN64
#    define FT_OS_WIN64 
#   else
#    define FT_OS_WIN32
#   endif

#  elif __APPLE__
#   define FT_APPLE
#   include <TargetConditionals.h>
#   if TARGET_IPHONE_SIMULATOR
#    define FT_APPLE_SIM
#   elif TARGET_OS_MACCATALYST
#    define FT_APPLE_MACCATALYST
#   elif TARGET_OS_IPHONE
#    define FT_APPLE_IOS
#   elif TARGET_OS_MAC
#    define FT_APPLE_OSX
#   else
#    error "Unknown Apple platform"
#   endif

#  elif __ANDROID__
#   define FT_ANDROID
#  elif __linux__
#   define FT_OS_LINUX
#  elif __unix__
#   define FT_UNIX
#  elif defined(_POSIX_VERSION)
#   define FT_POSIX
#  else
#   error "Unknown compiler"
#  endif

# endif

# include "./types.h"

extern	int				ft_argc;
extern	const_string	*ft_argv;
extern	const_string	*ft_env;
# define FT_INIT_ARGV(argc, argv, env) ft_argc=argc;ft_argv=argv;ft_env=env;

/*Error code returned by some ft functions*/
extern	S32		ft_errno;
# define FT_OK				0	/* No error */
# define FT_EOMEM			1	/* Out of memory */
# define FT_EINVPTR			2	/* Invalid pointer */
# define FT_EINVVAL			3	/* Invalid value */
# define FT_EINVOP			4	/* Invalid operation */
# define FT_ESYSCALL		5	/* System call failed */
# define FT_ENOENT			6	/* No entries found */
# define FT_ERANGE			7	/* Out of range */
# define FT_ENOINIT			8	/* Libft value not initialized */
# define FT_EOSPACE			9	/* Out of space */

# define FUNCTION_HOT __attribute__((hot))
# define FUNCTION_COLD __attribute__((cold))

# define IF_PREDICT(cond, expect) __builtin_expect((cond), expect)
# define IF_PREDICT_B(cond, expect) __builtin_expect(!!(cond), expect)
#define UNLIKELY(cond) IF_PREDICT(cond, FALSE)
#define LIKELY(cond) IF_PREDICT(cond, TRUE)
//#define UNLIKELY(cond) (cond)
//#define LIKELY(cond) (cond)

#endif