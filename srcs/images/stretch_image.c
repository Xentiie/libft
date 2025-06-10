/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stretch_image.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:49:59 by reclaire          #+#    #+#             */
/*   Updated: 2025/05/29 15:29:16 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_int.h"

#include "libft/images.h"
#include "libft/io.h"

#include "libft/bits/extended_aliases.h"
#include "libft/bits/variants/ft_stretch_image.h"

#include <stdarg.h>

void ft_stretch_image(t_image *dst, t_iv4 dst_rect, t_image *src, t_iv4 src_rect, U8 flags, ...)
{
	t_iv4 clip_rect;
	t_color col;
	va_list lst;

	t_v2 scl_factor;
	t_v2 src_start;

	va_start(lst, flags);

	{ /* Clipping */

		{ /* Get clip rect */
			clip_rect = ft_image_rect(dst);

			if (flags & FT_DRAW_FLAG_CLIP)
			{
				t_iv4 r = va_arg(lst, t_iv4);
				clip_rect = ft_clip_rect_rect(r, clip_rect);
			}
		}
	}

	src_start = vec2_zero;

	scl_factor = vec2_div(
		vec2(src_rect.z - src_rect.x, src_rect.w - src_rect.y),
		vec2(dst_rect.z - dst_rect.x, dst_rect.w - dst_rect.y)
	);

	if (dst_rect.x < clip_rect.x)
	{
		src_start.x = (clip_rect.x - dst_rect.x) * scl_factor.x;
		dst_rect.x = clip_rect.x;
	}

	if (dst_rect.y < clip_rect.y)
	{
		src_start.y = (clip_rect.y - dst_rect.y) * scl_factor.y;
		dst_rect.y = clip_rect.y;
	}

	if (dst_rect.z >= clip_rect.z)
		dst_rect.z = clip_rect.z;
	if (dst_rect.w >= clip_rect.w)
		dst_rect.w = clip_rect.w;

	src_start.x += src_rect.x;
	src_start.y += src_rect.y;

	if (flags & FT_DRAW_FLAG_COLOR)
	{
		col = va_arg(lst, t_color);
		if (flags & FT_DRAW_FLAG_NO_TRANSPARENCY)
			__ft_stretch_image_col_no_alpha(dst, dst_rect, src, scl_factor, src_start, col);
		else
			__ft_stretch_image_col_alpha(dst, dst_rect, src, scl_factor, src_start, col);
	}
	else
	{
		if (flags & FT_DRAW_FLAG_NO_TRANSPARENCY)
			__ft_stretch_image_no_alpha(dst, dst_rect, src, scl_factor, src_start);
		else
			__ft_stretch_image_alpha(dst, dst_rect, src, scl_factor, src_start);
	}

	va_end(lst);
}

EXTENDED_ALIAS("__ft_stretch_image_no_alpha", 0, (), ())
void __ft_stretch_image_no_alpha_base(t_image *dst, t_iv4 dst_rect, t_image *src, t_v2 scl_factor, t_v2 src_start)
{
	for (S32 dst_y = dst_rect.y; dst_y < dst_rect.w; dst_y++)
	{
		S32 src_y = (dst_y - dst_rect.y) * scl_factor.y + src_start.y;

		F32 src_x = src_start.x;
		for (S32 dst_x = dst_rect.x; dst_x < dst_rect.z; dst_x++, src_x += scl_factor.x)
		{
			t_color *dst_addr;
			t_color *src_addr;

			dst_addr = ft_get_pixel(dst, dst_x, dst_y);
			src_addr = ft_get_pixel(src, (S32)(src_x), src_y);

			*dst_addr = *src_addr;
		}
	}
}

