/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 03:28:15 by reclaire          #+#    #+#             */
/*   Updated: 2023/08/18 03:28:18 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "libft.h"

t_v2 _v2_iv2(t_iv2 v)													{ return (t_v2){v.x, v.y}; }
t_v2 _v2_iv3(t_iv3 v)													{ return (t_v2){v.x, v.y}; }
t_v2 _v2_iv4(t_iv4 v)													{ return (t_v2){v.x, v.y}; }
t_v2 _v2_v4(t_v4 v)														{ return (t_v2){v.x, v.y}; }
t_v2 _v2_v3(t_v3 v)														{ return (t_v2){v.x, v.y}; }
t_v2 _v2_float(float x)													{ return (t_v2){x, 0.0f}; }
t_v2 _v2_float_float(float x, float y)									{ return (t_v2){x, y}; }

t_v3 _v3_iv2(t_iv2 v) 													{ return (t_v3){v.x, v.y, 0.0f}; }
t_v3 _v3_iv3(t_iv3 v) 													{ return (t_v3){v.x, v.y, v.z}; }
t_v3 _v3_iv4(t_iv4 v) 													{ return (t_v3){v.x, v.y, v.z}; }
t_v3 _v3_v4(t_v4 v) 													{ return (t_v3){v.x, v.y, v.z}; }
t_v3 _v3_v2(t_v2 v) 													{ return (t_v3){v.x, v.y, 0.0f}; }
t_v3 _v3_float(float x)													{ return (t_v3){x, 0.0f, 0.0f}; }
t_v3 _v3_float_float(float x, float y)									{ return (t_v3){x, y, 0.0f}; }
t_v3 _v3_float_float_float(float x, float y, float z)					{ return (t_v3){x, y, z}; }
t_v3 _v3_v2_float(t_v2 v, float z)										{ return (t_v3){v.x, v.y, z}; }
t_v3 _v3_float_v2(float x, t_v2 v)										{ return (t_v3){x, v.x, v.y}; }

t_v4 _v4_iv2(t_iv2 v)													{ return (t_v4){v.x, v.y, 0.0f, 0.0f}; }
t_v4 _v4_iv3(t_iv3 v)													{ return (t_v4){v.x, v.y, v.z, 0.0f}; }
t_v4 _v4_iv4(t_iv4 v)													{ return (t_v4){v.x, v.y, v.z, v.w}; }
t_v4 _v4_v3(t_v3 v)														{ return (t_v4){v.x, v.y, v.z, 0.0f}; }
t_v4 _v4_v2(t_v2 v)														{ return (t_v4){v.x, v.y, 0.0f, 0.0f}; }
t_v4 _v4_float(float x)													{ return (t_v4){x, 0.0f, 0.0f, 0.0f}; }
t_v4 _v4_float_float(float x, float y)									{ return (t_v4){x, y, 0.0f, 0.0f}; }
t_v4 _v4_float_float_float(float x, float y, float z)					{ return (t_v4){x, y, z, 0.0f}; }
t_v4 _v4_float_float_float_float(float x, float y, float z, float w)	{ return (t_v4){x, y, z, w}; }
t_v4 _v4_float_v3(float x, t_v3 v)										{ return (t_v4){x, v.x, v.y, v.z}; }
t_v4 _v4_v3_float(t_v3 v, float w)										{ return (t_v4){v.x, v.y, v.z, w}; }
t_v4 _v4_v2_v2(t_v2 xy, t_v2 zw)										{ return (t_v4){xy.x, xy.y, zw.x, zw.y}; }
t_v4 _v4_float_v2_float(float x, t_v2 v, float w)						{ return (t_v4){x, v.x, v.y, w}; }
t_v4 _v4_float_float_v2(float x, float y, t_v2 v)						{ return (t_v4){x, y, v.x, v.y}; }
t_v4 _v4_v2_float_float(t_v2 v, float z, float w)						{ return (t_v4){v.x, v.y, z, w}; }

t_iv2 _iv2_v2(t_v2 v)													{ return (t_iv2){v.x, v.y}; }
t_iv2 _iv2_v3(t_v3 v)													{ return (t_iv2){v.x, v.y}; }
t_iv2 _iv2_v4(t_v4 v)													{ return (t_iv2){v.x, v.y}; }
t_iv2 _iv2_iv4(t_iv4 v)													{ return (t_iv2){v.x, v.y}; }
t_iv2 _iv2_iv3(t_iv3 v)													{ return (t_iv2){v.x, v.y}; }
t_iv2 _iv2_int(int x)													{ return (t_iv2){x, 0}; }
t_iv2 _iv2_int_int(int x, int y)										{ return (t_iv2){x, y}; }

t_iv3 _iv3_v2(t_v2 v)													{ return (t_iv3){v.x, v.y, 0}; }
t_iv3 _iv3_v3(t_v3 v)													{ return (t_iv3){v.x, v.y, v.z}; }
t_iv3 _iv3_v4(t_v4 v)													{ return (t_iv3){v.x, v.y, v.z}; }
t_iv3 _iv3_iv4(t_iv4 v)													{ return (t_iv3){v.x, v.y, v.z}; }
t_iv3 _iv3_iv2(t_iv2 v)													{ return (t_iv3){v.x, v.y, 0}; }
t_iv3 _iv3_int(int x)													{ return (t_iv3){x, 0, 0}; }
t_iv3 _iv3_int_int(int x, int y)										{ return (t_iv3){x, y, 0}; }
t_iv3 _iv3_int_int_int(int x, int y, int z)								{ return (t_iv3){x, y, z}; }
t_iv3 _iv3_iv2_int(t_iv2 v, int z)										{ return (t_iv3){v.x, v.y, z}; }
t_iv3 _iv3_int_iv2(int x, t_iv2 v)										{ return (t_iv3){x, v.x, v.y}; }

t_iv4 _iv4_v2(t_v2 v)													{ return (t_iv4){v.x, v.y, 0, 0}; }
t_iv4 _iv4_v3(t_v3 v)													{ return (t_iv4){v.x, v.y, v.z, 0}; }
t_iv4 _iv4_v4(t_v4 v)													{ return (t_iv4){v.x, v.y, v.z, v.w}; }
t_iv4 _iv4_iv3(t_iv3 v)													{ return (t_iv4){v.x, v.y, v.z, 0}; }
t_iv4 _iv4_iv2(t_iv2 v)													{ return (t_iv4){v.x, v.y, 0, 0}; }
t_iv4 _iv4_int(int x)													{ return (t_iv4){x, 0, 0, 0}; }
t_iv4 _iv4_int_int(int x, int y)										{ return (t_iv4){x, y, 0, 0}; }
t_iv4 _iv4_int_int_int(int x, int y, int z)								{ return (t_iv4){x, y, z, 0}; }
t_iv4 _iv4_int_int_int_int(int x, int y, int z, int w)					{ return (t_iv4){x, y, z, w}; }
t_iv4 _iv4_int_iv3(int x, t_iv3 v)										{ return (t_iv4){x, v.x, v.y, v.z}; }
t_iv4 _iv4_iv3_int(t_iv3 v, int w)										{ return (t_iv4){v.x, v.y, v.z, w}; }
t_iv4 _iv4_iv2_iv2(t_iv2 xy, t_iv2 zw)									{ return (t_iv4){xy.x, xy.y, zw.x, zw.y}; }
t_iv4 _iv4_int_iv2_int(int x, t_iv2 v, int w)							{ return (t_iv4){x, v.x, v.y, w}; }
t_iv4 _iv4_int_int_iv2(int x, int y, t_iv2 v)							{ return (t_iv4){x, y, v.x, v.y}; }
t_iv4 _iv4_iv2_int_int(t_iv2 v, int z, int w)							{ return (t_iv4){v.x, v.y, z, w}; }