/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 23:26:42 by reclaire          #+#    #+#             */
/*   Updated: 2025/03/11 00:31:07 by reclaire         ###   ########.fr       */
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
		U8 b;
		U8 g;
		U8 r;
		U8 a;

		/*
		U8 r;
		U8 g;
		U8 b;
		U8 a;
		*/
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

struct s_png_metadata
{
	/*
	Each element of the list contains 2 strings, one behind another.
	First one is the title, second is the text.
	*/
t_list *text_data;
};

typedef struct s_png_img
{
	U32 width;
	U32 height;
	U8 bit_depth;
	U8 bpp;
	U8 color_type;
	U8 compression_method;
	U8 filter_method;
	U8 interlace_method;

	U8 sample_depth;

	/* Pixels data */
	U8 *data;

	/*
	Each element of the list contains 2 strings, one behind another.
	First one is the title, second is the text.
	*/
	t_list *text_data;
} t_png_img;

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

extern void ft_stretch_image(t_image *dst, t_iv4 dst_rect, t_image *src, t_iv4 src_rect);
extern void ft_stretch_image2(t_image *dst, t_iv4 dst_rect, t_image *src, t_iv4 src_rect);

#if defined(_FT_IMAGES_EXTENDED_DECLARATIONS)
extern void ft_copy_image_abl(t_image *dst, t_iv2 dstpos, t_image *src, t_iv4 srcrect);
/* image copy, advanced alpha blend (2 pixels processed simultaneously) */
extern void ft_copy_image_abl_avx(t_image *dst, t_iv2 dstpos, t_image *src, t_iv4 srcrect);
/* image copy, super advanced alpha blend (4 pixels processed simultaneously) */
extern void ft_copy_image_abl_avx2(t_image *dst, t_iv2 dstpos, t_image *src, t_iv4 srcrect);
#endif

/* lines */
/* draws a line between `p1` and `p2`, bounded by `img->size` */
extern void ft_draw_line(t_image *img, t_iv2 p1, t_iv2 p2, t_color col);
/* draws a line between `p1` and `p2`, bounded by `img->size` and `bound` */
extern void ft_draw_line_bound(t_image *img, t_iv2 p1, t_iv2 p2, t_color col, t_iv4 bound);
/* draws an alpha blended line between `p1` and `p2`, bounded by `img->size` */
extern void ft_draw_line2(t_image *img, t_iv2 p1, t_iv2 p2, t_color col);
/* draws an alpha blended line between `p1` and `p2`, bounded by `img->size` and `bound` */
extern void ft_draw_line_bound2(t_image *img, t_iv2 p1, t_iv2 p2, t_color col, t_iv4 bound);

/* draws an horizontal line between `p1.x` and `x2`, bounded by `img->size` */
extern void ft_draw_line_horizontal(t_image *img, t_iv2 p1, S32 x2, t_color col);
/* draws an horizontal line between `p1.x` and `x2`, bounded by `img->size` and `bound` */
extern void ft_draw_line_horizontal_bound(t_image *img, t_iv2 p1, S32 x2, t_color col, t_iv4 bound);
/* draws an alpha blended horizontal line between `p1.x` and `x2`, bounded by `img->size` */
extern void ft_draw_line_horizontal2(t_image *img, t_iv2 p1, S32 x2, t_color col);
/* draws an alpha blended horizontal line between `p1.x` and `x2`, bounded by `img->size` and `bound` */
extern void ft_draw_line_horizontal_bound2(t_image *img, t_iv2 p1, S32 x2, t_color col, t_iv4 bound);

