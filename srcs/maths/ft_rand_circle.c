/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rand_circle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 01:17:38 by reclaire          #+#    #+#             */
/*   Updated: 2024/02/11 20:51:26 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "libft_int.h"


t_v2	ft_rand_circle(U32 seed)
{
	return (vec2(ft_sin(ft_rand(seed)), ft_cos(ft_rand(seed) + 1)));
}
