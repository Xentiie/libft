/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_noise2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 05:03:12 by reclaire          #+#    #+#             */
/*   Updated: 2024/03/04 18:50:13 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "libft_int.h"


F32	ft_noise2(v2f st)
{
	v2f	i;
	v2f	f;
	v4f	abcd;
	v2f	u;

	f = ft_frac2(st);
	i = (v2f){floorf(st[0]), floorf(st[1])};
	abcd[0] = ft_frand2(i);

	abcd[1] = ft_frand2(i + (v2f){1.0f, 0.0f});
	abcd[2] = ft_frand2(i + (v2f){0.0, 1.0});
	abcd[3] = ft_frand2(i + (v2f){1.0, 1.0});
	u = ft_smoothstep2((v2f){0.f, 0.f}, (v2f){1.f, 1.f}, f);
	return (ft_lerp(abcd[0], abcd[1], u[0]) + (abcd[2] - abcd[0]) * u[1] * (1.0 - u[0])
		+ (abcd[3] - abcd[1]) * u[0] * u[1]);
}
