/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lines.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 00:03:52 by reclaire          #+#    #+#             */
/*   Updated: 2025/03/10 23:51:36 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_int.h"

#include "libft/maths.h"

#define INSIDE 0
#define LEFT (1 << 0)
#define RIGHT (1 << 1)
#define BOTTOM (1 << 2)
#define TOP (1 << 3)

static U8 line_draw_intersect(t_iv2 p, t_iv4 rect)
{
	U8 outcode;

	outcode = INSIDE;
	if (p.x < rect.x)
		outcode |= LEFT;
	else if (p.x >= rect.z)
		outcode |= RIGHT;
	if (p.y < rect.y)
		outcode |= BOTTOM;
	else if (p.y >= rect.w)
		outcode |= TOP;
	return outcode;
}

bool ft_clip_line_rect(t_iv2 *p1, t_iv2 *p2, t_iv4 rect)
{
	t_iv2 intersection;
	U8 intersect1;
	U8 intersect2;
	U8 intersect_out;
	bool accept;
	S32 width;
	S32 height;

	width = rect.z - rect.x;
	height = rect.w - rect.y;

	intersect1 = line_draw_intersect(*p1, rect);
	intersect2 = line_draw_intersect(*p2, rect);

	accept = FALSE;
	while (TRUE)
	{
		if (!(intersect1 | intersect2)) /* both inside */
		{
			accept = TRUE;
			break;
		}
		else if (intersect1 & intersect2) /* both outside */
			return FALSE;
		else
		{
			intersect_out = (intersect1 != INSIDE) ? intersect1 : intersect2;
			if (intersect_out & TOP)
			{
				intersection.x = p1->x + (p2->x - p1->x) * (height - 1 - p1->y) / (p2->y - p1->y);
				intersection.y = height - 1;
			}
			else if (intersect_out & BOTTOM)
			{
				intersection.x = p1->x + (p2->x - p1->x) * (0 - p1->y) / (p2->y - p1->y);
				intersection.y = 0;
			}
			else if (intersect_out & RIGHT)
			{
				intersection.y = p1->y + (p2->y - p1->y) * (width - 1 - p1->x) / (p2->x - p1->x);
				intersection.x = width - 1;
			}
			else if (intersect_out & LEFT)
			{
				intersection.y = p1->y + (p2->y - p1->y) * (0 - p1->x) / (p2->x - p1->x);
				intersection.x = 0;
			}
			else
				intersection = ivec2(0, 0);

			if (intersect_out == intersect1)
			{
				*p1 = intersection;
				intersect1 = line_draw_intersect(*p1, rect);
			}
			else
			{
				*p2 = intersection;
				intersect2 = line_draw_intersect(*p2, rect);
			}
		}
	}
	return accept;
}

static U8 line_draw_intersect_flt(t_v2 p, t_v4 rect)
{
	U8 outcode;

	outcode = INSIDE;
	if (p.x < rect.x)
		outcode |= LEFT;
	else if (p.x >= rect.z)
		outcode |= RIGHT;
	if (p.y < rect.y)
		outcode |= BOTTOM;
	else if (p.y >= rect.w)
		outcode |= TOP;
	return outcode;
}

bool ft_clip_line_rect_flt(t_v2 *p1, t_v2 *p2, t_v4 rect)
{
	U8 intersect1;
	U8 intersect2;
	bool accept;
	S32 width;
	S32 height;

	width = rect.z - rect.x;
	height = rect.w - rect.y;

	intersect1 = line_draw_intersect_flt(*p1, rect);
	intersect2 = line_draw_intersect_flt(*p2, rect);

	accept = FALSE;
	while (TRUE)
	{
		if (!(intersect1 | intersect2)) /* both inside */
		{
			accept = TRUE;
			break;
		}
		else if (intersect1 & intersect2) /* both outside */
			return FALSE;
		else
		{
			t_v2 intersection;
			U8 intersect_out = (intersect1 != INSIDE) ? intersect1 : intersect2;
			if (intersect_out & TOP)
			{
				intersection.x = p1->x + (p2->x - p1->x) * (height - 1 - p1->y) / (p2->y - p1->y);
				intersection.y = height - 1;
			}
			else if (intersect_out & BOTTOM)
			{
				intersection.x = p1->x + (p2->x - p1->x) * (0 - p1->y) / (p2->y - p1->y);
				intersection.y = 0;
			}
			else if (intersect_out & RIGHT)
			{
				intersection.y = p1->y + (p2->y - p1->y) * (width - 1 - p1->x) / (p2->x - p1->x);
				intersection.x = width - 1;
			}
			else if (intersect_out & LEFT)
			{
				intersection.y = p1->y + (p2->y - p1->y) * (0 - p1->x) / (p2->x - p1->x);
				intersection.x = 0;
			}
			else
				intersection = vec2(0, 0);

			if (intersect_out == intersect1)
			{
				*p1 = intersection;
				intersect1 = line_draw_intersect_flt(*p1, rect);
			}
			else
			{
				*p2 = intersection;
				intersect2 = line_draw_intersect_flt(*p2, rect);
			}
		}
	}
	return accept;
}

F32 ft_dist_line(t_v2 p, t_v2 s1, t_v2 s2)
{
	t_v2 ab;
	t_v2 cd;
	F32 param;
	t_v2 d;
	t_v2 tmp;

	ab = vec2_sub(p, s1);
	cd = vec2_sub(s2, s1);
	param = 1;
	if (ft_dot2(cd, cd) != 0)
		param = ft_dot2(ab, cd) / ft_dot2(cd, cd);
	if (param < 0)
		tmp = vec2(s1.x, s1.y);
	else if (param > 1)
		tmp = vec2(s2.x, s2.y);
	else
		tmp = vec2(s1.x + param * cd.x, s1.y + param * cd.y);
	d = vec2_sub(p, tmp);
	return sqrt(d.x * d.x + d.y * d.y);
}
