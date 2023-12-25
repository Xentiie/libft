/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 16:22:43 by estarck           #+#    #+#             */
/*   Updated: 2023/09/26 19:59:08 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#ifdef FT_STRINGS
U64	ft_strlcat(string dest, const_string src, U64 size)
{
	U64	i;
	U64	j;
	U64	lsrc;

	i = 0;
	j = 0;
	lsrc = 0;
	while (src[lsrc] != '\0')
		lsrc++;
	while (dest[i] && i < size)
		i++;
	if (!size)
		return (size + lsrc);
	while (src[j] && (i + j < size - 1))
	{
		dest[i + j] = src[j];
		j++;
	}
	if (i < size)
		dest[i + j] = '\0';
	return (i + lsrc);
}
#endif