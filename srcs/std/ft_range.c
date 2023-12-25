/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_range.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 21:11:58 by reclaire          #+#    #+#             */
/*   Updated: 2023/09/27 17:30:40 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#ifdef FT_STD
S32	*ft_range(S32 min, S32 max)
{
	S32	size;
	S32	i;
	S32	counter;
	S32	*output;

	i = 0;
	size = max - min;
	if (size <= 0)
		return (NULL);
	output = malloc(sizeof(S32) * size + 1);
	counter = min;
	while (i < size)
	{
		output[i] = counter;
		counter++;
		i++;
	}
	return (output);
}
#endif