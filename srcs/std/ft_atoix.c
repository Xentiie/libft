/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoix.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 17:21:01 by reclaire          #+#    #+#             */
/*   Updated: 2023/09/26 21:52:06 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#ifdef FT_STD

U32	ft_atoix(const_string ptr, U64 *len)
{
	U64	count = 0;
	U32	v = 0;
    while (1)
    {
        if (ptr[count] >= '0' && ptr[count] <= '9')         v = v * 16 + ptr[count] - '0';
        else if (ptr[count] >= 'A' && ptr[count] <= 'F')    v = v * 16 + ptr[count] - 'A' + 10;
        else if (ptr[count] >= 'a' && ptr[count] <= 'f')    v = v * 16 + ptr[count] - 'a' + 10;
        else                                    break;
		count++;
    }
	if (len)
		*len = count;
	return v;
}
#endif