/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 19:45:20 by reclaire          #+#    #+#             */
/*   Updated: 2024/07/02 23:05:30 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_MATHS_H
#define LIBFT_MATHS_H

#include "_libft.h"
#include <math.h>

#if !defined(FT_PI)
#define FT_PI 3.14159265358979323846f
#endif /* FT_PI */

#if !defined(FT_DEG_TO_RAD)
#define FT_DEG_TO_RAD 0.01745329251
#endif /* FT_DEG_TO_RAD */
#if !defined(FT_RAD_TO_DEG)
#define FT_RAD_TO_DEG 57.2957795131
#endif /* FT_RAD_TO_DEG */

// https://gcc.gnu.org/onlinedocs/gcc/Other-Builtins.html#index-_005f_005fbuiltin_005finf
//  n = 1 of the bits must be 1
//  ? = either 0 or 1
#define FT_F32_U32(flt) ((union {F32 f; U32 b; }){.f = flt}.b)
#define FT_U32_F32(bits) ((union {F32 f; U32 b; }){.b = bits}.f)

#define FT_F32_PZERO FT_U32_F32(0x00000000) // 0 00000000 00000000000000000000000
#define FT_F32_NZERO FT_U32_F32(0x80000000) // 1 00000000 00000000000000000000000

#ifdef INFINITY
#define FT_F32_PINFINITY INFINITY  // 0 11111111 00000000000000000000000
#define FT_F32_NINFINITY -INFINITY // 1 11111111 00000000000000000000000
#define FT_F32_INF FT_F32_PINFINITY
#else
#define FT_F32_PINFINITY FT_U32_F32(0x7F800000) // 0 11111111 00000000000000000000000
#define FT_F32_NINFINITY FT_U32_F32(0xFF800000) // 1 11111111 00000000000000000000000
#define FT_F32_INF FT_F32_PINFINITY
#endif

#ifdef NAN
#define FT_F32_PQNAN NAN  // 0 11111111 1??????????????????????
#define FT_F32_NQNAN -NAN // 1 11111111 1??????????????????????
#define FT_F32_QNAN FT_F32_PQNAN
#else
#define FT_F32_PQNAN FT_U32_F32(0x7FC00001) // 0 11111111 1??????????????????????
#define FT_F32_NQNAN FT_U32_F32(0xFFC00001) // 1 11111111 1??????????????????????
#define FT_F32_QNAN FT_F32_PQNAN
#endif

#if defined(__has_builtin) && __has_builtin(__builtin_nans)
#define FT_F32_PSNAN __builtin_nansf("")  // 0 11111111 0nnnnnnnnnnnnnnnnnnnnnn
#define FT_F32_NSNAN -__builtin_nansf("") // 1 11111111 0nnnnnnnnnnnnnnnnnnnnnn
#define FT_F32_SNAN FT_F32_PSNAN
#else
#define FT_F32_PSNAN FT_U32_F32(0x7F800001) // 0 11111111 0nnnnnnnnnnnnnnnnnnnnnn
#define FT_F32_NSNAN FT_U32_F32(0xFF800001) // 1 11111111 0nnnnnnnnnnnnnnnnnnnnnn
#define FT_F32_SNAN FT_F32_PSNAN
#endif

#define FT_F32_PIND FT_U32_F32(0x7FC00000) // 0 11111111 10000000000000000000000
#define FT_F32_NIND FT_U32_F32(0xFFC00000) // 1 11111111 10000000000000000000000

#define FT_F32_ISZERO(flt) (FT_F32_U32(flt) == FT_F32_U32(FT_F32_PZERO))
#define FT_F32_ISPZERO(flt) (FT_F32_U32(flt) == FT_F32_U32(FT_F32_PZERO))
#define FT_F32_ISNZERO(flt) (FT_F32_U32(flt) == FT_F32_U32(FT_F32_NZERO))

#define FT_F32_ISINF(flt) (FT_F32_U32(flt) == FT_F32_U32(FT_F32_PINFINITY))
#define FT_F32_ISPINF(flt) (FT_F32_U32(flt) == FT_F32_U32(FT_F32_PINFINITY))
#define FT_F32_ISNINF(flt) (FT_F32_U32(flt) == FT_F32_U32(FT_F32_NINFINITY))

#if defined(__has_builtin) && __has_builtin(__builtin_isnan)
#define FT_F32_ISNAN(flt) (__builtin_isnan(flt))
#else
#define FT_F32_ISNAN(flt) (((FT_F32_U32(flt) & 0x7F800000) == 0x7F800000) && ((FT_F32_U32(flt) & 0x007FFFFF) != 0))
#endif

