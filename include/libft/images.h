/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 23:26:42 by reclaire          #+#    #+#             */
/*   Updated: 2025/05/20 23:23:36 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(LIBFT_IMAGES_H)
#define LIBFT_IMAGES_H

#include "libft/libft.h"
#include "libft/lists.h"
#include "libft/maths.h"
#include "libft/macros.h"

typedef union u_color
{
	U32 v;
	struct
	{
#if !defined(COLORS_FORMAT_MLX)
		U8 b;
		U8 g;
		U8 r;
		U8 a;
#else
		U8 r;
		U8 g;
		U8 b;
		U8 a;
#endif
	};
} t_color;

typedef struct s_image
{
	union
	{
		U8 *data;
		t_color *pixels;
	};
	t_iv2 size;
} t_image;

#define __ft_color5(_r, _g, _b, _a) ((t_color){.r = (_r), .g = (_g), .b = (_b), .a = (_a)})
#define __ft_color4(_r, _g, _b, ...)                                                 \
	VALUE_IFNOT(__VA_OPT__(1), (t_color){.r = (_r), .g = (_g), .b = (_b), .a = 255}) \
	__VA_OPT__(__ft_color5(_r, _g, _b, __VA_ARGS__))
#define __ft_color3(_r, _g, ...)                                                  \
	VALUE_IFNOT(__VA_OPT__(1), (t_color){.r = (_r), .g = (_g), .b = 0, .a = 255}) \
	__VA_OPT__(__ft_color4(_r, _g, __VA_ARGS__))
#define __ft_color2(_r, ...)                                                         \
	VALUE_IFNOT(__VA_OPT__(1), (t_color){.r = (_r), .g = (_r), .b = (_r), .a = 255}) \
	__VA_OPT__(__ft_color3(_r, __VA_ARGS__))

/* If only `red` specified: returns `(r, r, r, 255)`
 * If `red + green` specified: returns `(r, g, 0, 255)`
 * If `red + green + blue` specified: returns `(r, g, b, 255)`
 * If `red + green + blue + alpha` specified: returns `(r, g, b, a)` */
#define ft_color(...) __ft_color2(__VA_ARGS__)

/* The function should expect a `t_iv4` argument representing the bound of the element. No pixels will be drawn outside that boundary. */
#define FT_DRAW_FLAG_CLIP (1 << 0)
/* The function will not compute transparency. */
#define FT_DRAW_FLAG_NO_TRANSPARENCY (1 << 1)

/* initializes an image */
extern bool ft_init_image(t_image *img, t_iv2 size);
/* destroys an image */
extern void ft_destroy_image(t_image *img);
inline t_iv4 ft_image_rect(t_image *img) { return ivec4(0, 0, img->size.x, img->size.y); };
/* returns the pixel address at coordinates xy */
#define ft_get_pixel(img, _x, _y) ((img)->pixels + ((_y) * ((img)->size.x) + (_x)))

extern t_color ft_rand_color(U32 seed);

/* alpha-blending between 2 colors. Assumes under's alpha to be 255 */
extern t_color ft_alpha_blend(t_color under, t_color over);
/* full alpha-blending between 2 colors, computing the new alpha value */
extern t_color ft_alpha_blend2(t_color under, t_color over);

/* copies the region `srcrect` in `src` to `dst` at position `dstpos`, no alpha blending
 * no out-of-bounds memory access */
extern void ft_copy_image(t_image *dst, t_iv2 dstpos, t_image *src, t_iv4 srcrect);
/* copies the region `srcrect` in `src` to `dst` at position `dstpos`, with alpha blending
 * no out-of-bounds memory access */
extern void ft_copy_image2(t_image *dst, t_iv2 dstpos, t_image *src, t_iv4 srcrect);

extern void ft_stretch_image_new(t_image *dst, t_iv4 dst_rect, t_image *src, t_iv4 src_rect, U8 flags, ...);

extern void ft_stretch_image(t_image *dst, t_iv4 dst_rect, t_image *src, t_iv4 src_rect);
extern void ft_stretch_image2(t_image *dst, t_iv4 dst_rect, t_image *src, t_iv4 src_rect);
extern void ft_stretch_image3(t_image *dst, t_iv4 dst_rect, t_image *src, t_iv4 src_rect, t_color col);

/* lines */
/* draws a line between `p1` and `p2`, bounded by `img->size` */
extern void ft_draw_line(t_image *img, t_iv2 p1, t_iv2 p2, t_color col, U8 flags, ...);

/* draws an horizontal line between `p1.x` and `x2`, bounded by `img->size` */
extern void ft_draw_line_horizontal(t_image *img, t_iv2 p1, S32 x2, t_color col, U8 flags, ...);

/* draws an vertical line between `p1.x` and `x2`, bounded by `img->size` */
extern void ft_draw_line_vertical(t_image *img, t_iv2 p1, S32 y2, t_color col, U8 flags, ...);

/* Draws a rectangle. */
extern void ft_draw_rect(t_image *img, t_iv4 rect, t_color col, U8 flags, ...);

/* Draws a filled rectangle. */
extern void ft_fill_rect(t_image *img, t_iv4 rect, t_color col, U8 flags, ...);

extern void ft_draw_bezier(t_image *img, t_color col, t_v2 p1, t_v2 p2, t_v2 p3, S32 res, U8 flags, ...);

extern void ft_draw_circle_bound(t_image *img, t_iv2 pos, S32 radius, t_color col, t_iv4 bound);
extern void ft_draw_circle(t_image *img, t_iv2 pos, S32 radius, t_color col);
extern void ft_draw_circle_bound2(t_image *img, t_iv2 pos, S32 radius, t_color col, t_iv4 bound);
extern void ft_draw_circle2(t_image *img, t_iv2 pos, S32 radius, t_color col);

extern void ft_draw_disc(t_image *img, t_iv2 pos, S32 radius, t_color col, U8 flags, ...);

extern void ft_draw_triangle(t_image *img, t_iv2 p1, t_iv2 p2, t_iv2 p3, t_color col, U8 flags, ...);

/* bitmaps */
typedef struct s_bitmap
{
	t_image *img;
	U32 char_width;
	U32 char_height;
	U32 sep_width;
	U32 sep_height;
	U32 line_width;
} t_bitmap;

extern void ft_init_bitmap(t_bitmap *bitmap, t_image *img, t_iv2 char_size, U32 line_chars_count, t_iv2 sep_size);
extern t_iv4 ft_bitmap_rect_char_lines(t_bitmap *bitmap, t_iv2 pos, U32 line_width, U32 lines_cnt);
extern void ft_draw_bitmap_text(t_image *out, t_iv4 rect, t_bitmap *bitmap, string str, F32 scale, t_iv2 kerning, t_color col);
extern void ft_draw_bitmap_text_with_col(t_image *out, t_iv4 rect, t_bitmap *bitmap, string str, F32 scale, t_iv2 kerning, t_color col);

#endif