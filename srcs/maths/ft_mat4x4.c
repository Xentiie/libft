/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mat4x4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 02:51:20 by reclaire          #+#    #+#             */
/*   Updated: 2024/09/08 00:26:40 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <math.h>
#include "libft_int.h"

#define get(mat, col, row) ((F32 *)&mat)[col * 4 + row]

v4f *ft_mat4x4_col(t_mat4x4 *mat, S32 c)
{
	if (c * 4 >= 16)
		return NULL;
	return (v4f *)(((F32 *)mat) + c * 4);
}

F32 *ft_mat4x4_get(t_mat4x4 *mat, S32 r, S32 c)
{
	if (r + c * 4 >= 16)
		return NULL;
	F32 *ptr = (F32 *)mat;
	return &(ptr[r + c * 4]);
}

void ft_mat4x4_set_col(t_mat4x4 *mat, S32 c, v4f v)
{
	v4f *col = ft_mat4x4_col(mat, c);
	if (!col)
		return NULL;
	*col = v;
}

void ft_mat4x4_set_row(t_mat4x4 *mat, S32 r, v4f v)
{
	for (S32 i = 0; i < 4; i++)
		get(mat, r, i) = v[i];
}

t_mat4x4 ft_mat4x4_transpose(t_mat4x4 mat)
{
	t_mat4x4 r;

	for (S32 i = 0; i < 4; i++)
	{
		for (S32 j = 0; j < 4; j++)
			get(r, i, j) = get(mat, j, i);
	}
	return r;
}

F32 ft_mat4x4_det(t_mat4x4 v)
{
	return get(v, 0, 0) * (get(v, 1, 1) * (get(v, 2, 2) * get(v, 3, 3) - get(v, 2, 3) * get(v, 3, 2)) - get(v, 1, 2) * (get(v, 2, 1) * get(v, 3, 3) - get(v, 2, 3) * get(v, 3, 1)) + get(v, 1, 3) * (get(v, 2, 1) * get(v, 3, 2) - get(v, 2, 2) * get(v, 3, 1))) -
		   get(v, 0, 1) * (get(v, 1, 0) * (get(v, 2, 2) * get(v, 3, 3) - get(v, 2, 3) * get(v, 3, 2)) - get(v, 1, 2) * (get(v, 2, 0) * get(v, 3, 3) - get(v, 2, 3) * get(v, 3, 0)) + get(v, 1, 3) * (get(v, 2, 0) * get(v, 3, 2) - get(v, 2, 2) * get(v, 3, 0))) +
		   get(v, 0, 2) * (get(v, 1, 0) * (get(v, 2, 1) * get(v, 3, 3) - get(v, 2, 3) * get(v, 3, 1)) - get(v, 1, 1) * (get(v, 2, 0) * get(v, 3, 3) - get(v, 2, 3) * get(v, 3, 0)) + get(v, 1, 3) * (get(v, 2, 0) * get(v, 3, 1) - get(v, 2, 1) * get(v, 3, 0))) -
		   get(v, 0, 3) * (get(v, 1, 0) * (get(v, 2, 1) * get(v, 3, 2) - get(v, 2, 2) * get(v, 3, 1)) - get(v, 1, 1) * (get(v, 2, 0) * get(v, 3, 2) - get(v, 2, 2) * get(v, 3, 0)) + get(v, 1, 2) * (get(v, 2, 0) * get(v, 3, 1) - get(v, 2, 1) * get(v, 3, 0)));
}

t_mat4x4 ft_mat4x4_invert(t_mat4x4 mat)
{
	t_mat4x4 r;
	F32 d = 0;
	F32 si = 1;
	for (S32 i = 0; i < 4; i++)
	{
		F32 sj = si;
		for (S32 j = 0; j < 4; j++)
		{
			t_mat4x4 sub;
			for (S32 k = 0; k < 4 - 1; k++)
				for (S32 l = 0; l < 4 - 1; l++)
					get(sub, k, l) = get(mat, (k < j) ? k : k + 1, (l < i) ? l : l + 1);
			F32 dd = ft_mat4x4_det(sub) * sj;
			get(r, i, j) = dd;
			d += dd * get(mat, j, i);
			sj = -sj;
		}
		si = -si;
	}
	return ft_mat4x4_mult_flt(ft_mat4x4_mult_flt(r, d == 0 ? 0 : 1 / d), 4);
}

F32 rcp(F32 v)
{
	return v ? 1.0f / v : 0.0f;
}
t_mat4x4 ft_mat4x4_perspective(F32 fov, F32 near, F32 far)
{
	// Camera points towards -z.  0 < near < far.
	// Matrix maps z range [-near, -far] to [-1, 1], after homogeneous division.
	F32 f = rcp(tanf(fov * FT_PI / 360.0f));
	F32 d = rcp(near - far);

	return (t_mat4x4) {
		f, 0.f, 0.f, 0.f,
		0.f, f, 0.f, 0.f,
		0.f, 0.f, (near + far) * d, 2.f * near * far * d,
		0.f, 0.f, -1.f, 0.f
	};
}

t_mat4x4 ft_mat4x4_mult_matrix(t_mat4x4 a, t_mat4x4 b)
{
	t_mat4x4 r;
	for (S32 i = 0; i < 4; i++)
	{
		for (S32 j = 0; j < 4; j++)
		{
			F32 rr = 0;
			for (S32 k = 0; k < 4; k++)
				rr += (get(a, i, k) * get(b, k, j));
			get(r, i, j) = rr;
		}
	}
	return r;
}

/*
t_mat4x4	ft_mat4x4_mult_matrix(t_mat4x4 a, t_mat4x4 b)
{
	t_mat4x4	r;
	r.m00 = a.m00 * b.m00 + a.m01 * b.m10 + a.m02 * b.m20 + a.m03 * b.m30;
	r.m01 = a.m00 * b.m01 + a.m01 * b.m11 + a.m02 * b.m21 + a.m03 * b.m31;
	r.m02 = a.m00 * b.m02 + a.m01 * b.m12 + a.m02 * b.m22 + a.m03 * b.m32;
	r.m03 = a.m00 * b.m03 + a.m01 * b.m13 + a.m02 * b.m23 + a.m03 * b.m33;

	r.m10 = a.m10 * b.m00 + a.m11 * b.m10 + a.m12 * b.m20 + a.m13 * b.m30;
	r.m11 = a.m10 * b.m01 + a.m11 * b.m11 + a.m12 * b.m21 + a.m13 * b.m31;
	r.m12 = a.m10 * b.m02 + a.m11 * b.m12 + a.m12 * b.m22 + a.m13 * b.m32;
	r.m13 = a.m10 * b.m03 + a.m11 * b.m13 + a.m12 * b.m23 + a.m13 * b.m33;

	r.m20 = a.m20 * b.m00 + a.m21 * b.m10 + a.m22 * b.m20 + a.m23 * b.m30;
	r.m21 = a.m20 * b.m01 + a.m21 * b.m11 + a.m22 * b.m21 + a.m23 * b.m31;
	r.m22 = a.m20 * b.m02 + a.m21 * b.m12 + a.m22 * b.m22 + a.m23 * b.m32;
	r.m23 = a.m20 * b.m03 + a.m21 * b.m13 + a.m22 * b.m23 + a.m23 * b.m33;

	r.m30 = a.m30 * b.m00 + a.m31 * b.m10 + a.m32 * b.m20 + a.m33 * b.m30;
	r.m31 = a.m30 * b.m01 + a.m31 * b.m11 + a.m32 * b.m21 + a.m33 * b.m31;
	r.m32 = a.m30 * b.m02 + a.m31 * b.m12 + a.m32 * b.m22 + a.m33 * b.m32;
	r.m33 = a.m30 * b.m03 + a.m31 * b.m13 + a.m32 * b.m23 + a.m33 * b.m33;
	return r;
}
*/

