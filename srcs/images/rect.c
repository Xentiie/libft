/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rect.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 16:22:47 by reclaire          #+#    #+#             */
/*   Updated: 2025/05/21 03:09:48 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _FT_EXTENDED_ALIAS
#include "libft_int.h"

#include "libft/images.h"
#include "libft/io.h"

#include "libft/bits/extended_aliases.h"

#include "libft/bits/variants/ft_draw_rect.h"
#include "libft/bits/variants/ft_fill_rect.h"
#include "libft/bits/variants/ft_draw_line_horizontal.h"
#include "libft/bits/variants/ft_draw_line_vertical.h"

#include <stdarg.h>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wvolatile-register-var"

void ft_draw_rect(t_image *img, t_iv4 rect, t_color col, U8 flags, ...)
{
	t_iv4 clip_rect;
	va_list lst;
	S32 x_start, x_end;
	S32 y_start, y_end;

	/* If we aren't ignoring alpha and color's alpha is 0, ignore */
	if (!(flags & FT_DRAW_FLAG_NO_TRANSPARENCY) && col.a == 0)
		return;

	{ /* Clipping */

		{ /* Get clip rect */
			clip_rect = ft_image_rect(img);

			va_start(lst, flags);
			if (flags & FT_DRAW_FLAG_CLIP)
			{
				t_iv4 r = va_arg(lst, t_iv4);
				clip_rect = ft_clip_rect_rect(r, clip_rect);
			}
			va_end(lst);
		}
	}

	x_start = rect.x;
	if (x_start < clip_rect.x)
		x_start = clip_rect.x;
	x_end = rect.z;
	if (x_end > clip_rect.z)
		x_end = clip_rect.z;

	y_start = rect.y;
	if (y_start < clip_rect.y)
		y_start = clip_rect.y;
	y_end = rect.w;
	if (y_end > clip_rect.w)
		y_end = clip_rect.w;

	if (x_start > x_end || y_start > y_end)
		return;

	if ((flags & FT_DRAW_FLAG_NO_TRANSPARENCY) || col.a == 255)
	{
		if (y_start == rect.y) /* If no clipping for y_start */
			__ft_draw_line_horizontal_no_alpha(img, ivec2(x_start, rect.y), x_end, col);
		if (y_end == rect.w) /* If no clipping for y_end */
			__ft_draw_line_horizontal_no_alpha(img, ivec2(x_start, rect.w), x_end, col);

		if (x_start == rect.x) /* If no clipping for x_start */
			__ft_draw_line_vertical_no_alpha(img, ivec2(rect.x, y_start), y_end, col);
		if (x_end == rect.z) /* If no clipping for x_end */
			__ft_draw_line_vertical_no_alpha(img, ivec2(rect.z, y_start), y_end, col);
	}
	else
	{
		if (y_start == rect.y) /* If no clipping for y_start */
			__ft_draw_line_horizontal_alpha(img, ivec2(x_start, rect.y), x_end, col);
		if (y_end == rect.w) /* If no clipping for y_end */
			__ft_draw_line_horizontal_alpha(img, ivec2(x_start, rect.w), x_end, col);

		if (x_start == rect.x) /* If no clipping for x_start */
			__ft_draw_line_vertical_alpha(img, ivec2(rect.x, y_start), y_end, col);
		if (x_end == rect.z) /* If no clipping for x_end */
			__ft_draw_line_vertical_alpha(img, ivec2(rect.z, y_start), y_end, col);
	}
}

void ft_fill_rect(t_image *img, t_iv4 rect, t_color col, U8 flags, ...)
{
	t_iv4 clip_rect;
	va_list lst;

	/* If we aren't ignoring alpha and color's alpha is 0, ignore */
	if (!(flags & FT_DRAW_FLAG_NO_TRANSPARENCY) && col.a == 0)
		return;

	{ /* Clipping */

		{ /* Get clip rect */
			clip_rect = ft_image_rect(img);

			va_start(lst, flags);
			if (flags & FT_DRAW_FLAG_CLIP)
			{
				t_iv4 r = va_arg(lst, t_iv4);
				clip_rect = ft_clip_rect_rect(r, clip_rect);
			}
			va_end(lst);
		}

		rect = ft_clip_rect_rect(rect, clip_rect);

		/* Rect is invalid, ignore */
		if (rect.x > rect.z || rect.y > rect.w)
			return;
	}

	if ((flags & FT_DRAW_FLAG_NO_TRANSPARENCY) || col.a == 255)
		__ft_fill_rect_no_alpha(img, rect, col);
	else
		__ft_fill_rect_alpha(img, rect, col);
}

EXTENDED_ALIAS("__ft_fill_rect_no_alpha", 0, (), ())
void __ft_fill_rect_no_alpha_base(t_image *img, t_iv4 rect, t_color col)
{
	t_color *ptr;
	S32 ystep;
	S32 ylen;
	S32 xlen;

	ptr = ft_get_pixel(img, rect.x, rect.y);

	ylen = rect.w - rect.y;
	xlen = rect.z - rect.x;
	ystep = img->size.x - (rect.z - rect.x);
	for (S32 y = 0; y < ylen; y++, ptr += ystep)
		for (S32 x = 0; x < xlen; x++, ptr++)
			*ptr = col;
}

