/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 17:02:52 by reclaire          #+#    #+#             */
/*   Updated: 2024/01/12 11:36:33 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
regex to match all functions names:
extern\s*[a-zA-Z0-9_]*\s*[\*]*?ft_([a-zA-Z0-9_]*)
*/

/*
FT_CONFIG
TOGGLES:
	FT_MACROS
		FT_VA_OPT

	FT_STRINGS
	FT_FILEIO
	FT_STD
	FT_ANSI
	FT_LISTS
	FT_HASHMAPS
	FT_DEBUG
		FT_MEMCHECK
	FT_TIME
	FT_MATHS

Define FT_CONFIG to configure exactly what you need
*/

#if !defined(LIBFT_H)
# define LIBFT_H

# if defined(__cplusplus)
extern "C" {
# endif

# if !defined(FT_WIN32) && !defined(FT_OSX) && !defined(FT_LINUX)
#  warning No platform seem to be specified, errors WILL occur.
# endif

//Silence __attribute__ errors from vscode intellisense
# if defined(FT_WIN32)
#  define __attribute__(x)
# endif

//Temporary
# define FT_NO_ARRAYS
# define FT_NO_HASHMAPS
# if defined(FT_WIN32)
#  define FT_NO_MEMCHECK
# endif

//CONFIG
# if !defined(FT_CONFIG)

#  if !defined(FT_NO_MACROS)
#   define FT_MACROS
#   if !defined(FT_NO_VA_OPT)
#    define FT_VA_OPT
#   endif
#  endif

#  if !defined(FT_NO_STRINGS)
#   define FT_STRINGS
#  endif

#  if !defined(FT_NO_FILE_IO)
#   define FT_FILEIO
#  endif

#  if !defined(FT_NO_STD)
#   define FT_STD
#  endif

#  if !defined(FT_NO_ANSI)
#   define FT_ANSI
#  endif

#  if !defined(FT_NO_ARRAYS)
#   define FT_ARRAYS
#  endif

#  if !defined(FT_NO_LISTS)
#   define FT_LISTS
#  endif

#  if !defined(FT_NO_HASHMAPS)
#   define FT_HASHMAPS
#  endif

#  if !defined(FT_NO_DEBUG)
#   define FT_DEBUG
#   if !defined(FT_NO_MEMCHECK)
#    define FT_MEMCHECK
#   endif
#  endif

#  if !defined(FT_NO_TIME)
#   define FT_TIME
#  endif

#  if !defined(FT_NO_MATHS)
#   define FT_MATHS
#  endif

# endif





# if defined(FT_MACROS)
//EXPENSION
#  define	FT_EXP(x) x
//CONCAT
#  define	FT_CONCAT(X, Y) X##Y

//REMOVE PARENTHESIS
#  define FT_DEPAREN(X) __ESC(__ISH X)
#  define __ISH(...) __ISH __VA_ARGS__
#  define __ESC(...) __ESC_(__VA_ARGS__)
#  define __ESC_(...) __VAN ## __VA_ARGS__
#  define __VAN__ISH

/* __VA_ARGS__ UTILS */
/* REMOVE N FIRST ARGS */
#  define FT_VA_ARG_REMOVE_FIRST(N, ...) __FT_VA_ARG_REMOVE_FIRST_##N(__VA_ARGS__)
#  define __FT_VA_ARG_REMOVE_FIRST_1(X, ...) __VA_ARGS__
#  define __FT_VA_ARG_REMOVE_FIRST_2(X, ...) __FT_VA_ARG_REMOVE_FIRST_1(__VA_ARGS__)
#  define __FT_VA_ARG_REMOVE_FIRST_3(X, ...) __FT_VA_ARG_REMOVE_FIRST_2(__VA_ARGS__)
#  define __FT_VA_ARG_REMOVE_FIRST_4(X, ...) __FT_VA_ARG_REMOVE_FIRST_3(__VA_ARGS__)
#  define __FT_VA_ARG_REMOVE_FIRST_5(X, ...) __FT_VA_ARG_REMOVE_FIRST_4(__VA_ARGS__)
#  define __FT_VA_ARG_REMOVE_FIRST_6(X, ...) __FT_VA_ARG_REMOVE_FIRST_5(__VA_ARGS__)
#  define __FT_VA_ARG_REMOVE_FIRST_7(X, ...) __FT_VA_ARG_REMOVE_FIRST_6(__VA_ARGS__)
#  define __FT_VA_ARG_REMOVE_FIRST_8(X, ...) __FT_VA_ARG_REMOVE_FIRST_7(__VA_ARGS__)
#  define __FT_VA_ARG_REMOVE_FIRST_9(X, ...) __FT_VA_ARG_REMOVE_FIRST_8(__VA_ARGS__)
#  define __FT_VA_ARG_REMOVE_FIRST_10(X, ...) __FT_VA_ARG_REMOVE_FIRST_9(__VA_ARGS__)
#  define __FT_VA_ARG_REMOVE_FIRST_11(X, ...) __FT_VA_ARG_REMOVE_FIRST_10(__VA_ARGS__)
#  define __FT_VA_ARG_REMOVE_FIRST_12(X, ...) __FT_VA_ARG_REMOVE_FIRST_11(__VA_ARGS__)
#  define __FT_VA_ARG_REMOVE_FIRST_13(X, ...) __FT_VA_ARG_REMOVE_FIRST_12(__VA_ARGS__)
#  define __FT_VA_ARG_REMOVE_FIRST_14(X, ...) __FT_VA_ARG_REMOVE_FIRST_13(__VA_ARGS__)
#  define __FT_VA_ARG_REMOVE_FIRST_15(X, ...) __FT_VA_ARG_REMOVE_FIRST_14(__VA_ARGS__)
#  define __FT_VA_ARG_REMOVE_FIRST_16(X, ...) __FT_VA_ARG_REMOVE_FIRST_15(__VA_ARGS__)
/* REMOVE N FIRST ARGS */

/* COUNT VA ARG */
#  define FT_VA_ARG_COUNT(...) \
         __FT_VA_ARG_COUNT(__VA_ARGS__,__FT_VA_ARG_COUNT_RSEQ_N())
#  define __FT_VA_ARG_COUNT(...) \
         __FT_VA_ARG_COUNT_N(__VA_ARGS__)
#  define __FT_VA_ARG_COUNT_N( \
          _1, _2, _3, _4, _5, _6, _7, _8, _9,_10, \
         _11,_12,_13,_14,_15,_16,_17,_18,_19,_20, \
         _21,_22,_23,_24,_25,_26,_27,_28,_29,_30, \
         _31,_32,_33,_34,_35,_36,_37,_38,_39,_40, \
         _41,_42,_43,_44,_45,_46,_47,_48,_49,_50, \
         _51,_52,_53,_54,_55,_56,_57,_58,_59,_60, \
         _61,_62,_63,N,...) N
#  define __FT_VA_ARG_COUNT_RSEQ_N() \
         63,62,61,60,                   \
         59,58,57,56,55,54,53,52,51,50, \
         49,48,47,46,45,44,43,42,41,40, \
         39,38,37,36,35,34,33,32,31,30, \
         29,28,27,26,25,24,23,22,21,20, \
         19,18,17,16,15,14,13,12,11,10, \
         9,8,7,6,5,4,3,2,1,0
/* COUNT VA ARG */

