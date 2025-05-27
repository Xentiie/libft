/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 19:45:20 by reclaire          #+#    #+#             */
/*   Updated: 2025/05/21 23:15:22 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(LIBFT_MATHS_H)
#define LIBFT_MATHS_H

#include "libft/libft.h"

#include <stdlib.h>
#include <math.h>

/* pi */
#define FT_PI 3.1415927f
/* pi * 2 */
#define FT_PI_2 6.2831854f
/* degrees to radians ratio */
#define FT_DEG_TO_RAD 0.017453292f
/* radians to degrees ratio */
#define FT_RAD_TO_DEG 57.295779f

/*
 * https://gcc.gnu.org/onlinedocs/gcc/Other-Builtins.html#index-_005f_005fbuiltin_005finf
 *  n = 1 of the bits must be 1
 *  ? = either 0 or 1
 */

/* Converts a F32 to a U32. */
#define __f32_to_u32(flt) \
	((union {             \
		 F32 f;           \
		 U32 b;           \
	 }){.f = (flt)}       \
		 .b)

/* Converts a U32 to a F32. */
#define __u32_to_f32(bits) \
	((union {              \
		 F32 f;            \
		 U32 b;            \
	 }){.b = (bits)}       \
		 .f)

/* Mask for the sign bit in a F32. */
#define FT_F32_SIGN_BIT_MASK (0x80000000)
/* Mask for the exponant bits in a F32. */
#define FT_F32_EXPONANT_BITS_MASK (0x7F800000)
/* Mask for the fraction bits in a F32. */
#define FT_F32_FRACTION_BITS_MASK (0x007FFFFF)


/*
Zero: bits 1 to 31 sets to 0.
0 00000000 00000000000000000000000: negative zero.
1 00000000 00000000000000000000000: positive zero.
*/

/* Positive zero. */
#define FT_F32_PZERO __u32_to_f32(0x00000000)
/* Negative zero. */
#define FT_F32_NZERO __u32_to_f32(0x00000000 | FT_F32_SIGN_BIT_MASK)

/*
Infinity: bits 24 to 31 sets to 1.
0 11111111 00000000000000000000000: negative infinity.
1 11111111 00000000000000000000000: positive infinity.
*/

#if defined(INFINITY)
/* Positive infinity. */
#define FT_F32_PINFINITY INFINITY
/* Negative infinity. */
#define FT_F32_NINFINITY -INFINITY
/* Alias for FT_F32_PINFINITY (positive infinity). */
#define FT_F32_INF FT_F32_PINFINITY
#else
/* Positive infinity. */
#define FT_F32_PINFINITY __u32_to_f32(FT_F32_EXPONANT_BITS_MASK)
/* Negative infinity. */
#define FT_F32_NINFINITY __u32_to_f32(FT_F32_EXPONANT_BITS_MASK | FT_F32_SIGN_BIT_MASK)
/* Alias for FT_F32_PINFINITY (positive infinity). */
#define FT_F32_INF FT_F32_PINFINITY
#endif

/*
Infinity: bits 24 to 31 sets to 1.
0 11111111 00000000000000000000000: negative infinity.
1 11111111 00000000000000000000000: positive infinity.
*/

#if defined(NAN)
#define FT_F32_PQNAN NAN  /* 0 11111111 1?????????????????????? */
#define FT_F32_NQNAN -NAN /* 1 11111111 1?????????????????????? */
#define FT_F32_QNAN FT_F32_PQNAN
#else
#define FT_F32_PQNAN __u32_to_f32(0x7FC00001) /* 0 11111111 1?????????????????????? */
#define FT_F32_NQNAN __u32_to_f32(0xFFC00001) /* 1 11111111 1?????????????????????? */
#define FT_F32_QNAN FT_F32_PQNAN
#endif

#if FT_HAS_BUILTIN(__builtin_nans)
#define FT_F32_PSNAN __builtin_nansf("")  /* 0 11111111 0nnnnnnnnnnnnnnnnnnnnnn */
#define FT_F32_NSNAN -__builtin_nansf("") /* 1 11111111 0nnnnnnnnnnnnnnnnnnnnnn */
#define FT_F32_SNAN FT_F32_PSNAN
#else
#define FT_F32_PSNAN __u32_to_f32(0x7F800001) /* 0 11111111 0nnnnnnnnnnnnnnnnnnnnnn */
#define FT_F32_NSNAN __u32_to_f32(0xFF800001) /* 1 11111111 0nnnnnnnnnnnnnnnnnnnnnn */
#define FT_F32_SNAN FT_F32_PSNAN
#endif

#define FT_F32_PIND __u32_to_f32(0x7FC00000) /* 0 11111111 10000000000000000000000 */
#define FT_F32_NIND __u32_to_f32(0xFFC00000) /* 1 11111111 10000000000000000000000 */

