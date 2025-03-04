/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 20:21:20 by reclaire          #+#    #+#             */
/*   Updated: 2024/11/26 02:20:59 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_int.h"

void	*ft_memcpy(void *dst, void const *src, U64 n)
{
	if (UNLIKELY(dst == NULL || src == NULL))
		FT_RET_ERR(dst, FT_EINVPTR);

	U64	i = 0;
	while (i < n)
	{
		((U8 *)dst)[i] = ((U8 *)src)[i];
		i++;
	}
	FT_RET_OK(dst);
}
