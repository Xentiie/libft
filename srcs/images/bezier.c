/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bezier.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 16:22:26 by reclaire          #+#    #+#             */
/*   Updated: 2025/03/11 00:34:55 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/images.h"

void ft_draw_bezier(t_image *img, t_color col, t_v2 p1, t_v2 p2, t_v2 p3, S32 res)
{
	t_v2 prev = p1;
	for (S32 i = 0; i < res; i++)
	{
		F32 t = (i + 1.0f) / res;
		t_v2 p_on_curve = ft_bezier_interp(p1, p2, p3, t);
		ft_draw_line(img, vec2_int(prev), vec2_int(p_on_curve), col);
		prev = p_on_curve;
	}
}

void ft_draw_bezier_bound(t_image *img, t_color col, t_v2 p1, t_v2 p2, t_v2 p3, S32 res, t_iv4 bound)
{
	t_v2 prev = p1;
	for (S32 i = 0; i < res; i++)
	{
		F32 t = (i + 1.0f) / res;
		t_v2 p_on_curve = ft_bezier_interp(p1, p2, p3, t);
		//TODO: peut etre fait plus proprement
		ft_draw_line_bound(img, vec2_int(prev), vec2_int(p_on_curve), col, bound);
		prev = p_on_curve;
	}
}

void ft_draw_bezier2(t_image *img, t_color col, t_v2 p1, t_v2 p2, t_v2 p3, S32 res)
{
	t_v2 prev = p1;
	for (S32 i = 0; i < res; i++)
	{
		F32 t = (i + 1.0f) / res;
		t_v2 p_on_curve = ft_bezier_interp(p1, p2, p3, t);
		ft_draw_line2(img, vec2_int(prev), vec2_int(p_on_curve), col);
		prev = p_on_curve;
	}
}

void ft_draw_bezier_bound2(t_image *img, t_color col, t_v2 p1, t_v2 p2, t_v2 p3, S32 res, t_iv4 bound)
{
	t_v2 prev = p1;
	for (S32 i = 0; i < res; i++)
	{
		F32 t = (i + 1.0f) / res;
		t_v2 p_on_curve = ft_bezier_interp(p1, p2, p3, t);
		//TODO: peut etre fait plus proprement aussi
		ft_draw_line_bound2(img, vec2_int(prev), vec2_int(p_on_curve), col, bound);
		prev = p_on_curve;
	}
}
