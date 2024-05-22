/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_min.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 20:55:17 by reclaire          #+#    #+#             */
/*   Updated: 2024/05/21 22:28:03 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_int.h"

S32		ft_min_2(float a, float b)						{ return  MIN(a, b);}
S32		ft_min_3(float a, float b, float c)				{ return  MIN(MIN(a, b), c);}
S32		ft_min_4(float a, float b, float c, float d)	{ return  MIN(MIN(MIN(a, b), c), d);}
S32		ft_imin_2(int a, int b)							{ return  MIN(a, b);}
S32		ft_imin_3(int a, int b, int c)					{ return  MIN(MIN(a, b), c);}
S32		ft_imin_4(int a, int b, int c, int d)			{ return  MIN(MIN(MIN(a, b), c), d);}

F32 	ft_min2(t_v2 a)									{ return  MIN(a.x, a.y); }
t_v2 	ft_min2_2(t_v2 a, t_v2 b)						{ return  vec2(MIN(a.x, b.x), MIN(a.y, b.y)); }
t_v2 	ft_min2_3(t_v2 a, t_v2 b, t_v2 c)				{ return  vec2(MIN(MIN(a.x, b.x), c.x), MIN(MIN(a.y, b.y), c.y)); }
t_v2 	ft_min2_4(t_v2 a, t_v2 b, t_v2 c, t_v2 d)		{ return  vec2(MIN(MIN(MIN(a.x, b.x), c.x), d.x), MIN(MIN(MIN(a.y, b.y), c.y), d.y)); }
S32 	ft_min2i(t_iv2 a)								{ return  MIN(a.x, a.y); }
t_iv2	ft_min2i_2(t_iv2 a, t_iv2 b)					{ return  ivec2(MIN(a.x, b.x), MIN(a.y, b.y)); }
t_iv2	ft_min2i_3(t_iv2 a, t_iv2 b, t_iv2 c)			{ return  ivec2(MIN(MIN(a.x, b.x), c.x), MIN(MIN(a.y, b.y), c.y)); }
t_iv2	ft_min2i_4(t_iv2 a, t_iv2 b, t_iv2 c, t_iv2 d)	{ return  ivec2(MIN(MIN(MIN(a.x, b.x), c.x), d.x), MIN(MIN(MIN(a.y, b.y), c.y), d.y)); }

F32		ft_min3(t_v3 a)									{ return  MIN(MIN(a.x, a.y), a.z); }
t_v3 	ft_min3_2(t_v3 a, t_v3 b)						{ return  vec3(MIN(a.x, b.x), MIN(a.y, b.y), MIN(a.z, b.z)); }
t_v3 	ft_min3_3(t_v3 a, t_v3 b, t_v3 c)				{ return  vec3(MIN(MIN(a.x, b.x), c.x), MIN(MIN(a.y, b.y), c.y), MIN(MIN(a.z, b.z), c.z)); }
t_v3 	ft_min3_4(t_v3 a, t_v3 b, t_v3 c, t_v3 d)		{ return  vec3(MIN(MIN(MIN(a.x, b.x), c.x), d.x), MIN(MIN(MIN(a.y, b.y), c.y), d.y), MIN(MIN(MIN(a.z, b.z), c.z), d.z)); }
S32		ft_min3i(t_iv3 a)								{ return  MIN(MIN(a.x, a.y), a.z); }
t_iv3	ft_min3i_2(t_iv3 a, t_iv3 b)					{ return  ivec3(MIN(a.x, b.x), MIN(a.y, b.y), MIN(a.z, b.z)); }
t_iv3	ft_min3i_3(t_iv3 a, t_iv3 b, t_iv3 c)			{ return  ivec3(MIN(MIN(a.x, b.x), c.x), MIN(MIN(a.y, b.y), c.y), MIN(MIN(a.z, b.z), c.z)); }
t_iv3	ft_min3i_4(t_iv3 a, t_iv3 b, t_iv3 c, t_iv3 d)	{ return  ivec3(MIN(MIN(MIN(a.x, b.x), c.x), d.x), MIN(MIN(MIN(a.y, b.y), c.y), d.y), MIN(MIN(MIN(a.z, b.z), c.z), d.z)); }

F32 	ft_min4(t_v4 a)									{ return  MIN(MIN(MIN(a.x, a.y), a.z), a.w); }
t_v4 	ft_min4_2(t_v4 a, t_v4 b)						{ return  vec4(MIN(a.x, b.x), MIN(a.y, b.y), MIN(a.z, b.z), MIN(a.w, b.w)); }
t_v4 	ft_min4_3(t_v4 a, t_v4 b, t_v4 c)				{ return  vec4(MIN(MIN(a.x, b.x), c.x), MIN(MIN(a.y, b.y), c.y), MIN(MIN(a.z, b.z), c.z), MIN(MIN(a.w, b.w), c.w)); }
t_v4 	ft_min4_4(t_v4 a, t_v4 b, t_v4 c, t_v4 d)		{ return  vec4(MIN(MIN(MIN(a.x, b.x), c.x), d.x), MIN(MIN(MIN(a.y, b.y), c.y), d.y), MIN(MIN(MIN(a.z, b.z), c.z), d.z), MIN(MIN(MIN(a.w, b.w), c.w), d.w)); }
S32 	ft_min4i(t_iv4 a)								{ return  MIN(MIN(MIN(a.x, a.y), a.z), a.w); }
t_iv4 	ft_min4i_2(t_iv4 a, t_iv4 b)					{ return  ivec4(MIN(a.x, b.x), MIN(a.y, b.y), MIN(a.z, b.z), MIN(a.w, b.w)); }
t_iv4 	ft_min4i_3(t_iv4 a, t_iv4 b, t_iv4 c)			{ return  ivec4(MIN(MIN(a.x, b.x), c.x), MIN(MIN(a.y, b.y), c.y), MIN(MIN(a.z, b.z), c.z), MIN(MIN(a.w, b.w), c.w)); }
t_iv4 	ft_min4i_4(t_iv4 a, t_iv4 b, t_iv4 c, t_iv4 d)	{ return  ivec4(MIN(MIN(MIN(a.x, b.x), c.x), d.x), MIN(MIN(MIN(a.y, b.y), c.y), d.y), MIN(MIN(MIN(a.z, b.z), c.z), d.z), MIN(MIN(MIN(a.w, b.w), c.w), d.w)); }
