/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ceil.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 16:38:34 by reclaire          #+#    #+#             */
/*   Updated: 2024/02/13 16:39:48 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_int.h"
#include <math.h>

F32		ft_ceil(F32 n)		{ return ceil(n); }

t_v2	ft_ceil2(t_v2 n)	{ return vec2(ceil(n.x), ceil(n.y)); }
t_v3	ft_ceil3(t_v3 n)	{ return vec3(ceil(n.x), ceil(n.y), ceil(n.z)); }
t_v4	ft_ceil4(t_v4 n)	{ return vec4(ceil(n.x), ceil(n.y), ceil(n.z), ceil(n.w)); }
t_iv2	ft_iceil2(t_iv2 n)	{ return ivec2(ceil(n.x), ceil(n.y)); }
t_iv3	ft_iceil3(t_iv3 n)	{ return ivec3(ceil(n.x), ceil(n.y), ceil(n.z)); }
t_iv4	ft_iceil4(t_iv4 n)	{ return ivec4(ceil(n.x), ceil(n.y), ceil(n.z), ceil(n.w)); }
