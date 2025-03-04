/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 19:56:09 by reclaire          #+#    #+#             */
/*   Updated: 2025/03/04 23:48:51 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(FT_LIBFT_H)
#define FT_LIBFT_H

/*
-D _FT_ERRNO_LOCATION -> replace global variable ft_errno by the macro (*__ft_errno_location())
-D _FT_NO_IF_PREDICT -> disables branch prediction
-D _FT_RETURN -> exposes FT_RET_OK and FT_RET_ERR macros
-D _FT_AVOID_ALLOCA -> replace ft_alloca/ft_afree by malloc/free
-D _FT_NO_GLOBALS=1 -> replaces globals by getters/setters
-D _FT_GROWTH_FACTOR -> sets growth factor for stack
*/

#define _FT_ERRNO_LOCATION
#if !defined(_FT_NO_GLOBALS)
#define _FT_NO_GLOBALS 1
#endif

#include "_os.h"
#include "types.h"

#ifdef __has_builtin
#define FT_HAS_BUILTIN(x) __has_builtin(x)
#else
#pragma warn "No FT_HAS_BUILTIN"
#define FT_HAS_BUILTIN(x) FALSE
#endif

#ifdef __has_attribute
#define FT_HAS_ATTRIBUTE(x) __has_attribute(x)
#else
#pragma warn "No FT_HAS_ATTRIBUTE"
#define FT_HAS_ATTRIBUTE(x) FALSE
#endif

#if defined(_FT_NO_GLOBALS) && _FT_NO_GLOBALS
#define _FT_GLOBAL_VAR_DEC(type, name) type *__global_##name();
#define _FT_GLOBAL_VAR_DEF(type, name, ...)                                              \
	type *__global_##name()                                                               \
	{                                                                                    \
		static type __##name __VA_OPT__(= __VA_ARGS__);                                      \
		return &__##name;                                                                    \
	}
#define _FT_GLOBAL_VAR(name) (*(__global_##name()))
#else
#define _FT_GLOBAL_VAR_DEC(type, name)		extern type name;
#define _FT_GLOBAL_VAR_DEF(type, name, ...) type name __VA_OPT__(= __VA_ARGS__);
#define _FT_GLOBAL_VAR(name) (name)
#endif

_FT_GLOBAL_VAR_DEC(S32, ft_argc);
_FT_GLOBAL_VAR_DEC(string *, ft_argv);
_FT_GLOBAL_VAR_DEC(string *, ft_env);

#define ft_argc _FT_GLOBAL_VAR(ft_argc)
#define ft_argv _FT_GLOBAL_VAR(ft_argv)
#define ft_env _FT_GLOBAL_VAR(ft_env)

#define FT_INIT_ARGV(argc, argv, env)                                                    \
	ft_argc = argc;                                                                      \
	ft_argv = argv;                                                                      \
	ft_env = env;

/*Error code returned by some ft functions*/
//#define _FT_ERRNO_LOCATION /* TODO: */
#if defined(_FT_ERRNO_LOCATION)
S32 *__ft_errno_location();
#define ft_errno (*__ft_errno_location())
#else
extern __thread S32 ft_errno;
#endif

#define FT_OK		0 /* No error */
#define FT_EOMEM	1 /* Out of memory */
#define FT_EINVPTR	2 /* Invalid pointer */
#define FT_EINVVAL	3 /* Invalid value */
#define FT_EINVOP	4 /* Invalid operation */
#define FT_ESYSCALL 5 /* System call failed */
#define FT_ENOENT	6 /* No entries found */
#define FT_ERANGE	7 /* Out of range */
#define FT_ENOINIT	8 /* Libft value not initialized */
#define FT_EOSPACE	9 /* Out of space */

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

//#define _FT_NO_IF_PREDICT
#if !FT_HAS_BUILTIN(__builtin_expect) || defined(_FT_NO_IF_PREDICT)
#if !defined(_FT_NO_IF_PREDICT)
#pragma warn "No IF_PREDICT"
#endif
#define IF_PREDICT(cond, expect)   (cond)
#define IF_PREDICT_B(cond, expect) (cond)
#else
#define IF_PREDICT(cond, expect)   __builtin_expect((cond), expect)
#define IF_PREDICT_B(cond, expect) __builtin_expect(!!(cond), expect)
#endif
#define UNLIKELY(cond) IF_PREDICT(cond, FALSE)
#define LIKELY(cond)   IF_PREDICT(cond, TRUE)

// clang-format off
#if defined(_FT_RETURN)
# define FT_RET_OK(ret) do { ft_errno=FT_OK; return ret; } while (0)
# if defined(DEBUG)
#  include "libft/debug.h"
#  define FT_RET_ERR(ret, err) do { ft_errno = err ; ft_debug_break(); return ret; } while (0)
# else
#  define FT_RET_ERR(ret, err) do { ft_errno = err ; return ret; } while (0)
# endif
#endif
// clang-format on

// clang-format off
#if !defined(_FT_AVOID_ALLOCA)
# if defined(FT_OS_WIN) || defined(FT_OS_WIN_WSL)
#  include <malloc.h>
# else
#  include <alloca.h>
# endif
# define ft_alloca(...) alloca(__VA_ARGS__)
# define ft_afree(...)
#else
# define ft_alloca(...) malloc(__VA_ARGS__)
# define ft_afree(...) free(__VA_ARGS__)
#endif
// clang-format on

#if !defined(_FT_GROWTH_FACTOR)
#define _FT_GROWTH_FACTOR 2
#endif

/*
#include <stdio.h>
#define printf(...) do { printf("(%s:%d) ", __FILE__, __LINE__); printf(__VA_ARGS__); } while (0)
#define ft_printf(...) do { (printf)("(%s:%d) ", __FILE__, __LINE__); ft_printf(__VA_ARGS__); } while (0)
*/

#endif