#define FT_F32_ISZERO(flt) (__f32_to_u32(flt) == __f32_to_u32(FT_F32_PZERO))
#define FT_F32_ISPZERO(flt) (__f32_to_u32(flt) == __f32_to_u32(FT_F32_PZERO))
#define FT_F32_ISNZERO(flt) (__f32_to_u32(flt) == __f32_to_u32(FT_F32_NZERO))

#define FT_F32_ISINF(flt) (__f32_to_u32(flt) == __f32_to_u32(FT_F32_PINFINITY))
#define FT_F32_ISPINF(flt) (__f32_to_u32(flt) == __f32_to_u32(FT_F32_PINFINITY))
#define FT_F32_ISNINF(flt) (__f32_to_u32(flt) == __f32_to_u32(FT_F32_NINFINITY))

#if FT_HAS_BUILTIN(__builtin_isnan)
#define FT_F32_ISNAN(flt) (__builtin_isnan(flt))
#else
#define FT_F32_ISNAN(flt) \
	(((__f32_to_u32(flt) & 0x7F800000) == 0x7F800000) && ((__f32_to_u32(flt) & 0x007FFFFF) != 0))
#endif

#if FT_HAS_BUILTIN(__builtin_issignaling)
#define FT_F32_ISSNAN(flt) (FT_F32_ISNAN(flt) && __builtin_issignaling(flt))
#define FT_F32_ISQNAN(flt) (FT_F32_ISNAN(flt) && !__builtin_issignaling(flt))
#else
#define FT_F32_ISSNAN(flt) (FT_F32_ISNAN(flt) && ((__f32_to_u32(flt) & 0x00400000) == 0))
#define FT_F32_ISQNAN(flt) (FT_F32_ISNAN(flt) && ((__f32_to_u32(flt) & 0x00400000) == 0x00400000))
#endif

/* Returns a new `t_v2`, with elements set to `x` and `y`. */
inline ALWAYS_INLINE t_v2 vec2(F32 x, F32 y) { return (t_v2){.x = x, .y = y}; }
/* Returns a new `t_v3`, with elements set to `x`, `y` and `z`. */
inline ALWAYS_INLINE t_v3 vec3(F32 x, F32 y, F32 z) { return (t_v3){.x = x, .y = y, .z = z}; }
/* Returns a new `t_v4`, with elements set to `x`, `y`, `z` and `w`. */
inline ALWAYS_INLINE t_v4 vec4(F32 x, F32 y, F32 z, F32 w) { return (t_v4){.x = x, .y = y, .z = z, .w = w}; }
/* Returns a new `t_iv2`, with elements set to `x` and `y`. */
inline ALWAYS_INLINE t_iv2 ivec2(S32 x, S32 y) { return (t_iv2){.x = x, .y = y}; }
/* Returns a new `t_iv3`, with elements set to `x`, `y` and `z`. */
inline ALWAYS_INLINE t_iv3 ivec3(S32 x, S32 y, S32 z) { return (t_iv3){.x = x, .y = y, .z = z}; }
/* Returns a new `t_iv4`, with elements set to `x`, `y`, `z` and `w`. */
inline ALWAYS_INLINE t_iv4 ivec4(S32 x, S32 y, S32 z, S32 w) { return (t_iv4){.x = x, .y = y, .z = z, .w = w}; }

/* `t_v2`, with all elements set to 0. */
#define vec2_zero vec2(0, 0)
/* `t_v2`, with all elements set to 1. */
#define vec2_one vec2(1, 1)
/* `t_v2`, with all elements set to 2. */
#define vec2_two vec2(2, 2)

/* `t_v3`, with all elements set to 0. */
#define vec3_zero vec3(0, 0, 0)
/* `t_v3`, with all elements set to 1. */
#define vec3_one vec3(1, 1, 1)
/* `t_v3`, with all elements set to 2. */
#define vec3_two vec3(2, 2, 2)

/* `t_v4`, with all elements set to 0. */
#define vec4_zero vec4(0, 0, 0, 0)
/* `t_v4`, with all elements set to 1. */
#define vec4_one vec4(1, 1, 1, 1)
/* `t_v4`, with all elements set to 2. */
#define vec4_two vec4(2, 2, 2, 2)

/* `t_iv2`, with all elements set to 0. */
#define ivec2_zero ivec2(0, 0)
/* `t_iv2`, with all elements set to 1. */
#define ivec2_one ivec2(1, 1)
/* `t_iv2`, with all elements set to 2. */
#define ivec2_two ivec2(2, 2)

/* `t_iv3`, with all elements set to 0. */
#define ivec3_zero ivec3(0, 0, 0)
/* `t_iv3`, with all elements set to 1. */
#define ivec3_one ivec3(1, 1, 1)
/* `t_iv3`, with all elements set to 2. */
#define ivec3_two ivec3(2, 2, 2)

