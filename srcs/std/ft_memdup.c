/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 17:49:36 by reclaire          #+#    #+#             */
/*   Updated: 2023/09/26 22:14:37 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#ifdef FT_STD
void	*ft_memdup(const void *p, U64 n)
{
	void	*data;

	data = malloc(n);
	if (!data)
		return NULL;
	ft_memcpy(data, p, n);
	return (data);
}
#endif