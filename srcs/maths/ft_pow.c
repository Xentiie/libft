/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 14:09:25 by reclaire          #+#    #+#             */
/*   Updated: 2024/11/10 21:51:34 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_int.h"
#include "libft/maths.h"

S32	ft_pow(S32 nb, S32 power)
{
	S32	total;

	total = 1;
	if (power < 0)
		return (0);
	while (power > 0)
	{
		total *= nb;
		power--;
	}
	return (total);
}
