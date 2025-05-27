/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitmaps.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 21:44:36 by reclaire          #+#    #+#             */
/*   Updated: 2025/05/26 15:11:38 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/images.h"
#include "libft/strings.h"

#include <stdarg.h>

// #define BITMAP_TEXT_DEBUG 1

void ft_init_bitmap(t_bitmap *bitmap, t_image *img, t_iv2 char_size, U32 line_chars_count,
					t_iv2 sep_size)
{
	bitmap->img = img;
	bitmap->char_width = char_size.x;
	bitmap->char_height = char_size.y;
	bitmap->line_width = line_chars_count;
	bitmap->sep_width = sep_size.x;
	bitmap->sep_height = sep_size.y;
}

t_iv4 ft_bitmap_rect_char_lines(t_bitmap *bitmap, t_iv2 pos, U32 line_width, U32 lines_cnt)
{
	return ivec4(pos.x, pos.y, pos.x + (line_width * (bitmap->sep_width + bitmap->char_width)),
				 pos.y + (lines_cnt * (bitmap->sep_height + bitmap->char_height)));
}

void ft_draw_bitmap_text(t_image *out, t_iv4 rect, t_bitmap *bitmap, string str, F32 scale,
						 t_iv2 kerning, U8 flags, ...)
{
	va_list lst;
	/* Clipping rect. */
	t_iv4 clip_rect;

	/* The current character to draw. */
	char c;
	/* The current drawing position on `out`. */
	t_iv2 pos;
	/* The color to add to the bitmap. */
	t_color col;

	/* The amount of pixels to skip in the bitmap image to go to the next character. */
	t_iv2 char_step;
	/* Character position in bitmap image. */
	t_iv4 char_pos;
	/* Character rect in bitmap image. */
	t_iv4 char_rect;

	/* The amount of pixels to skip in the destination image to go to the next character. */
	t_iv2 out_step;
	/* Character rect in `out`. (scaled) */
	t_iv4 out_rect;

	clip_rect = ft_image_rect(out);
	va_start(lst, flags);
	if (flags & FT_DRAW_FLAG_CLIP)
		clip_rect = ft_clip_rect_rect(clip_rect, va_arg(lst, t_iv4));
	if (flags & FT_DRAW_FLAG_COLOR)
		col = va_arg(lst, t_color);
	va_end(lst);

	pos = ivec2(rect.x, rect.y);

	char_step = ivec2(
		bitmap->char_width + bitmap->sep_width,
		bitmap->char_height + bitmap->sep_height);
	out_step = ivec2(
		bitmap->char_width * scale + kerning.x,
		bitmap->char_height * scale + kerning.y);

	flags |= FT_DRAW_FLAG_CLIP;
	clip_rect = ft_clip_rect_rect(rect, clip_rect);

	c = *str;
	while (c && pos.x < rect.z && pos.y < rect.w)
	{
		if (c < 32 || c == 127)
			c = ' ';
		c -= 32;

		char_rect.x = (c % bitmap->line_width) * char_step.x;
		char_rect.y = (c / bitmap->line_width) * char_step.y;
		char_rect.z = char_rect.x + bitmap->char_width;
		char_rect.w = char_rect.y + bitmap->char_height;

		if (flags & FT_DRAW_FLAG_BITMAP_WRAP && pos.x + out_step.x >= rect.z)
		{
			pos.x = rect.x;
			pos.y += out_step.y;
		}

		out_rect.x = pos.x;
		out_rect.y = pos.y;
		out_rect.z = pos.x + out_step.x;
		out_rect.w = pos.y + out_step.y;

		ft_stretch_image(out, out_rect, bitmap->img, char_rect, flags, clip_rect, col);

		str++;
		c = *str;
		pos.x += out_step.x;
	}
}
