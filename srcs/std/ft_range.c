/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_range.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 21:11:58 by reclaire          #+#    #+#             */
/*   Updated: 2024/11/10 22:45:18 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_int.h"

#include <stdlib.h>

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
	if (UNLIKELY((output = malloc(sizeof(S32) * size + 1)) == NULL))
		__FTRETURN_ERR(NULL, FT_EOMEM);

	counter = min;
	while (i < size)
	{
		output[i] = counter;
		counter++;
		i++;
	}
	__FTRETURN_OK(output);
}
