/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 20:08:26 by reclaire          #+#    #+#             */
/*   Updated: 2023/09/26 21:51:29 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#ifdef FT_STD
void	*ft_memset(void *b, U8 c, U64 len)
{
	U64	i;
	U8	*str;

	i = 0;
	str = b;
	while (i < len)
	{
		str[i] = c;
		i++;
	}
	return (str);
}
#endif