/* `t_iv4`, with all elements set to 0. */
#define ivec4_zero ivec4(0, 0, 0, 0)
/* `t_iv4`, with all elements set to 1. */
#define ivec4_one ivec4(1, 1, 1, 1)
/* `t_iv4`, with all elements set to 2. */
#define ivec4_two ivec4(2, 2, 2, 2)

/* Converts a `t_v2` to a `t_iv2`. */
inline ALWAYS_INLINE t_iv2 vec2_int(t_v2 v) { return ivec2(v.x, v.y); }
/* Converts a `t_v3` to a `t_iv3`. */
inline ALWAYS_INLINE t_iv3 vec3_int(t_v3 v) { return ivec3(v.x, v.y, v.z); }
/* Converts a `t_v4` to a `t_iv4`. */
inline ALWAYS_INLINE t_iv4 vec4_int(t_v4 v) { return ivec4(v.x, v.y, v.z, v.w); }
/* Converts a `t_iv2` to a `t_v2`. */
inline ALWAYS_INLINE t_v2 ivec2_flt(t_iv2 v) { return vec2(v.x, v.y); }
/* Converts a `t_iv3` to a `t_v3`. */
inline ALWAYS_INLINE t_v3 ivec3_flt(t_iv3 v) { return vec3(v.x, v.y, v.z); }
/* Converts a `t_iv4` to a `t_v4`. */
inline ALWAYS_INLINE t_v4 ivec4_flt(t_iv4 v) { return vec4(v.x, v.y, v.z, v.w); }

/* Performs element-wise addition of `a` and `b`. */
inline ALWAYS_INLINE t_v2 vec2_add(t_v2 a, t_v2 b) { return vec2(a.x + b.x, a.y + b.y); }
/* Performs element-wise addition of `a` and `b`. */
inline ALWAYS_INLINE t_v3 vec3_add(t_v3 a, t_v3 b) { return vec3(a.x + b.x, a.y + b.y, a.z + b.z); }
/* Performs element-wise addition of `a` and `b`. */
inline ALWAYS_INLINE t_v4 vec4_add(t_v4 a, t_v4 b) { return vec4(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w); }
/* Performs element-wise addition of `a` and `b`. */
inline ALWAYS_INLINE t_iv2 ivec2_add(t_iv2 a, t_iv2 b) { return ivec2(a.x + b.x, a.y + b.y); }
/* Performs element-wise addition of `a` and `b`. */
inline ALWAYS_INLINE t_iv3 ivec3_add(t_iv3 a, t_iv3 b) { return ivec3(a.x + b.x, a.y + b.y, a.z + b.z); }
/* Performs element-wise addition of `a` and `b`. */
inline ALWAYS_INLINE t_iv4 ivec4_add(t_iv4 a, t_iv4 b) { return ivec4(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w); }

/* Performs element-wise subtraction of `b` from `a`. */
inline ALWAYS_INLINE t_v2 vec2_sub(t_v2 a, t_v2 b) { return vec2(a.x - b.x, a.y - b.y); }
/* Performs element-wise subtraction of `b` from `a`. */
inline ALWAYS_INLINE t_v3 vec3_sub(t_v3 a, t_v3 b) { return vec3(a.x - b.x, a.y - b.y, a.z - b.z); }
/* Performs element-wise subtraction of `b` from `a`. */
inline ALWAYS_INLINE t_v4 vec4_sub(t_v4 a, t_v4 b) { return vec4(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w); }
/* Performs element-wise subtraction of `b` from `a`. */
inline ALWAYS_INLINE t_iv2 ivec2_sub(t_iv2 a, t_iv2 b) { return ivec2(a.x - b.x, a.y - b.y); }
/* Performs element-wise subtraction of `b` from `a`. */
inline ALWAYS_INLINE t_iv3 ivec3_sub(t_iv3 a, t_iv3 b) { return ivec3(a.x - b.x, a.y - b.y, a.z - b.z); }
/* Performs element-wise subtraction of `b` from `a`. */
inline ALWAYS_INLINE t_iv4 ivec4_sub(t_iv4 a, t_iv4 b) { return ivec4(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w); }

/* Performs element-wise division of `a` by `b`. */
inline ALWAYS_INLINE t_v2 vec2_div(t_v2 a, t_v2 b) { return vec2(a.x / b.x, a.y / b.y); }
/* Performs element-wise division of `a` by `b`. */
inline ALWAYS_INLINE t_v3 vec3_div(t_v3 a, t_v3 b) { return vec3(a.x / b.x, a.y / b.y, a.z / b.z); }
/* Performs element-wise division of `a` by `b`. */
inline ALWAYS_INLINE t_v4 vec4_div(t_v4 a, t_v4 b) { return vec4(a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w); }
/* Performs element-wise division of `a` by `b`. */
inline ALWAYS_INLINE t_iv2 ivec2_div(t_iv2 a, t_iv2 b) { return ivec2(a.x / b.x, a.y / b.y); }
/* Performs element-wise division of `a` by `b`. */
inline ALWAYS_INLINE t_iv3 ivec3_div(t_iv3 a, t_iv3 b) { return ivec3(a.x / b.x, a.y / b.y, a.z / b.z); }
/* Performs element-wise division of `a` by `b`. */
inline ALWAYS_INLINE t_iv4 ivec4_div(t_iv4 a, t_iv4 b) { return ivec4(a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w); }