/* REVERSE VA ARG */
#  define __reverse_1(a) a
#  define __reverse_2(a, b) b, a
#  define __reverse_3(a, ...) __reverse_2(__VA_ARGS__), a
#  define __reverse_4(a, ...) __reverse_3(__VA_ARGS__), a
#  define __reverse_5(a, ...) __reverse_4(__VA_ARGS__), a
#  define __reverse_6(a, ...) __reverse_5(__VA_ARGS__), a
#  define __reverse_7(a, ...) __reverse_6(__VA_ARGS__), a
#  define __reverse_8(a, ...) __reverse_7(__VA_ARGS__), a
#  define __reverse_9(a, ...) __reverse_8(__VA_ARGS__), a
#  define __reverse_10(a, ...) __reverse_9(__VA_ARGS__), a
#  define __reverse_11(a, ...) __reverse_10(__VA_ARGS__), a
#  define __reverse_12(a, ...) __reverse_11(__VA_ARGS__), a
#  define __reverse_13(a, ...) __reverse_12(__VA_ARGS__), a
#  define __reverse_14(a, ...) __reverse_13(__VA_ARGS__), a
#  define __reverse_15(a, ...) __reverse_14(__VA_ARGS__), a
#  define __reverse_16(a, ...) __reverse_15(__VA_ARGS__), a
#  define __reverse1(N, ...) __reverse_##N(__VA_ARGS__)
#  define FT_MACRO_REVERSE(N, ...) __reverse1(N, __VA_ARGS__)
/* REVERSE VA ARG */


#  define FT_EXPAND(...) __VA_ARGS__
#  define FT_POP(X, ...) __VA_ARGS__
#  define FT_PUSH(X, ...) X, __VA_ARGS__
#  define FT_APPEND(X, ...) __VA_ARGS__, X
#  define FT_TOP(X, ...) X
#  define FT_VOID(...)
/* __VA_ARGS__ UTILS */

#  if defined(FT_VA_OPT)
#   ifndef FT_VA_OPT
#    define FT_VA_OPT
#   endif
//https://www.scs.stanford.edu/~dm/blog/va-opt.html

/* VA ARG FOREACH */
#   define __parens ()
#   define __expand(...) __expand_4(__expand_4(__expand_4(__expand_4(__VA_ARGS__))))
#   define __expand_4(...) __expand_3(__expand_3(__expand_3(__expand_3(__VA_ARGS__))))
#   define __expand_3(...) __expand_2(__expand_2(__expand_2(__expand_2(__VA_ARGS__))))
#   define __expand_2(...) __expand_1(__expand_1(__expand_1(__expand_1(__VA_ARGS__))))
#   define __expand_1(...) __VA_ARGS__
#   define FT_MACRO_FOR_EACH(macro, ...) __VA_OPT__(__expand(__for_each_helper(macro, __VA_ARGS__)))
#   define __for_each_helper(macro, a1, ...)	\
	macro(a1)								\
		__VA_OPT__(, __for_each_again __parens(macro, __VA_ARGS__))
#   define __for_each_again() __for_each_helper
/* VA ARG FOREACH */


/* VA ARG FOREACH BUT WITH sep BETWEEN EACH macro(x) -> FT_MACRO_FOR_EACH_sep(FT_EXP, %, a, b, c) -> a % b % c */
#   define FT_MACRO_FOR_EACH_sep(macro, sep, ...) __VA_OPT__(__expand(__for_each_sep_helper(macro, sep, __VA_ARGS__)))
#   define __for_each_sep_helper(macro, sep, a1, ...)	\
	macro(a1)								\
		__VA_OPT__(sep __for_each_sep_again __parens(macro, sep, __VA_ARGS__))
#   define __for_each_sep_again() __for_each_sep_helper

#   define FT_MACRO_FOR_EACH_sep_arg(macro, sep, arg, ...) __VA_OPT__(__expand(__for_each_sep_arg_helper(macro, sep, arg, __VA_ARGS__)))
#   define __for_each_sep_arg_helper(macro, sep, arg, a1, ...)	\
	macro(FT_DEPAREN(arg), a1)								\
		__VA_OPT__(sep __for_each_sep_arg_again __parens(macro, sep, arg, __VA_ARGS__))
#   define __for_each_sep_arg_again() __for_each_sep_arg_helper
/* VA ARG FOREACH BUT WITH sep BETWEEN EACH macro(x) -> FT_MACRO_FOR_EACH_sep(FT_EXP, %, a, b, c) -> a % b % c */

/* VA ARG FOREACH 2 (for nested FOREACH)*/
#   define __parens2 ()
#   define __expand2(...) __expand2_4(__expand2_4(__expand2_4(__expand2_4(__VA_ARGS__))))
#   define __expand2_4(...) __expand2_3(__expand2_3(__expand2_3(__expand2_3(__VA_ARGS__))))
#   define __expand2_3(...) __expand2_2(__expand2_2(__expand2_2(__expand2_2(__VA_ARGS__))))
#   define __expand2_2(...) __expand2_1(__expand2_1(__expand2_1(__expand2_1(__VA_ARGS__))))
#   define __expand2_1(...) __VA_ARGS__
#   define FT_MACRO_FOR_EACH2(macro, ...) __VA_OPT__(__expand2(__for_each_helper2(macro, __VA_ARGS__)))
#   define __for_each_helper2(macro, a1, ...)	\
	macro(a1)								\
		__VA_OPT__(, __for_each_again2 __parens2(macro, __VA_ARGS__))
#   define __for_each_again2() __for_each_helper2
/* VA ARG FOREACH 2 (for nested FOREACH)*/

/* VA ARG FOREACH WITH macro_args PASSED TO macro*/
#   define __parens3 ()
#   define __expand3(...) __expand3_4(__expand3_4(__expand3_4(__expand3_4(__VA_ARGS__))))
#   define __expand3_4(...) __expand3_3(__expand3_3(__expand3_3(__expand3_3(__VA_ARGS__))))
#   define __expand3_3(...) __expand3_2(__expand3_2(__expand3_2(__expand3_2(__VA_ARGS__))))
#   define __expand3_2(...) __expand3_1(__expand3_1(__expand3_1(__expand3_1(__VA_ARGS__))))
#   define __expand3_1(...) __VA_ARGS__
#   define FT_MACRO_FOR_EACH_arg(macro, macro_args, ...) __VA_OPT__(__expand3(__for_each_helper_arg(macro, macro_args, __VA_ARGS__)))
#   define __for_each_helper_arg(macro, macro_args, a1, ...)	\
	macro(FT_DEPAREN(macro_args), a1)								\
		__VA_OPT__(, __for_each_again_arg __parens3(macro, macro_args, __VA_ARGS__))
#   define __for_each_again_arg() __for_each_helper_arg
/* VA ARG FOREACH WITH macro_args PASSED TO macro*/

/* VA ARG FOREACH WITH macro_args PASSED TO macro 2 (for nested FOREACH_arg)*/
#   define __parens4 ()
#   define __expand4(...) __expand4_4(__expand4_4(__expand4_4(__expand4_4(__VA_ARGS__))))
#   define __expand4_4(...) __expand4_3(__expand4_3(__expand4_3(__expand4_3(__VA_ARGS__))))
#   define __expand4_3(...) __expand4_2(__expand4_2(__expand4_2(__expand4_2(__VA_ARGS__))))
#   define __expand4_2(...) __expand4_1(__expand4_1(__expand4_1(__expand4_1(__VA_ARGS__))))
#   define __expand4_1(...) __VA_ARGS__
#   define FT_MACRO_FOR_EACH_arg2(macro, macro_args, ...) __VA_OPT__(__expand4(__for_each_helper_arg2(macro, macro_args, __VA_ARGS__)))
#   define __for_each_helper_arg2(macro, macro_args, a1, ...)	\
	macro(FT_DEPAREN(macro_args), a1)								\
		__VA_OPT__(, __for_each_again_arg2 __parens4(macro, macro_args, __VA_ARGS__))
#   define __for_each_again_arg2() __for_each_helper_arg2

#   define FT_MACRO_GROUP_TYPE(...) void (*)(__VA_ARGS__)
#   define FT_MACRO_GROUP_TYPE_INST(...) (void (*)(FT_MACRO_FOR_EACH(typeof, __VA_ARGS__)))0
/* VA ARG FOREACH WITH macro_args PASSED TO macro 2 (for nested FOREACH_arg)*/


