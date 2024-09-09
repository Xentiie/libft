/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rand_circle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 01:17:38 by reclaire          #+#    #+#             */
/*   Updated: 2024/02/16 16:24:38 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "libft_int.h"


v2f	ft_rand_circle(U32 seed)
{
	return (v2f){ft_sin(ft_frand(seed)), ft_cos(ft_frand(seed) + 1)};
}
