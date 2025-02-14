/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ansi.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 19:53:23 by reclaire          #+#    #+#             */
/*   Updated: 2025/01/14 15:42:46 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(LIBFT_ANSI_H)
#define LIBFT_ANSI_H

#include "libft/libft.h"
#include "libft/macros.h"

#define __TC_STRINGIFY(x) #x
#define __TC_ARG(x) FT_EXPAND(__TC_STRINGIFY(x))

/* ANSI escape characters */
#define FT_TC_ESCAPE "\e["

/*
FT_TC: construct a ANSI color code. Each arguments is expected to be an int
*/
#define FT_TC(...) \
	FT_TC_ESCAPE   \
	FT_MACRO_FOR_EACH_sep(__TC_ARG, ";", __VA_ARGS__) "m"
/* Same as FT_TC, but always resets first */
#define FT_TCR(...)       \
	FT_TC_ESCAPE          \
	__TC_ARG(FT_TC_RESET) \
	__VA_OPT__(";" FT_MACRO_FOR_EACH_sep(__TC_ARG, ";", __VA_ARGS__)) "m"

/* colors */

#define FT_TC_COL_BLACK 30
#define FT_TC_COL_RED 31
#define FT_TC_COL_GREEN 32
#define FT_TC_COL_YELLOW 33
#define FT_TC_COL_BLUE 34
#define FT_TC_COL_MAGENTA 35
#define FT_TC_COL_CYAN 36
#define FT_TC_COL_WHITE 37
#define FT_TC_COL_DEFAULT 39

#define FT_TC_COL_GRAY 90
#define FT_TC_COL_BRIGHT_RED 91
#define FT_TC_COL_BRIGHT_GREEN 92
#define FT_TC_COL_BRIGHT_YELLOW 93
#define FT_TC_COL_BRIGHT_BLUE 94
#define FT_TC_COL_BRIGHT_MAGENTA 95
#define FT_TC_COL_BRIGHT_CYAN 96
#define FT_TC_COL_BRIGHT_WHITE 97
#define FT_TC_COL_BRIGHT_DEFAULT 99

#define FT_TC_COL_BG_BLACK 40
#define FT_TC_COL_BG_RED 41
#define FT_TC_COL_BG_GREEN 42
#define FT_TC_COL_BG_YELLOW 43
#define FT_TC_COL_BG_BLUE 44
#define FT_TC_COL_BG_MAGENTA 45
#define FT_TC_COL_BG_CYAN 46
#define FT_TC_COL_BG_WHITE 47
#define FT_TC_COL_BG_DEFAULT 49

#define FT_TC_COL_BG_BRIGHT_BLACK 100
#define FT_TC_COL_BG_BRIGHT_RED 101
#define FT_TC_COL_BG_BRIGHT_GREEN 102
#define FT_TC_COL_BG_BRIGHT_YELLOW 103
#define FT_TC_COL_BG_BRIGHT_BLUE 104
#define FT_TC_COL_BG_BRIGHT_MAGENTA 105
#define FT_TC_COL_BG_BRIGHT_CYAN 106
#define FT_TC_COL_BG_BRIGHT_WHITE 107
#define FT_TC_COL_BG_BRIGHT_DEFAULT 109

/* styles */

#define FT_TC_BOLD 1
#define FT_TC_DIM 2
#define FT_TC_ITALIC 3
#define FT_TC_UNDERLINE 4
#define FT_TC_BLINK 5
#define FT_TC_BLINK_FAST 6
#define FT_TC_INVERSE 7
#define FT_TC_INVISIBLE 8
#define FT_TC_STRIKETHROUGH 9
#define FT_TC_FONT1 10
#define FT_TC_FONT2 11
#define FT_TC_FONT3 12
#define FT_TC_FONT4 13
#define FT_TC_FONT5 14
#define FT_TC_FONT6 15
#define FT_TC_FONT7 16
#define FT_TC_FONT8 17
#define FT_TC_FONT9 18
#define FT_TC_FONT10 19
#define FT_TC_GOTHIC 20
#define FT_TC_UNDERLINE2 21
#define FT_TC_NO_INTENSITY 22
#define FT_TC_NO_ITALIC 23
#define FT_TC_NO_UNDERLINE 24
#define FT_TC_NO_BLINKING 25
#define FT_TC_NOTHING 26
#define FT_TC_NO_REVERSE 27
#define FT_TC_REVEAL 28
#define FT_TC_NO_STRIKE 29

/* expects the next 3 arguments for FT_TC to be a rgb tuple */
#define FT_TC_FOREGROUND_COLOR(r, g, b) \
	38;                                 \
	2
#define FT_TC_RESET_FOREGROUND "\e[39m"
/* expects the next 3 arguments for FT_TC to be a rgb tuple */
#define FT_TC_BACKGROUND_COLOR(r, g, b) \
	48;                                 \
	2
#define FT_TC_RESET_BACKGROUND "\e[49m"
#define FT_TC_FRAMED "\e[51m"
#define FT_TC_ENCIRCLED "\e[52m"
#define FT_TC_OVERLINED "\e[53m"
#define FT_TC_NO_FRAMED_ENCIRCLED "\e[54m"
#define FT_TC_NO_OVERLINED "\e[55m"
#define FT_TC_UNDERLINE_COLOR(r, g, b) "\e[58;2;" r ";" g ";" b "m"
#define FT_TC_NO_UNDERLINE_COLOR "\e[59m"

#define FT_TC_CURSOR_UP(n) "\e[" #n "A"
#define FT_TC_CURSOR_DOWN(n) "\e[" #n "B"
#define FT_TC_CURSOR_FORWARD(n) "\e[" #n "C"
#define FT_TC_CURSOR_BACK(n) "\e[" #n "D"

// Reset
#define FT_TC_RESET 0

#endif