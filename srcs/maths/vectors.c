/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 22:43:55 by reclaire          #+#    #+#             */
/*   Updated: 2025/03/10 22:50:16 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_int.h"

#include "libft/maths.h"

extern t_v2 vec2(F32 x, F32 y);
extern t_v3 vec3(F32 x, F32 y, F32 z);
extern t_v4 vec4(F32 x, F32 y, F32 z, F32 w);
extern t_iv2 ivec2(S32 x, S32 y);
extern t_iv3 ivec3(S32 x, S32 y, S32 z);
extern t_iv4 ivec4(S32 x, S32 y, S32 z, S32 w);

extern t_iv2 vec2_int(t_v2 v);
extern t_iv3 vec3_int(t_v3 v);
extern t_iv4 vec4_int(t_v4 v);
extern t_v2 ivec2_flt(t_iv2 v);
extern t_v3 ivec3_flt(t_iv3 v);
extern t_v4 ivec4_flt(t_iv4 v);

extern t_v2 vec2_add(t_v2 a, t_v2 b);
extern t_v3 vec3_add(t_v3 a, t_v3 b);
extern t_v4 vec4_add(t_v4 a, t_v4 b);
extern t_iv2 ivec2_add(t_iv2 a, t_iv2 b);
extern t_iv3 ivec3_add(t_iv3 a, t_iv3 b);
extern t_iv4 ivec4_add(t_iv4 a, t_iv4 b);

extern t_v2 vec2_sub(t_v2 a, t_v2 b);
extern t_v3 vec3_sub(t_v3 a, t_v3 b);
extern t_v4 vec4_sub(t_v4 a, t_v4 b);
extern t_iv2 ivec2_sub(t_iv2 a, t_iv2 b);
extern t_iv3 ivec3_sub(t_iv3 a, t_iv3 b);
extern t_iv4 ivec4_sub(t_iv4 a, t_iv4 b);

extern t_v2 vec2_div(t_v2 a, t_v2 b);
extern t_v3 vec3_div(t_v3 a, t_v3 b);
extern t_v4 vec4_div(t_v4 a, t_v4 b);
extern t_iv2 ivec2_div(t_iv2 a, t_iv2 b);
extern t_iv3 ivec3_div(t_iv3 a, t_iv3 b);
extern t_iv4 ivec4_div(t_iv4 a, t_iv4 b);

extern t_v2 vec2_mul(t_v2 a, t_v2 b);
extern t_v3 vec3_mul(t_v3 a, t_v3 b);
extern t_v4 vec4_mul(t_v4 a, t_v4 b);
extern t_iv2 ivec2_mul(t_iv2 a, t_iv2 b);
extern t_iv3 ivec3_mul(t_iv3 a, t_iv3 b);
extern t_iv4 ivec4_mul(t_iv4 a, t_iv4 b);

extern t_v2 vec2_scl(t_v2 a, F32 b);
extern t_v3 vec3_scl(t_v3 a, F32 b);
extern t_v4 vec4_scl(t_v4 a, F32 b);
extern t_iv2 ivec2_scl(t_iv2 a, S32 b);
extern t_iv3 ivec3_scl(t_iv3 a, S32 b);
extern t_iv4 ivec4_scl(t_iv4 a, S32 b);

extern t_iv2 ivec2_mod(t_iv2 a, t_iv2 b);
extern t_iv3 ivec3_mod(t_iv3 a, t_iv3 b);
extern t_iv4 ivec4_mod(t_iv4 a, t_iv4 b);

extern F32 vec2_mag(t_v2 v);
extern F32 vec3_mag(t_v3 v);
extern F32 vec4_mag(t_v4 v);