/* Performs element-wise multiplication of `a` and `b`. */
inline ALWAYS_INLINE t_v2 vec2_mul(t_v2 a, t_v2 b) { return vec2(a.x * b.x, a.y * b.y); }
/* Performs element-wise multiplication of `a` and `b`. */
inline ALWAYS_INLINE t_v3 vec3_mul(t_v3 a, t_v3 b) { return vec3(a.x * b.x, a.y * b.y, a.z * b.z); }
/* Performs element-wise multiplication of `a` and `b`. */
inline ALWAYS_INLINE t_v4 vec4_mul(t_v4 a, t_v4 b) { return vec4(a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w); }
/* Performs element-wise multiplication of `a` and `b`. */
inline ALWAYS_INLINE t_iv2 ivec2_mul(t_iv2 a, t_iv2 b) { return ivec2(a.x * b.x, a.y * b.y); }
/* Performs element-wise multiplication of `a` and `b`. */
inline ALWAYS_INLINE t_iv3 ivec3_mul(t_iv3 a, t_iv3 b) { return ivec3(a.x * b.x, a.y * b.y, a.z * b.z); }
/* Performs element-wise multiplication of `a` and `b`. */
inline ALWAYS_INLINE t_iv4 ivec4_mul(t_iv4 a, t_iv4 b) { return ivec4(a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w); }

/* Multiplies all elements of `a` with `b`. */
inline ALWAYS_INLINE t_v2 vec2_scl(t_v2 a, F32 b) { return vec2(a.x * b, a.y * b); }
/* Multiplies all elements of `a` with `b`. */
inline ALWAYS_INLINE t_v3 vec3_scl(t_v3 a, F32 b) { return vec3(a.x * b, a.y * b, a.z * b); }
/* Multiplies all elements of `a` with `b`. */
inline ALWAYS_INLINE t_v4 vec4_scl(t_v4 a, F32 b) { return vec4(a.x * b, a.y * b, a.z * b, a.w * b); }
/* Multiplies all elements of `a` with `b`. */
inline ALWAYS_INLINE t_iv2 ivec2_scl(t_iv2 a, S32 b) { return ivec2(a.x * b, a.y * b); }
/* Multiplies all elements of `a` with `b`. */
inline ALWAYS_INLINE t_iv3 ivec3_scl(t_iv3 a, S32 b) { return ivec3(a.x * b, a.y * b, a.z * b); }
/* Multiplies all elements of `a` with `b`. */
inline ALWAYS_INLINE t_iv4 ivec4_scl(t_iv4 a, S32 b) { return ivec4(a.x * b, a.y * b, a.z * b, a.w * b); }

/* Performs element-wise modulo of `a` and `b`. */
inline ALWAYS_INLINE t_iv2 ivec2_mod(t_iv2 a, t_iv2 b) { return ivec2(a.x % b.x, a.y % b.y); }
/* Performs element-wise modulo of `a` and `b`. */
inline ALWAYS_INLINE t_iv3 ivec3_mod(t_iv3 a, t_iv3 b) { return ivec3(a.x % b.x, a.y % b.y, a.z % b.z); }
/* Performs element-wise modulo of `a` and `b`. */
inline ALWAYS_INLINE t_iv4 ivec4_mod(t_iv4 a, t_iv4 b) { return ivec4(a.x % b.x, a.y % b.y, a.z % b.z, a.w % b.w); }

/* Computes the magnitude of `v`. */
inline ALWAYS_INLINE F32 vec2_mag(t_v2 v) { return sqrt(v.x * v.x + v.y * v.y); }
/* Computes the magnitude of `v`. */
inline ALWAYS_INLINE F32 vec3_mag(t_v3 v) { return sqrt(v.x * v.x + v.y * v.y + v.z * v.z); }
/* Computes the magnitude of `v`. */
inline ALWAYS_INLINE F32 vec4_mag(t_v4 v) { return sqrt(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w); }

/* Returns the fractional part of `v`. */
inline ALWAYS_INLINE F32 ft_frac(F32 v) { return (v - ((S64)v)); }
inline ALWAYS_INLINE t_v2 ft_frac2(t_v2 v) { return (vec2(ft_frac(v.x), ft_frac(v.y))); }