#if defined(__has_builtin) && __has_builtin(__builtin_issignaling)
#define FT_F32_ISSNAN(flt) (FT_F32_ISNAN(flt) && __builtin_issignaling(flt))
#define FT_F32_ISQNAN(flt) (FT_F32_ISNAN(flt) && !__builtin_issignaling(flt))
#else
#define FT_F32_ISSNAN(flt) (FT_F32_ISNAN(flt) && ((FT_F32_U32(flt) & 0x00400000) == 0))
#define FT_F32_ISQNAN(flt) (FT_F32_ISNAN(flt) && ((FT_F32_U32(flt) & 0x00400000) == 0x00400000))
#endif

#if 0 // Old functions
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

extern t_v2			vec2(float x, float y);
extern t_v3			vec3(float x, float y, float z);
extern t_v4			vec4(float x, float y, float z, float w);
extern t_iv2		ivec2(int x, int y);
extern t_iv3		ivec3(int x, int y, int z);
extern t_iv4		ivec4(int x, int y, int z, int w);
#endif

#define ft_mat4x4_identity          \
	(t_mat4x4)                      \
	{                               \
		1.0f, 0.0f, 0.0f, 0.0f,     \
			0.0f, 1.0f, 0.0f, 0.0f, \
			0.0f, 0.0f, 1.0f, 0.0f, \
			0.0f, 0.0f, 0.0f, 1.0f  \
	}

extern v4f *ft_mat4x4_col(t_mat4x4 *mat, S32 c);
extern F32 *ft_mat4x4_get(t_mat4x4 *mat, S32 r, S32 c);
extern void ft_mat4x4_set_col(t_mat4x4 *mat, S32 c, v4f v);
extern void ft_mat4x4_set_row(t_mat4x4 *mat, S32 r, v4f v);

extern t_mat4x4 ft_mat4x4_transpose(t_mat4x4 mat);
extern t_mat4x4 ft_mat4x4_invert(t_mat4x4 mat);
extern F32 ft_mat4x4_det(t_mat4x4 v);
extern t_mat4x4 ft_mat4x4_perspective(F32 fov, F32 near, F32 far);

extern t_mat4x4 ft_mat4x4_mult_matrix(t_mat4x4 a, t_mat4x4 b);
extern t_mat4x4 ft_mat4x4_mult_flt(t_mat4x4 a, F32 b);
extern v4f ft_mat4x4_mult_v4(t_mat4x4 a, v4f b);

extern t_mat4x4 ft_mat4x4_scale_v2(v2f v);
extern t_mat4x4 ft_mat4x4_scale_v3(v3f v);
extern t_mat4x4 ft_mat4x4_scale_v4(v4f v);
extern t_mat4x4 ft_mat4x4_scale_iv2(v2i v);
extern t_mat4x4 ft_mat4x4_scale_iv3(v3i v);
extern t_mat4x4 ft_mat4x4_scale_iv4(v4i v);

extern t_mat4x4 ft_mat4x4_translate_v2(v2f v);
extern t_mat4x4 ft_mat4x4_translate_v3(v3f v);
extern t_mat4x4 ft_mat4x4_translate_iv2(v2i v);
extern t_mat4x4 ft_mat4x4_translate_iv3(v3i v);

extern t_mat4x4 ft_mat4x4_fit_to_view(v2f pos, v2f size, v2f view_size);

#define ft_cos cos
extern v2f ft_cos2(v2f v);
extern v2i ft_icos2(v2i v);
extern v3f ft_cos3(v3f v);
extern v3i ft_icos3(v3i v);
extern t_v4 ft_cos4(t_v4 v);
extern v4i ft_icos4(v4i v);

#define ft_sin sin
extern v2f ft_sin2(v2f v);
extern v2i ft_isin2(v2i v);
extern v3f ft_sin3(v3f v);
extern v3i ft_isin3(v3i v);
extern t_v4 ft_sin4(t_v4 v);
extern v4i ft_isin4(v4i v);

extern F32 ft_radians(F32 degrees);
extern v2f ft_radians2(v2f degrees);
extern v3f ft_radians3(v3f degrees);
extern t_v4 ft_radians4(t_v4 degrees);
extern v2i ft_iradians2(v2i degrees);
extern v3i ft_iradians3(v3i degrees);
extern v4i ft_iradians4(v4i degrees);

