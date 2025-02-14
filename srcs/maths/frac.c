/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frac.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 22:47:36 by reclaire          #+#    #+#             */
/*   Updated: 2025/01/23 04:23:36 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_int.h"
#include "libft/maths.h"

inline F64	ft_frac(F64 v)
{
	return (v - ((long)v));
}

inline t_v2	ft_frac2(t_v2 v)
{
	return (vec2(ft_frac(v.x), ft_frac(v.y)));
}