#define ft_sin sin
inline ALWAYS_INLINE t_v2 ft_sin2(t_v2 v) { return (vec2(ft_sin(v.x), ft_sin(v.y))); }
inline ALWAYS_INLINE t_v3 ft_sin3(t_v3 v) { return (vec3(ft_sin(v.x), ft_sin(v.y), ft_sin(v.z))); }
inline ALWAYS_INLINE t_v4 ft_sin4(t_v4 v) { return (vec4(ft_sin(v.x), ft_sin(v.y), ft_sin(v.z), ft_sin(v.w))); }
inline ALWAYS_INLINE t_iv2 ft_isin2(t_iv2 v) { return (ivec2(ft_sin(v.x), ft_sin(v.y))); }
inline ALWAYS_INLINE t_iv3 ft_isin3(t_iv3 v) { return (ivec3(ft_sin(v.x), ft_sin(v.y), ft_sin(v.z))); }
inline ALWAYS_INLINE t_iv4 ft_isin4(t_iv4 v) { return (ivec4(ft_sin(v.x), ft_sin(v.y), ft_sin(v.z), ft_sin(v.w))); }

#define ft_cos cos
inline ALWAYS_INLINE t_v2 ft_cos2(t_v2 v) { return (vec2(ft_cos(v.x), ft_cos(v.y))); }
inline ALWAYS_INLINE t_v3 ft_cos3(t_v3 v) { return (vec3(ft_cos(v.x), ft_cos(v.y), ft_cos(v.z))); }
inline ALWAYS_INLINE t_v4 ft_cos4(t_v4 v) { return (vec4(ft_cos(v.x), ft_cos(v.y), ft_cos(v.z), ft_cos(v.w))); }
inline ALWAYS_INLINE t_iv2 ft_icos2(t_iv2 v) { return (ivec2(ft_cos(v.x), ft_cos(v.y))); }
inline ALWAYS_INLINE t_iv3 ft_icos3(t_iv3 v) { return (ivec3(ft_cos(v.x), ft_cos(v.y), ft_cos(v.z))); }
inline ALWAYS_INLINE t_iv4 ft_icos4(t_iv4 v) { return (ivec4(ft_cos(v.x), ft_cos(v.y), ft_cos(v.z), ft_cos(v.w))); }

inline ALWAYS_INLINE F32 ft_degrees(F32 radians) { return (radians * FT_RAD_TO_DEG); }
inline ALWAYS_INLINE t_v2 ft_degrees2(t_v2 radians) { return vec2(radians.x * FT_RAD_TO_DEG, radians.y * FT_RAD_TO_DEG); }
inline ALWAYS_INLINE t_v3 ft_degrees3(t_v3 radians) { return vec3(radians.x * FT_RAD_TO_DEG, radians.y * FT_RAD_TO_DEG, radians.z * FT_RAD_TO_DEG); }
inline ALWAYS_INLINE t_v4 ft_degrees4(t_v4 radians) { return vec4(radians.x * FT_RAD_TO_DEG, radians.y * FT_RAD_TO_DEG, radians.z * FT_RAD_TO_DEG, radians.w * FT_RAD_TO_DEG); }
inline ALWAYS_INLINE t_iv2 ft_idegrees2(t_iv2 radians) { return ivec2(radians.x * FT_RAD_TO_DEG, radians.y * FT_RAD_TO_DEG); }
inline ALWAYS_INLINE t_iv3 ft_idegrees3(t_iv3 radians) { return ivec3(radians.x * FT_RAD_TO_DEG, radians.y * FT_RAD_TO_DEG, radians.z * FT_RAD_TO_DEG); }
inline ALWAYS_INLINE t_iv4 ft_idegrees4(t_iv4 radians) { return ivec4(radians.x * FT_RAD_TO_DEG, radians.y * FT_RAD_TO_DEG, radians.z * FT_RAD_TO_DEG, radians.w * FT_RAD_TO_DEG); }

inline ALWAYS_INLINE F32 ft_radians(F32 degrees) { return (degrees * FT_DEG_TO_RAD); }
inline ALWAYS_INLINE t_v2 ft_radians2(t_v2 degrees) { return (vec2(degrees.x * FT_DEG_TO_RAD, degrees.y * FT_DEG_TO_RAD)); }
inline ALWAYS_INLINE t_v3 ft_radians3(t_v3 degrees) { return (vec3(degrees.x * FT_DEG_TO_RAD, degrees.y * FT_DEG_TO_RAD, degrees.z * FT_DEG_TO_RAD)); }
inline ALWAYS_INLINE t_v4 ft_radians4(t_v4 degrees) { return (vec4(degrees.x * FT_DEG_TO_RAD, degrees.y * FT_DEG_TO_RAD, degrees.z * FT_DEG_TO_RAD, degrees.w * FT_DEG_TO_RAD)); }
inline ALWAYS_INLINE t_iv2 ft_iradians2(t_iv2 degrees) { return (ivec2(degrees.x * FT_DEG_TO_RAD, degrees.y * FT_DEG_TO_RAD)); }
inline ALWAYS_INLINE t_iv3 ft_iradians3(t_iv3 degrees) { return (ivec3(degrees.x * FT_DEG_TO_RAD, degrees.y * FT_DEG_TO_RAD, degrees.z * FT_DEG_TO_RAD)); }
inline ALWAYS_INLINE t_iv4 ft_iradians4(t_iv4 degrees) { return (ivec4(degrees.x * FT_DEG_TO_RAD, degrees.y * FT_DEG_TO_RAD, degrees.z * FT_DEG_TO_RAD, degrees.w * FT_DEG_TO_RAD)); }

