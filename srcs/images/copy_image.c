/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 16:15:23 by reclaire          #+#    #+#             */
/*   Updated: 2025/06/10 09:52:38 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_int.h"

#include "libft/images.h"

#include "libft/bits/extended_aliases.h"

#include <stdarg.h>

void ft_copy_image(t_image *dst, t_iv2 dst_pos, t_image *src, t_iv4 src_rect, U8 flags, ...)
{
	S32 dst_y;
	S32 src_y;
	U64 len;

	va_list lst;
	t_iv4 clip_rect;
	t_color col;

	t_iv4 dst_rect;
	t_iv4 dst_rect_clipped;

	clip_rect = ft_image_rect(dst);

	{ /* Flags */
		va_start(lst, flags);
		if (flags & FT_DRAW_FLAG_CLIP)
			clip_rect = ft_clip_rect_rect(va_arg(lst, t_iv4), clip_rect);
		if (flags & FT_DRAW_FLAG_COLOR)
			col = va_arg(lst, t_color);
		va_end(lst);
	}

	dst_rect = ivec4(dst_pos.x, dst_pos.y, dst_pos.x + (src_rect.z - src_rect.x), dst_pos.y + (src_rect.w - src_rect.y));
	dst_rect_clipped = ft_clip_rect_rect(dst_rect, clip_rect);

	if (dst_rect_clipped.x > dst_rect_clipped.z || dst_rect_clipped.y > dst_rect_clipped.w)
		return;

	src_rect.x += dst_rect_clipped.x - dst_rect.x;
	src_rect.y += dst_rect_clipped.y - dst_rect.y;
	dst_rect = dst_rect_clipped;

	dst_y = dst_rect.y;
	src_y = src_rect.y;
	len = sizeof(t_color) * (dst_rect.z - dst_rect.x);
	while (dst_y < dst_rect.w)
	{
		ft_memcpy(
			ft_get_pixel(dst, dst_rect.x, dst_y),
			ft_get_pixel(src, src_rect.x, src_y),
			len);
		src_y++;
		dst_y++;
	}
}

#if 0
EXTENDED_ALIAS("ft_copy_image2", 0, (), ())
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

EXTENDED_ALIAS("ft_copy_image2", 1, ("sse2", "ssse3", "sse4_1"), ("sse"))
static void copy_image2_xmm(t_image *dst, t_iv2 dstpos, t_image *src, t_iv4 srcrect)
{
	const S32 step = 2; /* 2 pixels processed simultaneously */
	// clang-format off
	volatile const U8 mask[] = {
		6,  1, 6,  1, 6,  1, 6,  1,
		14, 1, 14, 1, 14, 1, 14, 1,
	};
	// clang-format on

	S32 dst_y;
	S32 src_y;
	t_color *dstaddr;
	t_color *srcaddr;
	S32 len;
	bool not_even;

	if (srcrect.x > srcrect.z || srcrect.y > srcrect.w)
		return;
	copy_image_clip(dst, &dstpos, src, &srcrect);

	dst_y = dstpos.y;
	src_y = srcrect.y;
	len = (srcrect.z - srcrect.x);
	not_even = len % step;
	len -= not_even;

	while (src_y < srcrect.w)
	{
		dstaddr = ft_get_pixel(dst, dstpos.x, dst_y);
		srcaddr = ft_get_pixel(src, srcrect.x, src_y);
		for (S32 i = 0; i < len; i += step)
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
				"movq         [%0], xmm0\n"
				:
				: "r"(dstaddr + i), "r"(srcaddr + i), "r"(mask)
				: "xmm0", "xmm1", "xmm2", "xmm3");
		}
		if (not_even)
			*(dstaddr + len) = *(srcaddr + len);
		src_y++;
		dst_y++;
	}
}

EXTENDED_ALIAS("ft_copy_image2", 2, ("avx2"), ("avx"))
void copy_image2_ymm(t_image *dst, t_iv2 dstpos, t_image *src, t_iv4 srcrect)
{
	const S32 step = 4; /* 4 pixels processed simultaneously */
	// clang-format off
	volatile const U8 mask[] = {
		6,  1, 6,  1, 6,  1, 6,  1,
		14, 1, 14, 1, 14, 1, 14, 1,
		6,  1, 6,  1, 6,  1, 6,  1,
		14, 1, 14, 1, 14, 1, 14, 1,
	};
	// clang-format on

	S32 dst_y;
	S32 src_y;
	t_color *dstaddr;
	t_color *srcaddr;
	S32 len;
	S32 rem;

	if (srcrect.x > srcrect.z || srcrect.y > srcrect.w)
		return;
	copy_image_clip(dst, &dstpos, src, &srcrect);

	dst_y = dstpos.y;
	src_y = srcrect.y;
	len = (srcrect.z - srcrect.x);
	rem = len % step;
	len -= rem;

	while (src_y < srcrect.w)
	{
		dstaddr = ft_get_pixel(dst, dstpos.x, dst_y);
		srcaddr = ft_get_pixel(src, srcrect.x, src_y);
		for (S32 i = 0; i < len; i += step)
		{
			asm(
				"vpmovzxbw    ymm0, [%0]\n"
				"vpmovzxbw    ymm1, [%1]\n"
				"vpshufb      ymm2, ymm1, [%2]\n"

				"vpmullw      ymm1, ymm1, ymm2\n" // alpha * over

				"vpcmpeqw     ymm3, ymm3, ymm3\n" /* 'pcmpeqw ymm%, ymm%' generates 0xfffff... */
				"vpsrlw       ymm3, ymm3, 8\n"	  /* shift right by 8 to keep only 0xff in each word */
				"vpsubw       ymm2, ymm3, ymm2\n" // (255 - alpha)
				"vpmullw      ymm0, ymm0, ymm2\n" // (255 - alpha) * under

				"vpaddw       ymm0, ymm0, ymm1\n" // (alpha * over) + ((255 - alpha) * under)
				"vpsrlw       ymm0, ymm0, 8\n"	  // (alpha * over) + ((255 - alpha) * under) / 255 (256 en vrai lol mais bon nsm)

				"vpackuswb    ymm0, ymm0, ymm0\n"		// Pack over to 0RGB
				"vpermq       ymm0, ymm0, 0b10011000\n" // Rearrange lanes
				"vmovdqu      [%0], xmm0\n"
				:
				: "r"(dstaddr + i), "r"(srcaddr + i), "r"(mask)
				: "ymm0", "ymm1", "ymm2", "ymm3");
		}
		for (S32 i = len; i < rem; i++)
			*(dstaddr + i) = *(srcaddr + i);
		src_y++;
		dst_y++;
	}
}

/* Auto-generated by build-aux/extended_aliases.py */
#include "libft/sys/cpuid.h"
#include "libft/sys/xsave.h"
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
	struct s_cpuid_flags *cpuid_flags;
	struct s_xcr0_flags os_flags;

	cpuid_flags = ft_cpuid_get_cached_flags();
	ft_xgetbv(0, &os_flags.flags);
	if (os_flags.avx && cpuid_flags->avx2)
		__resolved_ft_copy_image2 = copy_image2;
	//__resolved_ft_copy_image2 = copy_image2_ymm;
	else if (os_flags.sse && cpuid_flags->sse2 && cpuid_flags->ssse3 && cpuid_flags->sse4_1)
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

#endif