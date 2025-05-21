/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_bezier.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 18:13:40 by reclaire          #+#    #+#             */
/*   Updated: 2025/05/20 03:48:54 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(FT_BITS_VARIANTS_FT_DRAW_BEZIER_H)
#define FT_BITS_VARIANTS_FT_DRAW_BEZIER_H

#include "libft/images.h"

void __ft_draw_bezier_no_alpha(t_image *img, t_color col, t_v2 p1, t_v2 p2, t_v2 p3, S32 res);
void __ft_draw_bezier_no_alpha_base(t_image *img, t_color col, t_v2 p1, t_v2 p2, t_v2 p3, S32 res);

void __ft_draw_bezier_alpha(t_image *img, t_color col, t_v2 p1, t_v2 p2, t_v2 p3, S32 res);
void __ft_draw_bezier_alpha_base(t_image *img, t_color col, t_v2 p1, t_v2 p2, t_v2 p3, S32 res);

#endif
