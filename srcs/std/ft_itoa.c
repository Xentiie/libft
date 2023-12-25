/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 20:49:50 by reclaire          #+#    #+#             */
/*   Updated: 2023/09/26 22:15:56 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#ifdef FT_STD
static S32	num_digits(S64 n)
{
	S32	r;

	r = 0;
	if (n < 0)
	{
		n *= -1;
		r++;
	}
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n /= 10;
		r++;
	}
	return (r);
}

void	check_negative(S64 *nb, string str)
{
	if (*nb < 0)
	{
		*nb *= -1;
		str[0] = '-';
	}
}

string	ft_itoa(S32 n)
{
	S64		nb;
	S32		i;
	string	str;

	nb = n;
	i = num_digits(nb);
	str = malloc((i + 1) * sizeof(U8));
	str[i--] = '\0';
	if (nb == 0)
	{
		str[0] = '0';
		return (str);
	}
	check_negative(&nb, str);
	while (nb > 0)
	{
		str[i] = (nb % 10) + '0';
		nb /= 10;
		i--;
	}
	return (str);
}
#endif