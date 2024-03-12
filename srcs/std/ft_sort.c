/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 16:23:40 by reclaire          #+#    #+#             */
/*   Updated: 2024/02/22 04:20:05 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_int.h"

#define INDEX(i) ( ((U8 *)a) + ((i) * elem_size) )

void ft_sort(void *a, U64 elem_size, U64 array_size, S32 (*key)(void *, void *))
{
	bool swapped;
	for (U64 i = 0; i < array_size - 1; i++)
	{
		swapped = FALSE;
		for (U64 j = 0; j < array_size - i - 1; j++)
		{
			if (key(INDEX(j), INDEX(j+1)) > 0)
			{
				void *tmp = ft_memdup(INDEX(j), elem_size);
				ft_memcpy(INDEX(j), INDEX(j+1), elem_size);
				ft_memcpy(INDEX(j+1), tmp, elem_size);
				free(tmp);
				swapped = TRUE;
			}
		}
		if (!swapped)
			return;
	}
}
