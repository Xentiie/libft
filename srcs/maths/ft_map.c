/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 22:49:15 by reclaire          #+#    #+#             */
/*   Updated: 2023/09/26 22:11:19 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "libft.h"
#ifdef FT_MATHS
float	ft_map(float v, t_v2 from, t_v2 to)
{
	float	normal;
	float	tp_max_abs;
	float	to_abs;

	normal = (v - from.x) / (from.y - from.x);
	tp_max_abs = to.y - to.x;
	to_abs = tp_max_abs * normal;
	return (to_abs + to.x);
}
#endif