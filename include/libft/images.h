/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 23:26:42 by reclaire          #+#    #+#             */
/*   Updated: 2025/06/10 09:53:59 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(LIBFT_IMAGES_H)
#define LIBFT_IMAGES_H

#include "libft/libft.h"
#include "libft/lists.h"
#include "libft/maths.h"
#include "libft/macros.h"

/* should be the default */
//#define COLORS_FORMAT_MLX
typedef union u_color
{
	U32 v;
	struct
	{
#if defined(COLORS_FORMAT_MLX)
		U8 r;
		U8 g;
		U8 b;
		U8 a;
#else
		U8 b;
		U8 g;
		U8 r;
		U8 a;
#endif
	};
} t_color;

typedef struct s_color_hsv
{
	F32 hue;
	F32 sat;
	F32 val;
} t_color_hsv;

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

/*
Draw functions:
Draw functions accept a `flags` parameter, which is a bitwise combination
of the flags mentionned below. These flags will enable / disable certain
features of the draw function.
For each flag that is set, a corresponding variadic
argument may have to be provided in the variable argument list.

The arguments **must** be passed in the order of flag bit positions,
from least significant bit (LSB) to most significant bit (MSB). This means
that if `FT_DRAW_FLAG1` (bit 0), `FT_DRAW_FLAG2` (bit 1), and `FT_DRAW_FLAG3` (bit 2)
are all set, the arguments must be provided in the order corresponding to these bits:

Examples:
```c
ft_draw_function(FT_DRAW_FLAG1 | FT_DRAW_FLAG3, arg_for_flag1, arg_for_flag3);
ft_draw_function(FT_DRAW_FLAG3 | FT_DRAW_FLAG1, arg_for_flag1, arg_for_flag3);
ft_draw_function(FT_DRAW_FLAG3 | FT_DRAW_FLAG1 | FT_DRAW_FLAG2, arg_for_flag1, arg_for_flag2, arg_for_flag3);
```

Incorrect ordering or omitting expected arguments may lead to undefined behavior.
*/
#define FT_DRAW_FUNCTIONS_DOCUMENTATION

/* The function should expect a `t_iv4` argument representing the bound of the element. No pixels will be drawn outside that boundary. */
#define FT_DRAW_FLAG_CLIP (1 << 0)
/* The function will not compute transparency. */
#define FT_DRAW_FLAG_NO_TRANSPARENCY (1 << 1)
/* The function should expect a `t_color` argument. */
#define FT_DRAW_FLAG_COLOR (1 << 2)
/* Wrap mode for `ft_draw_bitmap_text`. The text will wrap back to the next line if it goes out of bounds. */
#define FT_DRAW_FLAG_BITMAP_WRAP (1 << 3)
/* Multiline text for `ft_draw_bitmap_text`. */
#define FT_DRAW_FLAG_BITMAP_MULTILINE (1 << 4)

/* Returns a randomly generated color based on `seed`. */
extern t_color ft_rand_color(U32 seed);

/* Converts a 2D point on the unit circle and a value into an HSV color.
 * The point determines hue and saturation; `val` sets the value (brightness). */
extern t_color_hsv ft_hsv_from_unit_circle(t_v2 p, F32 val);

/* Converts a 2D point on the circle (at center `p` and radius `radius`) and a value into an HSV color.
 * The point determines hue and saturation; `val` sets the value (brightness). */
extern t_color_hsv ft_hsv_from_circle(t_v2 p, F32 radius, F32 val);

/* Converts a point within a rectangular region into an HSV color.
 * The point is mapped relative to the rect's center and scaled to fit a circular hue-saturation space.
 * The point determines hue and saturation; `val` sets the value (brightness). */
extern t_color_hsv ft_hsv_from_rect(t_v2 p, t_v4 rect, F32 val);

/* Converts a RGB color to a HSV color. */
extern t_color_hsv ft_rgb_to_hsv(t_color col);
/* Converts a HSV color to a RGB color. */
extern t_color ft_hsv_to_rgb(t_color_hsv col);

/* Alpha-blending between 2 colors. Assumes under's alpha to be 255. */
extern t_color ft_alpha_blend(t_color under, t_color over);

/* Full alpha-blending between 2 colors, computing the new alpha value. */
extern t_color ft_alpha_blend2(t_color under, t_color over);

/*
Initializes an image.
### On error
Returns FALSE and sets ft_errno.
### ft_errno
- FT_EOMEM if out of memory.
*/
extern bool ft_init_image(t_image *img, t_iv2 size);

/* Destroys an image. */
extern void ft_destroy_image(t_image *img);

/* Shortcut for `ivec4(0, 0, img.size.x, img.size.y)`. */
inline t_iv4 ft_image_rect(t_image *img) { return ivec4(0, 0, img->size.x, img->size.y); };

/* Returns the pixel address at coordinates `x/y` */
#define ft_get_pixel(img, _x, _y) ((img)->pixels + ((_y) * ((img)->size.x) + (_x)))


/*
Copies the region `src_rect` in `src` to `dst` at position `dst_pos`.
Will not draw outside of `img`.
#### Draw function: see `FT_DRAW_FUNCTIONS_DOCUMENTATION`.
- `FT_DRAW_FLAG_CLIP`: Expects a `t_iv4` argument. Ignore (don't draw) any pixels outside of the specified rect.
- `FT_DRAW_FLAG_NO_TRANSPARENCY`: Ignores color transparency.
- `FT_DRAW_FLAG_COLOR`: Overlays a color while copying.
*/
extern void ft_copy_image(t_image *dst, t_iv2 dst_pos, t_image *src, t_iv4 src_rect, U8 flags, ...);

