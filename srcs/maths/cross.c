/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cross.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 21:24:50 by reclaire          #+#    #+#             */
/*   Updated: 2023/09/26 22:10:16 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "libft.h"
#ifdef FT_MATHS
t_v3 ft_cross3(t_v3 a, t_v3 b)
{
	t_v3 result;
	result.x = a.y * b.z - a.z * b.y;
	result.y = a.z * b.x - a.x * b.z;
	result.z = a.x * b.y - a.y * b.x;
	return result;
}
#endif