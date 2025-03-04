/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_eq.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:42:46 by reclaire          #+#    #+#             */
/*   Updated: 2025/02/06 16:43:00 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_int.h"

#include "libft/maths.h"

t_v4 ft_plane_eq(t_v3 p1, t_v3 p2, t_v3 p3)
{
	t_v3 v1;
	t_v3 v2;
	t_v3 n;
	F32	 k;

	v1 = vec3_sub(p2, p1);
	v2 = vec3_sub(p3, p1);
	n = vec3_scl(ft_normalize3(ft_cross3(v1, v2)), -1);
	k = -ft_dot3(p1, n);
	return vec4(n.x, n.y, n.z, k);
}

