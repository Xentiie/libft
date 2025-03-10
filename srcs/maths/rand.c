/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rand.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 23:48:39 by reclaire          #+#    #+#             */
/*   Updated: 2025/03/10 23:50:43 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_int.h"

#include "libft/maths.h"

F32	ft_frand(S32 n)
{
	n = (n << 13U) ^ n;
	n = n * (n * n * 15731U + 789221U) + 1376312589U;
	return ((F32)(n & (U32)(0x7fffffffU)) / (F32)(0x7fffffff));
}

F32	ft_frand2(t_v2 st)
{
	return (ft_frac(sin(ft_dot2(st, vec2(12.9898, 78.233)))
			* 43758.5453123));
}

t_v2	ft_rand_circle(U32 seed)
{
	return (vec2(ft_sin(ft_frand(seed)), ft_cos(ft_frand(seed + 1))));
}
