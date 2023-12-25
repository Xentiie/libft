/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 15:07:15 by reclaire          #+#    #+#             */
/*   Updated: 2023/09/26 14:58:28 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
#define LIBFT_H

#include <unistd.h>
#include <time.h>
#include <math.h>
#include <limits.h>
#include <float.h>
#include <signal.h>
#include "libft_macros.h"

#define TRUE 1
#define FALSE 0

#define NULLABLE

typedef unsigned char		U8;
typedef unsigned short		U16;
typedef unsigned int 		U32;
typedef unsigned long long	U64;
typedef signed char			S8;
typedef signed short		S16;
typedef signed int			S32;
typedef signed long long	S64;
typedef float				F32;
typedef double				F64;

#define U8_MAX  UCHAR_MAX
#define U8_MIN  0
#define U16_MAX USHRT_MAX
#define U16_MIN 0
#define U32_MAX UINT_MAX
#define U32_MIN 0
#define U64_MAX ULLONG_MAX
#define U64_MIN 0ULL
#define S8_MAX  SCHAR_MAX
#define S8_MIN  SCHAR_MIN
#define S16_MAX SHRT_MAX
#define S16_MIN SHRT_MIN
#define S32_MAX INT_MAX
#define S32_MIN INT_MIN
#define S64_MAX LLONG_MAX
#define S64_MIN LLONG_MIN
#define F32_MAX FLT_MAX
#define F32_MIN FLT_MIN
#define F64_MAX DBL_MAX
#define F64_MIN DBL_MIN

typedef S32					file;
typedef U8					bool;
typedef char				*string;
typedef char const			*const_string;
typedef S32					t_error_code;

#include <stddef.h>
#include <stdlib.h>

//COLORS
#define FT_BLACK "\e[0;30m"
#define FT_RED "\e[0;31m"
#define FT_GREEN "\e[0;32m"
#define FT_YELLOW "\e[0;33m"
#define FT_BLUE "\e[0;34m"
#define FT_MAGENTA "\e[0;35m"
#define FT_CYAN "\e[0;36m"
#define FT_WHITE "\e[0;37m"
#define FT_DEFAULT "\e[0;39m"

#define FT_LBLACK "\e[0;90m"
#define FT_LRED "\e[0;91m"
#define FT_LGREEN "\e[0;92m"
#define FT_LYELLOW "\e[0;93m"
#define FT_LBLUE "\e[0;94m"
#define FT_LMAGENTA "\e[0;95m"
#define FT_LCYAN "\e[0;96m"
#define FT_LWHITE "\e[0;97m"
#define FT_LDEFAULT "\e[0;99m"

#define FT_BG_BLACK "\e[0;40m"
#define FT_BG_RED "\e[0;41m"
#define FT_BG_GREEN "\e[0;42m"
#define FT_BG_YELLOW "\e[0;43m"
#define FT_BG_BLUE "\e[0;44m"
#define FT_BG_MAGENTA "\e[0;45m"
#define FT_BG_CYAN "\e[0;46m"
#define FT_BG_WHITE "\e[0;47m"
#define FT_BG_DEFAULT "\e[0;49m"

#define FT_BG_LBLACK "\e[0;100m"
#define FT_BG_LRED "\e[0;101m"
#define FT_BG_LGREEN "\e[0;102m"
#define FT_BG_LYELLOW "\e[0;103m"
#define FT_BG_LBLUE "\e[0;104m"
#define FT_BG_LMAGENTA "\e[0;105m"
#define FT_BG_LCYAN "\e[0;106m"
#define FT_BG_LWHITE "\e[0;107m"
#define FT_BG_LDEFAULT "\e[0;109m"

#define FT_BOLD "\e[1m"
#define FT_DIM "\e[2m"
#define FT_ITALIC "\e[3m"
#define FT_UNDERLINE "\e[4m"
#define FT_BLINK "\e[5m"
#define FT_INVERSE "\e[7m"
#define FT_INVISIBLE "\e[8m"
#define FT_STRIKETHROUGH "\e[9m"

//Reset
#define FT_CRESET "\e[0m"
#define FT_COLOR_RESET "\e[0m"
//COLORS


// DEBUG
bool	ft_is_debugger();
#define FT_DB_BREAK raise(SIGTRAP)

#ifdef MEMCHECK
extern void	*_malloc(U64 size, char *file, int line);
extern void	_free(void *p, char *file, int line);
extern bool	ft_check_leaks();
#  ifndef __MEMCHECK
#    define __MEMCHECK
#    define malloc(X)	_malloc(X, __FILE__, __LINE__)
#    define free(X)		_free(X, __FILE__, __LINE__)
#  endif
#endif
// DEBUG

// TIMERS
/* Machine-independent time format */
typedef struct s_time
{
	long seconds;		/* Time in whole seconds */
	long nanoseconds;	/* Sub-seconds in nanoseconds */
} t_time;

typedef struct s_clock
{
	t_time t1;			/* Start time */
	t_time t2;			/* Stop time */
	char buffer[24];	/* Buffer for formatting elapsed time */
} t_clock;

extern void		clk_diff(t_time *t1, t_time *t2, long *sec, long *nsec);
extern void		clk_init(t_clock *clk);
extern void		clk_start(t_clock *clk);
extern void		clk_stop(t_clock *clk);

/* Deprecated */
__attribute_deprecated__ extern char	*clk_elapsed_ms(t_clock *clk, char *buffer, U64 buflen);
__attribute_deprecated__ extern char	*clk_elapsed_us(t_clock *clk, char *buffer, U64 buflen);
__attribute_deprecated__ extern char	*clk_elapsed_ns(t_clock *clk, char *buffer, U64 buflen);

#ifndef TIMER_VERSION_1
/* Preferred */
extern char		*clk_fmt_elapsed_ms(t_clock *clk);
extern char		*clk_fmt_elapsed_us(t_clock *clk);
extern char		*clk_fmt_elapsed_ns(t_clock *clk);
extern char		*clk_fmt_elapsed_str(t_clock *clk);
extern double	clk_fmt_elapsed_dbl(t_clock *clk);
#endif /* !TIMER_VERSION_1 */
// TIMERS

// VECTORS
typedef struct s_v2		{ float x, y; }			t_v2;
typedef struct s_v3		{ float x, y, z; }		t_v3;
typedef struct s_v4		{ float x, y, z, w; }	t_v4;
typedef struct s_iv2	{ int x, y; }			t_iv2;
typedef struct s_iv3	{ int x, y, z; }		t_iv3;
typedef struct s_iv4	{ int x, y, z, w; }		t_iv4;

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunknown-pragmas"
#pragma region CONSTRUCTORS

extern t_v2 _v2_iv2(t_iv2 v);
extern t_v2 _v2_iv3(t_iv3 v);
extern t_v2 _v2_iv4(t_iv4 v);
extern t_v2 _v2_v4(t_v4 v);
extern t_v2 _v2_v3(t_v3 v);
extern t_v2 _v2_float(float x);
extern t_v2 _v2_float_float(float x, float y);

extern t_v3 _v3_iv2(t_iv2 v);
extern t_v3 _v3_iv3(t_iv3 v);
extern t_v3 _v3_iv4(t_iv4 v);
extern t_v3 _v3_v4(t_v4 v);
extern t_v3 _v3_v2(t_v2 v);
extern t_v3 _v3_float(float x);
extern t_v3 _v3_float_float(float x, float y);
extern t_v3 _v3_float_float_float(float x, float y, float z);
extern t_v3 _v3_v2_float(t_v2 v, float z);
extern t_v3 _v3_float_v2(float x, t_v2 v);

extern t_v4 _v4_iv2(t_iv2 v);
extern t_v4 _v4_iv3(t_iv3 v);
extern t_v4 _v4_iv4(t_iv4 v);
extern t_v4 _v4_v3(t_v3 v);
extern t_v4 _v4_v2(t_v2 v);
extern t_v4 _v4_float(float x);
extern t_v4 _v4_float_float(float x, float y);
extern t_v4 _v4_float_float_float(float x, float y, float z);
extern t_v4 _v4_float_float_float_float(float x, float y, float z, float w);
extern t_v4 _v4_float_v3(float x, t_v3 v);
extern t_v4 _v4_v3_float(t_v3 v, float w);
extern t_v4 _v4_v2_v2(t_v2 xy, t_v2 zw);
extern t_v4 _v4_float_v2_float(float x, t_v2 v, float w);
extern t_v4 _v4_float_float_v2(float x, float y, t_v2 v);
extern t_v4 _v4_v2_float_float(t_v2 v, float z, float w);

extern t_iv2 _iv2_v2(t_v2 v);
extern t_iv2 _iv2_v3(t_v3 v);
extern t_iv2 _iv2_v4(t_v4 v);
extern t_iv2 _iv2_iv4(t_iv4 v);
extern t_iv2 _iv2_iv3(t_iv3 v);
extern t_iv2 _iv2_int(int x);
extern t_iv2 _iv2_int_int(int x, int y);

extern t_iv3 _iv3_v2(t_v2 v);
extern t_iv3 _iv3_v3(t_v3 v);
extern t_iv3 _iv3_v4(t_v4 v);
extern t_iv3 _iv3_iv4(t_iv4 v);
extern t_iv3 _iv3_iv2(t_iv2 v);
extern t_iv3 _iv3_int(int x);
extern t_iv3 _iv3_int_int(int x, int y);
extern t_iv3 _iv3_int_int_int(int x, int y, int z);
extern t_iv3 _iv3_iv2_int(t_iv2 v, int z);
extern t_iv3 _iv3_int_iv2(int x, t_iv2 v);

extern t_iv4 _iv4_v2(t_v2 v);
extern t_iv4 _iv4_v3(t_v3 v);
extern t_iv4 _iv4_v4(t_v4 v);
extern t_iv4 _iv4_iv3(t_iv3 v);
extern t_iv4 _iv4_iv2(t_iv2 v);
extern t_iv4 _iv4_int(int x);
extern t_iv4 _iv4_int_int(int x, int y);
extern t_iv4 _iv4_int_int_int(int x, int y, int z);
extern t_iv4 _iv4_int_int_int_int(int x, int y, int z, int w);
extern t_iv4 _iv4_int_iv3(int x, t_iv3 v);
extern t_iv4 _iv4_iv3_int(t_iv3 v, int w);
extern t_iv4 _iv4_iv2_iv2(t_iv2 xy, t_iv2 zw);
extern t_iv4 _iv4_int_iv2_int(int x, t_iv2 v, int w);
extern t_iv4 _iv4_int_int_iv2(int x, int y, t_iv2 v);
extern t_iv4 _iv4_iv2_int_int(t_iv2 v, int z, int w);

#define vec2(...)																							\
	_Generic(FT_MACRO_GROUP_TYPE_INST(__VA_ARGS__),															\
		FT_MACRO_GROUP_TYPE(t_iv2):								_v2_iv2,									\
		FT_MACRO_GROUP_TYPE(t_iv3):								_v2_iv3,									\
		FT_MACRO_GROUP_TYPE(t_iv4):								_v2_iv4,									\
		FT_MACRO_GROUP_TYPE(t_v3):								_v2_v3,										\
		FT_MACRO_GROUP_TYPE(t_v4):								_v2_v4,										\
																											\
		FT_MACRO_GROUP_TYPE(float):								_v2_float,									\
		FT_MACRO_GROUP_TYPE(float, float):						_v2_float_float,							\
		FT_MACRO_GROUP_TYPE(double):							_v2_float,									\
		FT_MACRO_GROUP_TYPE(double, double):					_v2_float_float,							\
		FT_MACRO_GROUP_TYPE(int):								_v2_float,									\
		FT_MACRO_GROUP_TYPE(int, int):							_v2_float_float								\
		)(__VA_ARGS__)

