/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uitoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 14:15:23 by reclaire          #+#    #+#             */
/*   Updated: 2024/02/11 23:04:46 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_int.h"

static string compute(U64 nbr, S32 len)
{
	string	rtn;

	rtn = malloc(sizeof(U8) * (len + 1));
	if (rtn == NULL)
		__FTRETURN_ERR(NULL, FT_EOMEM);

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
	{
		rtn = ft_strdup("0");
		if (rtn == NULL)
			__FTRETURN_ERR(NULL, ft_errno);
		__FTRETURN_OK(rtn);
	}
	rtn = compute(nbr, ft_magnitude(nbr));
	if (rtn == NULL)
		__FTRETURN_ERR(NULL, ft_errno);
	__FTRETURN_OK(rtn);
}
