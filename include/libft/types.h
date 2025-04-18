/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 19:47:30 by reclaire          #+#    #+#             */
/*   Updated: 2025/04/15 01:53:33 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(LIBFT_TYPES_H)
#define LIBFT_TYPES_H

#include "libft/bits/os_defines.h"

#if FT_OS_WINDOWS
//TODO: handle TLS for windows with MINGW
#define threadlocal
#else
#define threadlocal __thread
#endif

typedef unsigned char U8;
typedef unsigned short U16;
typedef unsigned int U32;
#if FT_OS_WINDOWS
typedef unsigned long long U64;
typedef unsigned long long LU64;
#else
typedef unsigned long U64;
typedef unsigned long long LU64;
#endif
typedef signed char S8;
typedef signed short S16;
typedef signed int S32;
#if FT_OS_WINDOWS
typedef signed long long S64;
typedef signed long long LS64;
#else
typedef signed long S64;
typedef signed long long LS64;
#endif
typedef float F32;
typedef double F64;
typedef long double LF64;

typedef char *string;
typedef char const *const_string;
typedef int *wstring;
typedef int const *const_wstring;
typedef int wchar;
typedef U8 bool;

#if FT_OS_WINDOWS
typedef void *filedesc;
#elif FT_OS_POSIX
typedef S32 filedesc;
#else
/* Leave `filedesc` undefined, will cause error, as we don't know what to define as filedesc */
#endif
typedef struct s_file t_file;

typedef struct s_v2
{
	F32 x, y;
} t_v2;

typedef struct s_v3
{
	union
	{
		struct
		{
			F32 x, y, z;
		};
		struct
		{
			t_v2 xy;
			F32 _z;
		};
	};
} t_v3;

typedef struct s_v4
{
	union
	{
		struct
		{
			F32 x, y, z, w;
		};
		struct
		{
			t_v2 xy;
			t_v2 zw;
		};
	};
} t_v4;

typedef struct s_iv2
{
	S32 x, y;
} t_iv2;

typedef struct s_iv3
{
	union
	{
		struct
		{
			S32 x, y, z;
		};
		struct
		{
			t_iv2 xy;
			S32 _z;
		};
	};
} t_iv3;

typedef struct s_iv4
{
	union
	{
		struct
		{
			S32 x, y, z, w;
		};
		struct
		{
			t_iv2 xy;
			t_iv2 zw;
		};
	};
} t_iv4;

typedef struct s_mat4x4
{
	F32 m00, m10, m20, m30;
	F32 m01, m11, m21, m31;
	F32 m02, m12, m22, m32;
	F32 m03, m13, m23, m33;
} t_mat4x4;

typedef struct s_mat2x2
{
	F32 m[2][2];
} t_mat22;

typedef float xmm __attribute__((vector_size(16), may_alias));
typedef float ymm __attribute__((vector_size(32), may_alias));

#endif