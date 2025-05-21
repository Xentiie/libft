/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_triangle.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 18:13:40 by reclaire          #+#    #+#             */
/*   Updated: 2025/05/20 04:04:22 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(FT_BITS_VARIANTS_FT_DRAW_TRIANGLE_H)
#define FT_BITS_VARIANTS_FT_DRAW_TRIANGLE_H

#include "libft/images.h"

void __ft_draw_triangle_no_alpha(t_image *img, t_iv2 p1, t_iv2 p2, t_color col);
void __ft_draw_triangle_no_alpha_base(t_image *img, t_iv2 p1, t_iv2 p2, t_color col);

void __ft_draw_triangle_alpha(t_image *img, t_iv2 p1, t_iv2 p2, t_color col);
void __ft_draw_triangle_alpha_base(t_image *img, t_iv2 p1, t_iv2 p2, t_color col);

#endif
