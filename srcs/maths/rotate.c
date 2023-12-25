/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 22:56:39 by reclaire          #+#    #+#             */
/*   Updated: 2023/09/26 22:12:31 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "libft.h"
#ifdef FT_MATHS
t_v2	ft_rotate2(t_v2 v, float angle, t_v2 origin)
{
	t_v2	p;
	t_v2	tmp;

	p.x = v.x - origin.x;
	p.y = v.y - origin.y;
	tmp.x = p.x * cos(angle) - p.y * sin(angle);
	tmp.y = p.x * sin(angle) + p.y * cos(angle);
	return (vec2(tmp.x + origin.x, tmp.y + origin.y));
}
#endif