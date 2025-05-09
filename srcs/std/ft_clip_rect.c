/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clip_rect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 12:48:40 by reclaire          #+#    #+#             */
/*   Updated: 2025/05/06 12:50:22 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/maths.h"

t_iv4 ft_clip_rect(t_iv4 rect, t_iv4 limits)
{
	t_iv4 out;

	out.x = ft_clamp(limits.x, limits.z, rect.x);
	out.y = ft_clamp(limits.y, limits.w, rect.y);
	out.z = ft_clamp(limits.x, limits.z, rect.z);
	out.w = ft_clamp(limits.y, limits.w, rect.w);
	return out;
}