/* draws an vertical line between `p1.x` and `x2`, bounded by `img->size` */
extern void ft_draw_line_vertical(t_image *img, t_iv2 p1, S32 x2, t_color col);
/* draws an vertical line between `p1.x` and `x2`, bounded by `img->size` and `bound` */
extern void ft_draw_line_vertical_bound(t_image *img, t_iv2 p1, S32 x2, t_color col, t_iv4 bound);
/* draws an alpha blended vertical line between `p1.x` and `x2`, bounded by `img->size` */
extern void ft_draw_line_vertical2(t_image *img, t_iv2 p1, S32 x2, t_color col);
/* draws an alpha blended vertical line between `p1.x` and `x2`, bounded by `img->size` and `bound` */
extern void ft_draw_line_vertical_bound2(t_image *img, t_iv2 p1, S32 x2, t_color col, t_iv4 bound);

/* Draws a rectangle */
extern void ft_draw_rect(t_image *img, t_iv4 rect, t_color col);
/* Draws a rectangle with alpha-blending */
extern void ft_draw_rect2(t_image *img, t_iv4 rect, t_color col);
/* Draws a rectangle, clipped by `bound` */
extern void ft_draw_rect_bound(t_image *img, t_iv4 rect, t_color col, t_iv4 bound);
/* Draws a rectangle with alpha-blending, clipped by `bound` */
extern void ft_draw_rect_bound2(t_image *img, t_iv4 rect, t_color col, t_iv4 bound);

/* Fills a rectangle */
extern void ft_fill_rect(t_image *img, t_iv4 rect, t_color col);
/* Fills a rectangle with alpha-blending */
extern void ft_fill_rect2(t_image *img, t_iv4 rect, t_color col);
/* Fills a rectangle, clipped by `bound` */
extern void ft_fill_rect_bound(t_image *img, t_iv4 rect, t_color col, t_iv4 bound);
/* Fills a rectangle with alpha-blending, clipped by `bound` */
extern void ft_fill_rect_bound2(t_image *img, t_iv4 rect, t_color col, t_iv4 bound);

extern void ft_draw_bezier(t_image *img, t_color col, t_v2 p1, t_v2 p2, t_v2 p3, S32 res);
extern void ft_draw_bezier2(t_image *img, t_color col, t_v2 p1, t_v2 p2, t_v2 p3, S32 res);
extern void ft_draw_bezier_bound(t_image *img, t_color col, t_v2 p1, t_v2 p2, t_v2 p3, S32 res, t_iv4 bound);
extern void ft_draw_bezier_bound2(t_image *img, t_color col, t_v2 p1, t_v2 p2, t_v2 p3, S32 res, t_iv4 bound);

extern void ft_draw_circle_bound(t_image *img, t_iv2 pos, S32 radius, t_color col, t_iv4 bound);
extern void ft_draw_circle(t_image *img, t_iv2 pos, S32 radius, t_color col);
extern void ft_draw_circle_bound2(t_image *img, t_iv2 pos, S32 radius, t_color col, t_iv4 bound);
extern void ft_draw_circle2(t_image *img, t_iv2 pos, S32 radius, t_color col);

extern void ft_draw_disc_bound(t_image *img, t_iv2 pos, S32 radius, t_color col, t_iv4 bound);
extern void ft_draw_disc(t_image *img, t_iv2 pos, S32 radius, t_color col);
extern void ft_draw_disc_bound2(t_image *img, t_iv2 pos, S32 radius, t_color col, t_iv4 rect);
extern void ft_draw_disc2(t_image *img, t_iv2 pos, S32 radius, t_color col);

extern void ft_draw_triangle(t_image *img, t_iv2 p1, t_iv2 p2, t_iv2 p3, t_color col);
extern void ft_draw_triangle2(t_image *img, t_iv2 p1, t_iv2 p2, t_iv2 p3, t_color col);
extern void ft_draw_triangle_bound(t_image *img, t_iv2 p1, t_iv2 p2, t_iv2 p3, t_color col, t_iv4 bound);
extern void ft_draw_triangle_bound2(t_image *img, t_iv2 p1, t_iv2 p2, t_iv2 p3, t_color col, t_iv4 bound);

extern t_png_img *ft_load_png(filedesc f, bool verbose);
extern void ft_free_png_img(t_png_img *img);

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


#endif