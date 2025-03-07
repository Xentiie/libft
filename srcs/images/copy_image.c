/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 16:15:23 by reclaire          #+#    #+#             */
/*   Updated: 2025/03/07 09:57:55 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_int.h"

#define _FT_IMAGES_EXTENDED_DECLARATIONS

#include "libft/images.h"
#include "libft/maths.h"

static void copy_image_clip(t_image *dst, t_iv2 *dstpos, t_image *src, t_iv4 *srcrect)
{
	srcrect->x = ft_imax(srcrect->x, 0);
	srcrect->y = ft_imax(srcrect->y, 0);
	srcrect->z = ft_imin(srcrect->z, src->size.x);
	srcrect->w = ft_imin(srcrect->w, src->size.y);

	dstpos->x = ft_imax(dstpos->x, 0);
	dstpos->y = ft_imax(dstpos->y, 0);

	srcrect->z = ft_imin(srcrect->z, srcrect->x + dst->size.x - dstpos->x);
	srcrect->w = ft_imin(srcrect->w, srcrect->y + dst->size.y - dstpos->y);
}

void ft_copy_image(t_image *dst, t_iv2 dstpos, t_image *src, t_iv4 srcrect)
{
	S32 dst_y;
	S32 src_y;
	U64 len;

	if (srcrect.x > srcrect.z || srcrect.y > srcrect.w)
		return;
	copy_image_clip(dst, &dstpos, src, &srcrect);

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

EXTENDED_ALIAS("ft_copy_image2", 0)
static void copy_image2(t_image *dst, t_iv2 dstpos, t_image *src, t_iv4 srcrect)
{
	S32 dst_y;
	S32 src_y;

	t_color *dstaddr;
	t_color *srcaddr;
	U64 len;

	if (srcrect.x > srcrect.z || srcrect.y > srcrect.w)
		return;
	copy_image_clip(dst, &dstpos, src, &srcrect);

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

EXTENDED_ALIAS("ft_copy_image2", 1, "sse2", "ssse3", "sse4_1")
static void copy_image2_xmm(t_image *dst, t_iv2 dstpos, t_image *src, t_iv4 srcrect)
{
	const S32 step = 2; /* 2 pixels processed simultaneously */
	S32 dst_y;
	S32 src_y;
	t_color *dstaddr;
	t_color *srcaddr;
	S32 len;
	S32 len_rem;

	if (srcrect.x > srcrect.z || srcrect.y > srcrect.w)
		return;
	copy_image_clip(dst, &dstpos, src, &srcrect);

	dst_y = dstpos.y;
	src_y = srcrect.y;
	len = (srcrect.z - srcrect.x);

	// clang-format off
	volatile const U8 mask[] = {
		6,  1, 6,  1, 6,  1, 6,  1,
		14, 1, 14, 1, 14, 1, 14, 1,
	};
	// clang-format on

	while (src_y < srcrect.w)
	{
		dstaddr = ft_get_pixel(dst, dstpos.x, dst_y);
		srcaddr = ft_get_pixel(src, srcrect.x, src_y);
		for (U64 i = 0; i < len; i += step)
		{
			asm(
				"pmovzxbw     xmm0, [%0]\n"
				"pmovzxbw     xmm1, [%1]\n"
				"movdqu       xmm2, xmm1\n"
				"pshufb       xmm2, [%2]\n"

				"pmullw       xmm1, xmm2\n" // alpha * over

				"pcmpeqw      xmm3, xmm3\n" /* 'pcmpeqw xmm%, xmm%' generates 0xfffff... */
				"psrlw        xmm3, 8\n"	/* shift right by 8 to keep only 0xff in each word */
				"psubw        xmm3, xmm2\n" // (255 - alpha)
				"pmullw       xmm0, xmm3\n" // (255 - alpha) * under

				"paddw        xmm0, xmm1\n" // (alpha * over) + ((255 - alpha) * under)
				"psrlw        xmm0, 8\n"	// (alpha * over) + ((255 - alpha) * under) / 255 (256 en vrai lol
											// mais bon nsm)

				"packuswb     xmm0, xmm0\n" // Pack over to 0RGB
				"movdqu       [%0], xmm0\n"
				:
				: "r"(dstaddr + i), "r"(srcaddr + i), "r"(mask)
				: "xmm0", "xmm1", "xmm2", "xmm3");
		}
		src_y++;
		dst_y++;
	}
}

/* copies alpha blended pixels (4 pixels processed simultaneously) */
EXTENDED_ALIAS("ft_copy_image2", 2, "avx2")
void copy_image2_ymm(t_image *dst, t_iv2 dstpos, t_image *src, t_iv4 srcrect)
{
	S32 dst_y;
	S32 src_y;
	t_color *dstaddr;
	t_color *srcaddr;
	U64 len;

	if (srcrect.x > srcrect.z || srcrect.y > srcrect.w)
		return;
	copy_image_clip(dst, &dstpos, src, &srcrect);

	dst_y = dstpos.y;
	src_y = srcrect.y;
	len = (srcrect.z - srcrect.x);

	// clang-format off
	volatile U8 const mask[] = {
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
			asm(
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

/* Auto-generated by build-aux/extended_aliases.py */
#include "libft/sys/cpuid.h"
#if defined(DEBUG)
#include "libft/io.h"
#endif

#if defined(DEBUG)
static void *__resolved_ft_copy_image2 = NULL;
#endif
static void (*resolve_ft_copy_image2(void))(t_image *dst, t_iv2 dstpos, t_image *src, t_iv4 srcrect)
{
#if !defined(DEBUG)
	void *__resolved_ft_copy_image2 = NULL;
#endif
	struct s_cpuid_flags *flags;

	flags = ft_cpuid_get_cached_flags();
	if (flags->avx2)
		__resolved_ft_copy_image2 = copy_image2_ymm;
	else if (flags->sse2 && flags->ssse3 && flags->sse4_1)
		__resolved_ft_copy_image2 = copy_image2_xmm;
	else
		__resolved_ft_copy_image2 = copy_image2;
	return __resolved_ft_copy_image2;
}

void ft_copy_image2(t_image *dst, t_iv2 dstpos, t_image *src, t_iv4 srcrect)
	__attribute__((ifunc("resolve_ft_copy_image2")));

#if defined(DEBUG)
__attribute__((constructor)) static void __debug_ifunc()
{
	ft_printf("ft_copy_image2:");
	if (__resolved_ft_copy_image2 == copy_image2_ymm)
		ft_printf("copy_image2_ymm\n");
	else if (__resolved_ft_copy_image2 == copy_image2_xmm)
		ft_printf("copy_image2_xmm\n");
	else
		ft_printf("copy_image2\n");
}
#endif
