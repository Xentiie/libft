/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 17:49:36 by reclaire          #+#    #+#             */
/*   Updated: 2025/06/08 02:14:34 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_int.h"

#include <stdlib.h>

void	*ft_memdup(const void *p, U64 n)
{
	void	*data;

	if (UNLIKELY((data = ftalloc(n)) == NULL))
		FT_RET_ERR(NULL, FT_EOMEM);
	ft_memcpy(data, p, n);
	FT_RET_OK(data);
}