#define vec3(...)																							\
	_Generic(FT_MACRO_GROUP_TYPE_INST(__VA_ARGS__),															\
		FT_MACRO_GROUP_TYPE(t_iv2):								_v3_iv2,									\
		FT_MACRO_GROUP_TYPE(t_iv3):								_v3_iv3,									\
		FT_MACRO_GROUP_TYPE(t_iv4):								_v3_iv4,									\
		FT_MACRO_GROUP_TYPE(t_v2):								_v3_v2,										\
		FT_MACRO_GROUP_TYPE(t_v4):								_v3_v4,										\
																											\
		FT_MACRO_GROUP_TYPE(float):								_v3_float,									\
		FT_MACRO_GROUP_TYPE(float, float):						_v3_float_float,							\
		FT_MACRO_GROUP_TYPE(float, float, float):				_v3_float_float_float,						\
		FT_MACRO_GROUP_TYPE(double):							_v3_float,									\
		FT_MACRO_GROUP_TYPE(double, double):					_v3_float_float,							\
		FT_MACRO_GROUP_TYPE(double, double, double):			_v3_float_float_float,						\
		FT_MACRO_GROUP_TYPE(int):								_v3_float,									\
		FT_MACRO_GROUP_TYPE(int, int):							_v3_float_float,							\
		FT_MACRO_GROUP_TYPE(int, int, int):						_v3_float_float_float,						\
																											\
																											\
		FT_MACRO_GROUP_TYPE(t_v2, float):						_v3_v2_float,								\
		FT_MACRO_GROUP_TYPE(float, t_v2):						_v3_float_v2,								\
																											\
		FT_MACRO_GROUP_TYPE(t_v2, double):						_v3_v2_float,								\
		FT_MACRO_GROUP_TYPE(double, t_v2):						_v3_float_v2,								\
																											\
		FT_MACRO_GROUP_TYPE(t_v2, int):							_v3_v2_float,								\
		FT_MACRO_GROUP_TYPE(int, t_v2):							_v3_float_v2								\
		)(__VA_ARGS__)

#define vec4(...)																							\
	_Generic(FT_MACRO_GROUP_TYPE_INST(__VA_ARGS__),															\
		FT_MACRO_GROUP_TYPE(t_iv2):								_v4_iv2,									\
		FT_MACRO_GROUP_TYPE(t_iv3):								_v4_iv3,									\
		FT_MACRO_GROUP_TYPE(t_iv4):								_v4_iv4,									\
		FT_MACRO_GROUP_TYPE(t_v2):								_v4_v2,										\
		FT_MACRO_GROUP_TYPE(t_v3):								_v4_v3,										\
																											\
		FT_MACRO_GROUP_TYPE(float):								_v4_float,									\
		FT_MACRO_GROUP_TYPE(float, float):						_v4_float_float,							\
		FT_MACRO_GROUP_TYPE(float, float, float):				_v4_float_float_float,						\
		FT_MACRO_GROUP_TYPE(float, float, float, float):		_v4_float_float_float_float,				\
		FT_MACRO_GROUP_TYPE(double):							_v4_float,									\
		FT_MACRO_GROUP_TYPE(double, double):					_v4_float_float,							\
		FT_MACRO_GROUP_TYPE(double, double, double):			_v4_float_float_float,						\
		FT_MACRO_GROUP_TYPE(double, double, double, double):	_v4_float_float_float_float,				\
		FT_MACRO_GROUP_TYPE(int):								_v4_float,									\
		FT_MACRO_GROUP_TYPE(int, int):							_v4_float_float,							\
		FT_MACRO_GROUP_TYPE(int, int, int):						_v4_float_float_float,						\
		FT_MACRO_GROUP_TYPE(int, int, int, int):				_v4_float_float_float_float,				\
																											\
		FT_MACRO_GROUP_TYPE(t_v2, t_v2):						_v4_v2_v2,									\
																											\
		FT_MACRO_GROUP_TYPE(float, t_v3):						_v4_float_v3,								\
		FT_MACRO_GROUP_TYPE(t_v3, float):						_v4_v3_float,								\
		FT_MACRO_GROUP_TYPE(float, t_v2, float):				_v4_float_v2_float,							\
		FT_MACRO_GROUP_TYPE(float, float, t_v2):				_v4_float_float_v2,							\
		FT_MACRO_GROUP_TYPE(t_v2, float, float):				_v4_v2_float_float,							\
																											\
		FT_MACRO_GROUP_TYPE(double, t_v3):						_v4_float_v3,								\
		FT_MACRO_GROUP_TYPE(t_v3, double):						_v4_v3_float,								\
		FT_MACRO_GROUP_TYPE(double, t_v2, double):				_v4_float_v2_float,							\
		FT_MACRO_GROUP_TYPE(double, double, t_v2):				_v4_float_float_v2,							\
		FT_MACRO_GROUP_TYPE(t_v2, double, double):				_v4_v2_float_float,							\
																											\
		FT_MACRO_GROUP_TYPE(int, t_v3):							_v4_float_v3,								\
		FT_MACRO_GROUP_TYPE(t_v3, int):							_v4_v3_float,								\
		FT_MACRO_GROUP_TYPE(int, t_v2, int):					_v4_float_v2_float,							\
		FT_MACRO_GROUP_TYPE(int, int, t_v2):					_v4_float_float_v2,							\
		FT_MACRO_GROUP_TYPE(t_v2, int, int):					_v4_v2_float_float							\
		)(__VA_ARGS__)



#define ivec2(...)																							\
	_Generic(FT_MACRO_GROUP_TYPE_INST(__VA_ARGS__),															\
		FT_MACRO_GROUP_TYPE(t_v2):								_iv2_v2,									\
		FT_MACRO_GROUP_TYPE(t_v3):								_iv2_v3,									\
		FT_MACRO_GROUP_TYPE(t_v4):								_iv2_v4,									\
		FT_MACRO_GROUP_TYPE(t_iv3):								_iv2_iv3,									\
		FT_MACRO_GROUP_TYPE(t_iv4):								_iv2_iv4,									\
																											\
		FT_MACRO_GROUP_TYPE(float):								_iv2_int,									\
		FT_MACRO_GROUP_TYPE(float, float):						_iv2_int_int,								\
		FT_MACRO_GROUP_TYPE(double):							_iv2_int,									\
		FT_MACRO_GROUP_TYPE(double, double):					_iv2_int_int,								\
		FT_MACRO_GROUP_TYPE(int):								_iv2_int,									\
		FT_MACRO_GROUP_TYPE(int, int):							_iv2_int_int								\
		)(__VA_ARGS__)

#define ivec3(...)																							\
	_Generic(FT_MACRO_GROUP_TYPE_INST(__VA_ARGS__),															\
		FT_MACRO_GROUP_TYPE(t_v2):								_iv3_v2,									\
		FT_MACRO_GROUP_TYPE(t_v3):								_iv3_v3,									\
		FT_MACRO_GROUP_TYPE(t_v4):								_iv3_v4,									\
		FT_MACRO_GROUP_TYPE(t_iv2):								_iv3_iv2,									\
		FT_MACRO_GROUP_TYPE(t_iv4):								_iv3_iv4,									\
																											\
		FT_MACRO_GROUP_TYPE(float):								_iv3_int,									\
		FT_MACRO_GROUP_TYPE(float, float):						_iv3_int_int,								\
		FT_MACRO_GROUP_TYPE(float, float, float):				_iv3_int_int_int,							\
		FT_MACRO_GROUP_TYPE(double):							_iv3_int,									\
		FT_MACRO_GROUP_TYPE(double, double):					_iv3_int_int,								\
		FT_MACRO_GROUP_TYPE(double, double, double):			_iv3_int_int_int,							\
		FT_MACRO_GROUP_TYPE(int):								_iv3_int,									\
		FT_MACRO_GROUP_TYPE(int, int):							_iv3_int_int,								\
		FT_MACRO_GROUP_TYPE(int, int, int):						_iv3_int_int_int,							\
																											\
																											\
		FT_MACRO_GROUP_TYPE(t_iv2, int):						_iv3_iv2_int,								\
		FT_MACRO_GROUP_TYPE(int, t_iv2):						_iv3_int_iv2,								\
																											\
		FT_MACRO_GROUP_TYPE(t_iv2, float):						_iv3_iv2_int,								\
		FT_MACRO_GROUP_TYPE(float, t_iv2):						_iv3_int_iv2,								\
																											\
		FT_MACRO_GROUP_TYPE(t_iv2, double):						_iv3_iv2_int,								\
		FT_MACRO_GROUP_TYPE(double, t_iv2):						_iv3_int_iv2								\
		)(__VA_ARGS__)

#define ivec4(...)																							\
	_Generic(FT_MACRO_GROUP_TYPE_INST(__VA_ARGS__),															\
		FT_MACRO_GROUP_TYPE(t_v2):								_iv4_v2,									\
		FT_MACRO_GROUP_TYPE(t_v3):								_iv4_v3,									\
		FT_MACRO_GROUP_TYPE(t_v4):								_iv4_v4,									\
		FT_MACRO_GROUP_TYPE(t_iv2):								_iv4_iv2,									\
		FT_MACRO_GROUP_TYPE(t_iv3):								_iv4_iv3,									\
																											\
		FT_MACRO_GROUP_TYPE(float):								_iv4_int,									\
		FT_MACRO_GROUP_TYPE(float, float):						_iv4_int_int,								\
		FT_MACRO_GROUP_TYPE(float, float, float):				_iv4_int_int_int,							\
		FT_MACRO_GROUP_TYPE(float, float, float, float):		_iv4_int_int_int_int	,					\
		FT_MACRO_GROUP_TYPE(double):							_iv4_int,									\
		FT_MACRO_GROUP_TYPE(double, double):					_iv4_int_int,								\
		FT_MACRO_GROUP_TYPE(double, double, double):			_iv4_int_int_int,							\
		FT_MACRO_GROUP_TYPE(double, double, double, double):	_iv4_int_int_int_int,						\
		FT_MACRO_GROUP_TYPE(int):								_iv4_int,									\
		FT_MACRO_GROUP_TYPE(int, int):							_iv4_int_int,								\
		FT_MACRO_GROUP_TYPE(int, int, int):						_iv4_int_int_int,							\
		FT_MACRO_GROUP_TYPE(int, int, int, int):				_iv4_int_int_int_int,						\
																											\
		FT_MACRO_GROUP_TYPE(t_iv2, t_iv2):						_iv4_iv2_iv2,								\
																											\
		FT_MACRO_GROUP_TYPE(int, t_iv3):						_iv4_int_iv3,								\
		FT_MACRO_GROUP_TYPE(t_iv3, int):						_iv4_iv3_int,								\
		FT_MACRO_GROUP_TYPE(int, t_iv2, int):					_iv4_int_iv2_int,							\
		FT_MACRO_GROUP_TYPE(int, int, t_iv2):					_iv4_int_int_iv2,							\
		FT_MACRO_GROUP_TYPE(t_iv2, int, int):					_iv4_iv2_int_int,							\
																											\
		FT_MACRO_GROUP_TYPE(float, t_iv3):						_iv4_int_iv3,								\
		FT_MACRO_GROUP_TYPE(t_iv3, float):						_iv4_iv3_int,								\
		FT_MACRO_GROUP_TYPE(float, t_iv2, float):				_iv4_int_iv2_int,							\
		FT_MACRO_GROUP_TYPE(float, float, t_iv2):				_iv4_int_int_iv2,							\
		FT_MACRO_GROUP_TYPE(t_iv2, float, float):				_iv4_iv2_int_int,							\
																											\
		FT_MACRO_GROUP_TYPE(double, t_iv3):						_iv4_int_iv3,								\
		FT_MACRO_GROUP_TYPE(t_iv3, double):						_iv4_iv3_int,								\
		FT_MACRO_GROUP_TYPE(double, t_iv2, double):				_iv4_int_iv2_int,							\
		FT_MACRO_GROUP_TYPE(double, double, t_iv2):				_iv4_int_int_iv2,							\
		FT_MACRO_GROUP_TYPE(t_iv2, double, double):				_iv4_iv2_int_int							\
		)(__VA_ARGS__)
#pragma endregion
#pragma GCC diagnostic push

extern t_v2	_vadd_v2_v2(t_v2 v1, t_v2 v2);
extern t_v2	_vadd_v2_iv2(t_v2 v1, t_iv2 v2);
extern t_v2	_vadd_v2_float(t_v2 v1, float f);

extern t_v3	_vadd_v3_v3(t_v3 v1, t_v3 v2);
extern t_v3	_vadd_v3_iv3(t_v3 v1, t_iv3 v2);
extern t_v3	_vadd_v3_v2(t_v3 v1, t_v2 v2);
extern t_v3	_vadd_v3_iv2(t_v3 v1, t_iv2 v2);
extern t_v3	_vadd_v3_float(t_v3 v1, float f);

