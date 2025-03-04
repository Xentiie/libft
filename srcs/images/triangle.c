/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 19:39:00 by reclaire          #+#    #+#             */
/*   Updated: 2025/02/23 22:28:14 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/images.h"

void ft_draw_triangle(t_image *img, t_iv2 p1, t_iv2 p2, t_iv2 p3, t_color col)
{
	ft_draw_line(img, p1, p2, col);
	ft_draw_line(img, p2, p3, col);
	ft_draw_line(img, p3, p1, col);
}

void ft_draw_triangle_bound(t_image *img, t_iv2 p1, t_iv2 p2, t_iv2 p3, t_color col, t_iv4 bound)
{
	ft_draw_line_bound(img, p1, p2, col, bound);
	ft_draw_line_bound(img, p2, p3, col, bound);
	ft_draw_line_bound(img, p3, p1, col, bound);
}

void ft_draw_triangle2(t_image *img, t_iv2 p1, t_iv2 p2, t_iv2 p3, t_color col)
{
	ft_draw_line2(img, p1, p2, col);
	ft_draw_line2(img, p2, p3, col);
	ft_draw_line2(img, p3, p1, col);
}

void ft_draw_triangle_bound2(t_image *img, t_iv2 p1, t_iv2 p2, t_iv2 p3, t_color col, t_iv4 bound)
{
	ft_draw_line_bound2(img, p1, p2, col, bound);
	ft_draw_line_bound2(img, p2, p3, col, bound);
	ft_draw_line_bound2(img, p3, p1, col, bound);
}
