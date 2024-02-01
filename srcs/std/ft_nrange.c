/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nrange.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 10:28:32 by reclaire          #+#    #+#             */
/*   Updated: 2023/09/26 22:15:00 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#ifdef FT_STD
S32	ft_nrange(S32 **range, S32 min, S32 max)
{
	S32	size;
	S32	i;
	S32	counter;
	S32	*output;

	if (min >= max)
	{
		range = NULL;
		return (0);
	}
	size = max - min;
	output = malloc(sizeof(int) * size);
	if (output == NULL)
	{
		*range = NULL;
		__FTRETURN_ERR(-1, FT_EOMEM);
	}

	i = 0;
	counter = min;
	while (i < size)
	{
		output[i] = counter;
		counter++;
		i++;
	}
	*range = output;
	__FTRETURN_OK(size);
}
#endif