extern F32 ft_degrees(F32 radians);
extern v2f ft_degrees2(v2f radians);
extern v3f ft_degrees3(v3f radians);
extern t_v4 ft_degrees4(t_v4 radians);
extern v2i ft_idegrees2(v2i radians);
extern v3i ft_idegrees3(v3i radians);
extern v4i ft_idegrees4(v4i radians);

extern S32 ft_abs(S32 n);
extern F32 ft_fabs(F32 n);
extern v2f ft_abs2(v2f n);
extern v3f ft_abs3(v3f n);
extern t_v4 ft_abs4(t_v4 n);
extern v2i ft_iabs2(v2i n);
extern v3i ft_iabs3(v3i n);
extern v4i ft_iabs4(v4i n);

// Rotates a 2D vector around origin
extern v2f ft_rotate2(v2f v, F32 angle, v2f origin);

// Returns a random point on a circle of r=1
extern v2f ft_rand_circle(U32 seed);
// Returns a random float between 1 and 0 TODO: bad function, change
extern F32 ft_frand(S32 n);
// Returns a random float between 1 and 0 TODO: bad function, change
extern F32 ft_frand2(v2f st);
// Noise
extern F32 ft_noise2(v2f st);

// Wraps n in [min, max]
extern S32 ft_wrap(S32 n, S32 min, S32 max);
// Wraps n in [min, max]
extern F32 ft_fwrap(F32 x, F32 min, F32 max);
// Returns true if number is between the specified range. (Inclusive)
extern S32 ft_isrange(S32 i, S32 min, S32 max);
// Returns the magnitude of n.
extern U64 ft_magnitude(S64 n);
extern U64 ft_umagnitude(U64 n);
// Check if a number is prime.
extern S32 ft_is_prime(S32 nb);

extern F32 ft_fmin(F32 a, F32 b);
extern F32 ft_fmin_3(F32 a, F32 b, F32 c);
extern F32 ft_fmin_4(F32 a, F32 b, F32 c, F32 d);
extern S32 ft_imin(S32 a, S32 b);
extern S32 ft_imin_3(S32 a, S32 b, S32 c);
extern S32 ft_imin_4(S32 a, S32 b, S32 c, S32 d);

extern v2f ft_fmin2(v2f a, v2f b);
extern v2f ft_fmin2_3(v2f a, v2f b, v2f c);
extern v2f ft_fmin2_4(v2f a, v2f b, v2f c, v2f d);
extern v2i ft_imin2(v2i a, v2i b);
extern v2i ft_imin2_3(v2i a, v2i b, v2i c);
extern v2i ft_imin2_4(v2i a, v2i b, v2i c, v2i d);

extern v3f ft_fmin3(v3f a, v3f b);
extern v3f ft_fmin3_3(v3f a, v3f b, v3f c);
extern v3f ft_fmin3_4(v3f a, v3f b, v3f c, v3f d);
extern v3i ft_imin3(v3i a, v3i b);
extern v3i ft_imin3_3(v3i a, v3i b, v3i c);
extern v3i ft_imin3_4(v3i a, v3i b, v3i c, v3i d);

extern t_v4 ft_fmin4(t_v4 a, t_v4 b);
extern t_v4 ft_fmin4_3(t_v4 a, t_v4 b, t_v4 c);
extern t_v4 ft_fmin4_4(t_v4 a, t_v4 b, t_v4 c, t_v4 d);
extern v4i ft_imin4(v4i a, v4i b);
extern v4i ft_imin4_3(v4i a, v4i b, v4i c);
extern v4i ft_imin4_4(v4i a, v4i b, v4i c, v4i d);

extern F32 ft_fmax(F32 a, F32 b);
extern F32 ft_fmax_3(F32 a, F32 b, F32 c);
extern F32 ft_fmax_4(F32 a, F32 b, F32 c, F32 d);
extern S32 ft_imax(S32 a, S32 b);
extern S32 ft_imax_3(S32 a, S32 b, S32 c);
extern S32 ft_imax_4(S32 a, S32 b, S32 c, S32 d);

extern v2f ft_fmax2(v2f a, v2f b);
extern v2f ft_fmax2_3(v2f a, v2f b, v2f c);
extern v2f ft_fmax2_4(v2f a, v2f b, v2f c, v2f d);
extern v2i ft_imax2(v2i a, v2i b);
extern v2i ft_imax2_3(v2i a, v2i b, v2i c);
extern v2i ft_imax2_4(v2i a, v2i b, v2i c, v2i d);

