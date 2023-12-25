/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 14:37:08 by reclaire          #+#    #+#             */
/*   Updated: 2023/10/09 22:03:57 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#ifdef FT_STD
void	*ft_calloc(U64 count, U64 size)
{
	U64		i;
	void				*a;

	i = 0;
	a = malloc(size * count);
	while (i < size * count)
	{
		((char *)a)[i] = '\0';
		i++;
	}
	return (a);
}
#endif