/* OVERLOAD */
#   define __flparens ()
#   define __flexpand(...) __flexpand_4(__flexpand_4(__flexpand_4(__flexpand_4(__VA_ARGS__))))
#   define __flexpand_4(...) __flexpand_3(__flexpand_3(__flexpand_3(__flexpand_3(__VA_ARGS__))))
#   define __flexpand_3(...) __flexpand_2(__flexpand_2(__flexpand_2(__flexpand_2(__VA_ARGS__))))
#   define __flexpand_2(...) __flexpand_1(__flexpand_1(__flexpand_1(__flexpand_1(__VA_ARGS__))))
#   define __flexpand_1(...) __VA_ARGS__
#   define fix_list(...) __VA_OPT__(__flexpand(__fl_helper(__VA_ARGS__)))
#   define __fl_nempty(...) __VA_OPT__(__VA_ARGS__)
#   define __fl_helper(a1, ...) __fl_nempty(a1)	 __VA_OPT__(, __fl_again __flparens(__VA_ARGS__))
#   define __fl_again() __fl_helper


#   define DO_COMBS(M, MA, ...) __VA_OPT__(fix_list(__expand(__do_combs_helper(M, MA, (), __VA_ARGS__))))

#   define first_arg(opt) FT_TOP opt
#   define rm_first_arg(opt) (FT_POP opt)

#   define _next_opt(M, MA, lst, ...) __VA_OPT__(__do_combs_again __parens(M, MA, lst, __VA_ARGS__))
#   define __all_opt(M, MA, lst, opt, todo, ...) __VA_OPT__(__do_combs_again __parens(M, MA, lst, opt, FT_DEPAREN(todo)))
#   define _all_opt(M, MA, lst, opt, ...) __all_opt(M, MA, lst, opt, (__VA_ARGS__), FT_DEPAREN(opt))

#   define comma_if_not_empty(...) __VA_OPT__(__VA_ARGS__,)

#   define generate(M, MA, lst) FT_EXPAND(M(MA, lst)),
#   define try_generate(M, MA, lst, opt, ...) FT_DEPAREN(__VA_OPT__(FT_VOID)(generate(M, MA, (comma_if_not_empty(FT_DEPAREN(lst)) first_arg(opt)))))


#   define __do_combs_helper(M, MA, lst, opt, ...)	\
	try_generate(M, MA, lst, opt, __VA_ARGS__) \
	_next_opt(M, MA, (comma_if_not_empty(FT_DEPAREN(lst)) first_arg(opt)), __VA_ARGS__) \
	_all_opt(M, MA, lst, rm_first_arg(opt), __VA_ARGS__)

#   define __do_combs_again() __do_combs_helper

#   define build(f, X) FT_MACRO_GROUP_TYPE(FT_DEPAREN(X)): f
#   define do_one(f, ...) DO_COMBS(build, f, __VA_ARGS__)
#   define parse_args(X) do_one X


#   define OVERLOAD(args, ...)								\
	_Generic(FT_MACRO_GROUP_TYPE_INST args,				\
		FT_MACRO_FOR_EACH2(parse_args, __VA_ARGS__)		\
	)args
/* OVERLOAD */
/*
The most cursed C macro in existence to this day.

Provides full C function.
Usage:

#define my_c_overloaded_function(...) OVERLOAD((__VA_ARGS__)	\
	(my_c_overloaded_function1, (char*)),						\
	(my_c_overloaded_function1, (char*, void*)),				\
	(my_c_overloaded_function1, (float, double, int)),			\
)

*/


#  endif /* FT_VA_OPT */
# endif /* FT_MACROS */

# if defined(FT_ANSI)
#  define FT_BLACK						"\e[0;30m"
#  define FT_RED						"\e[0;31m"
#  define FT_GREEN						"\e[0;32m"
#  define FT_YELLOW						"\e[0;33m"
#  define FT_BLUE						"\e[0;34m"
#  define FT_MAGENTA					"\e[0;35m"
#  define FT_CYAN						"\e[0;36m"
#  define FT_WHITE						"\e[0;37m"
#  define FT_DEFAULT					"\e[0;39m"

#  define FT_LBLACK						"\e[0;90m"
#  define FT_LRED						"\e[0;91m"
#  define FT_LGREEN						"\e[0;92m"
#  define FT_LYELLOW					"\e[0;93m"
#  define FT_LBLUE						"\e[0;94m"
#  define FT_LMAGENTA					"\e[0;95m"
#  define FT_LCYAN						"\e[0;96m"
#  define FT_LWHITE						"\e[0;97m"
#  define FT_LDEFAULT					"\e[0;99m"

#  define FT_BG_BLACK					"\e[0;40m"
#  define FT_BG_RED						"\e[0;41m"
#  define FT_BG_GREEN					"\e[0;42m"
#  define FT_BG_YELLOW					"\e[0;43m"
#  define FT_BG_BLUE					"\e[0;44m"
#  define FT_BG_MAGENTA					"\e[0;45m"
#  define FT_BG_CYAN					"\e[0;46m"
#  define FT_BG_WHITE					"\e[0;47m"
#  define FT_BG_DEFAULT					"\e[0;49m"

#  define FT_BG_LBLACK					"\e[0;100m"
#  define FT_BG_LRED					"\e[0;101m"
#  define FT_BG_LGREEN					"\e[0;102m"
#  define FT_BG_LYELLOW					"\e[0;103m"
#  define FT_BG_LBLUE					"\e[0;104m"
#  define FT_BG_LMAGENTA				"\e[0;105m"
#  define FT_BG_LCYAN					"\e[0;106m"
#  define FT_BG_LWHITE					"\e[0;107m"
#  define FT_BG_LDEFAULT				"\e[0;109m"

#  define FT_BOLD						"\e[1m"
#  define FT_DIM						"\e[2m"
#  define FT_ITALIC						"\e[3m"
#  define FT_UNDERLINE					"\e[4m"
#  define FT_BLINK						"\e[5m"
#  define FT_BLINK_FAST					"\e[6m"
#  define FT_INVERSE					"\e[7m"
#  define FT_INVISIBLE					"\e[8m"
#  define FT_STRIKETHROUGH				"\e[9m"
#  define FT_FONT1						"\e[10m"
#  define FT_FONT2						"\e[11m"
#  define FT_FONT3						"\e[12m"
#  define FT_FONT4						"\e[13m"
#  define FT_FONT5						"\e[14m"
#  define FT_FONT6						"\e[15m"
#  define FT_FONT7						"\e[16m"
#  define FT_FONT8						"\e[17m"
#  define FT_FONT9						"\e[18m"
#  define FT_FONT10						"\e[19m"
#  define FT_GOTHIC						"\e[20m"
#  define FT_UNDERLINE2					"\e[21m"
#  define FT_NO_INTENSITY				"\e[22m"
#  define FT_NO_ITALIC					"\e[23m"
#  define FT_NO_UNDERLINE				"\e[24m"
#  define FT_NO_BLINKING				"\e[25m"
#  define FT_NOTHING					"\e[26m"
#  define FT_NO_REVERSE					"\e[27m"
#  define FT_REVEAL						"\e[28m"
#  define FT_NO_STRIKE					"\e[29m"
#  define FT_FOREGROUND_COLOR(r,g,b)	"\e[38;2;"r";"g";"b"m"
#  define FT_NO_FOREGROUND				"\e[39m"
#  define FT_BACKGROUND_COLOR(r,g,b)	"\e[48;2;"r";"g";"b"m"
#  define FT_NO_BACKGROUND				"\e[49m"
#  define FT_FRAMED						"\e[51m"
#  define FT_ENCIRCLED					"\e[52m"
#  define FT_OVERLINED					"\e[53m"
#  define FT_NO_FRAMED_ENCIRCLED		"\e[54m"
#  define FT_NO_OVERLINED				"\e[55m"
#  define FT_UNDERLINE_COLOR(r,g,b) 	"\e[58;2;"r";"g";"b"m"
#  define FT_NO_UNDERLINE_COLOR			"\e[59m"

