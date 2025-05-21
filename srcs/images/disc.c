/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 20:16:13 by reclaire          #+#    #+#             */
/*   Updated: 2025/05/20 23:26:57 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/images.h"

#include <stdarg.h>

void ft_draw_disc(t_image *img, t_iv2 pos, S32 radius, t_color col, U8 flags, ...)
{
	S32 x = 0, y = radius;
	S32 d = 1 - radius; // Decision parameter

	va_list lst;
	t_iv4 bound;

	bound = ft_image_rect(img);

	va_start(lst, flags);
	if (flags & FT_DRAW_FLAG_CLIP)
		bound = ft_clip_rect_rect(va_arg(lst, t_iv4), bound);
	va_end(lst);

	/* circle entirely outside the boundary */
	//	if (pos.x - x < bound.x && pos.x + x > )

	// Draw and fill the initial points on all octants
	ft_draw_line_horizontal(img, ivec2(pos.x - x, pos.y + y), pos.x + x, col, 0);
	ft_draw_line_horizontal(img, ivec2(pos.x - x, pos.y - y), pos.x + x, col, 0);
	ft_draw_line_horizontal(img, ivec2(pos.x - y, pos.y + x), pos.x + y, col, 0);
	ft_draw_line_horizontal(img, ivec2(pos.x - y, pos.y - x), pos.x + y, col, 0);

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
		ft_draw_line_horizontal(img, ivec2(pos.x - x, pos.y + y), pos.x + x, col, 0);
		ft_draw_line_horizontal(img, ivec2(pos.x - x, pos.y - y), pos.x + x, col, 0);
		ft_draw_line_horizontal(img, ivec2(pos.x - y, pos.y + x), pos.x + y, col, 0);
		ft_draw_line_horizontal(img, ivec2(pos.x - y, pos.y - x), pos.x + y, col, 0);
	}
}
