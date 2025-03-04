/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 16:15:23 by reclaire          #+#    #+#             */
/*   Updated: 2025/02/18 00:36:02 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_int.h"

#define _FT_IMAGES_EXTENDED_DECLARATIONS

#include "libft/images.h"
#include "libft/maths.h"

void ft_copy_image(t_image *dst, t_iv2 dstpos, t_image *src, t_iv4 srcrect)
{
	S32 dst_y;
	S32 src_y;
	U64 len;

	srcrect.x = ft_imax(srcrect.x, 0);
	srcrect.y = ft_imax(srcrect.y, 0);
	srcrect.z = ft_imin(srcrect.z, src->size.x);
	srcrect.w = ft_imin(srcrect.w, src->size.y);

	dstpos.x = ft_imax(dstpos.x, 0);
	dstpos.y = ft_imax(dstpos.y, 0);

	srcrect.z = ft_imin(srcrect.z, srcrect.x + dst->size.x - dstpos.x);
	srcrect.w = ft_imin(srcrect.w, srcrect.y + dst->size.y - dstpos.y);

	dst_y = dstpos.y;
	src_y = srcrect.y;
	len = sizeof(t_color) * (srcrect.z - srcrect.x);
	while (src_y < srcrect.w)
	{
		ft_memcpy(
			ft_get_pixel(dst, dstpos.x, dst_y),
			ft_get_pixel(src, srcrect.x, src_y),
			len);
		src_y++;
		dst_y++;
	}
}

typedef t_color (*f_copy_image2)(t_color, t_color);
static void (*resolve_copy_image2(void))(t_image *dst, t_iv2 dstpos, t_image *src, t_iv4 srcrect)
{
	return ft_copy_image_abl;
}

void ft_copy_image2(t_image *dst, t_iv2 dstpos, t_image *src, t_iv4 srcrect)
	__attribute__((ifunc("resolve_copy_image2")));

void ft_copy_image_abl(t_image *dst, t_iv2 dstpos, t_image *src, t_iv4 srcrect)
{
	S32 dst_y;
	S32 src_y;

	t_color *dstaddr;
	t_color *srcaddr;
	U64 len;

	if (srcrect.x > srcrect.z || srcrect.y > srcrect.w)
		return;

	srcrect.x = ft_imax(srcrect.x, 0);
	srcrect.y = ft_imax(srcrect.y, 0);
	srcrect.z = ft_imin(srcrect.z, src->size.x);
	srcrect.w = ft_imin(srcrect.w, src->size.y);

	dstpos.x = ft_imax(dstpos.x, 0);
	dstpos.y = ft_imax(dstpos.y, 0);

	srcrect.z = ft_imin(srcrect.z, srcrect.x + dst->size.x - dstpos.x);
	srcrect.w = ft_imin(srcrect.w, srcrect.y + dst->size.y - dstpos.y);

	dst_y = dstpos.y;
	src_y = srcrect.y;
	len = (srcrect.z - srcrect.x);
	while (src_y < srcrect.w)
	{
		dstaddr = ft_get_pixel(dst, dstpos.x, dst_y);
		srcaddr = ft_get_pixel(src, srcrect.x, src_y);
		for (U64 i = 0; i < len; i++)
			dstaddr[i] = ft_alpha_blend(dstaddr[i], srcaddr[i]);
		src_y++;
		dst_y++;
	}
}

/* copies alpha blended pixels (2 pixels processed simultaneously) */
void ft_copy_image_abl_avx(t_image *dst, t_iv2 dstpos, t_image *src, t_iv4 srcrect)
{
	S32 dst_y;
	S32 src_y;
	t_color *dstaddr;
	t_color *srcaddr;
	U64 len;

	srcrect.x = ft_imax(srcrect.x, 0);
	srcrect.y = ft_imax(srcrect.y, 0);
	srcrect.z = ft_imin(srcrect.z, src->size.x);
	srcrect.w = ft_imin(srcrect.w, src->size.y);

	dstpos.x = ft_imax(dstpos.x, 0);
	dstpos.y = ft_imax(dstpos.y, 0);

	srcrect.z = ft_imin(srcrect.z, srcrect.x + dst->size.x - dstpos.x);
	srcrect.w = ft_imin(srcrect.w, srcrect.y + dst->size.y - dstpos.y);

	dst_y = dstpos.y;
	src_y = srcrect.y;
	len = (srcrect.z - srcrect.x);

	// clang-format off
	volatile U8 mask[] = {
		6,  1, 6,  1, 6,  1, 6,  1,
		14, 1, 14, 1, 14, 1, 14, 1,
	};
	// clang-format on

	while (src_y < srcrect.w)
	{
		dstaddr = ft_get_pixel(dst, dstpos.x, dst_y);
		srcaddr = ft_get_pixel(src, srcrect.x, src_y);
		for (U64 i = 0; i < len; i += 2)
		{
			__asm__(
				"vpmovzxbw    xmm0, [rax]\n"
				"vpmovzxbw    xmm1, [rbx]\n"
				"vpshufb      xmm2, xmm1, [rcx]\n"

				"vpmullw      xmm1, xmm1, xmm2\n" // alpha * over

				"pcmpeqw      xmm3,xmm3\n"		  /* 'pcmpeqw xmm%, xmm%' generates 0xfffff... */
				"psrlw        xmm3,8\n"			  /* shift right by 8 to keep only 0xff in each word */
				"vpsubw       xmm2, xmm3, xmm2\n" // (255 - alpha)
				"vpmullw      xmm0, xmm0, xmm2\n" // (255 - alpha) * under

				"vpaddw       xmm0, xmm0, xmm1\n" // (alpha * over) + ((255 - alpha) * under)
				"psrlw        xmm0, 8\n"		  // (alpha * over) + ((255 - alpha) * under) / 255 (256 en vrai lol
												  // mais bon nsm)

				"packuswb     xmm0, xmm0\n" // Pack over to 0RGB
				"vmovdqu      [rax], xmm0\n"
				:
				: "a"(dstaddr + i), "b"(srcaddr + i), "c"(mask)
				: "xmm0", "xmm1", "xmm2", "xmm3");
		}
		src_y++;
		dst_y++;
	}
}