extern t_v4	_vadd_v4_v4(t_v4 v1, t_v4 v2);
extern t_v4	_vadd_v4_iv4(t_v4 v1, t_iv4 v2);
extern t_v4	_vadd_v4_v3(t_v4 v1, t_v3 v2);
extern t_v4	_vadd_v4_iv3(t_v4 v1, t_iv3 v2);
extern t_v4	_vadd_v4_v2(t_v4 v1, t_v2 v2);
extern t_v4	_vadd_v4_iv2(t_v4 v1, t_iv2 v2);
extern t_v4	_vadd_v4_float(t_v4 v1, float f);


extern t_iv2	_vadd_iv2_v2(t_iv2 v1, t_v2 v2);
extern t_iv2	_vadd_iv2_iv2(t_iv2 v1, t_iv2 v2);
extern t_iv2	_vadd_iv2_int(t_iv2 v1, int i);

extern t_iv3	_vadd_iv3_v3(t_iv3 v1, t_v3 v2);
extern t_iv3	_vadd_iv3_iv3(t_iv3 v1, t_iv3 v2);
extern t_iv3	_vadd_iv3_v2(t_iv3 v1, t_v2 v2);
extern t_iv3	_vadd_iv3_iv2(t_iv3 v1, t_iv2 v2);
extern t_iv3	_vadd_iv3_int(t_iv3 v1, int i);

extern t_iv4	_vadd_iv4_v4(t_iv4 v1, t_v4 v2);
extern t_iv4	_vadd_iv4_iv4(t_iv4 v1, t_iv4 v2);
extern t_iv4	_vadd_iv4_v3(t_iv4 v1, t_v3 v2);
extern t_iv4	_vadd_iv4_iv3(t_iv4 v1, t_iv3 v2);
extern t_iv4	_vadd_iv4_v2(t_iv4 v1, t_v2 v2);
extern t_iv4	_vadd_iv4_iv2(t_iv4 v1, t_iv2 v2);
extern t_iv4	_vadd_iv4_int(t_iv4 v1, int i);

#define vadd(...)																							\
	_Generic(FT_MACRO_GROUP_TYPE_INST(__VA_ARGS__),															\
		FT_MACRO_GROUP_TYPE(t_v2, t_v2):								_vadd_v2_v2,						\
		FT_MACRO_GROUP_TYPE(t_v2, t_iv2):								_vadd_v2_iv2,						\
		FT_MACRO_GROUP_TYPE(t_v2, float):								_vadd_v2_float,						\
		FT_MACRO_GROUP_TYPE(t_v2, double):								_vadd_v2_float,						\
		FT_MACRO_GROUP_TYPE(t_v2, int):									_vadd_v2_float,						\
																											\
		FT_MACRO_GROUP_TYPE(t_v3, t_v3):								_vadd_v3_v3,						\
		FT_MACRO_GROUP_TYPE(t_v3, t_iv3):								_vadd_v3_iv3,						\
		FT_MACRO_GROUP_TYPE(t_v3, t_v2):								_vadd_v3_v2,						\
		FT_MACRO_GROUP_TYPE(t_v3, t_iv2):								_vadd_v3_iv2,						\
		FT_MACRO_GROUP_TYPE(t_v3, float):								_vadd_v3_float,						\
		FT_MACRO_GROUP_TYPE(t_v3, double):								_vadd_v3_float,						\
		FT_MACRO_GROUP_TYPE(t_v3, int):									_vadd_v3_float,						\
																											\
		FT_MACRO_GROUP_TYPE(t_v4, t_v4):								_vadd_v4_v4,						\
		FT_MACRO_GROUP_TYPE(t_v4, t_iv4):								_vadd_v4_iv4,						\
		FT_MACRO_GROUP_TYPE(t_v4, t_v3):								_vadd_v4_v3,						\
		FT_MACRO_GROUP_TYPE(t_v4, t_iv3):								_vadd_v4_iv3,						\
		FT_MACRO_GROUP_TYPE(t_v4, t_v2):								_vadd_v4_v2,						\
		FT_MACRO_GROUP_TYPE(t_v4, t_iv2):								_vadd_v4_iv2,						\
		FT_MACRO_GROUP_TYPE(t_v4, float):								_vadd_v4_float,						\
		FT_MACRO_GROUP_TYPE(t_v4, double):								_vadd_v4_float,						\
		FT_MACRO_GROUP_TYPE(t_v4, int):									_vadd_v4_float,						\
																											\
		FT_MACRO_GROUP_TYPE(t_iv2, t_v2):								_vadd_iv2_v2,						\
		FT_MACRO_GROUP_TYPE(t_iv2, t_iv2):								_vadd_iv2_iv2,						\
		FT_MACRO_GROUP_TYPE(t_iv2, float):								_vadd_iv2_int,						\
		FT_MACRO_GROUP_TYPE(t_iv2, double):								_vadd_iv2_int,						\
		FT_MACRO_GROUP_TYPE(t_iv2, int):								_vadd_iv2_int,						\
																											\
		FT_MACRO_GROUP_TYPE(t_iv3, t_v3):								_vadd_iv3_v3,						\
		FT_MACRO_GROUP_TYPE(t_iv3, t_iv3):								_vadd_iv3_iv3,						\
		FT_MACRO_GROUP_TYPE(t_iv3, t_v2):								_vadd_iv3_v2,						\
		FT_MACRO_GROUP_TYPE(t_iv3, t_iv2):								_vadd_iv3_iv2,						\
		FT_MACRO_GROUP_TYPE(t_iv3, float):								_vadd_iv3_int,						\
		FT_MACRO_GROUP_TYPE(t_iv3, double):								_vadd_iv3_int,						\
		FT_MACRO_GROUP_TYPE(t_iv3, int):								_vadd_iv3_int,						\
																											\
		FT_MACRO_GROUP_TYPE(t_iv4, t_v4):								_vadd_iv4_v4,						\
		FT_MACRO_GROUP_TYPE(t_iv4, t_iv4):								_vadd_iv4_iv4,						\
		FT_MACRO_GROUP_TYPE(t_iv4, t_v3):								_vadd_iv4_v3,						\
		FT_MACRO_GROUP_TYPE(t_iv4, t_iv3):								_vadd_iv4_iv3,						\
		FT_MACRO_GROUP_TYPE(t_iv4, t_v2):								_vadd_iv4_v2,						\
		FT_MACRO_GROUP_TYPE(t_iv4, t_iv2):								_vadd_iv4_iv2,						\
		FT_MACRO_GROUP_TYPE(t_iv4, float):								_vadd_iv4_int,						\
		FT_MACRO_GROUP_TYPE(t_iv4, double):								_vadd_iv4_int,						\
		FT_MACRO_GROUP_TYPE(t_iv4, int):								_vadd_iv4_int						\
		)(__VA_ARGS__)

extern t_v2	_vsub_v2_v2(t_v2 v1, t_v2 v2);
extern t_v2	_vsub_v2_iv2(t_v2 v1, t_iv2 v2);
extern t_v2	_vsub_v2_float(t_v2 v1, float f);

extern t_v3	_vsub_v3_v3(t_v3 v1, t_v3 v2);
extern t_v3	_vsub_v3_iv3(t_v3 v1, t_iv3 v2);
extern t_v3	_vsub_v3_v2(t_v3 v1, t_v2 v2);
extern t_v3	_vsub_v3_iv2(t_v3 v1, t_iv2 v2);
extern t_v3	_vsub_v3_float(t_v3 v1, float f);

extern t_v4	_vsub_v4_v4(t_v4 v1, t_v4 v2);
extern t_v4	_vsub_v4_iv4(t_v4 v1, t_iv4 v2);
extern t_v4	_vsub_v4_v3(t_v4 v1, t_v3 v2);
extern t_v4	_vsub_v4_iv3(t_v4 v1, t_iv3 v2);
extern t_v4	_vsub_v4_v2(t_v4 v1, t_v2 v2);
extern t_v4	_vsub_v4_iv2(t_v4 v1, t_iv2 v2);
extern t_v4	_vsub_v4_float(t_v4 v1, float f);


extern t_iv2	_vsub_iv2_v2(t_iv2 v1, t_v2 v2);
extern t_iv2	_vsub_iv2_iv2(t_iv2 v1, t_iv2 v2);
extern t_iv2	_vsub_iv2_int(t_iv2 v1, int i);

extern t_iv3	_vsub_iv3_v3(t_iv3 v1, t_v3 v2);
extern t_iv3	_vsub_iv3_iv3(t_iv3 v1, t_iv3 v2);
extern t_iv3	_vsub_iv3_v2(t_iv3 v1, t_v2 v2);
extern t_iv3	_vsub_iv3_iv2(t_iv3 v1, t_iv2 v2);
extern t_iv3	_vsub_iv3_int(t_iv3 v1, int i);

extern t_iv4	_vsub_iv4_v4(t_iv4 v1, t_v4 v2);
extern t_iv4	_vsub_iv4_iv4(t_iv4 v1, t_iv4 v2);
extern t_iv4	_vsub_iv4_v3(t_iv4 v1, t_v3 v2);
extern t_iv4	_vsub_iv4_iv3(t_iv4 v1, t_iv3 v2);
extern t_iv4	_vsub_iv4_v2(t_iv4 v1, t_v2 v2);
extern t_iv4	_vsub_iv4_iv2(t_iv4 v1, t_iv2 v2);
extern t_iv4	_vsub_iv4_int(t_iv4 v1, int i);

#define vsub(...)																							\
	_Generic(FT_MACRO_GROUP_TYPE_INST(__VA_ARGS__),															\
		FT_MACRO_GROUP_TYPE(t_v2, t_v2):								_vsub_v2_v2,						\
		FT_MACRO_GROUP_TYPE(t_v2, t_iv2):								_vsub_v2_iv2,						\
		FT_MACRO_GROUP_TYPE(t_v2, float):								_vsub_v2_float,						\
		FT_MACRO_GROUP_TYPE(t_v2, double):								_vsub_v2_float,						\
		FT_MACRO_GROUP_TYPE(t_v2, int):									_vsub_v2_float,						\
																											\
		FT_MACRO_GROUP_TYPE(t_v3, t_v3):								_vsub_v3_v3,						\
		FT_MACRO_GROUP_TYPE(t_v3, t_iv3):								_vsub_v3_iv3,						\
		FT_MACRO_GROUP_TYPE(t_v3, t_v2):								_vsub_v3_v2,						\
		FT_MACRO_GROUP_TYPE(t_v3, t_iv2):								_vsub_v3_iv2,						\
		FT_MACRO_GROUP_TYPE(t_v3, float):								_vsub_v3_float,						\
		FT_MACRO_GROUP_TYPE(t_v3, double):								_vsub_v3_float,						\
		FT_MACRO_GROUP_TYPE(t_v3, int):									_vsub_v3_float,						\
																											\
		FT_MACRO_GROUP_TYPE(t_v4, t_v4):								_vsub_v4_v4,						\
		FT_MACRO_GROUP_TYPE(t_v4, t_iv4):								_vsub_v4_iv4,						\
		FT_MACRO_GROUP_TYPE(t_v4, t_v3):								_vsub_v4_v3,						\
		FT_MACRO_GROUP_TYPE(t_v4, t_iv3):								_vsub_v4_iv3,						\
		FT_MACRO_GROUP_TYPE(t_v4, t_v2):								_vsub_v4_v2,						\
		FT_MACRO_GROUP_TYPE(t_v4, t_iv2):								_vsub_v4_iv2,						\
		FT_MACRO_GROUP_TYPE(t_v4, float):								_vsub_v4_float,						\
		FT_MACRO_GROUP_TYPE(t_v4, double):								_vsub_v4_float,						\
		FT_MACRO_GROUP_TYPE(t_v4, int):									_vsub_v4_float,						\
																											\
		FT_MACRO_GROUP_TYPE(t_iv2, t_v2):								_vsub_iv2_v2,						\
		FT_MACRO_GROUP_TYPE(t_iv2, t_iv2):								_vsub_iv2_iv2,						\
		FT_MACRO_GROUP_TYPE(t_iv2, float):								_vsub_iv2_int,						\
		FT_MACRO_GROUP_TYPE(t_iv2, double):								_vsub_iv2_int,						\
		FT_MACRO_GROUP_TYPE(t_iv2, int):								_vsub_iv2_int,						\
																											\
		FT_MACRO_GROUP_TYPE(t_iv3, t_v3):								_vsub_iv3_v3,						\
		FT_MACRO_GROUP_TYPE(t_iv3, t_iv3):								_vsub_iv3_iv3,						\
		FT_MACRO_GROUP_TYPE(t_iv3, t_v2):								_vsub_iv3_v2,						\
		FT_MACRO_GROUP_TYPE(t_iv3, t_iv2):								_vsub_iv3_iv2,						\
		FT_MACRO_GROUP_TYPE(t_iv3, float):								_vsub_iv3_int,						\
		FT_MACRO_GROUP_TYPE(t_iv3, double):								_vsub_iv3_int,						\
		FT_MACRO_GROUP_TYPE(t_iv3, int):								_vsub_iv3_int,						\
																											\
		FT_MACRO_GROUP_TYPE(t_iv4, t_v4):								_vsub_iv4_v4,						\
		FT_MACRO_GROUP_TYPE(t_iv4, t_iv4):								_vsub_iv4_iv4,						\
		FT_MACRO_GROUP_TYPE(t_iv4, t_v3):								_vsub_iv4_v3,						\
		FT_MACRO_GROUP_TYPE(t_iv4, t_iv3):								_vsub_iv4_iv3,						\
		FT_MACRO_GROUP_TYPE(t_iv4, t_v2):								_vsub_iv4_v2,						\
		FT_MACRO_GROUP_TYPE(t_iv4, t_iv2):								_vsub_iv4_iv2,						\
		FT_MACRO_GROUP_TYPE(t_iv4, float):								_vsub_iv4_int,						\
		FT_MACRO_GROUP_TYPE(t_iv4, double):								_vsub_iv4_int,						\
		FT_MACRO_GROUP_TYPE(t_iv4, int):								_vsub_iv4_int						\
		)(__VA_ARGS__)

