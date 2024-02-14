/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 17:49:36 by reclaire          #+#    #+#             */
/*   Updated: 2024/02/11 23:03:10 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_int.h"

void	*ft_memdup(const void *p, U64 n)
{
	void	*data;

	data = malloc(n);
	if (data == NULL)
		__FTRETURN_ERR(NULL, FT_EOMEM);
	ft_memcpy(data, p, n);
	__FTRETURN_OK(data);
}
