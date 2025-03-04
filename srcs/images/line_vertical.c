/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_vertical.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 15:22:58 by reclaire          #+#    #+#             */
/*   Updated: 2025/02/23 22:27:49 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/images.h"
#include "libft/maths.h"

void ft_draw_line_vertical_bound(t_image *img, t_iv2 p1, S32 y2, t_color col, t_iv4 bound)
{
	t_color *ptr;
	S32 ylen;

	bound.x = ft_imax(bound.x, 0);
	bound.y = ft_imax(bound.y, 0);
	bound.z = ft_imin(bound.z, img->size.x);
	bound.w = ft_imin(bound.w, img->size.y);

	if (p1.x < bound.x || p1.x >= bound.w)
		return;

	p1.y = ft_clamp(bound.y, bound.w, p1.y);
	y2 = ft_clamp(bound.y, bound.w, y2);

	ylen = ft_abs(p1.y - y2);

	ptr = ft_get_pixel(img, p1.x, ft_imin(p1.y, y2));
	for (S32 y = 0; y < ylen; y++, ptr += img->size.x)
		*ptr = col;
}

void ft_draw_line_vertical(t_image *img, t_iv2 p1, S32 y2, t_color col)
{
	ft_draw_line_vertical_bound(img, p1, y2, col, ivec4(0, 0, img->size.x, img->size.y));
}

void ft_draw_line_vertical_bound2(t_image *img, t_iv2 p1, S32 y2, t_color col, t_iv4 bound)
{
	t_color *ptr;
	S32 ylen;

	bound.x = ft_imax(bound.x, 0);
	bound.y = ft_imax(bound.y, 0);
	bound.z = ft_imin(bound.z, img->size.x);
	bound.w = ft_imin(bound.w, img->size.y);

	if (p1.x < bound.x || p1.x >= bound.w)
		return;

	p1.y = ft_clamp(bound.y, bound.w, p1.y);
	y2 = ft_clamp(bound.y, bound.w, y2);

	ylen = ft_abs(p1.y - y2);

	ptr = ft_get_pixel(img, p1.x, ft_imin(p1.y, y2));
	for (S32 y = 0; y < ylen; y++, ptr += img->size.x)
		*ptr = ft_alpha_blend(*ptr, col);
}

void ft_draw_line_vertical2(t_image *img, t_iv2 p1, S32 y2, t_color col)
{
	ft_draw_line_vertical_bound2(img, p1, y2, col, ivec4(0, 0, img->size.x, img->size.y));
}
