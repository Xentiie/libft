/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stretch_image.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:49:59 by reclaire          #+#    #+#             */
/*   Updated: 2025/03/03 23:03:41 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/images.h"
#include "libft/maths.h"

#include "libft_int.h"

#include <stdlib.h>

void ft_stretch_image(t_image *dst, t_iv4 dst_rect, t_image *src, t_iv4 src_rect)
{
	t_iv4 dst_clipped;
	t_v2 dstsize;
	t_v2 srcsize;

	S32 *x_vals;
	F32 xfact;
	F32 yfact;

	t_color *dst_addr;
	t_color *src_addr;

	{	  /* clip rectangles */
		{ /* clip dst rect */
			dst_clipped = dst_rect;
			dst_clipped.x = ft_clamp(0, dst->size.x, dst_rect.x);
			dst_clipped.y = ft_clamp(0, dst->size.y, dst_rect.y);
			dst_clipped.z = ft_clamp(0, dst->size.x, dst_rect.z);
			dst_clipped.w = ft_clamp(0, dst->size.y, dst_rect.w);
		}

#if 0
		{ /* clip src rect */
			src_clipped = src_rect;
			src_clipped.x = ft_clamp(0, src->size.x, src_rect.x);
			src_clipped.y = ft_clamp(0, src->size.y, src_rect.y);
			src_clipped.z = ft_clamp(0, src->size.x, src_rect.z);
			src_clipped.w = ft_clamp(0, src->size.y, src_rect.w);

			src_clipped.x = ft_clamp(0, dst->size.x, src_rect.x);
			src_clipped.y = ft_clamp(0, dst->size.y, src_rect.y);
			src_clipped.z = ft_clamp(0, dst->size.x, src_rect.z);
			src_clipped.w = ft_clamp(0, dst->size.y, src_rect.w);
		}
#endif
	}

	dstsize.x = dst_rect.z - dst_rect.x;
	dstsize.y = dst_rect.w - dst_rect.y;

	srcsize.x = src_rect.z - src_rect.x;
	srcsize.y = src_rect.w - src_rect.y;

	xfact = 1.0f / (F32)dstsize.x * srcsize.x;
	yfact = 1.0f / (F32)dstsize.y * srcsize.y;

	x_vals = ft_alloca(sizeof(S32) * (dst_clipped.z - dst_clipped.x));
	for (S32 x = dst_rect.x; x < dst_rect.z; x++)
		x_vals[x - dst_rect.x] = (S32)(src_rect.x + (x - dst_rect.x) * xfact);

	for (S32 dsty = dst_clipped.y; dsty < dst_clipped.w; dsty++)
	{
		for (S32 dstx = dst_clipped.x; dstx < dst_clipped.z; dstx++)
		{
			dst_addr = ft_get_pixel(dst, dstx, dsty);
			src_addr = ft_get_pixel(src, x_vals[dstx - dst_rect.x],
									((S32)(src_rect.y + (dsty - dst_rect.y) * yfact)));
			*dst_addr = *src_addr;
		}
	}

	ft_afree(x_vals);
}