extern t_v2	_vmult_v2_v2(t_v2 v1, t_v2 v2);
extern t_v2	_vmult_v2_iv2(t_v2 v1, t_iv2 v2);
extern t_v2	_vmult_v2_float(t_v2 v1, float f);

extern t_v3	_vmult_v3_v3(t_v3 v1, t_v3 v2);
extern t_v3	_vmult_v3_iv3(t_v3 v1, t_iv3 v2);
extern t_v3	_vmult_v3_v2(t_v3 v1, t_v2 v2);
extern t_v3	_vmult_v3_iv2(t_v3 v1, t_iv2 v2);
extern t_v3	_vmult_v3_float(t_v3 v1, float f);

extern t_v4	_vmult_v4_v4(t_v4 v1, t_v4 v2);
extern t_v4	_vmult_v4_iv4(t_v4 v1, t_iv4 v2);
extern t_v4	_vmult_v4_v3(t_v4 v1, t_v3 v2);
extern t_v4	_vmult_v4_iv3(t_v4 v1, t_iv3 v2);
extern t_v4	_vmult_v4_v2(t_v4 v1, t_v2 v2);
extern t_v4	_vmult_v4_iv2(t_v4 v1, t_iv2 v2);
extern t_v4	_vmult_v4_float(t_v4 v1, float f);


extern t_iv2	_vmult_iv2_v2(t_iv2 v1, t_v2 v2);
extern t_iv2	_vmult_iv2_iv2(t_iv2 v1, t_iv2 v2);
extern t_iv2	_vmult_iv2_int(t_iv2 v1, int i);

extern t_iv3	_vmult_iv3_v3(t_iv3 v1, t_v3 v2);
extern t_iv3	_vmult_iv3_iv3(t_iv3 v1, t_iv3 v2);
extern t_iv3	_vmult_iv3_v2(t_iv3 v1, t_v2 v2);
extern t_iv3	_vmult_iv3_iv2(t_iv3 v1, t_iv2 v2);
extern t_iv3	_vmult_iv3_int(t_iv3 v1, int i);

extern t_iv4	_vmult_iv4_v4(t_iv4 v1, t_v4 v2);
extern t_iv4	_vmult_iv4_iv4(t_iv4 v1, t_iv4 v2);
extern t_iv4	_vmult_iv4_v3(t_iv4 v1, t_v3 v2);
extern t_iv4	_vmult_iv4_iv3(t_iv4 v1, t_iv3 v2);
extern t_iv4	_vmult_iv4_v2(t_iv4 v1, t_v2 v2);
extern t_iv4	_vmult_iv4_iv2(t_iv4 v1, t_iv2 v2);
extern t_iv4	_vmult_iv4_int(t_iv4 v1, int i);

#define vmult(...)																							\
	_Generic(FT_MACRO_GROUP_TYPE_INST(__VA_ARGS__),															\
		FT_MACRO_GROUP_TYPE(t_v2, t_v2):								_vmult_v2_v2,						\
		FT_MACRO_GROUP_TYPE(t_v2, t_iv2):								_vmult_v2_iv2,						\
		FT_MACRO_GROUP_TYPE(t_v2, float):								_vmult_v2_float,					\
		FT_MACRO_GROUP_TYPE(t_v2, double):								_vmult_v2_float,					\
		FT_MACRO_GROUP_TYPE(t_v2, int):									_vmult_v2_float,					\
																											\
		FT_MACRO_GROUP_TYPE(t_v3, t_v3):								_vmult_v3_v3,						\
		FT_MACRO_GROUP_TYPE(t_v3, t_iv3):								_vmult_v3_iv3,						\
		FT_MACRO_GROUP_TYPE(t_v3, t_v2):								_vmult_v3_v2,						\
		FT_MACRO_GROUP_TYPE(t_v3, t_iv2):								_vmult_v3_iv2,						\
		FT_MACRO_GROUP_TYPE(t_v3, float):								_vmult_v3_float,					\
		FT_MACRO_GROUP_TYPE(t_v3, double):								_vmult_v3_float,					\
		FT_MACRO_GROUP_TYPE(t_v3, int):									_vmult_v3_float,					\
																											\
		FT_MACRO_GROUP_TYPE(t_v4, t_v4):								_vmult_v4_v4,						\
		FT_MACRO_GROUP_TYPE(t_v4, t_iv4):								_vmult_v4_iv4,						\
		FT_MACRO_GROUP_TYPE(t_v4, t_v3):								_vmult_v4_v3,						\
		FT_MACRO_GROUP_TYPE(t_v4, t_iv3):								_vmult_v4_iv3,						\
		FT_MACRO_GROUP_TYPE(t_v4, t_v2):								_vmult_v4_v2,						\
		FT_MACRO_GROUP_TYPE(t_v4, t_iv2):								_vmult_v4_iv2,						\
		FT_MACRO_GROUP_TYPE(t_v4, float):								_vmult_v4_float,					\
		FT_MACRO_GROUP_TYPE(t_v4, double):								_vmult_v4_float,					\
		FT_MACRO_GROUP_TYPE(t_v4, int):									_vmult_v4_float,					\
																											\
		FT_MACRO_GROUP_TYPE(t_iv2, t_v2):								_vmult_iv2_v2,						\
		FT_MACRO_GROUP_TYPE(t_iv2, t_iv2):								_vmult_iv2_iv2,						\
		FT_MACRO_GROUP_TYPE(t_iv2, float):								_vmult_iv2_int,						\
		FT_MACRO_GROUP_TYPE(t_iv2, double):								_vmult_iv2_int,						\
		FT_MACRO_GROUP_TYPE(t_iv2, int):								_vmult_iv2_int,						\
																											\
		FT_MACRO_GROUP_TYPE(t_iv3, t_v3):								_vmult_iv3_v3,						\
		FT_MACRO_GROUP_TYPE(t_iv3, t_iv3):								_vmult_iv3_iv3,						\
		FT_MACRO_GROUP_TYPE(t_iv3, t_v2):								_vmult_iv3_v2,						\
		FT_MACRO_GROUP_TYPE(t_iv3, t_iv2):								_vmult_iv3_iv2,						\
		FT_MACRO_GROUP_TYPE(t_iv3, float):								_vmult_iv3_int,						\
		FT_MACRO_GROUP_TYPE(t_iv3, double):								_vmult_iv3_int,						\
		FT_MACRO_GROUP_TYPE(t_iv3, int):								_vmult_iv3_int,						\
																											\
		FT_MACRO_GROUP_TYPE(t_iv4, t_v4):								_vmult_iv4_v4,						\
		FT_MACRO_GROUP_TYPE(t_iv4, t_iv4):								_vmult_iv4_iv4,						\
		FT_MACRO_GROUP_TYPE(t_iv4, t_v3):								_vmult_iv4_v3,						\
		FT_MACRO_GROUP_TYPE(t_iv4, t_iv3):								_vmult_iv4_iv3,						\
		FT_MACRO_GROUP_TYPE(t_iv4, t_v2):								_vmult_iv4_v2,						\
		FT_MACRO_GROUP_TYPE(t_iv4, t_iv2):								_vmult_iv4_iv2,						\
		FT_MACRO_GROUP_TYPE(t_iv4, float):								_vmult_iv4_int,						\
		FT_MACRO_GROUP_TYPE(t_iv4, double):								_vmult_iv4_int,						\
		FT_MACRO_GROUP_TYPE(t_iv4, int):								_vmult_iv4_int						\
		)(__VA_ARGS__)

extern t_v2	_vdiv_v2_v2(t_v2 v1, t_v2 v2);
extern t_v2	_vdiv_v2_iv2(t_v2 v1, t_iv2 v2);
extern t_v2	_vdiv_v2_float(t_v2 v1, float f);

extern t_v3	_vdiv_v3_v3(t_v3 v1, t_v3 v2);
extern t_v3	_vdiv_v3_iv3(t_v3 v1, t_iv3 v2);
extern t_v3	_vdiv_v3_v2(t_v3 v1, t_v2 v2);
extern t_v3	_vdiv_v3_iv2(t_v3 v1, t_iv2 v2);
extern t_v3	_vdiv_v3_float(t_v3 v1, float f);

extern t_v4	_vdiv_v4_v4(t_v4 v1, t_v4 v2);
extern t_v4	_vdiv_v4_iv4(t_v4 v1, t_iv4 v2);
extern t_v4	_vdiv_v4_v3(t_v4 v1, t_v3 v2);
extern t_v4	_vdiv_v4_iv3(t_v4 v1, t_iv3 v2);
extern t_v4	_vdiv_v4_v2(t_v4 v1, t_v2 v2);
extern t_v4	_vdiv_v4_iv2(t_v4 v1, t_iv2 v2);
extern t_v4	_vdiv_v4_float(t_v4 v1, float f);


extern t_iv2	_vdiv_iv2_v2(t_iv2 v1, t_v2 v2);
extern t_iv2	_vdiv_iv2_iv2(t_iv2 v1, t_iv2 v2);
extern t_iv2	_vdiv_iv2_int(t_iv2 v1, int i);

extern t_iv3	_vdiv_iv3_v3(t_iv3 v1, t_v3 v2);
extern t_iv3	_vdiv_iv3_iv3(t_iv3 v1, t_iv3 v2);
extern t_iv3	_vdiv_iv3_v2(t_iv3 v1, t_v2 v2);
extern t_iv3	_vdiv_iv3_iv2(t_iv3 v1, t_iv2 v2);
extern t_iv3	_vdiv_iv3_int(t_iv3 v1, int i);

extern t_iv4	_vdiv_iv4_v4(t_iv4 v1, t_v4 v2);
extern t_iv4	_vdiv_iv4_iv4(t_iv4 v1, t_iv4 v2);
extern t_iv4	_vdiv_iv4_v3(t_iv4 v1, t_v3 v2);
extern t_iv4	_vdiv_iv4_iv3(t_iv4 v1, t_iv3 v2);
extern t_iv4	_vdiv_iv4_v2(t_iv4 v1, t_v2 v2);
extern t_iv4	_vdiv_iv4_iv2(t_iv4 v1, t_iv2 v2);
extern t_iv4	_vdiv_iv4_int(t_iv4 v1, int i);

