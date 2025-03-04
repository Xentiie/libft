/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lerp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 22:29:36 by reclaire          #+#    #+#             */
/*   Updated: 2025/01/23 04:25:04 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_int.h"
#include "libft/maths.h"

#include <math.h>

inline F64 ft_lerp(F64 x, F64 y, F64 t)
{
	return (x + ft_clampf(0, 1, t) * (y - x));
}

inline t_v2 ft_lerp2(t_v2 v_1, t_v2 v_2, F64 t)
{
	return (vec2(
		ft_lerp(v_1.x, v_2.x, t),
		ft_lerp(v_1.y, v_2.y, t)));
}

inline t_v3 ft_lerp3(t_v3 v_1, t_v3 v_2, F64 t)
{
	return (vec3(
		ft_lerp(v_1.x, v_2.x, t),
		ft_lerp(v_1.y, v_2.y, t),
		ft_lerp(v_1.z, v_2.z, t)));
}

inline t_v4 ft_lerp4(t_v4 v_1, t_v4 v_2, F64 t)
{
	return (vec4(
		ft_lerp(v_1.x, v_2.x, t),
		ft_lerp(v_1.y, v_2.y, t),
		ft_lerp(v_1.z, v_2.z, t),
		ft_lerp(v_1.w, v_2.w, t)));
}

inline S32 ft_lerp_i(S32 x, S32 y, F64 t)
{
	return (x + ft_clampf(0, 1, t) * (y - x));
}

inline t_iv2 ft_lerp2_i(t_iv2 v_1, t_iv2 v_2, F64 t)
{
	return (ivec2(
		ft_lerp_i(v_1.x, v_2.x, t),
		ft_lerp_i(v_1.y, v_2.y, t)));
}

inline t_iv3 ft_lerp3_i(t_iv3 v_1, t_iv3 v_2, F64 t)
{
	return (ivec3(
		ft_lerp_i(v_1.x, v_2.x, t),
		ft_lerp_i(v_1.y, v_2.y, t),
		ft_lerp_i(v_1.z, v_2.z, t)));
}

inline t_iv4 ft_lerp4_i(t_iv4 v_1, t_iv4 v_2, F64 t)
{
	return (ivec4(
		ft_lerp_i(v_1.x, v_2.x, t),
		ft_lerp_i(v_1.y, v_2.y, t),
		ft_lerp_i(v_1.z, v_2.z, t),
		ft_lerp_i(v_1.w, v_2.w, t)));
}

inline F64 ft_invlerp(F64 a, F64 b, F64 value)
{
	if (b - a == 0)
		return 0;
	return ((value - a) / (b - a));
}

inline t_v2 ft_invlerp2(t_v2 a, t_v2 b, t_v2 t)
{
	return (vec2(ft_invlerp(a.x, b.x, t.x),
				 ft_invlerp(a.y, b.y, t.y)));
}

inline t_v3 ft_invlerp3(t_v3 a, t_v3 b, t_v3 t)
{
	return (vec3(ft_invlerp_i(a.x, b.x, t.x),
				 ft_invlerp_i(a.y, b.y, t.y),
				 ft_invlerp_i(a.z, b.z, t.z)));
}

inline t_v4 ft_invlerp4(t_v4 a, t_v4 b, t_v4 t)
{
	return (vec4(ft_invlerp_i(a.x, b.x, t.x),
				 ft_invlerp_i(a.y, b.y, t.y),
				 ft_invlerp_i(a.z, b.z, t.z),
				 ft_invlerp_i(a.w, b.w, t.w)));
}

inline F64 ft_invlerp_i(S32 a, S32 b, S32 value)
{
	if (b - a == 0)
		return 0;
	return ((F64)(value - a) / (F64)(b - a));
}

inline t_v2 ft_invlerp2_i(t_iv2 a, t_iv2 b, t_iv2 t)
{
	return (vec2(ft_invlerp_i(a.x, b.x, t.x),
				 ft_invlerp_i(a.y, b.y, t.y)));
}

inline t_v3 ft_invlerp3_i(t_iv3 a, t_iv3 b, t_iv3 t)
{
	return (vec3(ft_invlerp_i(a.x, b.x, t.x),
				 ft_invlerp_i(a.y, b.y, t.y),
				 ft_invlerp_i(a.z, b.z, t.z)));
}

inline t_v4 ft_invlerp4_i(t_iv4 a, t_iv4 b, t_iv4 t)
{
	return (vec4(ft_invlerp_i(a.x, b.x, t.x),
				 ft_invlerp_i(a.y, b.y, t.y),
				 ft_invlerp_i(a.z, b.z, t.z),
				 ft_invlerp_i(a.w, b.w, t.w)));
}
