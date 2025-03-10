/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ceil.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 16:38:34 by reclaire          #+#    #+#             */
/*   Updated: 2025/01/23 04:22:10 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_int.h"
#include "libft/maths.h"

#include <math.h>

F64		ft_ceil(F64 n)		{ return ceil(n); }

t_v2	ft_ceil2(t_v2 n)	{ return vec2(ceil(n.x), ceil(n.y)); }
t_v3	ft_ceil3(t_v3 n)	{ return vec3(ceil(n.x), ceil(n.y), ceil(n.z)); }
t_v4	ft_ceil4(t_v4 n)	{ return vec4(ceil(n.x), ceil(n.y), ceil(n.z), ceil(n.w)); }