#define vdiv(...)																							\
	_Generic(FT_MACRO_GROUP_TYPE_INST(__VA_ARGS__),															\
		FT_MACRO_GROUP_TYPE(t_v2, t_v2):								_vdiv_v2_v2,						\
		FT_MACRO_GROUP_TYPE(t_v2, t_iv2):								_vdiv_v2_iv2,						\
		FT_MACRO_GROUP_TYPE(t_v2, float):								_vdiv_v2_float,						\
		FT_MACRO_GROUP_TYPE(t_v2, double):								_vdiv_v2_float,						\
		FT_MACRO_GROUP_TYPE(t_v2, int):									_vdiv_v2_float,						\
																											\
		FT_MACRO_GROUP_TYPE(t_v3, t_v3):								_vdiv_v3_v3,						\
		FT_MACRO_GROUP_TYPE(t_v3, t_iv3):								_vdiv_v3_iv3,						\
		FT_MACRO_GROUP_TYPE(t_v3, t_v2):								_vdiv_v3_v2,						\
		FT_MACRO_GROUP_TYPE(t_v3, t_iv2):								_vdiv_v3_iv2,						\
		FT_MACRO_GROUP_TYPE(t_v3, float):								_vdiv_v3_float,						\
		FT_MACRO_GROUP_TYPE(t_v3, double):								_vdiv_v3_float,						\
		FT_MACRO_GROUP_TYPE(t_v3, int):									_vdiv_v3_float,						\
																											\
		FT_MACRO_GROUP_TYPE(t_v4, t_v4):								_vdiv_v4_v4,						\
		FT_MACRO_GROUP_TYPE(t_v4, t_iv4):								_vdiv_v4_iv4,						\
		FT_MACRO_GROUP_TYPE(t_v4, t_v3):								_vdiv_v4_v3,						\
		FT_MACRO_GROUP_TYPE(t_v4, t_iv3):								_vdiv_v4_iv3,						\
		FT_MACRO_GROUP_TYPE(t_v4, t_v2):								_vdiv_v4_v2,						\
		FT_MACRO_GROUP_TYPE(t_v4, t_iv2):								_vdiv_v4_iv2,						\
		FT_MACRO_GROUP_TYPE(t_v4, float):								_vdiv_v4_float,						\
		FT_MACRO_GROUP_TYPE(t_v4, double):								_vdiv_v4_float,						\
		FT_MACRO_GROUP_TYPE(t_v4, int):									_vdiv_v4_float,						\
																											\
		FT_MACRO_GROUP_TYPE(t_iv2, t_v2):								_vdiv_iv2_v2,						\
		FT_MACRO_GROUP_TYPE(t_iv2, t_iv2):								_vdiv_iv2_iv2,						\
		FT_MACRO_GROUP_TYPE(t_iv2, float):								_vdiv_iv2_int,						\
		FT_MACRO_GROUP_TYPE(t_iv2, double):								_vdiv_iv2_int,						\
		FT_MACRO_GROUP_TYPE(t_iv2, int):								_vdiv_iv2_int,						\
																											\
		FT_MACRO_GROUP_TYPE(t_iv3, t_v3):								_vdiv_iv3_v3,						\
		FT_MACRO_GROUP_TYPE(t_iv3, t_iv3):								_vdiv_iv3_iv3,						\
		FT_MACRO_GROUP_TYPE(t_iv3, t_v2):								_vdiv_iv3_v2,						\
		FT_MACRO_GROUP_TYPE(t_iv3, t_iv2):								_vdiv_iv3_iv2,						\
		FT_MACRO_GROUP_TYPE(t_iv3, float):								_vdiv_iv3_int,						\
		FT_MACRO_GROUP_TYPE(t_iv3, double):								_vdiv_iv3_int,						\
		FT_MACRO_GROUP_TYPE(t_iv3, int):								_vdiv_iv3_int,						\
																											\
		FT_MACRO_GROUP_TYPE(t_iv4, t_v4):								_vdiv_iv4_v4,						\
		FT_MACRO_GROUP_TYPE(t_iv4, t_iv4):								_vdiv_iv4_iv4,						\
		FT_MACRO_GROUP_TYPE(t_iv4, t_v3):								_vdiv_iv4_v3,						\
		FT_MACRO_GROUP_TYPE(t_iv4, t_iv3):								_vdiv_iv4_iv3,						\
		FT_MACRO_GROUP_TYPE(t_iv4, t_v2):								_vdiv_iv4_v2,						\
		FT_MACRO_GROUP_TYPE(t_iv4, t_iv2):								_vdiv_iv4_iv2,						\
		FT_MACRO_GROUP_TYPE(t_iv4, float):								_vdiv_iv4_int,						\
		FT_MACRO_GROUP_TYPE(t_iv4, double):								_vdiv_iv4_int,						\
		FT_MACRO_GROUP_TYPE(t_iv4, int):								_vdiv_iv4_int						\
		)(__VA_ARGS__)

extern t_iv2	_vmod_iv2_iv2(t_iv2 v1, t_iv2 v2);
extern t_iv2	_vmod_iv2_int(t_iv2 v1, int i);

extern t_iv3	_vmod_iv3_iv3(t_iv3 v1, t_iv3 v2);
extern t_iv3	_vmod_iv3_iv2(t_iv3 v1, t_iv2 v2);
extern t_iv3	_vmod_iv3_int(t_iv3 v1, int i);

extern t_iv4	_vmod_iv4_iv4(t_iv4 v1, t_iv4 v2);
extern t_iv4	_vmod_iv4_iv3(t_iv4 v1, t_iv3 v2);
extern t_iv4	_vmod_iv4_iv2(t_iv4 v1, t_iv2 v2);
extern t_iv4	_vmod_iv4_int(t_iv4 v1, int i);

#define vmod(...)																							\
	_Generic(FT_MACRO_GROUP_TYPE_INST(__VA_ARGS__),															\
		FT_MACRO_GROUP_TYPE(t_iv2, t_iv2):								_vmod_iv2_iv2,						\
		FT_MACRO_GROUP_TYPE(t_iv2, int):								_vmod_iv2_int,						\
																											\
		FT_MACRO_GROUP_TYPE(t_iv3, t_iv3):								_vmod_iv3_iv3,						\
		FT_MACRO_GROUP_TYPE(t_iv3, t_iv2):								_vmod_iv3_iv2,						\
		FT_MACRO_GROUP_TYPE(t_iv3, int):								_vmod_iv3_int,						\
																											\
		FT_MACRO_GROUP_TYPE(t_iv4, t_iv4):								_vmod_iv4_iv4,						\
		FT_MACRO_GROUP_TYPE(t_iv4, t_iv3):								_vmod_iv4_iv3,						\
		FT_MACRO_GROUP_TYPE(t_iv4, t_iv2):								_vmod_iv4_iv2,						\
		FT_MACRO_GROUP_TYPE(t_iv4, int):								_vmod_iv4_int						\
		)(__VA_ARGS__)

extern int vlen2i(t_iv2 a);
extern float vlen2(t_v2 a);
// VECTORS

// ARRAY
typedef struct s_array	*t_array;
typedef t_error_code	t_array_code;

// Init array. Returns FT_OK or FT_OMEM
extern t_array		ft_array_new(U64 elem_size, t_array_code *err);
t_array_code		ft_array_init(t_array *array, U64 elem_size);
// Init array and copy buffer into array. Returns FT_OK or FT_OMEM
extern t_array_code	ft_array_init_from(t_array array, U64 elem_size, void *buffer, S32 count);
// Free array
extern void			ft_array_free(t_array array);

// Returns a pointer to the value at index. Return NULL if not found
extern void			*ft_array_get(t_array array, U64 index);

// Returns the number of elements in the array
extern U64			ft_array_count(t_array array);
// Returns the size in bytes of the array. (array_count * elem_size)
extern U64			ft_array_count_bytes(t_array array);

// Allocates a buffer and copy whole array on it. Returns FT_OK or FT_OMEM
extern void			*ft_array_to_buff(t_array array, t_array_code *err);
// Copies whole array to buff. Returns FT_OK or FT_OMEM
extern t_array_code ft_array_cpy_buff(t_array array, void *buff);

// Appends the value elem to the back of the array. Returns FT_OK or FT_OMEM
extern void			*ft_array_append(t_array array, void *elem, t_array_code *err);
// Clears the array
extern void			ft_array_clear(t_array array);
// ARRAY

// LIST
typedef struct s_list
{
	void *content;
	struct s_list *prev;
	struct s_list *next;
} t_list;

// Compares every element in lst against ref using f, removes if f returns >0
extern bool ft_lstremoveif(t_list **lst, void (*del)(void *),
							bool (*f)(), void *ref);
// Removes an element from a chained list. If del is not NULL,
// applies del to content and free the element
extern bool ft_lstremove(t_list **lst, t_list *elem, void (*del)(void *));

// Converts a list to an array
extern int ft_lst_to_array(t_list *lst, t_array array, U64 elem_size);
// Creates and returns a new array containing
// all the pointers of the chained list
extern void **ft_lst_to_array_pointers(t_list *lst);

// Creates a new list element using content
extern t_list *ft_lstnew(void *content);
// Adds new at the front of lst.
extern void ft_lstadd_front(t_list **lst, t_list *new);
// Adds new at the end of lst.
extern void ft_lstadd_back(t_list **lst, t_list *new);

// Returns the size of lst.
extern U64 ft_lstsize(t_list *lst);

// Returns the last element of lst.
extern t_list *ft_lstlast(t_list *lst);

// Deletes an element from lst, using del on it's content.
extern void ft_lstdelone(t_list *lst, void (*del)(void *));
// Iterates through lst, deleting every element (see ft_lstdelone).
extern void ft_lstclear(t_list **lst, void (*del)(void *));

// Iterates through lst, using f on each element's content.
extern void ft_lstiter(t_list *lst, void (*f)(void *));
// Find the value stored in ref, using function f
extern t_list *ft_lstfind(t_list *lst, bool (*f)(void *, void *), void *ref);
/*Iterates through "lst", applies "f" on every
element's content, puts results in a new list and returns it.
"del" is used if anything goes wrong.*/
extern t_list *ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
// LIST

// HASH

typedef void 			*t_hash_any;
typedef void 			*t_hash_map;
typedef t_error_code	t_hash_code;

// Initialize new hashmap
extern t_hash_map ft_hash_init(unsigned int (*key_hash)(void *), U64 key_len, U64 elem_len);
// Free the ft_hash. Return FT_MAP_MISSING if mutex can't be destroyed, FT_OK otherwise
extern t_hash_code ft_hash_free(t_hash_map in);

// Add an element to the hashmap. Return FT_OK or FT_OMEM.
extern t_hash_code ft_hash_put(t_hash_map in, void *key, t_hash_any value);
// Get an element from the hashmap. Return FT_OK or FT_MAP_MISSING.
extern t_hash_code ft_hash_get(t_hash_map in, void *key, t_hash_any *arg);
// Remove an element from the hashmap. Return FT_OK or FT_MAP_MISSING.
extern t_hash_code ft_hash_remove(t_hash_map in, void *key);

// Get the current size of a hashmap
extern t_hash_code ft_hash_length(t_hash_map in);

/*Get any element. Return FT_OK or FT_MAP_MISSING.
remove - should the element be removed from the hashmap*/
extern t_hash_code ft_hash_get_one(t_hash_map in, t_hash_any *arg, int remove);
/*Iteratively call f with argument (item, data) for
each element data in the hashmap. The function must
return a map status code. If it returns anything other
than FT_OK the traversal is terminated. f must
not reenter any hashmap functions, or deadlock may arise.*/
extern t_hash_code ft_hash_iterate(t_hash_map in, t_hash_code (*f)(t_hash_any item, t_hash_any elem), t_hash_any item);
// HASH

//================MATHS================
// MATRIX
typedef struct s_mat4x4
{
	F32 m00, m10, m20, m30;
	F32 m01, m11, m21, m31;
	F32 m02, m12, m22, m32;
	F32 m03, m13, m23, m33;
} t_mat4x4;

#define 	ft_matrix_identity	\
	(t_mat4x4) {				\
		1.0f, 0.0f, 0.0f, 0.0f,	\
		0.0f, 1.0f, 0.0f, 0.0f,	\
		0.0f, 0.0f, 1.0f, 0.0f,	\
		0.0f, 0.0f, 0.0f, 1.0f }
