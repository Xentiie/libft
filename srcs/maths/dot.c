/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dot.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 22:45:45 by reclaire          #+#    #+#             */
/*   Updated: 2023/09/26 22:10:24 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "libft.h"
#ifdef FT_MATHS
inline float	ft_dot2(t_v2 a, t_v2 b)
{
	return (a.x * b.x + a.y * b.y);
}

inline float	ft_dot3(t_v3 a, t_v3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}
#endif