v4f ft_mat4x4_mult_v4(t_mat4x4 a, v4f b)
{
	v4f r;
	for (S32 i = 0; i < 4; i++)
	{
		F32 rr = 0;
		for (S32 j = 0; j < 4; j++)
			rr += get(a, i, j) * b[j];
		r[i] = rr;
	}
	return r;
}

t_mat4x4 ft_mat4x4_mult_flt(t_mat4x4 a, F32 b)
{
	t_mat4x4 r;
	for (S32 i = 0; i < 4 * 4; i++)
		get(r, i, i) = get(a, i, i) * b;
	return r;
}

t_mat4x4 ft_mat4x4_scale2(v2f v)
{
	return (t_mat4x4) {
		v[0], 0.f, 0.f, 0.f,
		0.f, v[1], 0.f, 0.f,
		0.f, 0.f, 1.f, 0.f,
		0.f, 0.f, 0.f, 1.f,
	};
}

t_mat4x4 ft_mat4x4_scale3(v3f v)
{
	return (t_mat4x4) {
		v[0], 0.f, 0.f, 0.f,
		0.f, v[1], 0.f, 0.f,
		0.f, 0.f, v[2], 0.f,
		0.f, 0.f, 0.f, 1.f,
	};
}

t_mat4x4 ft_mat4x4_scale4(v4f v)
{
	return (t_mat4x4) {
		v[0], 0.f, 0.f, 0.f,
		0.f, v[1], 0.f, 0.f,
		0.f, 0.f, v[2], 0.f,
		0.f, 0.f, 0.f, v[3],
	};
}

