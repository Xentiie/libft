/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inetchecksum.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 04:13:32 by reclaire          #+#    #+#             */
/*   Updated: 2024/11/14 04:14:44 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_int.h"

U16 ft_inetchecksum(U16 *ptr, U64 nbytes)
{
	U64 sum;
	U16 oddbyte;
	U16 answer;

	sum = 0;
	while (nbytes > 1)
	{
		sum += *ptr++;
		nbytes -= 2;
	}

	if (nbytes == 1)
	{
		oddbyte = 0;
		*((U8 *)&oddbyte) = *(U8 *)ptr;
		sum += oddbyte;
	}

	sum = (sum >> 16) + (sum & 0xffff);
	sum += (sum >> 16);
	answer = ~sum;

	return answer;
}