/* copies alpha blended pixels (4 pixels processed simultaneously) */
void ft_copy_image_abl_avx2(t_image *dst, t_iv2 dstpos, t_image *src, t_iv4 srcrect)
{
	S32 dst_y;
	S32 src_y;
	t_color *dstaddr;
	t_color *srcaddr;
	U64 len;

	srcrect.x = ft_imax(srcrect.x, 0);
	srcrect.y = ft_imax(srcrect.y, 0);
	srcrect.z = ft_imin(srcrect.z, src->size.x);
	srcrect.w = ft_imin(srcrect.w, src->size.y);

	dstpos.x = ft_imax(dstpos.x, 0);
	dstpos.y = ft_imax(dstpos.y, 0);

	srcrect.z = ft_imin(srcrect.z, srcrect.x + dst->size.x - dstpos.x);
	srcrect.w = ft_imin(srcrect.w, srcrect.y + dst->size.y - dstpos.y);

	dst_y = dstpos.y;
	src_y = srcrect.y;
	len = (srcrect.z - srcrect.x);

	// clang-format off
	volatile U8 mask[] = {
		6,  1, 6,  1, 6,  1, 6,  1,
		14, 1, 14, 1, 14, 1, 14, 1,
		6,  1, 6,  1, 6,  1, 6,  1,
		14, 1, 14, 1, 14, 1, 14, 1,
	};
	// clang-format on

	while (src_y < srcrect.w)
	{
		dstaddr = ft_get_pixel(dst, dstpos.x, dst_y);
		srcaddr = ft_get_pixel(src, srcrect.x, src_y);
		for (U64 i = 0; i < len; i += 4)
		{
			__asm__(
				"vpmovzxbw    ymm0, [rax]\n"
				"vpmovzxbw    ymm1, [rbx]\n"
				"vpshufb      ymm2, ymm1, [rcx]\n"

				"vpmullw      ymm1, ymm1, ymm2\n" // alpha * over

				"vpcmpeqw     ymm3, ymm3,ymm3\n"  /* 'pcmpeqw ymm%, ymm%' generates 0xfffff... */
				"vpsrlw       ymm3, ymm3,8\n"	  /* shift right by 8 to keep only 0xff in each word */
				"vpsubw       ymm2, ymm3, ymm2\n" // (255 - alpha)
				"vpmullw      ymm0, ymm0, ymm2\n" // (255 - alpha) * under

				"vpaddw       ymm0, ymm0, ymm1\n" // (alpha * over) + ((255 - alpha) * under)
				"vpsrlw       ymm0, ymm0, 8\n"	  // (alpha * over) + ((255 - alpha) * under) / 255 (256 en vrai lol
												  // mais bon nsm)

				"vpackuswb    ymm0, ymm0, ymm0\n" // Pack over to 0RGB
				"vmovdqu      [rax], ymm0\n"
				:
				: "a"(dstaddr + i), "b"(srcaddr + i), "c"(mask)
				: "ymm0", "ymm1", "ymm2", "ymm3");
		}
		src_y++;
		dst_y++;
	}
}
