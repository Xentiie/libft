/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 15:22:58 by reclaire          #+#    #+#             */
/*   Updated: 2025/03/11 00:06:59 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/maths.h"
#include "libft/images.h"

static void draw_line(t_image *img, t_iv2 p1, t_iv2 p2, t_color col, t_iv4 rect)
{
	if (ft_clip_line_rect(&p1, &p2, rect))
	{
		S32 dx = ft_abs(p2.x - p1.x), dy = ft_abs(p2.y - p1.y);
		S32 sx = (p1.x < p2.x) ? 1 : -1;
		S32 sy = (p1.y < p2.y) ? 1 : -1;
		S32 err = dx - dy, e2;

		while (TRUE)
		{
			*ft_get_pixel(img, p1.x, p1.y) = col;
			if (p1.x == p2.x && p1.y == p2.y)
				break;

			e2 = 2 * err;
			if (e2 > -dy)
			{
				err -= dy;
				p1.x += sx;
			}
			if (e2 < dx)
			{
				err += dx;
				p1.y += sy;
			}
		}
	}
}

static void draw_line2(t_image *img, t_iv2 p1, t_iv2 p2, t_color col, t_iv4 rect)
{
	t_color *addr;

	if (ft_clip_line_rect(&p1, &p2, rect))
	{
		S32 dx = ft_abs(p2.x - p1.x), dy = ft_abs(p2.y - p1.y);
		S32 sx = (p1.x < p2.x) ? 1 : -1;
		S32 sy = (p1.y < p2.y) ? 1 : -1;
		S32 err = dx - dy, e2;

		while (TRUE)
		{
			addr = ft_get_pixel(img, p1.x, p1.y);
			*addr = ft_alpha_blend(*addr, col);
			if (p1.x == p2.x && p1.y == p2.y)
				break;

			e2 = 2 * err;
			if (e2 > -dy)
			{
				err -= dy;
				p1.x += sx;
			}
			if (e2 < dx)
			{
				err += dx;
				p1.y += sy;
			}
		}
	}
}

void ft_draw_line(t_image *img, t_iv2 p1, t_iv2 p2, t_color col)
{
	draw_line(img, p1, p2, col, ft_image_rect(img));
}

void ft_draw_line_bound(t_image *img, t_iv2 p1, t_iv2 p2, t_color col, t_iv4 bound)
{
	bound = ft_clip_rect_rect(bound, ft_image_rect(img));
	draw_line(img, p1, p2, col, bound);
}

void ft_draw_line2(t_image *img, t_iv2 p1, t_iv2 p2, t_color col)
{
	draw_line2(img, p1, p2, col, ft_image_rect(img));
}

void ft_draw_line_bound2(t_image *img, t_iv2 p1, t_iv2 p2, t_color col, t_iv4 bound)
{
	bound = ft_clip_rect_rect(bound, ft_image_rect(img));
	draw_line2(img, p1, p2, col, bound);
}