extern v3f ft_fmax3(v3f a, v3f b);
extern v3f ft_fmax3_3(v3f a, v3f b, v3f c);
extern v3f ft_fmax3_4(v3f a, v3f b, v3f c, v3f d);
extern v3i ft_imax3(v3i a, v3i b);
extern v3i ft_imax3_3(v3i a, v3i b, v3i c);
extern v3i ft_imax3_4(v3i a, v3i b, v3i c, v3i d);

extern t_v4 ft_fmax4(t_v4 a, t_v4 b);
extern t_v4 ft_fmax4_3(t_v4 a, t_v4 b, t_v4 c);
extern t_v4 ft_fmax4_4(t_v4 a, t_v4 b, t_v4 c, t_v4 d);
extern v4i ft_imax4(v4i a, v4i b);
extern v4i ft_imax4_3(v4i a, v4i b, v4i c);
extern v4i ft_imax4_4(v4i a, v4i b, v4i c, v4i d);

extern F32 ft_ceil(F32 n);
extern v2f ft_ceil2(v2f n);
extern v3f ft_ceil3(v3f n);
extern t_v4 ft_ceil4(t_v4 n);

extern F32 ft_lerp(F32 a, F32 b, F32 t);
extern v2f ft_lerp2(v2f a, v2f b, F32 t);
extern v3f ft_lerp3(v3f v_1, v3f v_2, F32 t);
extern t_v4 ft_lerp4(t_v4 v_1, t_v4 v_2, F32 t);

extern S32 ft_lerp_i(S32 a, S32 b, F32 t);
extern v2i ft_lerp2_i(v2i a, v2i b, F32 t);
extern v3i ft_lerp3_i(v3i v_1, v3i v_2, F32 t);
extern v4i ft_lerp4_i(v4i v_1, v4i v_2, F32 t);

extern F32 ft_invlerp(F32 a, F32 b, F32 t);
extern v2f ft_invlerp2(v2f a, v2f b, v2f t);
extern v3f ft_invlerp3(v3f v_1, v3f v_2, v3f t);
extern t_v4 ft_invlerp4(t_v4 v_1, t_v4 v_2, t_v4 t);

extern F32 ft_invlerp_i(S32 a, S32 b, S32 t);
extern v2f ft_invlerp2_i(v2i a, v2i b, v2i t);
extern v3f ft_invlerp3_i(v3i v_1, v3i v_2, v3i t);
extern t_v4 ft_invlerp4_i(v4i v_1, v4i v_2, v4i t);

extern F32 ft_smoothstep(F32 a, F32 b, F32 t);
extern v2f ft_smoothstep2(v2f a, v2f b, v2f t);
extern v3f ft_smoothstep3(v3f v_1, v3f v_2, v3f t);
extern t_v4 ft_smoothstep4(t_v4 v_1, t_v4 v_2, t_v4 t);

// Maps v from range [from.x, from.y] to range [to.x, to.y]
extern F32 ft_map(F32 v, v2f from, v2f to);

// Clamp
extern S32 ft_clamp(S32 min, S32 max, S32 v);
// Clamp for floats
extern F32 ft_clampf(F32 min, F32 max, F32 v);

// Returns the distance from p to line [s1;s2]
extern F32 ft_dist_line(v2f p, v2f s1, v2f s2);
// Distance between 2 2D points
extern F32 ft_dist2(v2f p1, v2f p2);
// Distance between 2 2D points raised to the power of 2
extern F32 ft_sqrdist2(v2f p1, v2f p2);
// Distance between 2 3D points
extern F32 ft_dist3(v3f p1, v3f p2);
// Distance between 2 3D points raised to the power of 2
extern F32 ft_sqrdist3(v3f p1, v3f p2);

// Normalizes a 3D vector
extern v3f ft_normalize3(v3f v);
// Normalizes a 2D vector
extern v2f ft_normalize2(v2f v);
// Dot product of a 2D vector
extern F32 ft_dot2(v2f a, v2f b);
// Dot product of a 3D vector
extern F32 ft_dot3(v3f a, v3f b);
extern v3f ft_cross3(v3f a, v3f b);

// Fractional part of v
extern F32 ft_frac(F32 v);
// Fractional part of v
extern v2f ft_frac2(v2f v);
// Fractional part of v
extern v3f ft_frac3(v3f v);
// Fractional part of v
extern v4f ft_frac4(v4f v);

v2f ft_bezier_interp(v2f p1, v2f p2, v2f p3, F32 t);

#endif
