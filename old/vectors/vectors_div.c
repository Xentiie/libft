/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors_div.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 02:10:37 by reclaire          #+#    #+#             */
/*   Updated: 2023/08/23 02:58:09 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_v2	_vdiv_v2_v2(t_v2 v1, t_v2 v2)			{return (t_v2){v1.x / v2.x, v1.y / v2.y};}
t_v2	_vdiv_v2_iv2(t_v2 v1, t_iv2 v2)			{return (t_v2){v1.x / v2.x, v1.y / v2.y};}
t_v2	_vdiv_v2_float(t_v2 v1, float f)		{return (t_v2){v1.x / f, v1.y / f};}

t_v3	_vdiv_v3_v3(t_v3 v1, t_v3 v2)			{return (t_v3){v1.x / v2.x, v1.y / v2.y, v1.z / v2.z};}
t_v3	_vdiv_v3_iv3(t_v3 v1, t_iv3 v2)			{return (t_v3){v1.x / v2.x, v1.y / v2.y, v1.z / v2.z};}
t_v3	_vdiv_v3_v2(t_v3 v1, t_v2 v2)			{return (t_v3){v1.x / v2.x, v1.y / v2.y, v1.z};}
t_v3	_vdiv_v3_iv2(t_v3 v1, t_iv2 v2)			{return (t_v3){v1.x / v2.x, v1.y / v2.y, v1.z};}
t_v3	_vdiv_v3_float(t_v3 v1, float f)		{return (t_v3){v1.x / f, v1.y / f, v1.z / f};}

t_v4	_vdiv_v4_v4(t_v4 v1, t_v4 v2)			{return (t_v4){v1.x / v2.x, v1.y / v2.y, v1.z / v2.z, v1.w / v2.w};}
t_v4	_vdiv_v4_iv4(t_v4 v1, t_iv4 v2)			{return (t_v4){v1.x / v2.x, v1.y / v2.y, v1.z / v2.z, v1.w / v2.w};}
t_v4	_vdiv_v4_v3(t_v4 v1, t_v3 v2)			{return (t_v4){v1.x / v2.x, v1.y / v2.y, v1.z / v2.z, v1.w};}
t_v4	_vdiv_v4_iv3(t_v4 v1, t_iv3 v2)			{return (t_v4){v1.x / v2.x, v1.y / v2.y, v1.z / v2.z, v1.w};}
t_v4	_vdiv_v4_v2(t_v4 v1, t_v2 v2)			{return (t_v4){v1.x / v2.x, v1.y / v2.y, v1.z, v1.w};}
t_v4	_vdiv_v4_iv2(t_v4 v1, t_iv2 v2)			{return (t_v4){v1.x / v2.x, v1.y / v2.y, v1.z, v1.w};}
t_v4	_vdiv_v4_float(t_v4 v1, float f)		{return (t_v4){v1.x / f, v1.y / f, v1.z / f, v1.w / f};}


t_iv2	_vdiv_iv2_v2(t_iv2 v1, t_v2 v2)			{return (t_iv2){v1.x / v2.x, v1.y / v2.y};}
t_iv2	_vdiv_iv2_iv2(t_iv2 v1, t_iv2 v2)		{return (t_iv2){v1.x / v2.x, v1.y / v2.y};}
t_iv2	_vdiv_iv2_int(t_iv2 v1, int i)			{return (t_iv2){v1.x / i, v1.y / i};}

t_iv3	_vdiv_iv3_v3(t_iv3 v1, t_v3 v2)			{return (t_iv3){v1.x / v2.x, v1.y / v2.y, v1.z / v2.z};}
t_iv3	_vdiv_iv3_iv3(t_iv3 v1, t_iv3 v2)		{return (t_iv3){v1.x / v2.x, v1.y / v2.y, v1.z / v2.z};}
t_iv3	_vdiv_iv3_v2(t_iv3 v1, t_v2 v2)			{return (t_iv3){v1.x / v2.x, v1.y / v2.y, v1.z};}
t_iv3	_vdiv_iv3_iv2(t_iv3 v1, t_iv2 v2)		{return (t_iv3){v1.x / v2.x, v1.y / v2.y, v1.z};}
t_iv3	_vdiv_iv3_float(t_iv3 v1, int i)		{return (t_iv3){v1.x / i, v1.y / i, v1.z / i};}

t_iv4	_vdiv_iv4_v4(t_iv4 v1, t_v4 v2)			{return (t_iv4){v1.x / v2.x, v1.y / v2.y, v1.z / v2.z, v1.w / v2.w};}
t_iv4	_vdiv_iv4_iv4(t_iv4 v1, t_iv4 v2)		{return (t_iv4){v1.x / v2.x, v1.y / v2.y, v1.z / v2.z, v1.w / v2.w};}
t_iv4	_vdiv_iv4_v3(t_iv4 v1, t_v3 v2)			{return (t_iv4){v1.x / v2.x, v1.y / v2.y, v1.z / v2.z, v1.w};}
t_iv4	_vdiv_iv4_iv3(t_iv4 v1, t_iv3 v2)		{return (t_iv4){v1.x / v2.x, v1.y / v2.y, v1.z / v2.z, v1.w};}
t_iv4	_vdiv_iv4_v2(t_iv4 v1, t_v2 v2)			{return (t_iv4){v1.x / v2.x, v1.y / v2.y, v1.z, v1.w};}
t_iv4	_vdiv_iv4_iv2(t_iv4 v1, t_iv2 v2)		{return (t_iv4){v1.x / v2.x, v1.y / v2.y, v1.z, v1.w};}
t_iv4	_vdiv_iv4_float(t_iv4 v1, int i)		{return (t_iv4){v1.x / i, v1.y / i, v1.z / i, v1.w / i};}