inline ALWAYS_INLINE S32 ft_abs(S32 n) { return abs(n); }
inline ALWAYS_INLINE F32 ft_fabs(F32 n) { return fabs(n); }
inline ALWAYS_INLINE t_v2 ft_abs2(t_v2 n) { return vec2(fabs(n.x), fabs(n.y)); }
inline ALWAYS_INLINE t_v3 ft_abs3(t_v3 n) { return vec3(fabs(n.x), fabs(n.y), fabs(n.z)); }
inline ALWAYS_INLINE t_v4 ft_abs4(t_v4 n) { return vec4(fabs(n.x), fabs(n.y), fabs(n.z), fabs(n.w)); }
inline ALWAYS_INLINE t_iv2 ft_iabs2(t_iv2 n) { return ivec2(abs(n.x), abs(n.y)); }
inline ALWAYS_INLINE t_iv3 ft_iabs3(t_iv3 n) { return ivec3(abs(n.x), abs(n.y), abs(n.z)); }
inline ALWAYS_INLINE t_iv4 ft_iabs4(t_iv4 n) { return ivec4(abs(n.x), abs(n.y), abs(n.z), abs(n.w)); }

inline ALWAYS_INLINE F32 ft_fmin(F32 a, F32 b) { return a < b ? a : b; }
inline ALWAYS_INLINE S32 ft_min(S32 a, S32 b) { return a < b ? a : b; }
inline ALWAYS_INLINE F32 ft_fmax(F32 a, F32 b) { return a > b ? a : b; }
inline ALWAYS_INLINE S32 ft_max(S32 a, S32 b) { return a > b ? a : b; }

inline ALWAYS_INLINE F32 ft_ceil(F32 n) { return ceilf(n); }
inline ALWAYS_INLINE t_v2 ft_ceil2(t_v2 n) { return vec2(ceilf(n.x), ceilf(n.y)); }
inline ALWAYS_INLINE t_v3 ft_ceil3(t_v3 n) { return vec3(ceilf(n.x), ceilf(n.y), ceilf(n.z)); }
inline ALWAYS_INLINE t_v4 ft_ceil4(t_v4 n) { return vec4(ceilf(n.x), ceilf(n.y), ceilf(n.z), ceilf(n.w)); }

inline ALWAYS_INLINE F32 ft_floor(F32 n) { return floorf(n); }
inline ALWAYS_INLINE t_v2 ft_floor2(t_v2 n) { return vec2(floorf(n.x), floorf(n.y)); }
inline ALWAYS_INLINE t_v3 ft_floor3(t_v3 n) { return vec3(floorf(n.x), floorf(n.y), floorf(n.z)); }
inline ALWAYS_INLINE t_v4 ft_floor4(t_v4 n) { return vec4(floorf(n.x), floorf(n.y), floorf(n.z), floorf(n.w)); }

inline ALWAYS_INLINE S32 ft_clamp(S32 min, S32 max, S32 v) { return ft_max(min, ft_min(max, v)); }
inline ALWAYS_INLINE F32 ft_clampf(F32 min, F32 max, F32 v) { return ft_fmax(min, ft_fmin(max, v)); }

/* Returns a random point on a circle of r=1 */
extern t_v2 ft_rand_circle(U32 seed);
/* Returns a random float between 1 and 0 TODO: bad function, change */
extern F32 ft_frand(S32 n);
/* Returns a random float between 1 and 0 TODO: bad function, change */
extern F32 ft_frand2(t_v2 st);
/* Noise */
extern F32 ft_noise2(t_v2 st);

/* Wraps n in [min, max] */
extern S32 ft_wrap(S32 n, S32 min, S32 max);
/* Wraps n in [min, max] */
extern F32 ft_fwrap(F32 x, F32 min, F32 max);
extern U64 ft_numsize(S64 n);
extern U64 ft_unumsize(U64 n);
/* Check if a number is prime. */
extern S32 ft_is_prime(S32 nb);

/* Maps v from range [from.x, from.y] to range [to.x, to.y] */
extern F32 ft_map(F32 v, t_v2 from, t_v2 to);

extern t_v2 ft_normalize2(t_v2 v);
extern t_v3 ft_normalize3(t_v3 v);

inline F32 ft_dot2(t_v2 a, t_v2 b) { return (a.x * b.x + a.y * b.y); }
inline F32 ft_dot3(t_v3 a, t_v3 b) { return (a.x * b.x + a.y * b.y + a.z * b.z); }
/* Dot product of a 3D vector stored in t_v4 */
inline F32 ft_dot3_4(t_v4 a, t_v4 b) { return (a.x * b.x + a.y * b.y + a.z * b.z); }

