/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   primes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 16:32:25 by reclaire          #+#    #+#             */
/*   Updated: 2025/03/10 23:49:23 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_int.h"

#include "libft/maths.h"

S32	ft_is_prime(S32 nb)
{
	S32	i;

	if (nb <= 1)
		return (0);
	i = 2;
	while (i < nb)
	{
		if (nb % i == 0 && i != nb)
			return (0);
		i++;
	}
	return (1);
}