//Reset
#  define FT_CRESET			"\e[0m"
# endif /* FT_ANSI */

# ifndef	NULL
#  define	NULL 	((void*)0)
# endif

# ifndef	TRUE
#  define	TRUE	1
# endif

# ifndef	FALSE
#  define	FALSE	0
# endif

# ifndef	LOCALHOST
#  define	LOCALHOST "localhost"
# endif

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


# define U8_MAX  255
# define U8_MIN  0
# define U16_MAX 65535
# define U16_MIN 0
# define U32_MAX 4294967295
# define U32_MIN 0
# define U64_MAX 18446744073709551615UL
# define U64_MIN 0UL
# define S8_MAX  127
# define S8_MIN  -128
# define S16_MAX 32767
# define S16_MIN -32768
# define S32_MAX 2147483647
# define S32_MIN -2147483648
# define S64_MAX 9223372036854775807
# define S64_MIN -9223372036854775808
# define F32_MAX 3.40282346638528859811704183484516925e+38F
# define F32_MIN 1.17549435082228750796873653722224568e-38F
# define F64_MAX ((double)1.79769313486231570814527423731704357e+308L)
# define F64_MIN ((double)2.22507385850720138309023271733240406e-308L)

typedef char			*string;
typedef char const		*const_string;
typedef U8				bool;
# if defined(FT_WIN32)
typedef void			*file;
# elif defined(FT_LINUX) || defined(FT_OSX)
typedef S32				file;
# endif
extern file ft_stdout;
extern file ft_stdin;
extern file ft_stderr;

extern	int				ft_argc;
extern	const_string	ft_argv;
extern	const_string	*ft_env;
# define FT_INIT_ARGV(argc, argv, env) ft_argc=argc;ft_argv=argv;ft_env=env;

# define FUNCTION_HOT __attribute__((hot))
# define FUNCTION_COLD __attribute__((cold))


# define ANY_SCAL U8,U16,U32,U64,S8,S16,S32,S64,F32,F64
# define ANY_N S32,F32


typedef S32					t_error_code;
/*Error code returned by some ft functions*/
extern	t_error_code		ft_errno;
/*Private usage*/
# define __FTRETURN_OK(ret) ({ ft_errno=FT_OK; return ret; })
# define __FTRETURN_ERR(ret, err) ({ ft_errno = err ; return ret; })

# define FT_OK							0
/*Out of memory*/
# define FT_EOMEM						1
/*Bad pointer*/
# define FT_EINVPTR						2
/*Bad value*/
# define FT_EINVVAL						3
/*System call failed*/
# define FT_ESYSCALL					4	


# if defined(FT_DEBUG)
# define	FT_DEBUG_FALSE		0
# define	FT_DEBUG_VALGRIND	1
# define	FT_DEBUG_TRUE		2

void		ft_debug_break();
S8			ft_is_debugger();

#  if defined(FT_MEMCHECK)
extern bool				ft_check_leaks();
extern void				ft_memcheck_init(const_string *argv, bool threaded);

extern void				*_malloc(U64 size, char *file, int line);
extern void				_free(void *p, char *file, int line);
#   define malloc(X)	_malloc(X, __FILE__, __LINE__)
#   define free(X)		_free(X, __FILE__, __LINE__)
#  endif /* FT_MEMCHECK */

# endif /* FT_DEBUG */

# if defined(FT_STRINGS)

/*
Append a at the end of b.
Caller gets ownership of returned string.
*/
extern string		ft_str_append(string a, string b, bool free_a, bool free_b);

/*
Append src behind dest. Dest must have enough space, including \0
*/
extern string		ft_strcat(string dest, const_string src);

/*
Appends string src to the end of dst.
It will append at most dstsize - strlen(dst) - 1 characters.
It will then NUL-terminate the new string
*/
extern U64			ft_strlcat(string dest, const_string src, U64 size);

/*
Concatenate s1 and s2.
Caller gets ownership of returned string.
### On error
Sets ft_errno and returns NULL.
### ft_errno
- FT_EOMEM if out of memory
*/
extern string		ft_strjoin(const_string s1, const_string s2);

/*
Copies up to dstsize - 1 characters from the string src to dst,
NUL-terminating the result if dstsize is not 0.
*/
extern U64			ft_strlcpy(string dest, const_string src, U64 size);

/*
Duplicates the string str into a new char array.
Caller gets ownership of returned string.
### On error
Sets ft_errno and returns NULL.
### ft_errno
- FT_EINVPTR if 'str' is NULL
- FT_EOMEM if out of memory
*/
extern string		ft_strdup(const_string str);

/*
Returns a new string from s, starting at index start with size len.
Caller gets ownership of returned string.
### On error
Sets ft_errno and returns NULL.
### ft_errno
- FT_EOMEM if out of memory
*/
extern string		ft_substr(const_string s, U64 start, U64 len);

/*
Locates the first occurrence of c in the string pointed to by s.
The terminating null character taken into account.
*/
extern const_string	ft_strchr(const_string str, U8 c);

/*
Locates the first occurrence of c in the string pointed to by s, searching at most len characters.
The terminating null character taken into account.
*/
extern const_string	ft_strnchr(const_string str, U8 c, U64 len);

/*
Locates the last occurrence of c in string s
*/
extern const_string	ft_strrchr(const_string str, U8 c);

/*
Locates the first occurrence of the null-terminated string needle in the
string haystack, where not more than len characters are searched.
If to_find is an empty string, str is returned; if to_find occurs
nowhere in str, NULL is returned; otherwise a pointer to the first
character of the first occurrence of to_find is returned.
*/
extern const_string	ft_strnstr(const_string haystack, const_string needle, U64 len);

/*
Returns the length of string
*/
extern U64		ft_strlen(const_string str);

/*
Returns the index of the first occurrence of c in str, -1 if not found.
*/
extern S64		ft_strgetindex(const_string str, U8 c);

/*
Compares string s1 against string s2. Returns s1 - s2
*/
extern S32		ft_strncmp(const_string s1, const_string s2, U64 n);

/*
Converts a lower-case letter to the corresponding upper-case letter.
*/
extern U8		ft_tolower(U8 c);

/*
Converts a upper-case letter to the corresponding lower-case letter.
*/
extern U8		ft_toupper(U8 c);

/*
Creates a copy of s1 wihout the characters in set at end and start of string.
### On error
Sets ft_errno and returns NULL.
### ft_errno
- FT_EOMEM if out of memory
*/
extern string	ft_strtrim(const_string s1, const_string set);

/*
Applies function f to each characters in string str, and returns
a new string of all the results of f.
Caller gets ownership of returned string.
*/
extern string	ft_strmapi(const_string str, U8 (*f)(U64 index, U8));

/*
Applies function f to each characters in string s.
*/
extern void		ft_striteri(string str, void (*f)(U64 index, string str));

/*
Splits string s by separator c.
*/
__attribute__ ((deprecated)) extern string *ft_split(const_string str, U8 c);

/*
Duplicates a split
Caller gets ownership of returned string.
*/
__attribute__ ((deprecated)) extern string *ft_dupsplit(const_string *split);

/*
Free a split
Caller gets ownership of returned string.
*/
__attribute__ ((deprecated)) extern void ft_freesplit(string *split);

/*
Returns the length of a split
Caller gets ownership of returned string.
*/
__attribute__ ((deprecated)) extern U64 ft_splitlen(const_string *split);

