/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 21:47:40 by reclaire          #+#    #+#             */
/*   Updated: 2024/02/11 23:09:31 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_int.h"

const_string	ft_strnstr(const_string str, const_string to_find, U64 len)
{
	U64	istr = 0;
	S32	ifind = 0;
	S32	xfind;

	if ((to_find[ifind]) == '\0' && ft_strlen(to_find) <= len)
		return (str);
	while (str[istr] != '\0' && istr < len)
	{
		if (str[istr] == to_find[ifind])
		{
			xfind = istr;
			while (str[istr++] == to_find[ifind++])
			{
				if (to_find[ifind] == '\0' && ft_strlen(to_find) + xfind <= len)
					return (str + xfind);
			}
			istr = xfind;
			ifind = 0;
		}
		istr++;
	}
	return (NULL);
}