void ft_stretch_image2(t_image *dst, t_iv4 dst_rect, t_image *src, t_iv4 src_rect)
{
	t_iv4 dst_clipped;
	t_iv4 src_clipped;
	t_v2 dstsize;
	t_v2 srcsize;

	S32 *x_vals;
	F32 xfact;
	F32 yfact;

	t_color *dst_addr;
	t_color *src_addr;

	{	  /* clip rectangles */
		{ /* clip dst rect */
			dst_clipped = dst_rect;
			dst_clipped.x = ft_clamp(0, dst->size.x, dst_rect.x);
			dst_clipped.y = ft_clamp(0, dst->size.y, dst_rect.y);
			dst_clipped.z = ft_clamp(0, dst->size.x, dst_rect.z);
			dst_clipped.w = ft_clamp(0, dst->size.y, dst_rect.w);
		}

		{ /* clip src rect */
			src_clipped = src_rect;
			src_clipped.x = ft_clamp(0, src->size.x, src_rect.x);
			src_clipped.y = ft_clamp(0, src->size.y, src_rect.y);
			src_clipped.z = ft_clamp(0, src->size.x, src_rect.z);
			src_clipped.w = ft_clamp(0, src->size.y, src_rect.w);

			src_clipped.x = ft_clamp(0, dst->size.x, src_rect.x);
			src_clipped.y = ft_clamp(0, dst->size.y, src_rect.y);
			src_clipped.z = ft_clamp(0, dst->size.x, src_rect.z);
			src_clipped.w = ft_clamp(0, dst->size.y, src_rect.w);
		}
	}

	dstsize.x = dst_rect.z - dst_rect.x;
	dstsize.y = dst_rect.w - dst_rect.y;

	srcsize.x = src_rect.z - src_rect.x;
	srcsize.y = src_rect.w - src_rect.y;

	xfact = 1.0f / (F32)dstsize.x * srcsize.x;
	yfact = 1.0f / (F32)dstsize.y * srcsize.y;

	x_vals = ft_alloca(sizeof(S32) * (dst_clipped.z - dst_clipped.x));
	for (S32 x = dst_rect.x; x < dst_rect.z; x++)
		x_vals[x - dst_rect.x] = (S32)(src_rect.x + (x - dst_rect.x) * xfact);

	for (S32 dsty = dst_clipped.y; dsty < dst_clipped.w; dsty++)
	{
		for (S32 dstx = dst_clipped.x; dstx < dst_clipped.z; dstx++)
		{
			dst_addr = ft_get_pixel(dst, dstx, dsty);
			src_addr = ft_get_pixel(src, x_vals[dstx - dst_rect.x],
									((S32)(src_rect.y + (dsty - dst_rect.y) * yfact)));
			*dst_addr = ft_alpha_blend(*dst_addr, *src_addr);
		}
	}

	ft_afree(x_vals);
}

#if 0
void ft_stretch_img(t_image *dst, t_image *src)
{
	S32 *x_vals = ft_alloca(sizeof(S32) * dst->size.x);
	for (S32 x = 0; x < dst->size.x; x++)
		x_vals[x] = (S32)((x / (F32)dst->size.x) * src->size.x);

	for (S32 y = 0; y < dst->size.y; y++)
	{
		for (S32 x = 0; x < dst->size.x; x++)
			*ft_get_pixel(dst, x, y) = *ft_get_pixel(src, x_vals[x], ((S32)(((y) / (F32)dst->size.y) * src->size.y)));
	}

	ft_afree(x_vals);
}

void ft_stretch_img2(t_image *dst, t_iv4 dst_rect, t_image *src, t_iv4 src_rect, t_color col)
{
	dst_rect.x = ft_clamp(0, dst->size.x, dst_rect.x);
	dst_rect.y = ft_clamp(0, dst->size.y, dst_rect.y);
	dst_rect.z = ft_clamp(0, dst->size.x, dst_rect.z);
	dst_rect.w = ft_clamp(0, dst->size.y, dst_rect.w);

	src_rect.x = ft_clamp(0, dst->size.x, src_rect.x);
	src_rect.y = ft_clamp(0, dst->size.y, src_rect.y);
	src_rect.z = ft_clamp(0, dst->size.x, src_rect.z);
	src_rect.w = ft_clamp(0, dst->size.y, src_rect.w);

	S32 dst_w = dst_rect.z - dst_rect.x;
	S32 dst_h = dst_rect.w - dst_rect.y;

	S32 src_w = src_rect.z - src_rect.x;
	S32 src_h = src_rect.w - src_rect.y;

	S32 *x_vals = ft_alloca(sizeof(S32) * dst_w);
	for (S32 x = dst_rect.x; x < dst_rect.z; x++)
		x_vals[x - dst_rect.x] = (S32)(src_rect.x + ((x - dst_rect.x) / (F32)dst_w) * src_w); // TODO: ici on a (x / y * z) ou y et z sont
																							  // constant. Peut etre simplifié

	for (S32 y = dst_rect.y; y < dst_rect.w; y++)
	{
		for (S32 x = dst_rect.x; x < dst_rect.z; x++)
		{
			t_color *dst_addr = ft_get_pixel(dst, x, y);
			t_color *src_addr = ft_get_pixel(src, x_vals[x - dst_rect.x],
											 ((S32)(src_rect.y + ((y - dst_rect.y) / (F32)dst_h) * src_h)));
			t_color src_col = *src_addr;
			t_color dst_col = *dst_addr;

			src_col.r *= (col.r / 255.0f);
			src_col.g *= (col.g / 255.0f);
			src_col.b *= (col.b / 255.0f);
			src_col.a *= (col.a / 255.0f);

			//*dst_addr = ft_alpha_blend(dst_col, src_col);
		}
	}

	ft_afree(x_vals);
}
#endif