/*
Stretches the region `src_rect` in `src` to `dst_rect` in `dst`.
Will not draw outside of `img`.
#### Draw function: see `FT_DRAW_FUNCTIONS_DOCUMENTATION`.
- `FT_DRAW_FLAG_CLIP`: Expects a `t_iv4` argument. Ignore (don't draw) any pixels outside of the specified rect.
- `FT_DRAW_FLAG_NO_TRANSPARENCY`: Ignores color transparency.
- `FT_DRAW_FLAG_COLOR`: Overlays a color while copying.
*/
extern void ft_stretch_image(t_image *dst, t_iv4 dst_rect, t_image *src, t_iv4 src_rect, U8 flags, ...);

/*
Draws a line between `p1` and `p2`, inclusive.
Will not draw outside of `img`.
#### Draw function: see `FT_DRAW_FUNCTIONS_DOCUMENTATION`.
- `FT_DRAW_FLAG_CLIP`: Expects a `t_iv4` argument. Ignore (don't draw) any pixels outside of the specified rect.
- `FT_DRAW_FLAG_NO_TRANSPARENCY`: Ignores color transparency.
*/
extern void ft_draw_line(t_image *img, t_iv2 p1, t_iv2 p2, t_color col, U8 flags, ...);

/*
Draws a horizontal line between `p1.x` and `x2`, inclusive.
Will not draw outside of `img`.
#### Draw function: see `FT_DRAW_FUNCTIONS_DOCUMENTATION`.
- `FT_DRAW_FLAG_CLIP`: Expects a `t_iv4` argument. Ignore (don't draw) any pixels outside of the specified rect.
- `FT_DRAW_FLAG_NO_TRANSPARENCY`: Ignores color transparency.
*/
extern void ft_draw_line_horizontal(t_image *img, t_iv2 p1, S32 x2, t_color col, U8 flags, ...);

/*
Draws a vertical line between `p1.y` and `y2`, inclusive.
Will not draw outside of `img`.
#### Draw function: see `FT_DRAW_FUNCTIONS_DOCUMENTATION`.
- `FT_DRAW_FLAG_CLIP`: Expects a `t_iv4` argument. Ignore (don't draw) any pixels outside of the specified rect.
- `FT_DRAW_FLAG_NO_TRANSPARENCY`: Ignores color transparency.
*/
extern void ft_draw_line_vertical(t_image *img, t_iv2 p1, S32 y2, t_color col, U8 flags, ...);

/*
Draws a rectangle.
Will not draw outside of `img`.
#### Draw function: see `FT_DRAW_FUNCTIONS_DOCUMENTATION`.
- `FT_DRAW_FLAG_CLIP`: Expects a `t_iv4` argument. Ignore (don't draw) any pixels outside of the specified rect.
- `FT_DRAW_FLAG_NO_TRANSPARENCY`: Ignores color transparency.
*/
extern void ft_draw_rect(t_image *img, t_iv4 rect, t_color col, U8 flags, ...);

/*
Draws a filled rectangle.
Will not draw outside of `img`.
#### Draw function: see `FT_DRAW_FUNCTIONS_DOCUMENTATION`.
- `FT_DRAW_FLAG_CLIP`: Expects a `t_iv4` argument. Ignore (don't draw) any pixels outside of the specified rect.
- `FT_DRAW_FLAG_NO_TRANSPARENCY`: Ignores color transparency.
*/
extern void ft_fill_rect(t_image *img, t_iv4 rect, t_color col, U8 flags, ...);

extern void ft_draw_bezier(t_image *img, t_color col, t_v2 p1, t_v2 p2, t_v2 p3, S32 res, U8 flags, ...);

extern void ft_draw_circle_bound(t_image *img, t_iv2 pos, S32 radius, t_color col, t_iv4 bound);
extern void ft_draw_circle(t_image *img, t_iv2 pos, S32 radius, t_color col);
extern void ft_draw_circle_bound2(t_image *img, t_iv2 pos, S32 radius, t_color col, t_iv4 bound);
extern void ft_draw_circle2(t_image *img, t_iv2 pos, S32 radius, t_color col);

/*
Draws a filled disc.
Will not draw outside of `img`.
#### Draw function: see `FT_DRAW_FUNCTIONS_DOCUMENTATION`.
- `FT_DRAW_FLAG_CLIP`: Expects a `t_iv4` argument. Ignore (don't draw) any pixels outside of the specified rect.
- `FT_DRAW_FLAG_NO_TRANSPARENCY`: Ignores color transparency.
*/
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

/*
Initializes a bitmap with the specified parameters.
`char_size`: the size of each characters, in pixels.
`line_chars_count`: the number of characters in on line in the specified image.
`sep_size`: the number of pixels separating each characters.
*/
extern void ft_init_bitmap(t_bitmap *bitmap, t_image *img, t_iv2 char_size, U32 line_chars_count, t_iv2 sep_size);

extern t_iv4 ft_bitmap_rect_char_lines(t_bitmap *bitmap, t_iv2 pos, U32 line_width, U32 lines_cnt);

/*
Renders the text `str` using `bitmap` with the specified parameters.
This function accepts every `FT_DRAW_FLAG_BITMAP_*` flags.
Will not draw outside of `img`, nor outside of `rect`.
#### Draw function: see `FT_DRAW_FUNCTIONS_DOCUMENTATION`.
- `FT_DRAW_FLAG_CLIP`: Expects a `t_iv4` argument. Ignore (don't draw) any pixels outside of the specified rect.
- `FT_DRAW_FLAG_COLOR`: Overlays a color while copying.
- `FT_DRAW_FLAG_BITMAP_WRAP`: Wraps the text inside the specified rect.
*/
extern void ft_draw_bitmap_text(t_image *out, t_iv4 rect, t_bitmap *bitmap, string str, F32 scale,
								t_iv2 kerning, U8 flags, ...);

#endif