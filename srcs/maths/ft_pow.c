/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 14:09:25 by reclaire          #+#    #+#             */
/*   Updated: 2023/09/26 22:11:51 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#ifdef FT_MATHS
int	ft_pow(int nb, int power)
{
	int	total;

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
#endif