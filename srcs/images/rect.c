/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rect.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 16:22:47 by reclaire          #+#    #+#             */
/*   Updated: 2025/03/21 09:24:49 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _FT_EXTENDED_ALIAS
#include "libft_int.h"

#include "libft/images.h"
#include "libft/sse.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wattributes"
#pragma GCC diagnostic ignored "-Wvolatile-register-var"

void ft_draw_rect_bound(t_image *img, t_iv4 rect, t_color col, t_iv4 bound)
{
	rect.x = ft_max(rect.x, bound.x);
	rect.y = ft_max(rect.y, bound.y);
	rect.z = ft_min(rect.z, bound.z);
	rect.w = ft_min(rect.w, bound.w);

	ft_draw_rect(img, rect, col);
}

void ft_draw_rect(t_image *img, t_iv4 rect, t_color col)
{
	ft_draw_line_horizontal(img, ivec2(rect.x, rect.y), rect.z, col);
	ft_draw_line_horizontal(img, ivec2(rect.x, rect.w), rect.z, col);
	ft_draw_line_vertical(img, ivec2(rect.x, rect.y), rect.w, col);
	ft_draw_line_vertical(img, ivec2(rect.z, rect.y), rect.w, col);
}

void ft_draw_rect_bound2(t_image *img, t_iv4 rect, t_color col, t_iv4 bound)
{
	rect.x = ft_max(rect.x, bound.x);
	rect.y = ft_max(rect.y, bound.y);
	rect.z = ft_min(rect.z, bound.z);
	rect.w = ft_min(rect.w, bound.w);

	ft_draw_rect2(img, rect, col);
}

void ft_draw_rect2(t_image *img, t_iv4 rect, t_color col)
{
	ft_draw_line_horizontal2(img, ivec2(rect.x, rect.y), rect.z, col);
	ft_draw_line_horizontal2(img, ivec2(rect.x, rect.w), rect.z, col);
	ft_draw_line_vertical2(img, ivec2(rect.x, rect.y), rect.w, col);
	ft_draw_line_vertical2(img, ivec2(rect.z, rect.y), rect.w, col);
}

void ft_fill_rect_bound(t_image *img, t_iv4 rect, t_color col, t_iv4 bound)
{
	rect.x = ft_max(rect.x, bound.x);
	rect.y = ft_max(rect.y, bound.y);
	rect.z = ft_min(rect.z, bound.z);
	rect.w = ft_min(rect.w, bound.w);

	ft_fill_rect(img, rect, col);
}

void ft_fill_rect_bound2(t_image *img, t_iv4 rect, t_color col, t_iv4 bound)
{
	rect.x = ft_max(rect.x, bound.x);
	rect.y = ft_max(rect.y, bound.y);
	rect.z = ft_min(rect.z, bound.z);
	rect.w = ft_min(rect.w, bound.w);

	ft_fill_rect2(img, rect, col);
}

EXTENDED_ALIAS("ft_fill_rect", 0, (), ())
static void fill_rect(t_image *img, t_iv4 rect, t_color col)
{
	t_color *ptr;
	S32 ystep;
	S32 ylen;
	S32 xlen;

	rect.x = ft_clamp(0, img->size.x, rect.x);
	rect.y = ft_clamp(0, img->size.y, rect.y);
	rect.z = ft_clamp(0, img->size.x, rect.z);
	rect.w = ft_clamp(0, img->size.y, rect.w);

	ptr = ft_get_pixel(img, rect.x, rect.y);

	ylen = rect.w - rect.y;
	xlen = rect.z - rect.x;
	ystep = img->size.x - (rect.z - rect.x);
	for (S32 y = 0; y < ylen; y++, ptr += ystep)
		for (S32 x = 0; x < xlen; x++, ptr++)
			*ptr = col;
}

EXTENDED_ALIAS("ft_fill_rect", 1, ("sse2"), ("sse"))
void fill_rect_xmm(t_image *img, t_iv4 rect, t_color col)
{
	const S32 xstep = 4; /* xmm = 128 bits = 4 U32 = 4 pixels */
	register volatile xmm dummy_variable_for_stupid_gcc_to_deny_use_of_xmm0 asm("xmm0");
	(void)dummy_variable_for_stupid_gcc_to_deny_use_of_xmm0;
	t_color *ptr;
	S32 ystep;
	S32 ylen;
	S32 xlen;
	S32 xlen_rem;

	rect.x = ft_clamp(0, img->size.x, rect.x);
	rect.y = ft_clamp(0, img->size.y, rect.y);
	rect.z = ft_clamp(0, img->size.x, rect.z);
	rect.w = ft_clamp(0, img->size.y, rect.w);

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

