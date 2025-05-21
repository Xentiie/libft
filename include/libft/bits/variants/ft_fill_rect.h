/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_rect.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 21:27:43 by reclaire          #+#    #+#             */
/*   Updated: 2025/05/19 21:41:28 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(FT_BITS_VARIANTS_FT_FILL_RECT_H)
#define FT_BITS_VARIANTS_FT_FILL_RECT_H

#include "libft/images.h"

void __ft_fill_rect_no_alpha(t_image *img, t_iv4 rect, t_color col);
void __ft_fill_rect_no_alpha_base(t_image *img, t_iv4 rect, t_color col);
void __ft_fill_rect_no_alpha_x4(t_image *img, t_iv4 rect, t_color col);
void __ft_fill_rect_no_alpha_x8(t_image *img, t_iv4 rect, t_color col);

void __ft_fill_rect_alpha(t_image *img, t_iv4 rect, t_color col);
void __ft_fill_rect_alpha_base(t_image *img, t_iv4 rect, t_color col);
void __ft_fill_rect_alpha_x4(t_image *img, t_iv4 rect, t_color col);

#endif