inline t_v3 ft_cross3(t_v3 a, t_v3 b) { return vec3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x); }
inline F32 ft_sqrdist2(t_v2 p1, t_v2 p2) { return (powf(p1.x - p2.x, 2) + powf(p1.y - p2.y, 2)); }
inline F32 ft_sqrdist3(t_v3 p1, t_v3 p2) { return (powf(p1.x - p2.x, 2) + powf(p1.y - p2.y, 2) + powf(p1.y - p2.y, 2)); }
inline F32 ft_dist2(t_v2 p1, t_v2 p2) { return (sqrtf(ft_sqrdist2(p1, p2))); }
inline F32 ft_dist3(t_v3 p1, t_v3 p2) { return (sqrtf(ft_sqrdist3(p1, p2))); }

/* Returns the distance from p to line [s1;s2] */
extern F32 ft_dist_line(t_v2 p, t_v2 s1, t_v2 s2);
/* Returns TRUE if line is entirely inside rect, FALSE if a part of a line has been clipped */
extern bool ft_clip_line_rect(t_iv2 *p1, t_iv2 *p2, t_iv4 rect);
/* Returns TRUE if line is entirely inside rect, FALSE if a part of a line has been clipped */
extern bool ft_clip_line_rect_flt(t_v2 *p1, t_v2 *p2, t_v4 rect);

/* Rotates a 2D vector around origin */
extern t_v2 ft_rotate2(t_v2 v, F32 angle, t_v2 origin);

inline F32 ft_lerp(F32 x, F32 y, F32 t) { return (x + ft_clampf(0, 1, t) * (y - x)); }
inline t_v2 ft_lerp2(t_v2 v_1, t_v2 v_2, F32 t) { return (vec2(ft_lerp(v_1.x, v_2.x, t), ft_lerp(v_1.y, v_2.y, t))); }
inline t_v3 ft_lerp3(t_v3 v_1, t_v3 v_2, F32 t) { return (vec3(ft_lerp(v_1.x, v_2.x, t), ft_lerp(v_1.y, v_2.y, t), ft_lerp(v_1.z, v_2.z, t))); }
inline t_v4 ft_lerp4(t_v4 v_1, t_v4 v_2, F32 t) { return (vec4(ft_lerp(v_1.x, v_2.x, t), ft_lerp(v_1.y, v_2.y, t), ft_lerp(v_1.z, v_2.z, t), ft_lerp(v_1.w, v_2.w, t))); }

inline S32 ft_lerp_i(S32 x, S32 y, F32 t) { return (x + ft_clampf(0, 1, t) * (y - x)); }
inline t_iv2 ft_lerp2_i(t_iv2 v_1, t_iv2 v_2, F32 t) { return (ivec2(ft_lerp_i(v_1.x, v_2.x, t), ft_lerp_i(v_1.y, v_2.y, t))); }
inline t_iv3 ft_lerp3_i(t_iv3 v_1, t_iv3 v_2, F32 t) { return (ivec3(ft_lerp_i(v_1.x, v_2.x, t), ft_lerp_i(v_1.y, v_2.y, t), ft_lerp_i(v_1.z, v_2.z, t))); }
inline t_iv4 ft_lerp4_i(t_iv4 v_1, t_iv4 v_2, F32 t) { return (ivec4(ft_lerp_i(v_1.x, v_2.x, t), ft_lerp_i(v_1.y, v_2.y, t), ft_lerp_i(v_1.z, v_2.z, t), ft_lerp_i(v_1.w, v_2.w, t))); }

inline F32 ft_invlerp(F32 a, F32 b, F32 value)
{
	if (b - a == 0)
		return 0;
	return ((value - a) / (b - a));
}
inline t_v2 ft_invlerp2(t_v2 a, t_v2 b, t_v2 t) { return (vec2(ft_invlerp(a.x, b.x, t.x), ft_invlerp(a.y, b.y, t.y))); }
inline t_v3 ft_invlerp3(t_v3 a, t_v3 b, t_v3 t) { return (vec3(ft_invlerp(a.x, b.x, t.x), ft_invlerp(a.y, b.y, t.y), ft_invlerp(a.z, b.z, t.z))); }
inline t_v4 ft_invlerp4(t_v4 a, t_v4 b, t_v4 t) { return (vec4(ft_invlerp(a.x, b.x, t.x), ft_invlerp(a.y, b.y, t.y), ft_invlerp(a.z, b.z, t.z), ft_invlerp(a.w, b.w, t.w))); }

