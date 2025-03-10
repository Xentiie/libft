/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_horizontal.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 15:22:58 by reclaire          #+#    #+#             */
/*   Updated: 2025/03/11 00:31:28 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/images.h"

static void draw_horiz_line(t_image *img, t_iv2 p1, S32 x2, t_color col, t_iv4 bound)
{
	t_color *ptr;
	S32 xlen;
	
	if (p1.y < bound.y || p1.y >= bound.w)
		return;

	p1.x = ft_clamp(bound.x, bound.z - 1, p1.x);
	x2 = ft_clamp(bound.x, bound.z - 1, x2);

	xlen = ft_abs(p1.x - x2);

	ptr = ft_get_pixel(img, ft_min(p1.x, x2), p1.y);
	for (S32 i = 0; i < xlen; i++, ptr++)
		*ptr = col;
}

static void draw_horiz_line2(t_image *img, t_iv2 p1, S32 x2, t_color col, t_iv4 bound)
{
	t_color *ptr;
	S32 xlen;
	
	if (p1.y < bound.y || p1.y >= bound.w)
		return;

	p1.x = ft_clamp(bound.x, bound.z - 1, p1.x);
	x2 = ft_clamp(bound.x, bound.z - 1, x2);

	xlen = ft_abs(p1.x - x2);

	ptr = ft_get_pixel(img, ft_min(p1.x, x2), p1.y);
	for (S32 i = 0; i < xlen; i++, ptr++)
		*ptr = ft_alpha_blend(*ptr, col);
}

void ft_draw_line_horizontal(t_image *img, t_iv2 p1, S32 x2, t_color col)
{
	draw_horiz_line(img, p1, x2, col, ft_image_rect(img));
}

void ft_draw_line_horizontal_bound(t_image *img, t_iv2 p1, S32 x2, t_color col, t_iv4 bound)
{
	bound = ft_clip_rect_rect(bound, ft_image_rect(img));
	draw_horiz_line(img, p1, x2, col, bound);
}

void ft_draw_line_horizontal2(t_image *img, t_iv2 p1, S32 x2, t_color col)
{
	draw_horiz_line2(img, p1, x2, col, ft_image_rect(img));
}

void ft_draw_line_horizontal_bound2(t_image *img, t_iv2 p1, S32 x2, t_color col, t_iv4 bound)
{
	bound = ft_clip_rect_rect(bound, ft_image_rect(img));
	draw_horiz_line2(img, p1, x2, col, bound);
}