# endif /* FT_STRINGS */


# if defined(FT_FILEIO)

/*
Opens a file. The string 'mode' can be one of the following:
	r: open for reading
	w: open for writing
	a: open for appending
	[r/w/a]+: read/write

Modes [w/a] will create the file if it doesn't exists
### On error
Sets ft_errno and returns -1.
### ft_errno
- FT_EINVPTR if 'path' or 'mode' is NULL
- FT_EINVVAL if 'mode' is invalid
- FT_ESYSCALL if a syscall fails
*/
extern file	ft_fopen(string path, string mode);

/*
Closes the file descriptor 'fd'
### On error
Sets ft_errno and returns -1.
### ft_errno
- FT_EINVVAL if 'fd' is invalid
- FT_ESYSCALL if a syscall fails
### TODO
Linux error check
*/
extern void	ft_fclose(file fd);

/*
Reads 'size' bytes from file 'fd' into 'buffer'.
### On error
Sets ft_errno and returns -1.
### ft_errno
- FT_ESYSCALL if a syscall fails
*/
extern U64		ft_fread(file fd, char *buffer, U64 size);

/*
Writes 'size' bytes from 'buffer' into file 'fd'.
### On error
Sets ft_errno and returns -1.
### ft_errno
- FT_ESYSCALL if a syscall fails
*/
extern U64		ft_fwrite(file fd, char *buffer, U64 size);

/*
Reads the whole file
### On error
Sets ft_errno and returns NULL.
### ft_errno
- FT_ESYSCALL if a syscall fails
- FT_EOMEM if out of memory
*/
extern string	ft_readfile(file fd, U64 read_size);

/*
Read the next line in fd, NULL if all lines are read.
*/
extern string	ft_gnl(file fd);

/*
printf !
*/
extern S64		ft_printf(const_string fmt, ...);
# endif /* FT_FILEIO */

# if defined(FT_STD)
/*
Writes n zeroed bytes to the string s.
*/
extern void		ft_bzero(void *s, U64 n);

/*
Locates the first occurrence of c in string s.
*/
extern void		*ft_memchr(void const *s, U8 c, U64 n);

/*
Compares byte string s1 against byte string s2.
*/
extern S32		ft_memcmp(void const *s1, void const *s2, U64 n);

/*
Copies n bytes from memory area src to memory area dst.
The two strings may not overlap. If they do use ft_memmove instead.
*/
extern void		*ft_memcpy(void *dst, void const *src, U64 n);

/*
Duplicates n bytes of src.
Caller owns returned value
### On error
Sets ft_errno and returns NULL.
### ft_errno
- FT_EOMEM if out of memory
*/
extern void		*ft_memdup(void const *src, U64 n);

/*
Copies len bytes from string src to string dst. The two strings may overlap;
the copy is always done in a non-destructive manner.
*/
extern void		*ft_memmove(void *dst, void const *src, U64 len);

/*
Writes len bytes of value c.
*/
extern void		*ft_memset(void *b, U8 c, U64 len);

/*
Stupid hash function, may or may not work
*/
extern U32		ft_hash_buffer(const void *buff, U64 size);

/*
Converts a string to an int.
*/
extern S32		ft_atoi(const_string str, U64 *out);

/*
Converts a string to a float.
*/
extern F32		ft_atof(const_string str, U64 *len);

/*
Converts a hex string to a unsigned int.
*/
extern U32		ft_atoix(const_string str, U64 *len);

/*
Converts an int to a string.
Caller owns returned value
### On error
Sets ft_errno and returns NULL.
### ft_errno
- FT_EOMEM if out of memory
*/
extern string	ft_itoa(S32 n);

/*
Converts an unsigned int to a string.
Caller owns returned value
### On error
Sets ft_errno and returns NULL.
### ft_errno
- FT_EOMEM if out of memory
*/
extern string	ft_uitoa(U64 n);

/*
Converts a float to a string.
Caller owns returned value
### On error
Sets ft_errno and returns NULL.
### ft_errno
- FT_EOMEM if out of memory
*/
extern string	ft_ftoa(F32 n);

#  if defined(FT_FILEIO)
/*
Writes character c in file descriptor fd.
### On error
Sets ft_errno.
### ft_errno
- FT_ESYSCALL if a syscall fails
*/
extern void 	ft_putchar_fd(U8 c, file fd);

/*
Write string s in file descriptor fd.
### On error
Sets ft_errno.
### ft_errno
- FT_ESYSCALL if a syscall fails
- FT_EINVPTR if 's' is NULL
*/
extern void 	ft_putstr_fd(string s, file fd);

/*
Write s in file fd, and append a line end.
### On error
Sets ft_errno.
### ft_errno
- FT_ESYSCALL if a syscall fails
- FT_EINVPTR if 's' is NULL
*/
extern void 	ft_putendl_fd(string s, file fd);

/*
Write a number in file descriptor fd.
### On error
Sets ft_errno.
### ft_errno
- FT_ESYSCALL if a syscall fails
*/
extern void 	ft_putnbr_fd(S32 n, file fd);
#  endif

/*
Check if character is digit or alpha.
*/
extern bool 	ft_isalnum(U8 c);

/*
Check if character is alpha.
*/
extern bool 	ft_isalpha(U8 c);

/*
Check if character is ascii.
*/
extern bool 	ft_isascii(U8 c);

/*
Check if character is digit.
*/
extern bool 	ft_isdigit(U8 c);

/*
Check if character is printable.
*/
extern bool 	ft_isprint(U8 c);

/*
Check if character is whitespace. (' ', '\t', '\r', '\n', '\v', '\f')
*/
extern bool		ft_iswhitespace(U8 c);

/*
Check if null-terminated string str is digit or alpha-numerical.
*/
extern bool 	ft_str_isalnum(string str);

/*
Check if null-terminated string str is alpha.
*/
extern bool 	ft_str_isalpha(string str);

/*
Check if null-terminated string str is ascii.
*/
extern bool 	ft_str_isascii(string str);

/*
Check if null-terminated string str is digit-only.
*/
extern bool 	ft_str_isdigit(string str);

/*
Check if null-terminated string str is printable.
*/
extern bool 	ft_str_isprint(string str);

/*
Check if null-terminated string str is whitespace. (' ', '\\t', '\\r', '\\n', '\\v', '\\f')
*/
extern bool 	ft_str_iswhitespace(string str);

/*
### On error
Sets ft_errno and returns NULL.
### ft_errno
- FT_EOMEM if out of memory
Creates an array of int from min to max.
*/
extern S32		*ft_range(S32 min, S32 max);

/*
Creates an array of int from min to max and returns the size of the array.
### On error
Sets ft_errno, sets the pointer pointed by 'range' to NULL and returns -1.
### ft_errno
- FT_EOMEM if out of memory
*/
extern S32		ft_nrange(S32 **range, S32 min, S32 max);

# endif /* FT_STD */

# if defined(FT_TIME)
//https://github.com/jleffler/soq/tree/master/src/libsoq

/* Machine-independent time format */
typedef struct s_time
{
	U64	seconds;		/* Time in whole seconds */
	U64	nanoseconds;	/* Sub-seconds in nanoseconds */
} t_time;

typedef struct s_clock
{
	t_time	t1;			/* Start time */
	t_time	t2;			/* Stop time */
	U8		buffer[24];	/* Buffer for formatting elapsed time */
} t_clock;

extern void									clk_diff(t_time *t1, t_time *t2, long *sec, long *nsec);
extern void									clk_init(t_clock *clk);
extern void									clk_start(t_clock *clk);
extern void									clk_stop(t_clock *clk);

__attribute__ ((deprecated)) extern string	clk_elapsed_ms(t_clock *clk, string buffer, U64 buflen);
__attribute__ ((deprecated)) extern string	clk_elapsed_us(t_clock *clk, string buffer, U64 buflen);
__attribute__ ((deprecated)) extern string	clk_elapsed_ns(t_clock *clk, string buffer, U64 buflen);

