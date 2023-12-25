/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distance.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 22:40:54 by reclaire          #+#    #+#             */
/*   Updated: 2023/09/26 22:10:20 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "libft.h"
#ifdef FT_MATHS
inline float	ft_dist2(t_v2 p1, t_v2 p2)
{
	return (sqrtf(powf(p1.x - p2.x, 2) + powf(p1.y - p2.y, 2)));
}

inline float	ft_sqrdist2(t_v2 p1, t_v2 p2)
{
	return (powf(p1.x - p2.x, 2) + powf(p1.y - p2.y, 2));
}

inline float	ft_dist3(t_v3 p1, t_v3 p2)
{
	return (sqrtf(powf(p1.x - p2.x, 2) + powf(p1.y - p2.y, 2)
			+ powf(p1.y - p2.y, 2)));
}

inline float	ft_sqrdist3(t_v3 p1, t_v3 p2)
{
	return (powf(p1.x - p2.x, 2) + powf(p1.y - p2.y, 2) + powf(p1.y - p2.y, 2));
}
#endif