/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrices_2x2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 18:42:51 by reclaire          #+#    #+#             */
/*   Updated: 2025/03/10 23:51:47 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_int.h"

#include "libft/maths.h"

t_mat22 ft_mat22_inv(t_mat22 m)
{
	F32		det;
	t_mat22 inv;

	det = m.m[0][0] * m.m[1][1] - m.m[0][1] * m.m[1][0];
	inv.m[0][0] = m.m[1][1] / det;
	inv.m[0][1] = -m.m[0][1] / det;
	inv.m[1][0] = -m.m[1][0] / det;
	inv.m[1][1] = m.m[0][0] / det;
	return (inv);
}

t_v2 ft_mat22_vec2_mul(t_mat22 m, t_v2 v)
{
	return ((t_v2){.x = m.m[0][0] * v.x + m.m[0][1] * v.y,
				   .y = m.m[1][0] * v.x + m.m[1][1] * v.y});
}