EXTENDED_ALIAS("__ft_stretch_image_alpha", 0, (), ())
void __ft_stretch_image_alpha_base(t_image *dst, t_iv4 dst_rect, t_image *src, t_v2 scl_factor, t_v2 src_start)
{
	for (S32 dst_y = dst_rect.y; dst_y < dst_rect.w; dst_y++)
	{
		S32 src_y = (dst_y - dst_rect.y) * scl_factor.y + src_start.y;

		F32 src_x = src_start.x;
		for (S32 dst_x = dst_rect.x; dst_x < dst_rect.z; dst_x++, src_x += scl_factor.x)
		{
			t_color *dst_addr;
			t_color *src_addr;

			dst_addr = ft_get_pixel(dst, dst_x, dst_y);
			src_addr = ft_get_pixel(src, (S32)(src_x), src_y);
			*dst_addr = ft_alpha_blend(*dst_addr, *src_addr);
		}
	}
}

EXTENDED_ALIAS("__ft_stretch_image_col_no_alpha", 0, (), ())
void __ft_stretch_image_col_no_alpha_base(t_image *dst, t_iv4 dst_rect, t_image *src, t_v2 scl_factor, t_v2 src_start, t_color col)
{
	t_color c;

	for (S32 dst_y = dst_rect.y; dst_y < dst_rect.w; dst_y++)
	{
		S32 src_y = (dst_y - dst_rect.y) * scl_factor.y + src_start.y;

		F32 src_x = src_start.x;
		for (S32 dst_x = dst_rect.x; dst_x < dst_rect.z; dst_x++, src_x += scl_factor.x)
		{
			t_color *dst_addr;
			t_color *src_addr;

			dst_addr = ft_get_pixel(dst, dst_x, dst_y);
			src_addr = ft_get_pixel(src, (S32)(src_x), src_y);

			c = *src_addr;
			c.r *= col.r / 255;
			c.g *= col.g / 255;
			c.b *= col.b / 255;

			*dst_addr = c;
		}
	}
}

EXTENDED_ALIAS("__ft_stretch_image_col_alpha", 0, (), ())
void __ft_stretch_image_col_alpha_base(t_image *dst, t_iv4 dst_rect, t_image *src, t_v2 scl_factor, t_v2 src_start, t_color col)
{
	t_color c;
	U8 a;

	for (S32 dst_y = dst_rect.y; dst_y < dst_rect.w; dst_y++)
	{
		S32 src_y = (dst_y - dst_rect.y) * scl_factor.y + src_start.y;

		F32 src_x = src_start.x;
		for (S32 dst_x = dst_rect.x; dst_x < dst_rect.z; dst_x++, src_x += scl_factor.x)
		{
			t_color *dst_addr;
			t_color *src_addr;

			dst_addr = ft_get_pixel(dst, dst_x, dst_y);
			src_addr = ft_get_pixel(src, (S32)(src_x), src_y);

			c = *src_addr;
			a = c.a;
			c = ft_alpha_blend(c, col);
			c.a = a;
			*dst_addr = ft_alpha_blend(*dst_addr, c);
		}
	}
}

/* Auto-generated by build-aux/extended_aliases.py */

#include "libft/sys/cpuid.h"
#include "libft/sys/xsave.h"
#include "libft/io.h"

#if defined(DEBUG)
static void *__resolved___ft_stretch_image_no_alpha = NULL;
#endif
static void (*resolve___ft_stretch_image_no_alpha(void))(t_image * dst, t_iv4 dst_rect, t_image * src, t_v2 scl_factor, t_v2 src_start)
{

#if !defined(DEBUG)
        void *__resolved___ft_stretch_image_no_alpha = NULL;
#endif
        struct s_cpuid_flags *cpuid_flags;
        struct s_xcr0_flags os_flags;

        cpuid_flags = ft_cpuid_get_cached_flags();
        ft_xgetbv(0, &os_flags.flags);
        if (1)
                __resolved___ft_stretch_image_no_alpha = __ft_stretch_image_no_alpha_base;
        return __resolved___ft_stretch_image_no_alpha;
}

void __ft_stretch_image_no_alpha(t_image * dst, t_iv4 dst_rect, t_image * src, t_v2 scl_factor, t_v2 src_start)
    __attribute__((ifunc("resolve___ft_stretch_image_no_alpha")));
