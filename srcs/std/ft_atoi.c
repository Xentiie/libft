/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 13:51:00 by reclaire          #+#    #+#             */
/*   Updated: 2023/09/26 21:51:35 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#ifdef FT_STD
S32	ft_atoi(const_string str, U64 *len)
{
	S8		neg = 1;
	U64		i = 0;
	U64		result = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
		neg = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (ft_isdigit(str[i]) && str[i] != '\0')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	if (result > 9223372036854775807 && neg < 0)
		return (0);
	if (result >= 9223372036854775807 && neg > 0)
		return (0);
	if (len)
		*len = i;
	return (result*neg);
}
#endif