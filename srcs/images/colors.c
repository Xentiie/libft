/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 15:20:53 by reclaire          #+#    #+#             */
/*   Updated: 2025/05/30 16:44:14 by reclaire         ###   ########.fr       */
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

t_color_hsv ft_hsv_from_unit_circle(t_v2 p, F32 val)
{
	F32 r;
	F32 angle;
	t_color_hsv col;

	r = sqrtf(p.x * p.x + p.y * p.y);
	angle = atan2f(p.y, p.x);

	col.hue = (angle / (2.0f * FT_PI)) + 0.5f;
	col.sat = r;
	col.val = val;

	return col;
}

t_color_hsv ft_hsv_from_circle(t_v2 p, F32 radius, F32 val)
{
	t_v2 d;

	d.x = p.x / radius;
	d.y = p.y / radius;

	return ft_hsv_from_unit_circle(d, val);
}

t_color_hsv ft_hsv_from_rect(t_v2 p, t_v4 rect, F32 val)
{
	t_v2 c;
	t_v2 d;
	F32 radius;

	c.x = rect.x + (rect.z - rect.x) / 2.0f;
	c.y = rect.y + (rect.w - rect.y) / 2.0f;
	if (c.x > c.y)
		radius = c.x - rect.x;
	else
		radius = c.y - rect.y;

	d.x = p.x - c.x;
	d.y = p.y - c.y;

	return ft_hsv_from_circle(d, radius, val);
}

t_color_hsv ft_rgb_to_hsv(t_color col)
{
	F32 r, g, b;
	F32 min, max, delta;
	t_color_hsv out;

	r = col.r / 255.0f;
	g = col.g / 255.0f;
	b = col.b / 255.0f;

	min = ft_fmin(r, ft_fmin(g, b));
	max = ft_fmax(r, ft_fmax(g, b));
	delta = max - min;

	if (delta == 0.0f)
		out.hue = 0.0f; // undefined hue
	else if (max == r)
		out.hue = fmodf(((g - b) / delta), 6.0f) / 6.0f;
	else if (max == g)
		out.hue = (((b - r) / delta) + 2.0f) / 6.0f;
	else // max == b
		out.hue = (((r - g) / delta) + 4.0f) / 6.0f;

	if (out.hue < 0.0f)
		out.hue += 1.0f;
	out.sat = (max == 0.0f) ? 0.0f : (delta / max);
	out.val = max;

	return out;
}

t_color ft_hsv_to_rgb(t_color_hsv col)
{
	S32 i;
	F32 r, g, b;
	F32 f, p, q, t;
	t_color out;

	i = (S32)(col.hue * 6.0f);
	f = col.hue * 6.0f - i;
	p = col.val * (1.0f - col.sat);
	q = col.val * (1.0f - f * col.sat);
	t = col.val * (1.0f - (1.0f - f) * col.sat);

	switch (i % 6)
	{
		// clang-format off
		case 0: r = col.val; g = t; b = p; break;
		case 1: r = q; g = col.val; b = p; break;
		case 2: r = p; g = col.val; b = t; break;
		case 3: r = p; g = q; b = col.val; break;
		case 4: r = t; g = p; b = col.val; break;
		case 5: r = col.val; g = p; b = q; break;
		default: r = g = b = 0; break; // should never happen
		//clang-format: on
	}

	out.r = (U8)(r * 255.0f);
	out.g = (U8)(g * 255.0f);
	out.b = (U8)(b * 255.0f);
	out.a = 255;

	return out;
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
	return ablend_simd;
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