#  ifndef TIMER_VERSION_1
/* Preferred */
extern string								clk_fmt_elapsed_ms(t_clock *clk);
extern string								clk_fmt_elapsed_us(t_clock *clk);
extern string								clk_fmt_elapsed_ns(t_clock *clk);
extern string								clk_fmt_elapsed_str(t_clock *clk);
extern double								clk_fmt_elapsed_dbl(t_clock *clk);
#  endif /*#  ifndef TIMER_VERSION_1*/
# endif /* FT_TIME */

# if defined(FT_ARRAYS)
typedef struct s_array	*t_array;

/*
Inits and returns a new array.
ft_perror:
	FT_OK: Success
	FT_OMEM: Memory allocation error
*/
extern t_array		ft_array_new(U64 elem_size);

/*
Inits a new array and copies buffer into array.
ft_perror:
	FT_OK: Success
	FT_OMEM: Memory allocation error
*/
extern void			ft_array_init_from(t_array array, U64 elem_size, void *buffer, S32 count);

/*
Free array
ft_perror:
	FT_OK: Success
*/
extern void			ft_array_free(t_array array);

/*
Executes f on all elements of array.
If function f returns FALSE, and returns FALSE. Returns TRUE otherwise
*/
extern bool			ft_array_iter(t_array array, bool (*f)(void *));

/*
Returns a pointer to the value at index. Return NULL if not found
*/
extern void			*ft_array_get(t_array array, U64 index);

/*
Returns the number of elements in the array
*/
extern U64			ft_array_count(t_array array);

/*
Returns the size in bytes of the array. (array_count * elem_size)
*/
extern U64			ft_array_count_bytes(t_array array);

/*
Allocates a buffer and copy whole array on it. Returns FT_OK or FT_OMEM
*/
extern void			*ft_array_to_buff(t_array array);

/*
Copies whole array to buff. Returns FT_OK or FT_OMEM
*/
extern void			ft_array_cpy_buff(t_array array, void *buff);

/*
Appends the value elem to the back of the array. Returns FT_OK or FT_OMEM
*/
extern void			*ft_array_append(t_array array, void *elem);

/*
Returns last value and removes it. Returns FT_OK or > 0
*/
extern void			*ft_array_pop(t_array array);

/*
Clears the array
*/
extern void			ft_array_clear(t_array array);
# endif /* FT_ARRAYS */


# if defined(FT_LISTS)

typedef struct s_list
{
	void *content;
	struct s_list *prev;
	struct s_list *next;
} t_list;

/*
Compares every element in lst against ref using f, removes if f returns > 0
### On error
Sets ft_errno and returns FALSE.
### ft_errno
- FT_EINVPTR if 'lst' or 'f' is NULL
- FT_EINVPTR if ft_lstdelone fails
### TODO
*/
extern bool		ft_lstremoveif(t_list **lst, void (*del)(void *),
							bool (*f)(), void *ref);

/*
Removes an element from a chained list by it's content. If del is not NULL,
applies del to content and free the element
### On error
Sets ft_errno and returns FALSE.
### ft_errno
- FT_EINVPTR if 'lst' is NULL
- FT_EINVPTR if ft_lstdelone fails
### TODO
*/
extern bool		ft_lstremove2(t_list **lst, void *content, void (*del)(void *));

/*
Removes an element from a chained list. If del is not NULL,
applies del to content and free the element
### On error
Sets ft_errno and returns FALSE.
### ft_errno
- FT_EINVPTR if 'lst' or 'elem' is NULL
- FT_EINVPTR if ft_lstdelone fails
### TODO
*/
extern bool		ft_lstremove(t_list **lst, t_list *elem, void (*del)(void *));

#  if defined(FT_ARRAYS)
/*
Converts a list to an array
*/
extern int		ft_lst_to_array(t_list *lst, t_array array, U64 elem_size);
#  endif

/*
Creates and returns a new array containing
all the pointers of the chained list
### On error
Sets ft_errno and returns NULL.
### ft_errno
- FT_EINVPTR if 'lst' is NULL
- FT_EOMEM if out of memory
### TODO
*/
extern void		**ft_lsttopointers(t_list *lst);

/*
Creates a new list element using content
### On error
Sets ft_errno and returns NULL.
### ft_errno
- FT_EOMEM if out of memory
### TODO
*/
extern t_list	*ft_lstnew(void *content);

/*
Adds new at the front of lst.
### On error
Sets ft_errno.
### ft_errno
- FT_EINVPTR if 'lst' is NULL.
### TODO
*/
extern void		ft_lstadd_front(t_list **lst, t_list *new);

/*
Adds new at the end of lst.
### On error
Sets ft_errno.
### ft_errno
- FT_EINVPTR if 'lst' is NULL.
### TODO
*/
extern void		ft_lstadd_back(t_list **lst, t_list *new);

/*
Returns the size of lst.
### On error
No error possible
### ft_errno
### TODO
*/
extern U64		ft_lstsize(t_list *lst);

/*
Returns the last element of lst.
### On error
Sets ft_errno and returns NULL.
### ft_errno
- FT_EINVPTR if 'lst' is NULL.
### TODO
*/
extern t_list	*ft_lstlast(t_list *lst);

/*
Deletes an element from lst, using del on it's content.
### On error
Sets ft_errno.
### ft_errno
- FT_EINVPTR if 'lst' is NULL.
### TODO
*/
extern void		ft_lstdelone(t_list *lst, void (*del)(void *));

/*
Iterates through lst, deleting every element (see ft_lstdelone).
### On error
Sets ft_errno.
### ft_errno
- FT_EINVPTR if 'lst' is NULL.
### TODO
*/
extern void		ft_lstclear(t_list **lst, void (*del)(void *));

/*
Iterates through lst, using f on each element's content.
### On error
Sets ft_errno.
### ft_errno
- FT_EINVPTR if 'lst' or 'f' is NULL.
### TODO
*/
extern void		ft_lstiter(t_list *lst, void (*f)(void *));

/*
Finds an element by calling 'f' with each element's content as first argument, and 'ref' as second.
If 'f' returns TRUE, returns the element. If no elements are found, returns NULL.
### On error
Sets ft_errno and returns NULL.
### ft_errno
- FT_EINVPTR if 'lst' or 'f' is NULL.
### TODO
*/
extern t_list	*ft_lstfind(t_list *lst, bool (*f)(void *, void *), void *ref);

/*
Finds an element where the content's address is equal to the address of 'ptr'.
If no elements are found, returns NULL.
### On error
Sets ft_errno and returns NULL.
### ft_errno
- FT_EINVPTR if 'lst' is NULL.
### TODO
*/
extern t_list	*ft_lstfind2(t_list *lst, void *ptr);


/*
Iterates through "lst", applies "f" on every
element's content, puts results in a new list and returns it.
"del" is used to free the new list if anything goes wrong.
### On error
Sets ft_errno and returns NULL.
### ft_errno
- FT_EINVPTR if 'lst' or 'f' is NULL.
- FT_EOMEM if out of memory.
### TODO
*/
extern t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

# endif /* FT_LISTS */


# if defined(FT_HASHMAPS)
typedef void 			*t_hash_any;
typedef void 			*t_hash_map;
typedef t_error_code	t_hash_code;

/*
Initialize new hashmap
*/
extern t_hash_map	ft_hash_init(unsigned int (*key_hash)(void *), U64 key_len, U64 elem_len);

/*
Free the ft_hash. Return FT_MAP_MISSING if mutex can't be destroyed, FT_OK otherwise
*/
extern t_hash_code	ft_hash_free(t_hash_map in);

