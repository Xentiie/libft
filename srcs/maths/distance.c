/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distance.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 04:16:06 by reclaire          #+#    #+#             */
/*   Updated: 2024/09/08 04:16:06 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "libft_int.h"
#include <math.h>

inline F32 ft_dist2(v2f p1, v2f p2)
{
	return (sqrtf(powf(p1[0] - p2[0], 2) + powf(p1[1] - p2[1], 2)));
}

inline F32 ft_sqrdist2(v2f p1, v2f p2)
{
	return (powf(p1[0] - p2[0], 2) + powf(p1[1] - p2[1], 2));
}

inline F32 ft_dist3(v3f p1, v3f p2)
{
	return (sqrtf(powf(p1[0] - p2[0], 2) + powf(p1[1] - p2[1], 2) + powf(p1[2] - p2[2], 2)));
}

inline F32 ft_sqrdist3(v3f p1, v3f p2)
{
	return (powf(p1[0] - p2[0], 2) + powf(p1[1] - p2[1], 2) + powf(p1[2] - p2[2], 2));
}
