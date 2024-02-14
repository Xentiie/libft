/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_max.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 20:58:48 by reclaire          #+#    #+#             */
/*   Updated: 2024/02/11 20:51:26 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_int.h"


#define MAX(a, b) a > b ? a : b

F32		ft_max_2(float a, float b)							{ return  MAX(a, b);}
F32		ft_max_3(float a, float b, float c)					{ return  MAX(MAX(a, b), c);}
F32		ft_max_4(float a, float b, float c, float d)		{ return  MAX(MAX(MAX(a, b), c), d);}
S32		ft_imax_2(int a, int b)								{ return  MAX(a, b);}
S32		ft_imax_3(int a, int b, int c)						{ return  MAX(MAX(a, b), c);}
S32		ft_imax_4(int a, int b, int c, int d)				{ return  MAX(MAX(MAX(a, b), c), d);}

F32 	ft_max2(t_v2 a)										{ return  MAX(a.x, a.y); }
t_v2 	ft_max2_2(t_v2 a, t_v2 b)							{ return  vec2(MAX(a.x, b.x), MAX(a.y, b.y)); }
t_v2 	ft_max2_3(t_v2 a, t_v2 b, t_v2 c)					{ return  vec2(MAX(MAX(a.x, b.x), c.x), MAX(MAX(a.y, b.y), c.y)); }
t_v2 	ft_max2_4(t_v2 a, t_v2 b, t_v2 c, t_v2 d)			{ return  vec2(MAX(MAX(MAX(a.x, b.x), c.x), d.x), MAX(MAX(MAX(a.y, b.y), c.y), d.y)); }
S32 	ft_max2i(t_iv2 a)									{ return  MAX(a.x, a.y); }
t_iv2	ft_max2i_2(t_iv2 a, t_iv2 b)						{ return  ivec2(MAX(a.x, b.x), MAX(a.y, b.y)); }
t_iv2	ft_max2i_3(t_iv2 a, t_iv2 b, t_iv2 c)				{ return  ivec2(MAX(MAX(a.x, b.x), c.x), MAX(MAX(a.y, b.y), c.y)); }
t_iv2	ft_max2i_4(t_iv2 a, t_iv2 b, t_iv2 c, t_iv2 d)		{ return  ivec2(MAX(MAX(MAX(a.x, b.x), c.x), d.x), MAX(MAX(MAX(a.y, b.y), c.y), d.y)); }

F32		ft_max3(t_v3 a)										{ return  MAX(MAX(a.x, a.y), a.z); }
t_v3 	ft_max3_2(t_v3 a, t_v3 b)							{ return  vec3(MAX(a.x, b.x), MAX(a.y, b.y), MAX(a.z, b.z)); }
t_v3 	ft_max3_3(t_v3 a, t_v3 b, t_v3 c)					{ return  vec3(MAX(MAX(a.x, b.x), c.x), MAX(MAX(a.y, b.y), c.y), MAX(MAX(a.z, b.z), c.z)); }
t_v3 	ft_max3_4(t_v3 a, t_v3 b, t_v3 c, t_v3 d)			{ return  vec3(MAX(MAX(MAX(a.x, b.x), c.x), d.x), MAX(MAX(MAX(a.y, b.y), c.y), d.y), MAX(MAX(MAX(a.z, b.z), c.z), d.z)); }
S32		ft_max3i(t_iv3 a)									{ return  MAX(MAX(a.x, a.y), a.z); }
t_iv3	ft_max3i_2(t_iv3 a, t_iv3 b)						{ return  ivec3(MAX(a.x, b.x), MAX(a.y, b.y), MAX(a.z, b.z)); }
t_iv3	ft_max3i_3(t_iv3 a, t_iv3 b, t_iv3 c)				{ return  ivec3(MAX(MAX(a.x, b.x), c.x), MAX(MAX(a.y, b.y), c.y), MAX(MAX(a.z, b.z), c.z)); }
t_iv3	ft_max3i_4(t_iv3 a, t_iv3 b, t_iv3 c, t_iv3 d)		{ return  ivec3(MAX(MAX(MAX(a.x, b.x), c.x), d.x), MAX(MAX(MAX(a.y, b.y), c.y), d.y), MAX(MAX(MAX(a.z, b.z), c.z), d.z)); }

F32 	ft_max4(t_v4 a)										{ return  MAX(MAX(MAX(a.x, a.y), a.z), a.w); }
t_v4 	ft_max4_2(t_v4 a, t_v4 b)							{ return  vec4(MAX(a.x, b.x), MAX(a.y, b.y), MAX(a.z, b.z), MAX(a.w, b.w)); }
t_v4 	ft_max4_3(t_v4 a, t_v4 b, t_v4 c)					{ return  vec4(MAX(MAX(a.x, b.x), c.x), MAX(MAX(a.y, b.y), c.y), MAX(MAX(a.z, b.z), c.z), MAX(MAX(a.w, b.w), c.w)); }
t_v4 	ft_max4_4(t_v4 a, t_v4 b, t_v4 c, t_v4 d)			{ return  vec4(MAX(MAX(MAX(a.x, b.x), c.x), d.x), MAX(MAX(MAX(a.y, b.y), c.y), d.y), MAX(MAX(MAX(a.z, b.z), c.z), d.z), MAX(MAX(MAX(a.w, b.w), c.w), d.w)); }
S32 	ft_max4i(t_iv4 a)									{ return  MAX(MAX(MAX(a.x, a.y), a.z), a.w); }
t_iv4 	ft_max4i_2(t_iv4 a, t_iv4 b)						{ return  ivec4(MAX(a.x, b.x), MAX(a.y, b.y), MAX(a.z, b.z), MAX(a.w, b.w)); }
t_iv4 	ft_max4i_3(t_iv4 a, t_iv4 b, t_iv4 c)				{ return  ivec4(MAX(MAX(a.x, b.x), c.x), MAX(MAX(a.y, b.y), c.y), MAX(MAX(a.z, b.z), c.z), MAX(MAX(a.w, b.w), c.w)); }
t_iv4 	ft_max4i_4(t_iv4 a, t_iv4 b, t_iv4 c, t_iv4 d)		{ return  ivec4(MAX(MAX(MAX(a.x, b.x), c.x), d.x), MAX(MAX(MAX(a.y, b.y), c.y), d.y), MAX(MAX(MAX(a.z, b.z), c.z), d.z), MAX(MAX(MAX(a.w, b.w), c.w), d.w)); }