/*
Add an element to the hashmap. Return FT_OK or FT_OMEM.
*/
extern t_hash_code ft_hash_put(t_hash_map in, void *key, t_hash_any value);

/*
Get an element from the hashmap. Return FT_OK or FT_MAP_MISSING.
*/
extern t_hash_code ft_hash_get(t_hash_map in, void *key, t_hash_any *arg);

/*
Remove an element from the hashmap. Return FT_OK or FT_MAP_MISSING.
*/
extern t_hash_code ft_hash_remove(t_hash_map in, void *key);

/*
Get the current size of a hashmap
*/
extern t_hash_code ft_hash_length(t_hash_map in);

/*
Get any element. Return FT_OK or FT_MAP_MISSING.
remove - should the element be removed from the hashmap
*/
extern t_hash_code ft_hash_get_one(t_hash_map in, t_hash_any *arg, int remove);

/*
Iteratively calls f with argument (item, data) for
each element data in the hashmap. The function must
return a map status code. If it returns anything other
than FT_OK the traversal is terminated. f must
not reenter any hashmap functions, or deadlock may arise.
*/
extern t_hash_code	ft_hash_iterate(t_hash_map in, t_hash_code (*f)(t_hash_any item, t_hash_any elem), t_hash_any item);
# endif /* FT_HASHMAPS */



# if defined(FT_MATHS)

#  if !defined(FT_PI)
#   define FT_PI 3.14159265358979323846f
#  endif /* FT_PI */

#  if !defined(FT_DEG_TO_RAD)
#   define FT_DEG_TO_RAD 0.01745329251
#  endif /* FT_DEG_TO_RAD */
#  if !defined(FT_RAD_TO_DEG)
#   define FT_RAD_TO_DEG 57.2957795131
#  endif /* FT_RAD_TO_DEG */

typedef struct s_v2		{ float x, y; }			t_v2;
typedef struct s_v3		{ float x, y, z; }		t_v3;
typedef struct s_v4		{ float x, y, z, w; }	t_v4;
typedef struct s_iv2	{ int x, y; }			t_iv2;
typedef struct s_iv3	{ int x, y, z; }		t_iv3;
typedef struct s_iv4	{ int x, y, z, w; }		t_iv4;

extern t_v2		vec2(float x, float y);
extern t_v3		vec3(float x, float y, float z);
extern t_v4		vec4(float x, float y, float z, float w);
extern t_iv2	ivec2(int x, int y);
extern t_iv3	ivec3(int x, int y, int z);
extern t_iv4	ivec4(int x, int y, int z, int w);

extern t_v2		vec2_add(t_v2 a, t_v2 b);
extern t_v3		vec3_add(t_v3 a, t_v3 b);
extern t_v4		vec4_add(t_v4 a, t_v4 b);
extern t_iv2	ivec2_add(t_iv2 a, t_iv2 b);
extern t_iv3	ivec3_add(t_iv3 a, t_iv3 b);
extern t_iv4	ivec4_add(t_iv4 a, t_iv4 b);

extern t_v2		vec2_sub(t_v2 a, t_v2 b);
extern t_v3		vec3_sub(t_v3 a, t_v3 b);
extern t_v4		vec4_sub(t_v4 a, t_v4 b);
extern t_iv2	ivec2_sub(t_iv2 a, t_iv2 b);
extern t_iv3	ivec3_sub(t_iv3 a, t_iv3 b);
extern t_iv4	ivec4_sub(t_iv4 a, t_iv4 b);

extern t_v2		vec2_div(t_v2 a, t_v2 b);
extern t_v3		vec3_div(t_v3 a, t_v3 b);
extern t_v4		vec4_div(t_v4 a, t_v4 b);
extern t_iv2	ivec2_div(t_iv2 a, t_iv2 b);
extern t_iv3	ivec3_div(t_iv3 a, t_iv3 b);
extern t_iv4	ivec4_div(t_iv4 a, t_iv4 b);

extern t_v2		vec2_mul(t_v2 a, t_v2 b);
extern t_v3		vec3_mul(t_v3 a, t_v3 b);
extern t_v4		vec4_mul(t_v4 a, t_v4 b);
extern t_iv2	ivec2_mul(t_iv2 a, t_iv2 b);
extern t_iv3	ivec3_mul(t_iv3 a, t_iv3 b);
extern t_iv4	ivec4_mul(t_iv4 a, t_iv4 b);

extern t_v2		vec2_scl(t_v2 a, float b);
extern t_v3		vec3_scl(t_v3 a, float b);
extern t_v4		vec4_scl(t_v4 a, float b);
extern t_iv2	ivec2_scl(t_iv2 a, int b);
extern t_iv3	ivec3_scl(t_iv3 a, int b);
extern t_iv4	ivec4_scl(t_iv4 a, int b);

extern t_iv2	ivec2_mod(t_iv2 a, t_iv2 b);
extern t_iv3	ivec3_mod(t_iv3 a, t_iv3 b);
extern t_iv4	ivec4_mod(t_iv4 a, t_iv4 b);

typedef struct s_mat4x4
{
	F32 m00, m10, m20, m30;
	F32 m01, m11, m21, m31;
	F32 m02, m12, m22, m32;
	F32 m03, m13, m23, m33;
} t_mat4x4;

#  define 	ft_matrix_identity	\
	(t_mat4x4) {				\
		1.0f, 0.0f, 0.0f, 0.0f,	\
		0.0f, 1.0f, 0.0f, 0.0f,	\
		0.0f, 0.0f, 1.0f, 0.0f,	\
		0.0f, 0.0f, 0.0f, 1.0f }
extern t_v4		*ft_matrix_col(t_mat4x4 *mat, int c);
extern float	*ft_matrix_get(t_mat4x4 *mat, int r, int c);
extern t_v4		*ft_matrix_set_col(t_mat4x4 *mat, int c, t_v4 v);
extern bool		ft_matrix_set_row(t_mat4x4 *mat, int r, t_v4 v);

extern t_mat4x4	ft_matrix_transpose(t_mat4x4 mat);
extern t_mat4x4	ft_matrix_invert(t_mat4x4 mat);
extern float	ft_matrix_det(t_mat4x4 v);
extern t_mat4x4	ft_matrix_perspective(F32 fov, F32 near, F32 far);

extern t_mat4x4	ft_matrix_mult_matrix(t_mat4x4 a, t_mat4x4 b);
extern t_mat4x4	ft_matrix_mult_float(t_mat4x4 a, float b);
extern t_v4		ft_matrix_mult_v4(t_mat4x4 a, t_v4 b);


extern t_mat4x4	ft_matrix_scale_v2(t_v2 v);
extern t_mat4x4	ft_matrix_scale_v3(t_v3 v);
extern t_mat4x4	ft_matrix_scale_v4(t_v4 v);
extern t_mat4x4	ft_matrix_scale_iv2(t_iv2 v);
extern t_mat4x4	ft_matrix_scale_iv3(t_iv3 v);
extern t_mat4x4	ft_matrix_scale_iv4(t_iv4 v);

extern t_mat4x4	ft_matrix_translate_v2(t_v2 v);
extern t_mat4x4	ft_matrix_translate_v3(t_v3 v);
extern t_mat4x4	ft_matrix_translate_iv2(t_iv2 v);
extern t_mat4x4	ft_matrix_translate_iv3(t_iv3 v);

extern t_mat4x4	ft_matrix_fit_to_view(t_v2 pos, t_v2 size, t_v2 view_size);


#  define		ft_cos	cos
extern t_v2		ft_cos2(t_v2 v);
extern t_iv2	ft_icos2(t_iv2 v);
extern t_v3		ft_cos3(t_v3 v);
extern t_iv3	ft_icos3(t_iv3 v);
extern t_v4		ft_cos4(t_v4 v);
extern t_iv4	ft_icos4(t_iv4 v);

