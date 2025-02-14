/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 23:26:42 by reclaire          #+#    #+#             */
/*   Updated: 2025/02/13 14:49:34 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(LIBFT_IMAGES_H)
#define LIBFT_IMAGES_H

#include "libft.h"
#include "libft/lists.h"
#include "libft/macros.h"

typedef union u_color
{
	U32 v;
	struct
	{
		/*
		U8 b;
		U8 r;
		U8 g;
		U8 a;
*/
		U8 r;
		U8 g;
		U8 b;
		U8 a;
	};
} t_color;

typedef struct s_image
{
	union
	{
		U8		*data;
		t_color *pixels;
	};
	t_iv2 size;
} t_image;

struct s_png_metadata
{
};

typedef struct s_png_img
{
	U32		width;
	U32		height;
	U8		bit_depth;
	U8		bpp;
	U8		color_type;
	U8		compression_method;
	U8		filter_method;
	U8		interlace_method;

	U8		sample_depth;

	/* Pixels data */
	U8	   *data;

	/*
	Each element of the list contains 2 strings, one behind another.
	First one is the title, second is the text.
	*/
	t_list *text_data;
} t_png_img;

#define __ft_color5(_r, _g, _b, _a) ((t_color) {.r = (_r), .g = (_g), .b = (_b), .a = (_a)})
#define __ft_color4(_r, _g, _b, ...)                                                               \
	VALUE_IFNOT(__VA_OPT__(1), (t_color) {.r = (_r), .g = (_g), .b = (_b), .a = 255})              \
	__VA_OPT__(__ft_color5(_r, _g, _b, __VA_ARGS__))
#define __ft_color3(_r, _g, ...)                                                                   \
	VALUE_IFNOT(__VA_OPT__(1), (t_color) {.r = (_r), .g = (_g), .b = 0, .a = 255})                 \
	__VA_OPT__(__ft_color4(_r, _g, __VA_ARGS__))
#define __ft_color2(_r, ...)                                                                       \
	VALUE_IFNOT(__VA_OPT__(1), (t_color) {.r = (_r), .g = (_r), .b = (_r), .a = 255})              \
	__VA_OPT__(__ft_color3(_r, __VA_ARGS__))

/* If only `red` specified: returns `(r, r, r, 255)`
 * If `red + green` specified: returns `(r, g, 0, 255)`
 * If `red + green + blue` specified: returns `(r, g, b, 255)`
 * If `red + green + blue + alpha` specified: returns `(r, g, b, a)` */
#define ft_color(...) __ft_color2(__VA_ARGS__)

#define ft_get_pixel(img, _x, _y) ((img)->pixels + ((_y) * ((img)->size.x) + (_x)))

bool ft_init_image(t_image *img, t_iv2 size);
void ft_destroy_image(t_image *img);

t_png_img *ft_load_png(filedesc f, bool verbose);
void ft_free_png_img(t_png_img *img);

#endif