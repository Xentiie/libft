/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stretch_image.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 17:39:54 by reclaire          #+#    #+#             */
/*   Updated: 2025/05/21 17:41:57 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(FT_BITS_VARIANTS_FT_STRETCH_IMAGE_H)
#define FT_BITS_VARIANTS_FT_STRETCH_IMAGE_H

#include "libft/images.h"

void __ft_stretch_image_no_alpha(t_image *dst, t_iv4 dst_rect, t_image *src, t_v2 scl_factor, t_v2 src_start);
void __ft_stretch_image_no_alpha_base(t_image *dst, t_iv4 dst_rect, t_image *src, t_v2 scl_factor, t_v2 src_start);

void __ft_stretch_image_alpha(t_image *dst, t_iv4 dst_rect, t_image *src, t_v2 scl_factor, t_v2 src_start);
void __ft_stretch_image_alpha_base(t_image *dst, t_iv4 dst_rect, t_image *src, t_v2 scl_factor, t_v2 src_start);

#endif
