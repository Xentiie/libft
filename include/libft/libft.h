/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 19:56:09 by reclaire          #+#    #+#             */
/*   Updated: 2025/04/14 20:07:54 by reclaire         ###   ########.fr       */
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

#include "libft/bits/os_defines.h"

#define _FT_PRIVATE_BITS
#include "libft/bits/private/no_globals.h"
#include "libft/bits/private/errno_location.h"

#include "libft/bits/private/builtins_defines.h"
#include "libft/bits/private/attributes_defines.h"

#include "libft/bits/private/intellisense.h" /* VSCode Intellisense fixs */
#undef _FT_PRIVATE_BITS

#include "libft/types.h"

_FT_GLOBAL_VAR_DEC(S32, ft_argc);
_FT_GLOBAL_VAR_DEC(string *, ft_argv);
_FT_GLOBAL_VAR_DEC(string *, ft_env);

#define ft_argc _FT_GLOBAL_VAR(ft_argc)
#define ft_argv _FT_GLOBAL_VAR(ft_argv)
#define ft_env _FT_GLOBAL_VAR(ft_env)

#define FT_OK 0		  /* No error */
#define FT_EOMEM 1	  /* Out of memory */
#define FT_EINVPTR 2  /* Invalid pointer */
#define FT_EINVVAL 3  /* Invalid value */
#define FT_EINVOP 4	  /* Invalid operation */
#define FT_ESYSCALL 5 /* System call failed */
#define FT_ENOENT 6	  /* No entries found */
#define FT_ERANGE 7	  /* Out of range */
#define FT_ENOINIT 8  /* Libft value not initialized */
#define FT_EOSPACE 9  /* Out of space */

#define UNLIKELY(cond) IF_PREDICT(cond, FALSE)
#define LIKELY(cond) IF_PREDICT(cond, TRUE)

#if !defined(_FT_GROWTH_FACTOR)
#define _FT_GROWTH_FACTOR 2
#endif

#if !defined(packed_enum)
#define packed_enum __attribute__((packed)) enum
#endif

/*
#include <stdio.h>
#define printf(...) do { printf("(%s:%d) ", __FILE__, __LINE__); printf(__VA_ARGS__); } while (0)
#define ft_printf(...) do { (printf)("(%s:%d) ", __FILE__, __LINE__); ft_printf(__VA_ARGS__); } while (0)
*/

#endif