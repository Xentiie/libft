/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors_mod.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 22:41:09 by reclaire          #+#    #+#             */
/*   Updated: 2023/08/23 02:56:14 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
t_iv2	mod2i(t_iv2 v1, t_iv2 v2)
{
	return (iv2(v1.x % v2.x, v1.y % v2.y));
}

t_iv3	mod3i(t_iv3 v1, t_iv3 v2)
{
	return (iv3(v1.x % v2.x, v1.y % v2.y, v1.z % v2.z));
}

t_iv4	mod4i(t_iv4 v1, t_iv4 v2)
{
	return (iv4(v1.x % v2.x, v1.y % v2.y, v1.z % v2.z, v1.w % v2.w));
}
*/

t_iv2	_vmod_iv2_iv2(t_iv2 v1, t_iv2 v2)		{return (t_iv2){v1.x % v2.x, v1.y % v2.y};}
t_iv2	_vmod_iv2_int(t_iv2 v1, int i)			{return (t_iv2){v1.x % i, v1.y % i};}

t_iv3	_vmod_iv3_iv3(t_iv3 v1, t_iv3 v2)		{return (t_iv3){v1.x % v2.x, v1.y % v2.y, v1.z % v2.z};}
t_iv3	_vmod_iv3_iv2(t_iv3 v1, t_iv2 v2)		{return (t_iv3){v1.x % v2.x, v1.y % v2.y, v1.z};}
t_iv3	_vmod_iv3_int(t_iv3 v1, int i)			{return (t_iv3){v1.x % i, v1.y % i, v1.z % i};}

t_iv4	_vmod_iv4_iv4(t_iv4 v1, t_iv4 v2)		{return (t_iv4){v1.x % v2.x, v1.y % v2.y, v1.z % v2.z, v1.w % v2.w};}
t_iv4	_vmod_iv4_iv3(t_iv4 v1, t_iv3 v2)		{return (t_iv4){v1.x % v2.x, v1.y % v2.y, v1.z % v2.z, v1.w};}
t_iv4	_vmod_iv4_iv2(t_iv4 v1, t_iv2 v2)		{return (t_iv4){v1.x % v2.x, v1.y % v2.y, v1.z, v1.w};}
t_iv4	_vmod_iv4_int(t_iv4 v1, int i)			{return (t_iv4){v1.x % i, v1.y % i, v1.z % i, v1.w % i};}