t_mat4x4 ft_mat4x4_translate2(v2f v)
{
	t_mat4x4 r = ft_mat4x4_identity;
	for (S32 i = 0; i < 2; i++)
		get(r, i, 2) = v[i];
	return r;
}
t_mat4x4 ft_mat4x4_translate3(v3f v)
{
	t_mat4x4 r = ft_mat4x4_identity;
	for (S32 i = 0; i < 3; i++)
		get(r, i, 3) = v[i];
	return r;
}
t_mat4x4 ft_mat4x4_translate4(v4f v)
{
	t_mat4x4 r = ft_mat4x4_identity;
	for (S32 i = 0; i < 3; i++)
		get(r, i, 3) = v[i];
	return r;
}

t_mat4x4 ft_mat4x4_translate_iv2(v2i v)
{
	t_mat4x4 r = ft_mat4x4_identity;
	for (S32 i = 0; i < 2; i++)
		get(r, i, 2) = v[i];
	return r;
}
t_mat4x4 ft_mat4x4_translate_iv3(v3i v)
{
	t_mat4x4 r = ft_mat4x4_identity;
	for (S32 i = 0; i < 3; i++)
		get(r, i, 3) = v[i];
	return r;
}

t_mat4x4 ft_mat4x4_fit_to_view(v2f pos, v2f size, v2f view_size)
{
	v2f ratio = view_size / size;
	F32 min_ratio = ratio[0] < ratio[1] ? ratio[0] : ratio[1];

	// clang-format off
	t_mat4x4 s1 = (t_mat4x4){
		2.f / view_size[0],	0.f,				0.f,	0.f,
		0.f,				2.f / view_size[1],	0.f,	0.f,
		0.f,				0.f,				1.f,	0.f,
		0.f,				0.f,				0.f,	1.f,
	};

	t_mat4x4 s2 = (t_mat4x4){
		min_ratio,	0.f,		0.f, 0.f,
		0.f,		min_ratio,	0.f, 0.f,
		0.f,		0.f,		1.f, 0.f,
		0.f,		0.f,		0.f, 1.f,
	};

	t_mat4x4 s3 = (t_mat4x4){
		1.f,	0.f,	0.f,	-pos[0] - size[0] * 0.5f,
		0.f,	1.f,	0.f,	-pos[1] - size[1] * 0.5f,
		0.f,	0.f,	1.f,	0.f,
		0.f,	0.f,	0.f,	1.f,
	};
	// clang-format on

	// TODO: faire les maths

	return ft_mat4x4_mult_matrix(ft_mat4x4_mult_matrix(s1, s2), s3);
}
