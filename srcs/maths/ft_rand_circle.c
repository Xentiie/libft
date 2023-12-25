/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rand_circle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 01:17:38 by reclaire          #+#    #+#             */
/*   Updated: 2023/09/26 22:12:10 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "libft.h"
#ifdef FT_MATHS
t_v2	ft_rand_circle(unsigned int seed)
{
	return (vec2(ft_sin(ft_rand(seed)), ft_cos(ft_rand(seed) + 1)));
}
#endif