EXTENDED_ALIAS("__ft_fill_rect_no_alpha", 1, ("sse2"), ("sse"))
void __ft_fill_rect_no_alpha_x4(t_image *img, t_iv4 rect, t_color col)
{
	const S32 xstep = 4; /* xmm = 128 bits = 4 U32 = 4 pixels */
	register volatile xmm dummy_variable_for_stupid_gcc_to_deny_use_of_xmm0 asm("xmm0");
	(void)dummy_variable_for_stupid_gcc_to_deny_use_of_xmm0;
	t_color *ptr;
	S32 ystep;
	S32 ylen;
	S32 xlen;
	S32 xlen_rem;

	ptr = ft_get_pixel(img, rect.x, rect.y);

	ylen = rect.w - rect.y;
	xlen = rect.z - rect.x;
	xlen_rem = xlen % xstep;
	xlen -= xlen_rem;
	ystep = img->size.x - (rect.z - rect.x);

	asm(
		"movd   xmm0, %0\n"
		"pshufd xmm0, xmm0, 0\n" : : "r"(col.v));

	for (S32 y = 0; y < ylen; y++, ptr += ystep)
	{
		S32 x;
		for (x = 0; x < xlen; x += xstep, ptr += xstep)
			asm("movdqu [%0], xmm0\n" : : "r"(ptr));
		for (; x < xlen + xlen_rem; x++, ptr++)
			*ptr = col;
	}
}

EXTENDED_ALIAS("__ft_fill_rect_no_alpha", 2, ("avx", "avx2"), ("avx"))
void __ft_fill_rect_no_alpha_x8(t_image *img, t_iv4 rect, t_color col)
{
	const S32 xstep = 8; /* ymm = 256 bits = 8 U32 = 8 pixels */
	register volatile xmm dummy_variable_for_stupid_gcc_to_deny_use_of_ymm0 asm("ymm0");
	(void)dummy_variable_for_stupid_gcc_to_deny_use_of_ymm0;
	t_color *ptr;
	S32 ystep;
	S32 ylen;
	S32 xlen;
	S32 xlen_rem;

	ptr = ft_get_pixel(img, rect.x, rect.y);

	ylen = rect.w - rect.y;
	xlen = rect.z - rect.x;
	xlen_rem = xlen % xstep;
	xlen -= xlen_rem;
	ystep = img->size.x - (rect.z - rect.x);

	asm("vpbroadcastd ymm0, %0\n" : : "m"(col.v));
	for (S32 y = 0; y < ylen; y++, ptr += ystep)
	{
		S32 x;
		for (x = 0; x < xlen; x += xstep, ptr += xstep)
			asm("vmovdqu %0, ymm0\n" : "=m"(*(ymm *)ptr));
		for (; x < xlen + xlen_rem; x++, ptr++)
			*ptr = col;
	}
}

EXTENDED_ALIAS("__ft_fill_rect_alpha", 0, (), ())
void __ft_fill_rect_alpha_base(t_image *img, t_iv4 rect, t_color col)
{
	t_color *ptr;
	S32 ystep;

	ptr = ft_get_pixel(img, rect.x, rect.y);
	ystep = img->size.x - (rect.z - rect.x);

	for (S32 y = rect.y; y < rect.w; y++, ptr += ystep)
	{
		for (S32 x = rect.x; x < rect.z; x++, ptr++)
			*ptr = ft_alpha_blend(*ptr, col);
	}
}

EXTENDED_ALIAS("__ft_fill_rect_alpha", 1, ("sse2"), ("sse"))
void __ft_fill_rect_alpha_x4(t_image *img, t_iv4 rect, t_color col)
{
	const S32 xstep = 4; /* xmm = 128 bits = 4 U32 = 4 pixels */
	register volatile xmm dummy_variable_for_stupid_gcc_to_deny_use_of_xmm0 asm("xmm0");
	(void)dummy_variable_for_stupid_gcc_to_deny_use_of_xmm0;
	t_color *ptr;
	S32 ystep;
	S32 ylen;
	S32 xlen;
	S32 xlen_rem;

	t_iv4 aaa;

	0b10110000;
	0x0d176;

	ptr = ft_get_pixel(img, rect.x, rect.y);

	asm(
		"movd	xmm0, [%0]\n"

		"pshufd xmm1, xmm0, 0b10110000\n"
		"pshufd xmm2, xmm0, 0b00010000\n"
		"psubd  xmm2, xmm1\n"

		"movd	[%1], xmm2\n"

		: : "r"(&aaa), "r"(&rect) : "xmm0");

	ylen = rect.w - rect.y;
	xlen = rect.z - rect.x;

	ft_printf("%d %d\n", xlen, ylen);
	ft_printf("%d %d\n", aaa.x, aaa.y);

	xlen_rem = xlen % xstep;
	xlen -= xlen_rem;
	ystep = img->size.x - (rect.z - rect.x);

	asm(
		"movd   xmm0, %0\n"
		"pshufd xmm0, xmm0, 0\n"
		: : "r"(col.v));

	for (S32 y = 0; y < ylen; y++, ptr += ystep)
	{
		S32 x;
		for (x = 0; x < xlen; x += xstep, ptr += xstep)
			asm("movdqu [%0], xmm0\n" : : "r"(ptr));
		for (; x < xlen + xlen_rem; x++, ptr++)
			*ptr = col;
	}
}