inline F32 ft_invlerp_i(S32 a, S32 b, S32 value)
{
	if (b - a == 0)
		return 0;
	return ((F32)(value - a) / (F32)(b - a));
}
inline t_v2 ft_invlerp2_i(t_iv2 a, t_iv2 b, t_iv2 t) { return (vec2(ft_invlerp_i(a.x, b.x, t.x), ft_invlerp_i(a.y, b.y, t.y))); }
inline t_v3 ft_invlerp3_i(t_iv3 a, t_iv3 b, t_iv3 t) { return (vec3(ft_invlerp_i(a.x, b.x, t.x), ft_invlerp_i(a.y, b.y, t.y), ft_invlerp_i(a.z, b.z, t.z))); }
inline t_v4 ft_invlerp4_i(t_iv4 a, t_iv4 b, t_iv4 t) { return (vec4(ft_invlerp_i(a.x, b.x, t.x), ft_invlerp_i(a.y, b.y, t.y), ft_invlerp_i(a.z, b.z, t.z), ft_invlerp_i(a.w, b.w, t.w))); }

extern F32 ft_smoothstep(F32 a, F32 b, F32 t);
extern t_v2 ft_smoothstep2(t_v2 a, t_v2 b, t_v2 t);
extern t_v3 ft_smoothstep3(t_v3 v_1, t_v3 v_2, t_v3 t);
extern t_v4 ft_smoothstep4(t_v4 v_1, t_v4 v_2, t_v4 t);

inline t_v2 ft_bezier_interp(t_v2 p1, t_v2 p2, t_v2 p3, F32 t)
{
	F32 t_inv;

	t_inv = 1.0f - t;
	return vec2(
		((t_inv * t_inv) * p1.x) + ((2 * t) * t_inv * p2.x) + ((t * t) * p3.x),
		((t_inv * t_inv) * p1.y) + ((2 * t) * t_inv * p2.y) + ((t * t) * p3.y));
}

inline t_iv2 ft_irectsize(t_iv4 rect) { return ivec2(rect.z - rect.x, rect.w - rect.y); }
inline t_v2 ft_rectsize(t_v4 rect) { return vec2(rect.z - rect.x, rect.w - rect.y); }
inline t_iv4 ft_clip_rect_rect(t_iv4 rect, t_iv4 bound) { return ivec4(ft_max(rect.x, bound.x), ft_max(rect.y, bound.y), ft_min(rect.z, bound.z), ft_min(rect.w, bound.w)); }
inline t_v4 ft_clip_rect_rect_flt(t_v4 rect, t_v4 bound) { return vec4(ft_fmax(rect.x, bound.x), ft_fmax(rect.y, bound.y), ft_fmin(rect.z, bound.z), ft_fmin(rect.w, bound.w)); }

extern t_v4 ft_plane_eq(t_v3 p1, t_v3 p2, t_v3 p3);

#define ft_mat4x4_identity                                     \
	(t_mat4x4){1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, \
			   0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f}

extern t_v4 *ft_mat4x4_col(t_mat4x4 *mat, S32 c);
extern F32 *ft_mat4x4_get(t_mat4x4 *mat, S32 r, S32 c);
extern void ft_mat4x4_set_col(t_mat4x4 *mat, S32 c, t_v4 v);
extern void ft_mat4x4_set_row(t_mat4x4 *mat, S32 r, t_v4 v);

extern t_mat4x4 ft_mat4x4_transpose(t_mat4x4 mat);
extern t_mat4x4 ft_mat4x4_invert(t_mat4x4 mat);
extern F32 ft_mat4x4_det(t_mat4x4 v);
extern t_mat4x4 ft_mat4x4_perspective(F32 fov, F32 near, F32 far);

extern t_mat4x4 ft_mat4x4_mult_mat(t_mat4x4 a, t_mat4x4 b);
extern t_mat4x4 ft_mat4x4_mult_float(t_mat4x4 a, F32 b);
extern t_v4 ft_mat4x4_mult_v4(t_mat4x4 a, t_v4 b);

extern t_mat4x4 ft_mat4x4_scale_v2(t_v2 v);
extern t_mat4x4 ft_mat4x4_scale_v3(t_v3 v);
extern t_mat4x4 ft_mat4x4_scale_v4(t_v4 v);
extern t_mat4x4 ft_mat4x4_scale_iv2(t_iv2 v);
extern t_mat4x4 ft_mat4x4_scale_iv3(t_iv3 v);
extern t_mat4x4 ft_mat4x4_scale_iv4(t_iv4 v);

extern t_mat4x4 ft_mat4x4_translate_v2(t_v2 v);
extern t_mat4x4 ft_mat4x4_translate_v3(t_v3 v);
extern t_mat4x4 ft_mat4x4_translate_iv2(t_iv2 v);
extern t_mat4x4 ft_mat4x4_translate_iv3(t_iv3 v);

extern t_mat4x4 ft_mat4x4_rotate_euler(t_v3 rot);

extern t_mat4x4 ft_mat4x4_fit_to_view(t_v2 pos, t_v2 size, t_v2 view_size);

extern t_mat22 ft_mat22_inv(t_mat22 m);
extern t_v2 ft_mat22_vec2_mul(t_mat22 m, t_v2 v);

#endif
