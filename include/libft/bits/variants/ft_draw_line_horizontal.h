/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_line_horizontal.h                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 18:13:40 by reclaire          #+#    #+#             */
/*   Updated: 2025/05/20 03:45:12 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(FT_BITS_VARIANTS_FT_DRAW_LINE_HORIZONTAL_H)
#define FT_BITS_VARIANTS_FT_DRAW_LINE_HORIZONTAL_H

void __ft_draw_line_horizontal_no_alpha(t_image *img, t_iv2 p1, S32 x2, t_color col);
void __ft_draw_line_horizontal_no_alpha_base(t_image *img, t_iv2 p1, S32 x2, t_color col);

void __ft_draw_line_horizontal_alpha(t_image *img, t_iv2 p1, S32 x2, t_color col);
void __ft_draw_line_horizontal_alpha_base(t_image *img, t_iv2 p1, S32 x2, t_color col);

#endif