t_v4		*ft_matrix_col(t_mat4x4 *mat, int c);
float		*ft_matrix_get(t_mat4x4 *mat, int r, int c);
t_v4		*ft_matrix_set_col(t_mat4x4 *mat, int c, t_v4 v);
bool		ft_matrix_set_row(t_mat4x4 *mat, int r, t_v4 v);

t_mat4x4	ft_matrix_transpose(t_mat4x4 mat);
t_mat4x4	ft_matrix_invert(t_mat4x4 mat);
float		ft_matrix_det(t_mat4x4 v);
t_mat4x4	ft_matrix_perspective(F32 fov, F32 near, F32 far);

t_mat4x4	__ft_matrix_mult_matrix(t_mat4x4 a, t_mat4x4 b);
t_v4		__ft_matrix_mult_v4(t_mat4x4 a, t_v4 b);
t_mat4x4	__ft_matrix_mult_float(t_mat4x4 a, float b);
#define 	ft_matrix_mult(...)																				\
	_Generic(FT_MACRO_GROUP_TYPE_INST(__VA_ARGS__),															\
		FT_MACRO_GROUP_TYPE(t_mat4x4, t_mat4x4):							__ft_matrix_mult_matrix,		\
		FT_MACRO_GROUP_TYPE(t_mat4x4, t_v4):								__ft_matrix_mult_v4,			\
		FT_MACRO_GROUP_TYPE(t_mat4x4, float):								__ft_matrix_mult_float,			\
		FT_MACRO_GROUP_TYPE(t_mat4x4, double):								__ft_matrix_mult_float,			\
		FT_MACRO_GROUP_TYPE(t_mat4x4, int):									__ft_matrix_mult_float			\
		)(__VA_ARGS__)


t_mat4x4	__ft_matrix_scale_v2(t_v2 v);
t_mat4x4	__ft_matrix_scale_v3(t_v3 v);
t_mat4x4	__ft_matrix_scale_v4(t_v4 v);
t_mat4x4	__ft_matrix_scale_iv2(t_iv2 v);
t_mat4x4	__ft_matrix_scale_iv3(t_iv3 v);
t_mat4x4	__ft_matrix_scale_iv4(t_iv4 v);
#define 	ft_matrix_scale(...)																			\
	_Generic(FT_MACRO_GROUP_TYPE_INST(__VA_ARGS__),															\
		FT_MACRO_GROUP_TYPE(t_v2):											__ft_matrix_scale_v2,			\
		FT_MACRO_GROUP_TYPE(t_v3):											__ft_matrix_scale_v3,			\
		FT_MACRO_GROUP_TYPE(t_v4):											__ft_matrix_scale_v4,			\
		FT_MACRO_GROUP_TYPE(t_iv2):											__ft_matrix_scale_iv2,			\
		FT_MACRO_GROUP_TYPE(t_iv3):											__ft_matrix_scale_iv3,			\
		FT_MACRO_GROUP_TYPE(t_iv4):											__ft_matrix_scale_iv4			\
		)(__VA_ARGS__)


t_mat4x4	__ft_matrix_translate_v2(t_v2 v);
t_mat4x4	__ft_matrix_translate_v3(t_v3 v);
t_mat4x4	__ft_matrix_translate_iv2(t_iv2 v);
t_mat4x4	__ft_matrix_translate_iv3(t_iv3 v);
#define 	ft_matrix_translate(...)																		\
	_Generic(FT_MACRO_GROUP_TYPE_INST(__VA_ARGS__),															\
		FT_MACRO_GROUP_TYPE(t_v2):											__ft_matrix_translate_v2,		\
		FT_MACRO_GROUP_TYPE(t_v3):											__ft_matrix_translate_v3,		\
		FT_MACRO_GROUP_TYPE(t_iv2):											__ft_matrix_translate_iv2,		\
		FT_MACRO_GROUP_TYPE(t_iv3):											__ft_matrix_translate_iv3		\
		)(__VA_ARGS__)

t_mat4x4	ft_matrix_fit_to_view(t_v2 pos, t_v2 size, t_v2 view_size);
// MATRIX

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
#define DEG_TO_RAD 0.01745329251
#define RAD_TO_DEG 57.2957795131

extern t_v2		__ft_cos2(t_v2 v);
extern t_iv2	__ft_icos2(t_iv2 v);
extern t_v3		__ft_cos3(t_v3 v);
extern t_iv3	__ft_icos3(t_iv3 v);
extern t_v4		__ft_cos4(t_v4 v);
extern t_iv4	__ft_icos4(t_iv4 v);
#define ft_cos(...)																							\
	_Generic(FT_MACRO_GROUP_TYPE_INST(__VA_ARGS__),															\
		FT_MACRO_GROUP_TYPE(double):										cos,							\
		FT_MACRO_GROUP_TYPE(float):											cosf,							\
		FT_MACRO_GROUP_TYPE(int):											cos,							\
		FT_MACRO_GROUP_TYPE(t_v2):											__ft_cos2,						\
		FT_MACRO_GROUP_TYPE(t_v3):											__ft_cos3,						\
		FT_MACRO_GROUP_TYPE(t_v4):											__ft_cos4,						\
		FT_MACRO_GROUP_TYPE(t_iv2):											__ft_icos2,						\
		FT_MACRO_GROUP_TYPE(t_iv3):											__ft_icos3,						\
		FT_MACRO_GROUP_TYPE(t_iv4):											__ft_icos4						\
	)(__VA_ARGS__)

extern t_v2		__ft_sin2(t_v2 v);
extern t_iv2	__ft_isin2(t_iv2 v);
extern t_v3		__ft_sin3(t_v3 v);
extern t_iv3	__ft_isin3(t_iv3 v);
extern t_v4		__ft_sin4(t_v4 v);
extern t_iv4	__ft_isin4(t_iv4 v);
#define ft_sin(...)																							\
	_Generic(FT_MACRO_GROUP_TYPE_INST(__VA_ARGS__),															\
		FT_MACRO_GROUP_TYPE(double):										sin,							\
		FT_MACRO_GROUP_TYPE(float):											sinf,							\
		FT_MACRO_GROUP_TYPE(int):											sin,							\
		FT_MACRO_GROUP_TYPE(t_v2):											__ft_sin2,						\
		FT_MACRO_GROUP_TYPE(t_v3):											__ft_sin3,						\
		FT_MACRO_GROUP_TYPE(t_v4):											__ft_sin4,						\
		FT_MACRO_GROUP_TYPE(t_iv2):											__ft_isin2,						\
		FT_MACRO_GROUP_TYPE(t_iv3):											__ft_isin3,						\
		FT_MACRO_GROUP_TYPE(t_iv4):											__ft_isin4						\
	)(__VA_ARGS__)

extern F32		__ft_radians(float degrees);
extern t_v2		__ft_radians2(t_v2 degrees);
extern t_v3		__ft_radians3(t_v3 degrees);
extern t_v4		__ft_radians4(t_v4 degrees);
extern t_iv2	__ft_iradians2(t_iv2 degrees);
extern t_iv3	__ft_iradians3(t_iv3 degrees);
extern t_iv4	__ft_iradians4(t_iv4 degrees);
#define ft_radians(...)																						\
	_Generic(FT_MACRO_GROUP_TYPE_INST(__VA_ARGS__),															\
		FT_MACRO_GROUP_TYPE(double):										__ft_radians,					\
		FT_MACRO_GROUP_TYPE(float):											__ft_radians,					\
		FT_MACRO_GROUP_TYPE(int):											__ft_radians,					\
		FT_MACRO_GROUP_TYPE(t_v2):											__ft_radians2,					\
		FT_MACRO_GROUP_TYPE(t_v3):											__ft_radians3,					\
		FT_MACRO_GROUP_TYPE(t_v4):											__ft_radians4,					\
		FT_MACRO_GROUP_TYPE(t_iv2):											__ft_iradians2,					\
		FT_MACRO_GROUP_TYPE(t_iv3):											__ft_iradians3,					\
		FT_MACRO_GROUP_TYPE(t_iv4):											__ft_iradians4					\
	)(__VA_ARGS__)

extern F32		__ft_degrees(float radians);
extern t_v2		__ft_degrees2(t_v2 radians);
extern t_v3		__ft_degrees3(t_v3 radians);
extern t_v4		__ft_degrees4(t_v4 radians);
extern t_iv2	__ft_idegrees2(t_iv2 radians);
extern t_iv3	__ft_idegrees3(t_iv3 radians);
extern t_iv4	__ft_idegrees4(t_iv4 radians);
#define ft_degrees(...)																						\
	_Generic(FT_MACRO_GROUP_TYPE_INST(__VA_ARGS__),															\
		FT_MACRO_GROUP_TYPE(double):										__ft_degrees,					\
		FT_MACRO_GROUP_TYPE(float):											__ft_degrees,					\
		FT_MACRO_GROUP_TYPE(int):											__ft_degrees,					\
		FT_MACRO_GROUP_TYPE(t_v2):											__ft_degrees2,					\
		FT_MACRO_GROUP_TYPE(t_v3):											__ft_degrees3,					\
		FT_MACRO_GROUP_TYPE(t_v4):											__ft_degrees4,					\
		FT_MACRO_GROUP_TYPE(t_iv2):											__ft_idegrees2,					\
		FT_MACRO_GROUP_TYPE(t_iv3):											__ft_idegrees3,					\
		FT_MACRO_GROUP_TYPE(t_iv4):											__ft_idegrees4					\
	)(__VA_ARGS__)




// Rotates a 2D vector around origin
extern t_v2 ft_rotate2(t_v2 v, float angle, t_v2 origin);

// Returns a random point on a circle of r=1
extern t_v2 ft_rand_circle(unsigned int seed);

// Returns a random float between 1 and 0
extern F32 ft_rand(int n);
// Returns a random float between 1 and 0
extern F32 ft_rand2(t_v2 st);

// Noise
extern F32 ft_noise2(t_v2 st);

extern S32		__ft_abs(int n);
extern F32		__ft_fabs(float n);
extern t_v2		__ft_abs2(t_v2 n);
extern t_v3		__ft_abs3(t_v3 n);
extern t_v4		__ft_abs4(t_v4 n);
extern t_iv2	__ft_iabs2(t_iv2 n);
extern t_iv3	__ft_iabs3(t_iv3 n);
extern t_iv4	__ft_iabs4(t_iv4 n);
#define ft_abs(...)																						\
	_Generic(FT_MACRO_GROUP_TYPE_INST(__VA_ARGS__),														\
		FT_MACRO_GROUP_TYPE(double):										__ft_fabs,					\
		FT_MACRO_GROUP_TYPE(float):											__ft_fabs,					\
		FT_MACRO_GROUP_TYPE(int):											__ft_abs,					\
		FT_MACRO_GROUP_TYPE(t_v2):											__ft_abs2,					\
		FT_MACRO_GROUP_TYPE(t_v3):											__ft_abs3,					\
		FT_MACRO_GROUP_TYPE(t_v4):											__ft_abs4,					\
		FT_MACRO_GROUP_TYPE(t_iv2):											__ft_iabs2,					\
		FT_MACRO_GROUP_TYPE(t_iv3):											__ft_iabs3,					\
		FT_MACRO_GROUP_TYPE(t_iv4):											__ft_iabs4					\
	)(__VA_ARGS__)

// Wraps n in [min, max]
extern S32 ft_wrap(int n, int min, int max);
// Wraps n in [min, max]
extern F32 ft_fwrap(float x, float min, float max);
// Returns true if number is between the specified range. (Inclusive)
extern S32 ft_isrange(int i, int min, int max);

// Returns the magnitude of n.
extern U64 ft_magnitude(long n);

// Check if a number is prime.
extern S32 ft_is_prime(int nb);

// Raises nb to power
extern S32 ft_pow(int nb, int power);

extern S32		__ft_min_f_2(float a, float b);
extern S32		__ft_min_f_3(float a, float b, float c);
extern S32		__ft_min_f_4(float a, float b, float c, float d);
extern S32		__ft_min_i_2(int a, int b);
extern S32		__ft_min_i_3(int a, int b, int c);
extern S32		__ft_min_i_4(int a, int b, int c, int d);

