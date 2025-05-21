/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 19:39:00 by reclaire          #+#    #+#             */
/*   Updated: 2025/05/20 04:05:42 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/images.h"

#include "libft/bits/extended_aliases.h"
#include "libft/bits/variants/ft_draw_triangle.h"
#include "libft/bits/variants/ft_draw_line.h"

#include <stdarg.h>

void ft_draw_triangle(t_image *img, t_iv2 p1, t_iv2 p2, t_iv2 p3, t_color col, U8 flags, ...)
{
	va_list lst;
	t_iv4 clip_rect;

	/* If we aren't ignoring alpha and color's alpha is 0, ignore */
	if (!(flags & FT_DRAW_FLAG_NO_TRANSPARENCY) && col.a == 0)
		return;

	{ /* Get clip rect */
		clip_rect = ft_image_rect(img);

		va_start(lst, flags);
		if (flags & FT_DRAW_FLAG_CLIP)
			clip_rect = ft_clip_rect_rect(va_arg(lst, t_iv4), clip_rect);
		va_end(lst);
	}

	ft_draw_line(img, p1, p2, col, flags & FT_DRAW_FLAG_CLIP, clip_rect);
	ft_draw_line(img, p2, p3, col, flags & FT_DRAW_FLAG_CLIP, clip_rect);
	ft_draw_line(img, p3, p1, col, flags & FT_DRAW_FLAG_CLIP, clip_rect);
}
