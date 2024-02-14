/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lerp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 22:29:36 by reclaire          #+#    #+#             */
/*   Updated: 2024/02/11 20:51:26 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "libft_int.h"


inline F32		ft_lerp(F32 x, F32 y, F32 t)
{
	return (x + ft_clampf(0, 1, t) * (y - x));
}

inline t_v2		ft_lerp2(t_v2 v_1, t_v2 v_2, F32 t)
{
	return (vec2(
			ft_lerp(v_1.x, v_2.x, t),
			ft_lerp(v_1.y, v_2.y, t)));
}

inline t_v3		ft_lerp3(t_v3 v_1, t_v3 v_2, F32 t)
{
	return (vec3(
			ft_lerp(v_1.x, v_2.x, t),
			ft_lerp(v_1.y, v_2.y, t),
			ft_lerp(v_1.z, v_2.z, t)));
}

inline t_v4		ft_lerp4(t_v4 v_1, t_v4 v_2, F32 t)
{
	return (vec4(
			ft_lerp(v_1.x, v_2.x, t),
			ft_lerp(v_1.y, v_2.y, t),
			ft_lerp(v_1.z, v_2.z, t),
			ft_lerp(v_1.w, v_2.w, t)));
}

inline F32	ft_invlerp(F32 a, F32 b, F32 value)
{
	return ((value - a) / (b - a));
}

inline t_v2		ft_invlerp2(t_v2 a, t_v2 b, t_v2 t)
{
	return (vec2((t.x - a.x) / (b.x - a.x),
			(t.y - a.y) / (b.y - a.y)));
}

inline t_v3		ft_invlerp3(t_v3 a, t_v3 b, t_v3 t)
{
	return (vec3((t.x - a.x) / (b.x - a.x),
			(t.y - a.y) / (b.y - a.y),
			(t.z - a.z) / (b.z - a.z)));
}

inline t_v4		ft_invlerp4(t_v4 a, t_v4 b, t_v4 t)
{
	return (vec4((t.x - a.x) / (b.x - a.x),
			(t.y - a.y) / (b.y - a.y),
			(t.z - a.z) / (b.z - a.z),
			(t.w - a.w) / (b.w - a.w)));
}
