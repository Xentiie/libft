/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 22:49:15 by reclaire          #+#    #+#             */
/*   Updated: 2025/01/23 04:23:25 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_int.h"
#include "libft/maths.h"

#include <math.h>

F64	ft_map(F64 v, t_v2 from, t_v2 to)
{
	F64	normal;
	F64	tp_max_abs;
	F64	to_abs;

	normal = (v - from.x) / (from.y - from.x);
	tp_max_abs = to.y - to.x;
	to_abs = tp_max_abs * normal;
	return (to_abs + to.x);
}
