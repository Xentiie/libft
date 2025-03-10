/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_vertical.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 15:22:58 by reclaire          #+#    #+#             */
/*   Updated: 2025/03/11 00:34:51 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/images.h"

static void draw_vert_line(t_image *img, t_iv2 p1, S32 y2, t_color col, t_iv4 bound)
{
	t_color *ptr;
	S32 ylen;

	if (p1.x < bound.x || p1.x >= bound.z)
		return;

	p1.y = ft_clamp(bound.y, bound.w, p1.y);
	y2 = ft_clamp(bound.y, bound.w, y2);

	ylen = ft_abs(p1.y - y2);

	ptr = ft_get_pixel(img, p1.x, ft_min(p1.y, y2));
	for (S32 y = 0; y < ylen; y++, ptr += img->size.x)
		*ptr = col;
}

static void draw_vert_line2(t_image *img, t_iv2 p1, S32 y2, t_color col, t_iv4 bound)
{
	t_color *ptr;
	S32 ylen;

	if (p1.x < bound.x || p1.x >= bound.z)
		return;

	p1.y = ft_clamp(bound.y, bound.w, p1.y);
	y2 = ft_clamp(bound.y, bound.w, y2);

	ylen = ft_abs(p1.y - y2);

	ptr = ft_get_pixel(img, p1.x, ft_min(p1.y, y2));
	for (S32 y = 0; y < ylen; y++, ptr += img->size.x)
		*ptr = ft_alpha_blend(*ptr, col);
}

void ft_draw_line_vertical(t_image *img, t_iv2 p1, S32 y2, t_color col)
{
	draw_vert_line(img, p1, y2, col, ft_image_rect(img));
}

void ft_draw_line_vertical_bound(t_image *img, t_iv2 p1, S32 y2, t_color col, t_iv4 bound)
{
	bound = ft_clip_rect_rect(bound, ft_image_rect(img));
	draw_vert_line(img, p1, y2, col, bound);
}

void ft_draw_line_vertical2(t_image *img, t_iv2 p1, S32 y2, t_color col)
{
	draw_vert_line2(img, p1, y2, col, ft_image_rect(img));
}

void ft_draw_line_vertical_bound2(t_image *img, t_iv2 p1, S32 y2, t_color col, t_iv4 bound)
{
	bound = ft_clip_rect_rect(bound, ft_image_rect(img));
	draw_vert_line2(img, p1, y2, col, bound);
}