EXTENDED_ALIAS("__ft_fill_rect_alpha", 0, (), ())
static void __ft_fill_rect_alpha_ft_alpha_blend(t_image *img, t_iv4 rect, t_color col)
{
	t_color *ptr;
	S32 ystep;

	rect.x = ft_clamp(0, img->size.x, rect.x);
	rect.y = ft_clamp(0, img->size.y, rect.y);
	rect.z = ft_clamp(0, img->size.x, rect.z);
	rect.w = ft_clamp(0, img->size.y, rect.w);

	ptr = ft_get_pixel(img, rect.x, rect.y);
	ystep = img->size.x - (rect.z - rect.x);

	for (S32 y = rect.y; y < rect.w; y++, ptr += ystep)
	{
		for (S32 x = rect.x; x < rect.z; x++, ptr++)
			*ptr = ft_alpha_blend(*ptr, col);
	}
}

#pragma GCC diagnostics pop

/* Auto-generated by build-aux/extended_aliases.py */

#include "libft/sys/cpuid.h"
#include "libft/sys/xsave.h"
#include "libft/io.h"

#if defined(DEBUG)
static void *__resolved___ft_fill_rect_no_alpha = NULL;
#endif
static void (*resolve___ft_fill_rect_no_alpha(void))(t_image *img, t_iv4 rect, t_color col)
{

#if !defined(DEBUG)
	void *__resolved___ft_fill_rect_no_alpha = NULL;
#endif
	struct s_cpuid_flags *cpuid_flags;
	struct s_xcr0_flags os_flags;

	cpuid_flags = ft_cpuid_get_cached_flags();
	ft_xgetbv(0, &os_flags.flags);
	if (os_flags.avx && cpuid_flags->avx && cpuid_flags->avx2)
		__resolved___ft_fill_rect_no_alpha = __ft_fill_rect_no_alpha_x8;
	else if (os_flags.sse && cpuid_flags->sse2)
		__resolved___ft_fill_rect_no_alpha = __ft_fill_rect_no_alpha_x4;
	else
		__resolved___ft_fill_rect_no_alpha = __ft_fill_rect_no_alpha_base;
	return __resolved___ft_fill_rect_no_alpha;
}

void __ft_fill_rect_no_alpha(t_image *img, t_iv4 rect, t_color col)
	__attribute__((ifunc("resolve___ft_fill_rect_no_alpha")));
#if defined(DEBUG)
static void *__resolved___ft_fill_rect_alpha = NULL;
#endif
static void (*resolve___ft_fill_rect_alpha(void))(t_image *img, t_iv4 rect, t_color col)
{

#if !defined(DEBUG)
	void *__resolved___ft_fill_rect_alpha = NULL;
#endif
	struct s_cpuid_flags *cpuid_flags;
	struct s_xcr0_flags os_flags;

	cpuid_flags = ft_cpuid_get_cached_flags();
	ft_xgetbv(0, &os_flags.flags);
	if (os_flags.sse && cpuid_flags->sse2)
		__resolved___ft_fill_rect_alpha = __ft_fill_rect_alpha_x4;
	else if (1)
		__resolved___ft_fill_rect_alpha = __ft_fill_rect_alpha_base;
	else
		__resolved___ft_fill_rect_alpha = __ft_fill_rect_alpha_ft_alpha_blend;
	return __resolved___ft_fill_rect_alpha;
}

void __ft_fill_rect_alpha(t_image *img, t_iv4 rect, t_color col)
	__attribute__((ifunc("resolve___ft_fill_rect_alpha")));

#if defined(DEBUG)
__attribute__((constructor)) static void __debug_ifunc()
{
	ft_printf("__ft_fill_rect_no_alpha:");
	if (__resolved___ft_fill_rect_no_alpha == __ft_fill_rect_no_alpha_x8)
		ft_printf("__ft_fill_rect_no_alpha_x8\n");
	else if (__resolved___ft_fill_rect_no_alpha == __ft_fill_rect_no_alpha_x4)
		ft_printf("__ft_fill_rect_no_alpha_x4\n");
	else
		ft_printf("__ft_fill_rect_no_alpha_base\n");
	ft_printf("__ft_fill_rect_alpha:");
	if (__resolved___ft_fill_rect_alpha == __ft_fill_rect_alpha_x4)
		ft_printf("__ft_fill_rect_alpha_x4\n");
	else if (__resolved___ft_fill_rect_alpha == __ft_fill_rect_alpha_base)
		ft_printf("__ft_fill_rect_alpha_base\n");
	else
		ft_printf("__ft_fill_rect_alpha_ft_alpha_blend\n");
}
#endif