EXTENDED_ALIAS("ft_fill_rect", 2, ("avx", "avx2"), ("avx"))
void fill_rect_ymm(t_image *img, t_iv4 rect, t_color col)
{
	const S32 xstep = 8; /* ymm = 256 bits = 8 U32 = 8 pixels */
	register volatile xmm dummy_variable_for_stupid_gcc_to_deny_use_of_ymm0 asm("ymm0");
	(void)dummy_variable_for_stupid_gcc_to_deny_use_of_ymm0;
	t_color *ptr;
	S32 ystep;
	S32 ylen;
	S32 xlen;
	S32 xlen_rem;

	rect.x = ft_clamp(0, img->size.x, rect.x);
	rect.y = ft_clamp(0, img->size.y, rect.y);
	rect.z = ft_clamp(0, img->size.x, rect.z);
	rect.w = ft_clamp(0, img->size.y, rect.w);

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

EXTENDED_ALIAS("ft_fill_rect2", 0, (), ())
static void fill_rect2(t_image *img, t_iv4 rect, t_color col)
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

EXTENDED_ALIAS("ft_fill_rect2", 1, ("sse2"), ("sse"))
void fill_rect2_xmm(t_image *img, t_iv4 rect, t_color col)
{
	const S32 xstep = 4; /* xmm = 128 bits = 4 U32 = 4 pixels */
	register volatile xmm dummy_variable_for_stupid_gcc_to_deny_use_of_xmm0 asm("xmm0");
	(void)dummy_variable_for_stupid_gcc_to_deny_use_of_xmm0;
	t_color *ptr;
	S32 ystep;
	S32 ylen;
	S32 xlen;
	S32 xlen_rem;

	rect.x = ft_clamp(0, img->size.x, rect.x);
	rect.y = ft_clamp(0, img->size.y, rect.y);
	rect.z = ft_clamp(0, img->size.x, rect.z);
	rect.w = ft_clamp(0, img->size.y, rect.w);

	ptr = ft_get_pixel(img, rect.x, rect.y);

	ylen = rect.w - rect.y;
	xlen = rect.z - rect.x;
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

EXTENDED_ALIAS("ft_fill_rect2", 1, ("avx2", "sse2"), ("sse", "avx"))
static void fill_rect2_avx2(t_image *img, t_iv4 rect, t_color col)
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
#if defined(DEBUG)
#include "libft/io.h"
#endif

#if defined(DEBUG)
static void *__resolved_ft_fill_rect = NULL;
#endif
static void (*resolve_ft_fill_rect(void))(t_image *img, t_iv4 rect, t_color col)
{
#if !defined(DEBUG)
	void *__resolved_ft_fill_rect = NULL;
#endif
	struct s_cpuid_flags *cpuid_flags;
	struct s_xcr0_flags os_flags;

	cpuid_flags = ft_cpuid_get_cached_flags();
	ft_xgetbv(0, &os_flags.flags);
	if (os_flags.avx && cpuid_flags->avx && cpuid_flags->avx2)
		__resolved_ft_fill_rect = fill_rect_ymm;
	else if (os_flags.sse && cpuid_flags->sse2)
		__resolved_ft_fill_rect = fill_rect_xmm;
	else
		__resolved_ft_fill_rect = fill_rect;
	return __resolved_ft_fill_rect;
}

void ft_fill_rect(t_image *img, t_iv4 rect, t_color col)
	__attribute__((ifunc("resolve_ft_fill_rect")));

#if defined(DEBUG)
static void *__resolved_ft_fill_rect2 = NULL;
#endif
static void (*resolve_ft_fill_rect2(void))(t_image *img, t_iv4 rect, t_color col)
{
#if !defined(DEBUG)
	void *__resolved_ft_fill_rect2 = NULL;
#endif
	struct s_cpuid_flags *cpuid_flags;
	struct s_xcr0_flags os_flags;

	cpuid_flags = ft_cpuid_get_cached_flags();
	ft_xgetbv(0, &os_flags.flags);
	if (os_flags.sse && os_flags.avx && cpuid_flags->avx2 && cpuid_flags->sse2)
		__resolved_ft_fill_rect2 = fill_rect2_avx2;
	else
		__resolved_ft_fill_rect2 = fill_rect2;
	return __resolved_ft_fill_rect2;
}

void ft_fill_rect2(t_image *img, t_iv4 rect, t_color col)
	__attribute__((ifunc("resolve_ft_fill_rect2")));

#if defined(DEBUG)
__attribute__((constructor)) static void __debug_ifunc()
{
	ft_printf("ft_fill_rect:");
	if (__resolved_ft_fill_rect == fill_rect_ymm)
		ft_printf("fill_rect_ymm\n");
	else if (__resolved_ft_fill_rect == fill_rect_xmm)
		ft_printf("fill_rect_xmm\n");
	else
		ft_printf("fill_rect\n");
	ft_printf("ft_fill_rect2:");
	if (__resolved_ft_fill_rect2 == fill_rect2_avx2)
		ft_printf("fill_rect2_avx2\n");
	else
		ft_printf("fill_rect2\n");
}
#endif
