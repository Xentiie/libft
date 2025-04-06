/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitmaps.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 21:44:36 by reclaire          #+#    #+#             */
/*   Updated: 2025/04/02 15:08:03 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/images.h"
#include "libft/strings.h"

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

void ft_draw_bitmap_text_with_col(t_image *out, t_iv4 rect, t_bitmap *bitmap, string str, F32 scale, t_iv2 kerning, t_color col)
{
	S32 char_size;
	S32 line_size;
	S32 chars_per_line;
	U64 len;
	S32 str_len;

	S32 bitmap_x_step;
	S32 bitmap_y_step;

	len = ft_strlen(str);
	char_size = (bitmap->char_width * scale + kerning.x);
	line_size = (bitmap->char_height * scale + kerning.y);

	chars_per_line = (rect.z - rect.x + kerning.x) / char_size;
	str_len = ft_min(len, chars_per_line);

	bitmap_x_step = bitmap->char_width + bitmap->sep_width;
	bitmap_y_step = bitmap->char_height + bitmap->sep_height;

	for (S32 i = 0; i < str_len; i++)
	{
		S8 v = str[i];
		if (v < 32)
			v = ' ';
		v -= 32;

		t_iv2 out_pos = ivec2(rect.x + ((i % chars_per_line) * char_size),
							  rect.y + ((i / chars_per_line) * line_size));
		t_iv2 bitmap_pos = ivec2((v % bitmap->line_width) * bitmap_x_step,
								 (v / bitmap->line_width) * bitmap_y_step);

		t_iv4 out_rect = ivec4(out_pos.x, out_pos.y, out_pos.x + bitmap->char_width * scale,
							   out_pos.y + bitmap->char_height * scale);
		t_iv4 bitmap_rect = ivec4(bitmap_pos.x, bitmap_pos.y, bitmap_pos.x + bitmap->char_width,
								  bitmap_pos.y + bitmap->char_height);
		ft_stretch_image3(out, out_rect, bitmap->img, bitmap_rect, col);
		//ft_stretch_image2(out, out_rect, bitmap->img, bitmap_rect);
	}
}

void ft_draw_bitmap_text(t_image *out, t_iv4 rect, t_bitmap *bitmap, string str, F32 scale,
						 t_iv2 kerning, t_color col)
{
	S32 char_size;
	S32 line_size;
	S32 chars_per_line;
	S32 available_lines;
	U64 len;
	S32 str_len;

	S32 bitmap_x_step;
	S32 bitmap_y_step;
	(void) col;

	len = ft_strlen(str);
	char_size = (bitmap->char_width * scale + kerning.x);
	line_size = (bitmap->char_height * scale + kerning.y);

	chars_per_line = (rect.z - rect.x + kerning.x) / char_size;
	available_lines = (rect.w - rect.y + kerning.y) / line_size;

	str_len = ft_min(len, chars_per_line * available_lines);

	bitmap_x_step = bitmap->char_width + bitmap->sep_width;
	bitmap_y_step = bitmap->char_height + bitmap->sep_height;

	for (S32 i = 0; i < str_len; i++)
	{
		S8 v = str[i];
		if (v < 32)
			v = ' ';
		v -= 32;

		t_iv2 out_pos = ivec2(rect.x + ((i % chars_per_line) * char_size),
							  rect.y + ((i / chars_per_line) * line_size));
		t_iv2 bitmap_pos = ivec2((v % bitmap->line_width) * bitmap_x_step + 1,
								 (v / bitmap->line_width) * bitmap_y_step + 1);

		t_iv4 out_rect = ivec4(out_pos.x, out_pos.y, out_pos.x + bitmap->char_width * scale,
							   out_pos.y + bitmap->char_height * scale);
		t_iv4 bitmap_rect = ivec4(bitmap_pos.x, bitmap_pos.y, bitmap_pos.x + bitmap->char_width,
								  bitmap_pos.y + bitmap->char_height);

		ft_stretch_image2(out, out_rect, bitmap->img, bitmap_rect);
	}
}