#  define		ft_sin	sin
extern t_v2		ft_sin2(t_v2 v);
extern t_iv2	ft_isin2(t_iv2 v);
extern t_v3		ft_sin3(t_v3 v);
extern t_iv3	ft_isin3(t_iv3 v);
extern t_v4		ft_sin4(t_v4 v);
extern t_iv4	ft_isin4(t_iv4 v);


extern F32		ft_radians(float degrees);
extern t_v2		ft_radians2(t_v2 degrees);
extern t_v3		ft_radians3(t_v3 degrees);
extern t_v4		ft_radians4(t_v4 degrees);
extern t_iv2	ft_iradians2(t_iv2 degrees);
extern t_iv3	ft_iradians3(t_iv3 degrees);
extern t_iv4	ft_iradians4(t_iv4 degrees);


extern F32		ft_degrees(float radians);
extern t_v2		ft_degrees2(t_v2 radians);
extern t_v3		ft_degrees3(t_v3 radians);
extern t_v4		ft_degrees4(t_v4 radians);
extern t_iv2	ft_idegrees2(t_iv2 radians);
extern t_iv3	ft_idegrees3(t_iv3 radians);
extern t_iv4	ft_idegrees4(t_iv4 radians);


extern S32		ft_abs(int n);
extern F32		ft_fabs(float n);
extern t_v2		ft_abs2(t_v2 n);
extern t_v3		ft_abs3(t_v3 n);
extern t_v4		ft_abs4(t_v4 n);
extern t_iv2	ft_iabs2(t_iv2 n);
extern t_iv3	ft_iabs3(t_iv3 n);
extern t_iv4	ft_iabs4(t_iv4 n);


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


extern S32		ft_min_2(float a, float b);
extern S32		ft_min_3(float a, float b, float c);
extern S32		ft_min_4(float a, float b, float c, float d);
extern S32		ft_imin_2(int a, int b);
extern S32		ft_imin_3(int a, int b, int c);
extern S32		ft_imin_4(int a, int b, int c, int d);

extern F32	 	ft_min2(t_v2 a);
extern t_v2 	ft_min2_2(t_v2 a, t_v2 b);
extern t_v2 	ft_min2_3(t_v2 a, t_v2 b, t_v2 c);
extern t_v2 	ft_min2_4(t_v2 a, t_v2 b, t_v2 c, t_v2 d);
extern S32		ft_min2i(t_iv2 a);
extern t_iv2	ft_min2i_2(t_iv2 a, t_iv2 b);
extern t_iv2	ft_min2i_3(t_iv2 a, t_iv2 b, t_iv2 c);
extern t_iv2	ft_min2i_4(t_iv2 a, t_iv2 b, t_iv2 c, t_iv2 d);


extern F32		ft_min3(t_v3 a);
extern t_v3		ft_min3_2(t_v3 a, t_v3 b);
extern t_v3		ft_min3_3(t_v3 a, t_v3 b, t_v3 c);
extern t_v3		ft_min3_4(t_v3 a, t_v3 b, t_v3 c, t_v3 d);
extern S32		ft_min3i(t_iv3 a);
extern t_iv3	ft_min3i_2(t_iv3 a, t_iv3 b);
extern t_iv3	ft_min3i_3(t_iv3 a, t_iv3 b, t_iv3 c);
extern t_iv3	ft_min3i_4(t_iv3 a, t_iv3 b, t_iv3 c, t_iv3 d);

extern F32		ft_min4(t_v4 a);
extern t_v4		ft_min4_2(t_v4 a, t_v4 b);
extern t_v4		ft_min4_3(t_v4 a, t_v4 b, t_v4 c);
extern t_v4		ft_min4_4(t_v4 a, t_v4 b, t_v4 c, t_v4 d);
extern S32		ft_min4i(t_iv4 a);
extern t_iv4	ft_min4i_2(t_iv4 a, t_iv4 b);
extern t_iv4	ft_min4i_3(t_iv4 a, t_iv4 b, t_iv4 c);
extern t_iv4	ft_min4i_4(t_iv4 a, t_iv4 b, t_iv4 c, t_iv4 d);


extern F32		ft_max_2(float a, float b);
extern F32		ft_max_3(float a, float b, float c);
extern F32		ft_max_4(float a, float b, float c, float d);
extern S32		ft_imax_2(int a, int b);
extern S32		ft_imax_3(int a, int b, int c);
extern S32		ft_imax_4(int a, int b, int c, int d);

extern F32	 	ft_max2(t_v2 a);
extern t_v2 	ft_max2_2(t_v2 a, t_v2 b);
extern t_v2 	ft_max2_3(t_v2 a, t_v2 b, t_v2 c);
extern t_v2 	ft_max2_4(t_v2 a, t_v2 b, t_v2 c, t_v2 d);
extern S32		ft_max2i(t_iv2 a);
extern t_iv2	ft_max2i_2(t_iv2 a, t_iv2 b);
extern t_iv2	ft_max2i_3(t_iv2 a, t_iv2 b, t_iv2 c);
extern t_iv2	ft_max2i_4(t_iv2 a, t_iv2 b, t_iv2 c, t_iv2 d);

extern F32		ft_max3(t_v3 a);
extern t_v3		ft_max3_2(t_v3 a, t_v3 b);
extern t_v3		ft_max3_3(t_v3 a, t_v3 b, t_v3 c);
extern t_v3		ft_max3_4(t_v3 a, t_v3 b, t_v3 c, t_v3 d);
extern S32		ft_max3i(t_iv3 a);
extern t_iv3	ft_max3i_2(t_iv3 a, t_iv3 b);
extern t_iv3	ft_max3i_3(t_iv3 a, t_iv3 b, t_iv3 c);
extern t_iv3	ft_max3i_4(t_iv3 a, t_iv3 b, t_iv3 c, t_iv3 d);

extern F32		ft_max4(t_v4 a);
extern t_v4		ft_max4_2(t_v4 a, t_v4 b);
extern t_v4		ft_max4_3(t_v4 a, t_v4 b, t_v4 c);
extern t_v4		ft_max4_4(t_v4 a, t_v4 b, t_v4 c, t_v4 d);
extern S32		ft_max4i(t_iv4 a);
extern t_iv4	ft_max4i_2(t_iv4 a, t_iv4 b);
extern t_iv4	ft_max4i_3(t_iv4 a, t_iv4 b, t_iv4 c);
extern t_iv4	ft_max4i_4(t_iv4 a, t_iv4 b, t_iv4 c, t_iv4 d);

extern F32		ft_lerp(float a, float b, float t);
extern t_v2		ft_lerp2(t_v2 a, t_v2 b, float t);
extern t_v3		ft_lerp3(t_v3 v_1, t_v3 v_2, float t);
extern t_v4		ft_lerp4(t_v4 v_1, t_v4 v_2, float t);

extern F32		ft_invlerp(float a, float b, float t);
extern t_v2		ft_invlerp2(t_v2 a, t_v2 b, t_v2 t);
extern t_v3		ft_invlerp3(t_v3 v_1, t_v3 v_2, t_v3 t);
extern t_v4		ft_invlerp4(t_v4 v_1, t_v4 v_2, t_v4 t);

extern F32		ft_smoothstep(float a, float b, float t);
extern t_v2		ft_smoothstep2(t_v2 a, t_v2 b, t_v2 t);
extern t_v3		ft_smoothstep3(t_v3 v_1, t_v3 v_2, t_v3 t);
extern t_v4		ft_smoothstep4(t_v4 v_1, t_v4 v_2, t_v4 t);

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

# endif /* FT_MATHS */


//No forget to undef otherwise std headers go crazy
# if defined(FT_WIN32)
#  undef __attribute__
# endif

# if defined(__cplusplus)
}
# endif

#endif /* LIBFT_H */