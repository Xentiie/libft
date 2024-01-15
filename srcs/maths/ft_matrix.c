/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 02:51:20 by reclaire          #+#    #+#             */
/*   Updated: 2023/09/29 23:50:58 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
#ifdef FT_MATHS
# include <math.h>
# define get(mat, i, j) ((float *)&mat)[i*4+j]

t_v4		*ft_matrix_col(t_mat4x4 *mat, int c)
{
	if (c * 4 >= 16)
		return NULL;
	return (t_v4*)(((float*)mat) + c * 4);
}

float		*ft_matrix_get(t_mat4x4 *mat, int r, int c)
{
	if (r+c*4 >= 16)
		return NULL;
	float *ptr = (float*)mat;
	return &(ptr[r + c * 4]);
}

t_v4		*ft_matrix_set_col(t_mat4x4 *mat, int c, t_v4 v)
{
	t_v4 *col = ft_matrix_col(mat, c);
	if (!col)
		return NULL;
	*col = v;
	return col;
}

bool		ft_matrix_set_row(t_mat4x4 *mat, int r, t_v4 v)
{
	for (int i = 0; i < 4; i++)
	{
		float *ptr = ft_matrix_get(mat, r, i);
		if (!ptr)
			return FALSE;
		*ptr = ((float*)&v)[i];
	}
	return TRUE;
}

t_mat4x4	ft_matrix_transpose(t_mat4x4 mat)
{
	t_mat4x4	r;

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
			get(r, i, j) = get(mat, j, i);
	}
	return r;
}

float	ft_matrix_det(t_mat4x4 v)
{
    return get(v, 0, 0) * (get(v, 1, 1) * (get(v, 2, 2) * get(v, 3, 3) - get(v, 2, 3) * get(v, 3, 2)) - get(v, 1, 2) * (get(v, 2, 1) * get(v, 3, 3) - get(v, 2, 3) * get(v, 3, 1)) + get(v, 1, 3) * (get(v, 2, 1) * get(v, 3, 2) - get(v, 2, 2) * get(v, 3, 1))) -
           get(v, 0, 1) * (get(v, 1, 0) * (get(v, 2, 2) * get(v, 3, 3) - get(v, 2, 3) * get(v, 3, 2)) - get(v, 1, 2) * (get(v, 2, 0) * get(v, 3, 3) - get(v, 2, 3) * get(v, 3, 0)) + get(v, 1, 3) * (get(v, 2, 0) * get(v, 3, 2) - get(v, 2, 2) * get(v, 3, 0))) +
           get(v, 0, 2) * (get(v, 1, 0) * (get(v, 2, 1) * get(v, 3, 3) - get(v, 2, 3) * get(v, 3, 1)) - get(v, 1, 1) * (get(v, 2, 0) * get(v, 3, 3) - get(v, 2, 3) * get(v, 3, 0)) + get(v, 1, 3) * (get(v, 2, 0) * get(v, 3, 1) - get(v, 2, 1) * get(v, 3, 0))) -
           get(v, 0, 3) * (get(v, 1, 0) * (get(v, 2, 1) * get(v, 3, 2) - get(v, 2, 2) * get(v, 3, 1)) - get(v, 1, 1) * (get(v, 2, 0) * get(v, 3, 2) - get(v, 2, 2) * get(v, 3, 0)) + get(v, 1, 2) * (get(v, 2, 0) * get(v, 3, 1) - get(v, 2, 1) * get(v, 3, 0)));
}

t_mat4x4 ft_matrix_invert(t_mat4x4 mat)
{
    t_mat4x4	r;
    float		d = 0;
    float		si = 1;
    for (int i = 0; i < 4; i++)
    {
        float	sj = si;
        for (int j = 0; j < 4; j++)
        {
            t_mat4x4	sub;
            for (int k = 0; k < 4 - 1; k++)
                for (int l = 0; l < 4 - 1; l++)
                    get(sub, k, l) = get(mat, (k < j) ? k : k + 1, (l < i) ? l : l + 1);
            float dd = ft_matrix_det(sub) * sj;
            get(r, i, j) = dd;
            d += dd * get(mat, j, i);
            sj = -sj;
        }
        si = -si;
    }
    return ft_matrix_mult_float(ft_matrix_mult_float(r, d == 0 ? 0 : 1/d), 4);
}

float rcp(float v)
{
	return v ? 1.0f/v : 0.0f;
}
t_mat4x4 ft_matrix_perspective(F32 fov, F32 near, F32 far)
{
	// Camera points towards -z.  0 < near < far.
	// Matrix maps z range [-near, -far] to [-1, 1], after homogeneous division.
    F32 f = rcp(tanf(fov * FT_PI / 360.0f));
    F32 d = rcp(near - far);

    t_mat4x4 r;
	ft_matrix_set_row(&r, 0, vec4(f,	0.0f,	0.0f,				0.0f));
	ft_matrix_set_row(&r, 1, vec4(0.0f,	f,		0.0f,				0.0f));
	ft_matrix_set_row(&r, 2, vec4(0.0f,	0.0f,	(near + far) * d,	2.0f * near * far * d));
	ft_matrix_set_row(&r, 3, vec4(0.0f,	0.0f,	-1.0f,				0.0f));

    return r;
}


t_mat4x4	ft_matrix_mult_matrix(t_mat4x4 a, t_mat4x4 b)
{
	t_mat4x4	r;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			float rr = 0;
			for (int k = 0; k < 4; k++)
				rr += (*ft_matrix_get(&a, i, k) * *ft_matrix_get(&b, k, j));
			*ft_matrix_get(&r, i, j) = rr;
		}
	}
	return r;
}


/*
t_mat4x4	ft_matrix_mult_matrix(t_mat4x4 a, t_mat4x4 b)
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

t_v4	ft_matrix_mult_v4(t_mat4x4 a, t_v4 b)
{
	t_v4	r;
	for (int i = 0; i < 4; i++)
	{
		float rr = 0;
		for (int j = 0; j < 4; j++)
			rr += *ft_matrix_get(&a, i, j) * ((float*)&b)[j];
		((float*)&r)[i] = rr;
	}
	return r;
}

t_mat4x4	ft_matrix_mult_float(t_mat4x4 a, float b)
{
	t_mat4x4	r;
	for (int i = 0; i < 4 * 4; i++)
		get(r, i, i) = get(a, i, i) * b;
	return r;
}

t_mat4x4	ft_matrix_scale_v2(t_v2 v)
{
    t_mat4x4	r = ft_matrix_identity;
    for (int i = 0; i < 2; i++)
        *ft_matrix_get(&r, i, i) = ((float *)&v)[i];
    return r;
}

t_mat4x4	ft_matrix_scale_v3(t_v3 v)
{
    t_mat4x4	r = ft_matrix_identity;
    for (int i = 0; i < 3; i++)
        *ft_matrix_get(&r, i, i) = ((float *)&v)[i];
    return r;
}

t_mat4x4	ft_matrix_scale_v4(t_v4 v)
{
    t_mat4x4	r = ft_matrix_identity;
    for (int i = 0; i < 4; i++)
        *ft_matrix_get(&r, i, i) = ((float *)&v)[i];
    return r;
}

t_mat4x4	ft_matrix_scale_iv2(t_iv2 v)
{
    t_mat4x4	r = ft_matrix_identity;
    for (int i = 0; i < 2; i++)
        *ft_matrix_get(&r, i, i) = ((float *)&v)[i];
    return r;
}

t_mat4x4	ft_matrix_scale_iv3(t_iv3 v)
{
    t_mat4x4	r = ft_matrix_identity;
    for (int i = 0; i < 3; i++)
        *ft_matrix_get(&r, i, i) = ((float *)&v)[i];
    return r;
}

t_mat4x4	ft_matrix_scale_iv4(t_iv4 v)
{
    t_mat4x4	r = ft_matrix_identity;
    for (int i = 0; i < 4; i++)
        *ft_matrix_get(&r, i, i) = ((float *)&v)[i];
    return r;
}

t_mat4x4	ft_matrix_translate_v2(t_v2 v)
{
    t_mat4x4	r = ft_matrix_identity;
    for (int i = 0; i < 2; i++)
        *ft_matrix_get(&r, i, 2) = ((float *)&v)[i];
    return r;
}
t_mat4x4	ft_matrix_translate_v3(t_v3 v)
{
    t_mat4x4	r = ft_matrix_identity;
    for (int i = 0; i < 3; i++)
        *ft_matrix_get(&r, i, 3) = ((float *)&v)[i];
    return r;
}

t_mat4x4	ft_matrix_translate_iv2(t_iv2 v)
{
    t_mat4x4	r = ft_matrix_identity;
    for (int i = 0; i < 2; i++)
        *ft_matrix_get(&r, i, 2) = ((int *)&v)[i];
    return r;
}
t_mat4x4	ft_matrix_translate_iv3(t_iv3 v)
{
    t_mat4x4	r = ft_matrix_identity;
    for (int i = 0; i < 3; i++)
        *ft_matrix_get(&r, i, 3) = ((int *)&v)[i];
    return r;
}

t_mat4x4	ft_matrix_fit_to_view(t_v2 pos, t_v2 size, t_v2 view_size)
{
	t_v2		view_size_h = vec2_div(vec2(2.0f, 2.0f), view_size);
	t_mat4x4 	s1 = ft_matrix_scale_v3(vec3(view_size_h.x, view_size_h.y, 1.0f));

	//Mat4f::scale(Vec3f((viewSize / size).min(), 1.0f)) ?????????
	t_v2		ratio = vec2_div(view_size, size);
	float		min_ratio = ratio.x < ratio.y ? ratio.x : ratio.y;
	t_mat4x4 	s2 = ft_matrix_scale_v3(vec3(min_ratio, min_ratio, 1.0f));

	//vec3( -pos - size * 0.5f, 0.0f )
	t_mat4x4	s3 = ft_matrix_translate_v3(vec3(
		-pos.x - size.x * 0.5f,
		-pos.y - size.y * 0.5f, 0.0f));
    
	return ft_matrix_mult_matrix(ft_matrix_mult_matrix(s1, s2), s3);
}
#endif