extern F32	 	__ft_min_v2(t_v2 a);
extern t_v2 	__ft_min_v2_2(t_v2 a, t_v2 b);
extern t_v2 	__ft_min_v2_3(t_v2 a, t_v2 b, t_v2 c);
extern t_v2 	__ft_min_v2_4(t_v2 a, t_v2 b, t_v2 c, t_v2 d);
extern S32		__ft_min_iv2(t_iv2 a);
extern t_iv2	__ft_min_iv2_2(t_iv2 a, t_iv2 b);
extern t_iv2	__ft_min_iv2_3(t_iv2 a, t_iv2 b, t_iv2 c);
extern t_iv2	__ft_min_iv2_4(t_iv2 a, t_iv2 b, t_iv2 c, t_iv2 d);


extern F32		__ft_min_v3(t_v3 a);
extern t_v3		__ft_min_v3_2(t_v3 a, t_v3 b);
extern t_v3		__ft_min_v3_3(t_v3 a, t_v3 b, t_v3 c);
extern t_v3		__ft_min_v3_4(t_v3 a, t_v3 b, t_v3 c, t_v3 d);
extern S32		__ft_min_iv3(t_iv3 a);
extern t_iv3	__ft_min_iv3_2(t_iv3 a, t_iv3 b);
extern t_iv3	__ft_min_iv3_3(t_iv3 a, t_iv3 b, t_iv3 c);
extern t_iv3	__ft_min_iv3_4(t_iv3 a, t_iv3 b, t_iv3 c, t_iv3 d);

extern F32		__ft_min_v4(t_v4 a);
extern t_v4		__ft_min_v4_2(t_v4 a, t_v4 b);
extern t_v4		__ft_min_v4_3(t_v4 a, t_v4 b, t_v4 c);
extern t_v4		__ft_min_v4_4(t_v4 a, t_v4 b, t_v4 c, t_v4 d);
extern S32		__ft_min_iv4(t_iv4 a);
extern t_iv4	__ft_min_iv4_2(t_iv4 a, t_iv4 b);
extern t_iv4	__ft_min_iv4_3(t_iv4 a, t_iv4 b, t_iv4 c);
extern t_iv4	__ft_min_iv4_4(t_iv4 a, t_iv4 b, t_iv4 c, t_iv4 d);

#define ft_min(...)															\
	_Generic(FT_MACRO_GROUP_TYPE_INST(__VA_ARGS__),							\
		FT_MACRO_GROUP_TYPE(float, float):					__ft_min_f_2,	\
		FT_MACRO_GROUP_TYPE(float, float, float):			__ft_min_f_3,	\
		FT_MACRO_GROUP_TYPE(float, float, float, float):	__ft_min_f_4,	\
																			\
		FT_MACRO_GROUP_TYPE(int, int):						__ft_min_i_2,	\
		FT_MACRO_GROUP_TYPE(int, int, int):					__ft_min_i_3,	\
		FT_MACRO_GROUP_TYPE(int, int, int, int):			__ft_min_i_4,	\
																			\
		FT_MACRO_GROUP_TYPE(t_v2):							__ft_min_v2,	\
		FT_MACRO_GROUP_TYPE(t_v2, t_v2):					__ft_min_v2_2,	\
		FT_MACRO_GROUP_TYPE(t_v2, t_v2, t_v2):				__ft_min_v2_3,	\
		FT_MACRO_GROUP_TYPE(t_v2, t_v2, t_v2, t_v2):		__ft_min_v2_4,	\
																			\
		FT_MACRO_GROUP_TYPE(t_iv2):							__ft_min_iv2,	\
		FT_MACRO_GROUP_TYPE(t_iv2, t_iv2):					__ft_min_iv2_2,	\
		FT_MACRO_GROUP_TYPE(t_iv2, t_iv2, t_iv2):			__ft_min_iv2_3,	\
		FT_MACRO_GROUP_TYPE(t_iv2, t_iv2, t_iv2, t_iv2):	__ft_min_iv2_4,	\
																			\
		FT_MACRO_GROUP_TYPE(t_v3):							__ft_min_v3,	\
		FT_MACRO_GROUP_TYPE(t_v3, t_v3):					__ft_min_v3_2,	\
		FT_MACRO_GROUP_TYPE(t_v3, t_v3, t_v3):				__ft_min_v3_3,	\
		FT_MACRO_GROUP_TYPE(t_v3, t_v3, t_v3, t_v3):		__ft_min_v3_4,	\
																			\
		FT_MACRO_GROUP_TYPE(t_iv3):							__ft_min_iv3,	\
		FT_MACRO_GROUP_TYPE(t_iv3, t_iv3):					__ft_min_iv3_2,	\
		FT_MACRO_GROUP_TYPE(t_iv3, t_iv3, t_iv3):			__ft_min_iv3_3,	\
		FT_MACRO_GROUP_TYPE(t_iv3, t_iv3, t_iv3, t_iv3):	__ft_min_iv3_4,	\
																			\
		FT_MACRO_GROUP_TYPE(t_v4):							__ft_min_v4,	\
		FT_MACRO_GROUP_TYPE(t_v4, t_v4):					__ft_min_v4_2,	\
		FT_MACRO_GROUP_TYPE(t_v4, t_v4, t_v4):				__ft_min_v4_3,	\
		FT_MACRO_GROUP_TYPE(t_v4, t_v4, t_v4, t_v4):		__ft_min_v4_4,	\
																			\
		FT_MACRO_GROUP_TYPE(t_iv4):							__ft_min_iv4,	\
		FT_MACRO_GROUP_TYPE(t_iv4, t_iv4):					__ft_min_iv4_2,	\
		FT_MACRO_GROUP_TYPE(t_iv4, t_iv4, t_iv4):			__ft_min_iv4_3,	\
		FT_MACRO_GROUP_TYPE(t_iv4, t_iv4, t_iv4, t_iv4):	__ft_min_iv4_4	\
																			\
	)(__VA_ARGS__)


extern F32		__ft_max_f_2(float a, float b);
extern F32		__ft_max_f_3(float a, float b, float c);
extern F32		__ft_max_f_4(float a, float b, float c, float d);
extern S32		__ft_max_i_2(int a, int b);
extern S32		__ft_max_i_3(int a, int b, int c);
extern S32		__ft_max_i_4(int a, int b, int c, int d);

extern F32	 	__ft_max_v2(t_v2 a);
extern t_v2 	__ft_max_v2_2(t_v2 a, t_v2 b);
extern t_v2 	__ft_max_v2_3(t_v2 a, t_v2 b, t_v2 c);
extern t_v2 	__ft_max_v2_4(t_v2 a, t_v2 b, t_v2 c, t_v2 d);
extern S32		__ft_max_iv2(t_iv2 a);
extern t_iv2	__ft_max_iv2_2(t_iv2 a, t_iv2 b);
extern t_iv2	__ft_max_iv2_3(t_iv2 a, t_iv2 b, t_iv2 c);
extern t_iv2	__ft_max_iv2_4(t_iv2 a, t_iv2 b, t_iv2 c, t_iv2 d);

extern F32		__ft_max_v3(t_v3 a);
extern t_v3		__ft_max_v3_2(t_v3 a, t_v3 b);
extern t_v3		__ft_max_v3_3(t_v3 a, t_v3 b, t_v3 c);
extern t_v3		__ft_max_v3_4(t_v3 a, t_v3 b, t_v3 c, t_v3 d);
extern S32		__ft_max_iv3(t_iv3 a);
extern t_iv3	__ft_max_iv3_2(t_iv3 a, t_iv3 b);
extern t_iv3	__ft_max_iv3_3(t_iv3 a, t_iv3 b, t_iv3 c);
extern t_iv3	__ft_max_iv3_4(t_iv3 a, t_iv3 b, t_iv3 c, t_iv3 d);

extern F32		__ft_max_v4(t_v4 a);
extern t_v4		__ft_max_v4_2(t_v4 a, t_v4 b);
extern t_v4		__ft_max_v4_3(t_v4 a, t_v4 b, t_v4 c);
extern t_v4		__ft_max_v4_4(t_v4 a, t_v4 b, t_v4 c, t_v4 d);
extern S32		__ft_max_iv4(t_iv4 a);
extern t_iv4	__ft_max_iv4_2(t_iv4 a, t_iv4 b);
extern t_iv4	__ft_max_iv4_3(t_iv4 a, t_iv4 b, t_iv4 c);
extern t_iv4	__ft_max_iv4_4(t_iv4 a, t_iv4 b, t_iv4 c, t_iv4 d);

#define ft_max(...)															\
	_Generic(FT_MACRO_GROUP_TYPE_INST(__VA_ARGS__),							\
		FT_MACRO_GROUP_TYPE(float, float):					__ft_max_f_2,	\
		FT_MACRO_GROUP_TYPE(float, float, float):			__ft_max_f_3,	\
		FT_MACRO_GROUP_TYPE(float, float, float, float):	__ft_max_f_4,	\
																			\
		FT_MACRO_GROUP_TYPE(int, int):						__ft_max_i_2,	\
		FT_MACRO_GROUP_TYPE(int, int, int):					__ft_max_i_3,	\
		FT_MACRO_GROUP_TYPE(int, int, int, int):			__ft_max_i_4,	\
																			\
		FT_MACRO_GROUP_TYPE(t_v2):							__ft_max_v2,	\
		FT_MACRO_GROUP_TYPE(t_v2, t_v2):					__ft_max_v2_2,	\
		FT_MACRO_GROUP_TYPE(t_v2, t_v2, t_v2):				__ft_max_v2_3,	\
		FT_MACRO_GROUP_TYPE(t_v2, t_v2, t_v2, t_v2):		__ft_max_v2_4,	\
																			\
		FT_MACRO_GROUP_TYPE(t_iv2):							__ft_max_iv2,	\
		FT_MACRO_GROUP_TYPE(t_iv2, t_iv2):					__ft_max_iv2_2,	\
		FT_MACRO_GROUP_TYPE(t_iv2, t_iv2, t_iv2):			__ft_max_iv2_3,	\
		FT_MACRO_GROUP_TYPE(t_iv2, t_iv2, t_iv2, t_iv2):	__ft_max_iv2_4,	\
																			\
		FT_MACRO_GROUP_TYPE(t_v3):							__ft_max_v3,	\
		FT_MACRO_GROUP_TYPE(t_v3, t_v3):					__ft_max_v3_2,	\
		FT_MACRO_GROUP_TYPE(t_v3, t_v3, t_v3):				__ft_max_v3_3,	\
		FT_MACRO_GROUP_TYPE(t_v3, t_v3, t_v3, t_v3):		__ft_max_v3_4,	\
																			\
		FT_MACRO_GROUP_TYPE(t_iv3):							__ft_max_iv3,	\
		FT_MACRO_GROUP_TYPE(t_iv3, t_iv3):					__ft_max_iv3_2,	\
		FT_MACRO_GROUP_TYPE(t_iv3, t_iv3, t_iv3):			__ft_max_iv3_3,	\
		FT_MACRO_GROUP_TYPE(t_iv3, t_iv3, t_iv3, t_iv3):	__ft_max_iv3_4,	\
																			\
		FT_MACRO_GROUP_TYPE(t_v4):							__ft_max_v4,	\
		FT_MACRO_GROUP_TYPE(t_v4, t_v4):					__ft_max_v4_2,	\
		FT_MACRO_GROUP_TYPE(t_v4, t_v4, t_v4):				__ft_max_v4_3,	\
		FT_MACRO_GROUP_TYPE(t_v4, t_v4, t_v4, t_v4):		__ft_max_v4_4,	\
																			\
		FT_MACRO_GROUP_TYPE(t_iv4):							__ft_max_iv4,	\
		FT_MACRO_GROUP_TYPE(t_iv4, t_iv4):					__ft_max_iv4_2,	\
		FT_MACRO_GROUP_TYPE(t_iv4, t_iv4, t_iv4):			__ft_max_iv4_3,	\
		FT_MACRO_GROUP_TYPE(t_iv4, t_iv4, t_iv4, t_iv4):	__ft_max_iv4_4	\
																			\
	)(__VA_ARGS__)


