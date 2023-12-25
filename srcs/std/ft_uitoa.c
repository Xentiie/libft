/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uitoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 14:15:23 by reclaire          #+#    #+#             */
/*   Updated: 2023/09/26 22:20:37 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#ifdef FT_STD
static string compute(U64 nbr, S32 len)
{
	string	rtn;

	rtn = malloc(sizeof(U8) * (len + 1));
	rtn[len] = '\0';
	while (--len)
	{
		rtn[len] = (nbr % 10) + '0';
		nbr /= 10;
	}
	rtn[0] = (nbr % 10) + '0';
	return (rtn);
}

string ft_uitoa(U64 n)
{
	string	rtn;
	U64		nbr;

	nbr = n;
	if (nbr == 0)
		return (ft_strdup("0"));
	rtn = compute(nbr, ft_magnitude(nbr));
	if (!rtn)
		return (0);
	return (rtn);
}
#endif