/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 18:27:24 by reclaire          #+#    #+#             */
/*   Updated: 2025/01/22 18:28:57 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_int.h"

#include <stdlib.h>

void *ft_calloc(U64 n, U64 size)
{
	void *ptr;

	if (UNLIKELY((ptr = malloc(n * size)) == NULL))
		return NULL;
	ft_bzero(ptr, n * size);
	return ptr;
}