extern F32	__ft_lerp(float a, float b, float t);
extern t_v2	__ft_lerp2(t_v2 a, t_v2 b, float t);
extern t_v3	__ft_lerp3(t_v3 v_1, t_v3 v_2, float t);
extern t_v4	__ft_lerp4(t_v4 v_1, t_v4 v_2, float t);
#define ft_lerp(...)												\
	_Generic(FT_MACRO_GROUP_TYPE_INST(__VA_ARGS__),					\
		FT_MACRO_GROUP_TYPE(float, float, float):		__ft_lerp,	\
		FT_MACRO_GROUP_TYPE(t_v2, t_v2, float):			__ft_lerp2,	\
		FT_MACRO_GROUP_TYPE(t_v3, t_v3, float):			__ft_lerp3,	\
		FT_MACRO_GROUP_TYPE(t_v4, t_v4, float):			__ft_lerp4	\
	)(__VA_ARGS__)

extern F32	__ft_invlerp(float a, float b, float t);
extern t_v2	__ft_invlerp2(t_v2 a, t_v2 b, t_v2 t);
extern t_v3	__ft_invlerp3(t_v3 v_1, t_v3 v_2, t_v3 t);
extern t_v4	__ft_invlerp4(t_v4 v_1, t_v4 v_2, t_v4 t);
#define ft_invlerp(...)												\
	_Generic(FT_MACRO_GROUP_TYPE_INST(__VA_ARGS__),					\
		FT_MACRO_GROUP_TYPE(float, float, float):		__ft_invlerp,	\
		FT_MACRO_GROUP_TYPE(t_v2, t_v2, t_v2):			__ft_invlerp2,	\
		FT_MACRO_GROUP_TYPE(t_v3, t_v3, t_v3):			__ft_invlerp3,	\
		FT_MACRO_GROUP_TYPE(t_v4, t_v4, t_v4):			__ft_invlerp4	\
	)(__VA_ARGS__)

extern F32	__ft_smoothstep(float a, float b, float t);
extern t_v2	__ft_smoothstep2(t_v2 a, t_v2 b, t_v2 t);
extern t_v3	__ft_smoothstep3(t_v3 v_1, t_v3 v_2, t_v3 t);
extern t_v4	__ft_smoothstep4(t_v4 v_1, t_v4 v_2, t_v4 t);
#define ft_smoothstep(...)												\
	_Generic(FT_MACRO_GROUP_TYPE_INST(__VA_ARGS__),					\
		FT_MACRO_GROUP_TYPE(float, float, float):		__ft_smoothstep,	\
		FT_MACRO_GROUP_TYPE(t_v2, t_v2, t_v2):			__ft_smoothstep2,	\
		FT_MACRO_GROUP_TYPE(t_v3, t_v3, t_v3):			__ft_smoothstep3,	\
		FT_MACRO_GROUP_TYPE(t_v4, t_v4, t_v4):			__ft_smoothstep4	\
	)(__VA_ARGS__)

// Maps v from range [from.x, from.y] to range [to.x, to.y]
extern F32 ft_map(float v, t_v2 from, t_v2 to);

// Clamp
extern S32 ft_clamp(int min, int max, int v);
// Clamp for floats
extern F32 ft_clampf(float min, float max, float v);

// Returns the distance from p to line [s1;s2]
extern F32 ft_dist_line(t_v2 p, t_v2 s1, t_v2 s2);
// Distance between 2 2D points
extern F32 ft_dist2(t_v2 p1, t_v2 p2);
// Distance between 2 2D points raised to the power of 2
extern F32 ft_sqrdist2(t_v2 p1, t_v2 p2);
// Distance between 2 3D points
extern F32 ft_dist3(t_v3 p1, t_v3 p2);
// Distance between 2 3D points raised to the power of 2
extern F32 ft_sqrdist3(t_v3 p1, t_v3 p2);

// Normalizes a 3D vector
extern t_v3 ft_normalize3(t_v3 v);
// Normalizes a 2D vector
extern t_v2 ft_normalize2(t_v2 v);
// Dot product of a 2D vector
extern F32 ft_dot2(t_v2 a, t_v2 b);
// Dot product of a 3D vector
extern F32 ft_dot3(t_v3 a, t_v3 b);
extern t_v3 ft_cross3(t_v3 a, t_v3 b);

// Fractional part of v
extern F32 ft_frac(float v);
// Fractional part of v
extern t_v2 ft_frac2(t_v2 v);

//================MATHS================

extern int ft_cmpint(void *i1, void *i2);
extern int ft_cmpaddr(void *p1, void *p2);

//=================STD=================
// MEM
// Writes n zeroed bytes to the string s.
extern void ft_bzero(void *s, U64 n);
// Locates the first occurrence of c in string s.
extern void *ft_memchr(void const *s, U8 c, U64 n);
// Compares byte string s1 against byte string s2.
extern S32 ft_memcmp(void const *s1, void const *s2, U64 n);
/*Copies n bytes from memory area src to memory area dst.
The two strings may not overlap. If they do use ft_memmove instead.*/
extern void *ft_memcpy(void *dst, void const *src, U64 n);
/*Duplicated n bytes of src.
Caller owns returned value*/
extern void *ft_memdup(void const *src, U64 n);
/*Copies len bytes from string src to string dst. The two strings may overlap;
the copy is always done in a non-destructive manner.*/
extern void *ft_memmove(void *dst, void const *src, U64 len);
// Writes len bytes of value c.
extern void *ft_memset(void *b, U8 c, U64 len);
// MEM

// STR->INT INT->STR
// Converts a string to an int.
extern S32 ft_atoi(const_string str, U64 *out);
// Converts a string to a float.
extern F32 ft_atof(const_string str, U64 *len);
// Converts a hex string to a unsigned int.
extern U32 ft_atoix(const_string str, U64 *len);
/*Converts an int to a string.
Caller owns returned value*/
extern string ft_itoa(S32 n);
/*Converts an unsigned int to a string.
Caller owns returned value*/
extern string ft_uitoa(U32 n);
/*Converts a float to a string.
Caller owns returned value*/
extern string ft_ftoa(float n);
// STR->INT INT->STR

// PUTFD
// Writes character c in file descriptor fd.
extern void ft_putchar_fd(char c, file fd);
// Write string s in file descriptor fd.
extern void ft_putstr_fd(string s, file fd);
// Write s in file fd, and append a line end.
extern void ft_putendl_fd(string s, file fd);
// Write a number in file descriptor fd.
extern void ft_putnbr_fd(int n, file fd);
// PUTFD

// CHAR/STR CHECKS
// Check if character is digit or alpha.
extern bool ft_isalnum(U8 c);
// Check if character is alpha.
extern bool ft_isalpha(U8 c);
// Check if character is ascii.
extern bool ft_isascii(U8 c);
// Check if character is digit.
extern bool ft_isdigit(U8 c);
// Check if character is printable.
extern bool ft_isprint(U8 c);

// Check if null-terminated string str is digit or alpha-numerical.
extern bool ft_str_isalnum(U8 c);
// Check if null-terminated string str is alpha.
extern bool ft_str_isalpha(U8 c);
// Check if null-terminated string str is ascii.
extern bool ft_str_isascii(U8 c);
// Check if null-terminated string str is digit-only.
extern bool ft_str_isdigit(string str);
// Check if null-terminated string str is printable.
extern bool ft_str_isprint(U8 c);
// CHAR/STR CHECKS

// FILE I/O
// Reads the whole file
extern char *ft_readfile(file fd, U64 read_size);
// Read the next line in fd, NULL if all lines are read.
extern char *ft_gnl(file fd);
// FILE I/O

// RANGE
// Creates an array of int from min to max.
extern S32 *ft_range(S32 min, S32 max);
// Creates an array of int from min to max and returns the size of the array.
extern S32 ft_nrange(S32 **range, S32 min, S32 max);
// RANGE

// Printf
extern int ft_printf(const_string str, ...);
//=================STD=================

//===============STRINGS===============
// STRINGS
/*Append a at the end of b.
Caller gets ownership of returned string.*/
extern string ft_str_append(string a, string b, bool free_a, bool free_b);
// Append src behind dest. dest must have enough space, including \0
extern string ft_strcat(string dest, const_string src);
/*Appends string src to the end of dst.
It will append at most dstsize - strlen(dst) - 1 characters.
It will then NUL-terminate the new string*/
extern U64 ft_strlcat(string dest, const_string src, U64 size);
/*Concatenate s1 and s2.
Caller gets ownership of returned string.*/
extern string ft_strjoin(const_string s1, const_string s2);

/*Copies up to dstsize - 1 characters from the string src to dst,
NUL-terminating the result if dstsize is not 0.*/
extern U64 ft_strlcpy(string dest, const_string src, U64 size);
/*Duplicates the string s1 into a new char array.
Caller gets ownership of returned string.*/
extern string ft_strdup(const_string s1);
/*Returns a new string from s, starting at index start with size len.
Caller gets ownership of returned string.*/
extern string ft_substr(const_string s, U64 start, U64 len);

/*Locates the first occurrence of c in the string pointed to by s.
The terminating null character taken into account.*/
extern const_string ft_strchr(const_string str, U8 c);
/*Locates the first occurrence of c in the string pointed to by s, searching at most len characters.
The terminating null character taken into account.*/
extern const_string ft_strnchr(const_string str, U8 c, U64 len);

/*Locates the first occurrence of the null-terminated string needle in the
string haystack, where not more than len characters are searched.
If to_find is an empty string, str is returned; if to_find occurs
nowhere in str, NULL is returned; otherwise a pointer to the first
character of the first occurrence of to_find is returned.*/
extern const_string ft_strnstr(const_string haystack, const_string needle, U64 len);
// Locates the last occurrence of c in string s
extern const_string ft_strrchr(const_string str, U8 c);

// Returns the length of string
extern U64 ft_strlen(const_string str);
// Returns the index of the first occurrence of c in str, -1 if not found.
extern S64 ft_strgetindex(const_string str, U8 c);

// Compares string s1 against string s2. Returns s1 - s2
extern S32 ft_strncmp(const_string s1, const_string s2, U64 n);

// Converts a lower-case letter to the corresponding upper-case letter.
extern U8 ft_tolower(U8 c);
// Converts a upper-case letter to the corresponding lower-case letter.
extern U8 ft_toupper(U8 c);
// Creates a copy of s1 wihout the characters in set at end and start of string.
extern string ft_strtrim(const_string s1, const_string set);

/*Applies function f to each characters in string str, and returns
a new string of all the results of f.
Caller gets ownership of returned string.*/
extern string ft_strmapi(const_string str, U8 (*f)(U64 index, U8));
// Applies function f to each characters in string s.
extern void ft_striteri(string str, void (*f)(U64 index, string str));
// STRINGS
//===============STRINGS===============

// Splits string s by separator c.
__attribute_deprecated__ extern string *ft_split(const_string str, U8 c);
/*Duplicates a split
Caller gets ownership of returned string.*/
__attribute_deprecated__ extern string *ft_dupsplit(const_string *split);
/*Free a split
Caller gets ownership of returned string.*/
__attribute_deprecated__ extern void ft_freesplit(string *split);
/*Returns the length of a split
Caller gets ownership of returned string.*/
__attribute_deprecated__ extern U64 ft_splitlen(const_string *split);


//================ERROR================

#ifndef FT_CUSTOM_OFFSET
# define FT_CUSTOM_OFFSET 0
#endif

#define FT_OK							0
#define FT_OMEM							1 + FT_CUSTOM_OFFSET
#define FT_BAD_FD						2 + FT_CUSTOM_OFFSET

#define FT_MAP_FULL						3 + FT_CUSTOM_OFFSET			/* Hashmap is full */
#define FT_MAP_MISSING					4 + FT_CUSTOM_OFFSET			/* No such element */

#define FT_ERROR_VALUES_OFFSET			4 + FT_CUSTOM_OFFSET

static const const_string	ft_error_lookup_table[] = {
	"SUCCESS",
	"FT_OMEM",
	"FT_BAD_FD",
	"FT_MAP_FULL",
	"FT_MAP_MISSING",
};

# define FT_ERROR_LOOKUP(CODE) (CODE==0 || CODE > FT_CUSTOM_OFFSET && CODE <= FT_ERROR_VALUES_OFFSET) ? ft_error_lookup_table[CODE == 0 ? CODE : CODE - FT_CUSTOM_OFFSET] : "NO ERROR INFO"


//================ERROR================
#endif


