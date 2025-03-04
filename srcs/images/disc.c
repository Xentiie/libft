/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 20:16:13 by reclaire          #+#    #+#             */
/*   Updated: 2025/02/23 22:27:34 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/images.h"
#include "libft/maths.h"

void ft_draw_disc_bound(t_image *img, t_iv2 pos, S32 radius, t_color col, t_iv4 bound)
{
	S32 x = 0, y = radius;
	S32 d = 1 - radius; // Decision parameter

	// Draw and fill the initial points on all octants
	ft_draw_line_horizontal_bound(img, ivec2(pos.x - x, pos.y + y), pos.x + x, col, bound);
	ft_draw_line_horizontal_bound(img, ivec2(pos.x - x, pos.y - y), pos.x + x, col, bound);
	ft_draw_line_horizontal_bound(img, ivec2(pos.x - y, pos.y + x), pos.x + y, col, bound);
	ft_draw_line_horizontal_bound(img, ivec2(pos.x - y, pos.y - x), pos.x + y, col, bound);

	while (x < y)
	{
		x++;

		if (d < 0)
			d += 2 * x + 1;
		else
		{
			y--;
			d += 2 * (x - y) + 1;
		}

		// Draw and fill horizontal lines for each segment
		ft_draw_line_horizontal_bound(img, ivec2(pos.x - x, pos.y + y), pos.x + x, col, bound);
		ft_draw_line_horizontal_bound(img, ivec2(pos.x - x, pos.y - y), pos.x + x, col, bound);
		ft_draw_line_horizontal_bound(img, ivec2(pos.x - y, pos.y + x), pos.x + y, col, bound);
		ft_draw_line_horizontal_bound(img, ivec2(pos.x - y, pos.y - x), pos.x + y, col, bound);
	}
}

void ft_draw_disc(t_image *img, t_iv2 pos, S32 radius, t_color col)
{
	ft_draw_disc_bound(img, pos, radius, col, ivec4(0, 0, img->size.x, img->size.y));
}

void ft_draw_disc_bound2(t_image *img, t_iv2 pos, S32 radius, t_color col, t_iv4 rect)
{
	S32 x = 0, y = radius;
	S32 d = 1 - radius; // Decision parameter

	// Draw and fill the initial points on all octants
	ft_draw_line_horizontal_bound2(img, ivec2(pos.x - x, pos.y + y), pos.x + x, col, rect);
	ft_draw_line_horizontal_bound2(img, ivec2(pos.x - x, pos.y - y), pos.x + x, col, rect);
	ft_draw_line_horizontal_bound2(img, ivec2(pos.x - y, pos.y + x), pos.x + y, col, rect);
	ft_draw_line_horizontal_bound2(img, ivec2(pos.x - y, pos.y - x), pos.x + y, col, rect);

	while (x < y)
	{
		x++;

		if (d < 0)
			d += 2 * x + 1;
		else
		{
			y--;
			d += 2 * (x - y) + 1;
		}

		// Draw and fill horizontal lines for each segment
		ft_draw_line_horizontal_bound2(img, ivec2(pos.x - x, pos.y + y), pos.x + x, col, rect);
		ft_draw_line_horizontal_bound2(img, ivec2(pos.x - x, pos.y - y), pos.x + x, col, rect);
		ft_draw_line_horizontal_bound2(img, ivec2(pos.x - y, pos.y + x), pos.x + y, col, rect);
		ft_draw_line_horizontal_bound2(img, ivec2(pos.x - y, pos.y - x), pos.x + y, col, rect);
	}
}

void ft_draw_disc2(t_image *img, t_iv2 pos, S32 radius, t_color col)
{
	ft_draw_disc_bound2(img, pos, radius, col, ivec4(0, 0, img->size.x, img->size.y));
}
