/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dist_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 04:34:41 by reclaire          #+#    #+#             */
/*   Updated: 2024/02/11 20:51:26 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_int.h"
#include <math.h>

F32 ft_dist_line(v2f p, v2f s1, v2f s2)
{
	v2f ab;
	v2f cd;
	v2f d;
	v2f tmp;
	F32 param;

	ab = p - s1;
	cd = s2 - s1;
	param = 1;
	if (ft_dot2(cd, cd) != 0)
		param = ft_dot2(ab, cd) / ft_dot2(cd, cd);
	if (param < 0)
		tmp = (v2f){s1[0], s1[1]};
	else if (param > 1)
		tmp = (v2f){s2[0], s2[1]};
	else
		tmp = (v2f){s1[0] + param * cd[0], s1[1] + param * cd[1]};
	d = p - tmp;
	return sqrt(d[0] * d[0] + d[1] * d[1]);
}
