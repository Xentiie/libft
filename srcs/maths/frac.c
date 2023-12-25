/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frac.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 22:47:36 by reclaire          #+#    #+#             */
/*   Updated: 2023/09/26 22:10:27 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "libft.h"
#ifdef FT_MATHS
inline float	ft_frac(float v)
{
	return (v - ((long)v));
}

inline t_v2	ft_frac2(t_v2 v)
{
	return (vec2(ft_frac(v.x), ft_frac(v.y)));
}
#endif