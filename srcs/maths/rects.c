/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rects.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:55:12 by reclaire          #+#    #+#             */
/*   Updated: 2025/06/10 09:21:59 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_int.h"

#include "libft/maths.h"

extern t_iv2 ft_irectsize(t_iv4 rect);
extern t_v2 ft_rectsize(t_v4 rect);
extern t_iv4 ft_clip_rect_rect(t_iv4 r1, t_iv4 r2);
extern t_v4 ft_clip_rect_rect_flt(t_v4 r1, t_v4 r2);

extern t_iv4 ft_offset_rect(t_iv4 rect, t_iv2 ofs);
extern t_v4 ft_offset_rect_flt(t_v4 rect, t_v2 ofs);
