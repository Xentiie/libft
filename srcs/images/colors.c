/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 15:20:53 by reclaire          #+#    #+#             */
/*   Updated: 2025/04/15 02:29:36 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/io.h"
#include "libft/images.h"

#include "libft/bits/extended_aliases.h"

t_color ft_rand_color(U32 seed)
{
	return (t_color){.r = ft_frand(seed) * 255,
					 .g = ft_frand(seed + 1) * 255,
					 .b = ft_frand(seed + 2) * 255,
					 .a = 255};
}

MAYBE_UNUSED
static t_color ablend_no_simd(t_color under, t_color over)
{
	return (t_color){
		.r = ((over.a * over.r) + ((255 - over.a) * under.r)) / 255,
		.g = ((over.a * over.g) + ((255 - over.a) * under.g)) / 255,
		.b = ((over.a * over.b) + ((255 - over.a) * under.b)) / 255,
		.a = 255,
	};
}

static t_color ablend_simd(t_color under, t_color over)
{
	t_color result;

	asm(
		/*
		Alpha blending formula: ((alpha * over) + ((255 - alpha) * under)) / 255

		eax/xmm0: 'under'
		ebx/xmm1: 'over'
		ecx/xmm2: 'over alpha'

		Note:
			Values in xmm registers: 4x16 bits. One letter = 16 bits. Exemple:
				- 000R0G0B: 00[64->48] 0R[48->32] 0G[32->16] 0B[16->0]
		*/
		"vmovd        xmm0, eax\n"		// Load 'under' color into xmm0
		"vmovd        xmm1, ebx\n"		// Load 'over' color into xmm1
		"vpsrld       xmm2, xmm1, 24\n" // Shift 'over' right *24 into xmm2 to retrieve only alpha

		//		"movq        ymm0, rax\n"

		/*
		At this point:
			- xmm0: under ABGR
			- xmm1: over  ABGR
			- xmm2: alpha 000A
		*/

		"pxor        xmm3, xmm3\n" // Zero-out xmm3
		"punpcklbw   xmm0, xmm3\n" // Expand under to 0A0B0G0R
		"punpcklbw   xmm1, xmm3\n" // Expand over to  0A0B0G0R

		"punpcklwd   xmm2, xmm2\n" // Expand alpha to 00000A0A
		"punpcklwd   xmm2, xmm2\n" // Expand alpha to 0A0A0A0A

		"pmullw      xmm1, xmm2\n" // alpha * over

		// TODO: 4 instructions pour avoir 00FF 00FF 00FF 00FF dans xmm3 c'est beaucoup. Peut mieux
		// faire
		//  (étudier la piste d'un chargement d'une constante dans la mémoire ? Faut tester
		//  la rapidité)
		//"movdqa       rax, [0x00FF00FF00FF00FF location]\n"

		"mov          eax,  0xFF\n"
		"vmovd        xmm3, eax\n"
		"punpcklwd    xmm3, xmm3\n"
		"punpcklwd    xmm3, xmm3\n"

		"vpsubw       xmm2, xmm3, xmm2\n" // (255 - alpha)
		"pmullw       xmm0, xmm2\n"		  // (255 - alpha) * under
		"paddw        xmm1, xmm0\n"		  // (alpha * over) + ((255 - alpha) * under)
		"psrlw        xmm1, 8\n"		  // (alpha * over) + ((255 - alpha) * under) / 255 (256 en vrai lol
										  // mais bon nsm)

		"packuswb     xmm1, xmm1\n" // Pack over to 0RGB
		"movd         eax, xmm1\n"
		"and          eax, 0x00FFFFFF\n"
		"or           eax, 0xFF000000\n"

		: "=a"(result.v) : "a"(under.v), "b"(over.v) : "xmm0", "xmm1", "xmm2", "xmm3");

	return result;
}

typedef t_color (*f_ablend)(t_color, t_color);
static f_ablend resolve_ablend()
{
	return ablend_no_simd;
}

t_color ft_alpha_blend(t_color under, t_color over)
	__attribute__((ifunc("resolve_ablend")));

t_color ft_alpha_blend2(t_color under, t_color over)
{
	F32 over_a;
	F32 inv_over_a;
	F32 under_a;

	over_a = (F32)over.a / 255.0F;
	under_a = (F32)under.a / 255.0f;
	inv_over_a = 1.0f - over_a;
	return (t_color){.r = over_a * over.r + inv_over_a * under.r * under_a,
					 .g = over_a * over.g + inv_over_a * under.g * under_a,
					 .b = over_a * over.b + inv_over_a * under.b * under_a,
					 .a = (over_a + under_a * inv_over_a) * 255.0f};
}
