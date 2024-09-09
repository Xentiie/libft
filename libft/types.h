/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 19:47:30 by reclaire          #+#    #+#             */
/*   Updated: 2024/09/05 04:00:22 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_TYPES_H
#define LIBFT_TYPES_H

#include "_os.h"

#ifndef NULL
#define NULL ((void *)0)
#endif

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifndef LOCALHOST
#define LOCALHOST "localhost"
#endif

typedef unsigned char U8;
typedef unsigned short U16;
typedef unsigned int U32;
#ifdef FT_OS_WIN
typedef unsigned long long U64;
typedef unsigned long long LU64;
#else
typedef unsigned long U64;
typedef unsigned long long LU64;
#endif
typedef signed char S8;
typedef signed short S16;
typedef signed int S32;
#ifdef FT_OS_WIN
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

#if defined(FT_OS_WIN)
typedef void *file;
#elif defined(FT_OS_LINUX) || defined(FT_OS_MAC)
typedef S32 file;
#endif

typedef F32 __attribute__((vector_size(sizeof(F32) * 2))) v2f;
typedef F32 __attribute__((vector_size(sizeof(F32) * 4))) v3f;
typedef F32 __attribute__((vector_size(sizeof(F32) * 4))) v4f;
typedef S32 __attribute__((vector_size(sizeof(S32) * 2))) v2i;
typedef S32 __attribute__((vector_size(sizeof(S32) * 4))) v3i;
typedef S32 __attribute__((vector_size(sizeof(S32) * 4))) v4i;

typedef union
{
	/* Raw vector value (can be used with operators, compiles to 'SIMD' instructions) */
	v2f v;
	/* Accessors */
	struct
	{
		F32 x;
		F32 y;
	};
} t_v2;

typedef union
{
	/* Raw vector value (can be used with operators, compiles to 'SIMD' instructions) */
	v3f v;
	/* Accessors */
	struct
	{
		F32 x;
		F32 y;
		F32 z;
	};
} t_v3;

typedef union
{
	/* Raw vector value (can be used with operators, compiles to 'SIMD' instructions) */
	v4f v;
	/* Accessors */
	struct
	{
		F32 x;
		F32 y;
		F32 z;
		F32 w;
	};
} t_v4;

typedef union
{
	/* Raw vector value (can be used with operators, compiles to 'SIMD' instructions) */
	v2i v;
	/* Accessors */
	struct
	{
		S32 x;
		S32 y;
	};
} t_iv2;

typedef union
{
	/* Raw vector value (can be used with operators, compiles to 'SIMD' instructions) */
	v3i v;
	/* Accessors */
	struct
	{
		S32 x;
		S32 y;
		S32 z;
	};
} t_iv3;

typedef union
{
	/* Raw vector value (can be used with operators, compiles to 'SIMD' instructions) */
	v4i v;
	/* Accessors */
	struct
	{
		S32 x;
		S32 y;
		S32 z;
		S32 w;
	};
} t_iv4;

typedef struct s_mat4x4
{
	F32 m_r0c0, m_r1c0, m_r2c0, m_r3c0;
	F32 m_r0c1, m_r1c1, m_r2c1, m_r3c1;
	F32 m_r0c2, m_r1c2, m_r2c2, m_r3c2;
	F32 m_r0c3, m_r1c3, m_r2c3, m_r3c3;
} t_mat4x4;

#endif