#if defined(DEBUG)
static void *__resolved___ft_stretch_image_alpha = NULL;
#endif
static void (*resolve___ft_stretch_image_alpha(void))(t_image * dst, t_iv4 dst_rect, t_image * src, t_v2 scl_factor, t_v2 src_start)
{

#if !defined(DEBUG)
        void *__resolved___ft_stretch_image_alpha = NULL;
#endif
        struct s_cpuid_flags *cpuid_flags;
        struct s_xcr0_flags os_flags;

        cpuid_flags = ft_cpuid_get_cached_flags();
        ft_xgetbv(0, &os_flags.flags);
        if (1)
                __resolved___ft_stretch_image_alpha = __ft_stretch_image_alpha_base;
        return __resolved___ft_stretch_image_alpha;
}

void __ft_stretch_image_alpha(t_image * dst, t_iv4 dst_rect, t_image * src, t_v2 scl_factor, t_v2 src_start)
    __attribute__((ifunc("resolve___ft_stretch_image_alpha")));
#if defined(DEBUG)
static void *__resolved___ft_stretch_image_col_no_alpha = NULL;
#endif
static void (*resolve___ft_stretch_image_col_no_alpha(void))(t_image * dst, t_iv4 dst_rect, t_image * src, t_v2 scl_factor, t_v2 src_start, t_color col)
{

#if !defined(DEBUG)
        void *__resolved___ft_stretch_image_col_no_alpha = NULL;
#endif
        struct s_cpuid_flags *cpuid_flags;
        struct s_xcr0_flags os_flags;

        cpuid_flags = ft_cpuid_get_cached_flags();
        ft_xgetbv(0, &os_flags.flags);
        if (1)
                __resolved___ft_stretch_image_col_no_alpha = __ft_stretch_image_col_no_alpha_base;
        return __resolved___ft_stretch_image_col_no_alpha;
}

void __ft_stretch_image_col_no_alpha(t_image * dst, t_iv4 dst_rect, t_image * src, t_v2 scl_factor, t_v2 src_start, t_color col)
    __attribute__((ifunc("resolve___ft_stretch_image_col_no_alpha")));
#if defined(DEBUG)
static void *__resolved___ft_stretch_image_col_alpha = NULL;
#endif
static void (*resolve___ft_stretch_image_col_alpha(void))(t_image * dst, t_iv4 dst_rect, t_image * src, t_v2 scl_factor, t_v2 src_start, t_color col)
{

#if !defined(DEBUG)
        void *__resolved___ft_stretch_image_col_alpha = NULL;
#endif
        struct s_cpuid_flags *cpuid_flags;
        struct s_xcr0_flags os_flags;

        cpuid_flags = ft_cpuid_get_cached_flags();
        ft_xgetbv(0, &os_flags.flags);
        if (1)
                __resolved___ft_stretch_image_col_alpha = __ft_stretch_image_col_alpha_base;
        return __resolved___ft_stretch_image_col_alpha;
}

void __ft_stretch_image_col_alpha(t_image * dst, t_iv4 dst_rect, t_image * src, t_v2 scl_factor, t_v2 src_start, t_color col)
    __attribute__((ifunc("resolve___ft_stretch_image_col_alpha")));

#if defined(DEBUG)
__attribute__((constructor)) static void __debug_ifunc()
{
        ft_printf("__ft_stretch_image_no_alpha:");
        if (__resolved___ft_stretch_image_no_alpha == __ft_stretch_image_no_alpha_base)
                ft_printf("__ft_stretch_image_no_alpha_base\n");
        ft_printf("__ft_stretch_image_alpha:");
        if (__resolved___ft_stretch_image_alpha == __ft_stretch_image_alpha_base)
                ft_printf("__ft_stretch_image_alpha_base\n");
        ft_printf("__ft_stretch_image_col_no_alpha:");
        if (__resolved___ft_stretch_image_col_no_alpha == __ft_stretch_image_col_no_alpha_base)
                ft_printf("__ft_stretch_image_col_no_alpha_base\n");
        ft_printf("__ft_stretch_image_col_alpha:");
        if (__resolved___ft_stretch_image_col_alpha == __ft_stretch_image_col_alpha_base)
                ft_printf("__ft_stretch_image_col_alpha_base\n");

}
#endif
