/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lerp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 22:29:36 by reclaire          #+#    #+#             */
/*   Updated: 2024/06/09 04:06:07 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "libft_int.h"

inline F32 ft_lerp(F32 x, F32 y, F32 t)
{
	return (x + ft_clampf(0, 1, t) * (y - x));
}

inline v2f ft_lerp2(v2f v_1, v2f v_2, F32 t)
{
	return (v2f){
		ft_lerp(v_1[0], v_2[0], t),
		ft_lerp(v_1[1], v_2[1], t)};
}

inline v3f ft_lerp3(v3f v_1, v3f v_2, F32 t)
{
	return (v2f){
		ft_lerp(v_1[0], v_2[0], t),
		ft_lerp(v_1[1], v_2[1], t),
		ft_lerp(v_1[2], v_2[2], t)};
}

inline v4f ft_lerp4(v4f v_1, v4f v_2, F32 t)
{
	return (v4f){
		ft_lerp(v_1[0], v_2[0], t),
		ft_lerp(v_1[1], v_2[1], t),
		ft_lerp(v_1[2], v_2[2], t),
		ft_lerp(v_1[3], v_2[3], t)};
}

inline S32 ft_lerp_i(S32 x, S32 y, float t)
{
	return (x + ft_clampf(0, 1, t) * (y - x));
}

inline v2i ft_lerp2_i(v2i v_1, v2i v_2, F32 t)
{
	return (v2i){
		ft_lerp_i(v_1[0], v_2[0], t),
		ft_lerp_i(v_1[1], v_2[1], t)};
}

inline v3i ft_lerp3_i(v3i v_1, v3i v_2, F32 t)
{
	return (v3i){
		ft_lerp_i(v_1[0], v_2[0], t),
		ft_lerp_i(v_1[1], v_2[1], t),
		ft_lerp_i(v_1[2], v_2[2], t)};
}

inline v4i ft_lerp4_i(v4i v_1, v4i v_2, F32 t)
{
	return (v4i){
		ft_lerp_i(v_1[0], v_2[0], t),
		ft_lerp_i(v_1[1], v_2[1], t),
		ft_lerp_i(v_1[2], v_2[2], t),
		ft_lerp_i(v_1[3], v_2[3], t)};
}

inline F32 ft_invlerp(F32 a, F32 b, F32 value)
{
	return ((value - a) / (b - a));
}

inline v2f ft_invlerp2(v2f a, v2f b, v2f t)
{
	return (v2f){(t[0] - a[0]) / (b[0] - a[0]),
				 (t[1] - a[1]) / (b[1] - a[1])};
}

inline v3f ft_invlerp3(v3f a, v3f b, v3f t)
{
	return (v3f){(t[0] - a[0]) / (b[0] - a[0]),
				 (t[1] - a[1]) / (b[1] - a[1]),
				 (t[2] - a[2]) / (b[2] - a[2])};
}

inline v4f ft_invlerp4(v4f a, v4f b, v4f t)
{
	return (v4f){(t[0] - a[0]) / (b[0] - a[0]),
				 (t[1] - a[1]) / (b[1] - a[1]),
				 (t[2] - a[2]) / (b[2] - a[2]),
				 (t[3] - a[3]) / (b[3] - a[3])};
}

inline F32 ft_invlerp_i(S32 a, S32 b, S32 value)
{
	return ((F32)(value - a) / (F32)(b - a));
}

inline v2f ft_invlerp2_i(v2i a, v2i b, v2i t)
{
	return (v2f){ft_invlerp_i(a[0], b[0], t[0]),
				 ft_invlerp_i(a[1], b[1], t[1])};
}

inline v3f ft_invlerp3_i(v3i a, v3i b, v3i t)
{
	return (v3f){ft_invlerp_i(a[0], b[0], t[0]),
				 ft_invlerp_i(a[1], b[1], t[1]),
				 ft_invlerp_i(a[2], b[2], t[2])};
}

inline v4f ft_invlerp4_i(v4i a, v4i b, v4i t)
{
	return (v4f){ft_invlerp_i(a[0], b[0], t[0]),
				 ft_invlerp_i(a[1], b[1], t[1]),
				 ft_invlerp_i(a[2], b[2], t[2]),
				 ft_invlerp_i(a[3], b[3], t[3])};
}
