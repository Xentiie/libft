/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rect.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 16:22:47 by reclaire          #+#    #+#             */
/*   Updated: 2025/03/05 13:53:57 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/images.h"
#include "libft/maths.h"

void ft_draw_rect_bound(t_image *img, t_iv4 rect, t_color col, t_iv4 bound)
{
	rect.x = ft_imax(rect.x, bound.x);
	rect.y = ft_imax(rect.y, bound.y);
	rect.z = ft_imin(rect.z, bound.z);
	rect.w = ft_imin(rect.w, bound.w);

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
	rect.x = ft_imax(rect.x, bound.x);
	rect.y = ft_imax(rect.y, bound.y);
	rect.z = ft_imin(rect.z, bound.z);
	rect.w = ft_imin(rect.w, bound.w);

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
	rect.x = ft_imax(rect.x, bound.x);
	rect.y = ft_imax(rect.y, bound.y);
	rect.z = ft_imin(rect.z, bound.z);
	rect.w = ft_imin(rect.w, bound.w);

	ft_fill_rect(img, rect, col);
}

void ft_fill_rect_bound2(t_image *img, t_iv4 rect, t_color col, t_iv4 bound)
{
	rect.x = ft_imax(rect.x, bound.x);
	rect.y = ft_imax(rect.y, bound.y);
	rect.z = ft_imin(rect.z, bound.z);
	rect.w = ft_imin(rect.w, bound.w);

	ft_fill_rect2(img, rect, col);
}

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

static void fill_rect_avx2(t_image *img, t_iv4 rect, t_color col)
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

static void (*resolve_ft_fill_rect(void))(t_image *img, t_iv4 rect, t_color col)
{
	return fill_rect;
}

void ft_fill_rect(t_image *img, t_iv4 rect, t_color col)
	__attribute__((ifunc("resolve_ft_fill_rect")));


static void fill_rect_abl(t_image *img, t_iv4 rect, t_color col)
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

static void (*resolve_ft_fill_rect2(void))(t_image *img, t_iv4 rect, t_color col)
{
	return fill_rect_abl;
}

void ft_fill_rect2(t_image *img, t_iv4 rect, t_color col)
	__attribute__((ifunc("resolve_ft_fill_rect2")));
