/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clamp.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 22:37:50 by reclaire          #+#    #+#             */
/*   Updated: 2023/09/26 22:10:06 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "libft.h"
#ifdef FT_MATHS
float	ft_clampf(float min, float max, float v)
{
	if (v > max)
		return (max);
	if (v < min)
		return (min);
	return (v);
}

int	ft_clamp(int min, int max, int v)
{
	if (v > max)
		return (max);
	if (v < min)
		return (min);
	return (v);
}
#endif