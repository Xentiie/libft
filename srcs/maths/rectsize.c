/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rectsize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:55:12 by reclaire          #+#    #+#             */
/*   Updated: 2025/02/13 14:56:44 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/maths.h"

#include "libft_int.h"

t_iv2 ft_irectsize(t_iv4 rect)
{
	return ivec2(rect.z - rect.x, rect.w - rect.y);
}

t_v2 ft_rectsize(t_v4 rect)
{
	return vec2(rect.z - rect.x, rect.w - rect.y);
}
