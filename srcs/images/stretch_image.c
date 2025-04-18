/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stretch_image.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:49:59 by reclaire          #+#    #+#             */
/*   Updated: 2025/04/15 02:30:28 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_int.h"

#include "libft/images.h"

#include "libft/bits/alloca.h"

void ft_stretch_image(t_image *dst, t_iv4 dst_rect, t_image *src, t_iv4 src_rect)
{
	t_iv4	 dst_clipped;
	t_v2	 dstsize;
	t_v2	 srcsize;

	S32		*x_vals;
	F32		 xfact;
	F32		 yfact;

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

	xfact = 1.0f / (F32) dstsize.x * srcsize.x;
	yfact = 1.0f / (F32) dstsize.y * srcsize.y;

	x_vals = ft_alloca(sizeof(S32) * (dst_clipped.z - dst_clipped.x));
	for (S32 x = dst_rect.x; x < dst_rect.z; x++)
		x_vals[x - dst_rect.x] = (S32) (src_rect.x + (x - dst_rect.x) * xfact);

	for (S32 dsty = dst_clipped.y; dsty < dst_clipped.w; dsty++)
	{
		for (S32 dstx = dst_clipped.x; dstx < dst_clipped.z; dstx++)
		{
			dst_addr = ft_get_pixel(dst, dstx, dsty);
			src_addr = ft_get_pixel(src, x_vals[dstx - dst_rect.x],
									((S32) (src_rect.y + (dsty - dst_rect.y) * yfact)));
			*dst_addr = *src_addr;
		}
	}

	ft_afree(x_vals);
}

void ft_stretch_image2(t_image *dst, t_iv4 dst_rect, t_image *src, t_iv4 src_rect)
{
	t_iv4 dst_clipped;
	MAYBE_UNUSED
	t_iv4	 src_clipped;
	t_v2	 dstsize;
	t_v2	 srcsize;

	S32		*x_vals;
	F32		 xfact;
	F32		 yfact;

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

	xfact = 1.0f / (F32) dstsize.x * srcsize.x;
	yfact = 1.0f / (F32) dstsize.y * srcsize.y;

	x_vals = ft_alloca(sizeof(S32) * (dst_clipped.z - dst_clipped.x));
	for (S32 x = dst_rect.x; x < dst_rect.z; x++)
		x_vals[x - dst_rect.x] = (S32) (src_rect.x + (x - dst_rect.x) * xfact);

	for (S32 dsty = dst_clipped.y; dsty < dst_clipped.w; dsty++)
	{
		for (S32 dstx = dst_clipped.x; dstx < dst_clipped.z; dstx++)
		{
			dst_addr = ft_get_pixel(dst, dstx, dsty);
			src_addr = ft_get_pixel(src, x_vals[dstx - dst_rect.x],
									((S32) (src_rect.y + (dsty - dst_rect.y) * yfact)));
			*dst_addr = ft_alpha_blend2(*dst_addr, *src_addr);
		}
	}

	ft_afree(x_vals);
}

void ft_stretch_image3(t_image *dst, t_iv4 dst_rect, t_image *src, t_iv4 src_rect, t_color col)
{
	t_iv4 dst_clipped;
	MAYBE_UNUSED
	t_iv4	 src_clipped;
	t_v2	 dstsize;
	t_v2	 srcsize;

	S32		*x_vals;
	F32		 xfact;
	F32		 yfact;

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

	xfact = 1.0f / (F32) dstsize.x * srcsize.x;
	yfact = 1.0f / (F32) dstsize.y * srcsize.y;

	x_vals = ft_alloca(sizeof(S32) * (dst_clipped.z - dst_clipped.x));
	for (S32 x = dst_rect.x; x < dst_rect.z; x++)
		x_vals[x - dst_rect.x] = (S32) (src_rect.x + (x - dst_rect.x) * xfact);

	for (S32 dsty = dst_clipped.y; dsty < dst_clipped.w; dsty++)
	{
		for (S32 dstx = dst_clipped.x; dstx < dst_clipped.z; dstx++)
		{
			dst_addr = ft_get_pixel(dst, dstx, dsty);
			src_addr = ft_get_pixel(src, x_vals[dstx - dst_rect.x],
									((S32) (src_rect.y + (dsty - dst_rect.y) * yfact)));

			t_color tmp = ft_color(src_addr->r * col.r / 255, src_addr->g * col.g / 255, src_addr->b * col.b / 255, src_addr->a * col.a / 255);
			*dst_addr = ft_alpha_blend2(*dst_addr, tmp);
		}
	}

	ft_afree(x_vals);
}
