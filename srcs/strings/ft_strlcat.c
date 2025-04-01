/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 16:22:43 by estarck           #+#    #+#             */
/*   Updated: 2025/04/01 02:48:21 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_int.h"
#include "libft/strings.h"

U64 ft_strlcat(string dest, const_string src, U64 size)
{
	size_t srclen;
	size_t dstlen;

	srclen = ft_strlen(src);
	dstlen = ft_strnlen(dest, size);
	if (dstlen == size)
		return size + srclen;
	if (srclen < size - dstlen)
		ft_memcpy(dest + dstlen, src, srclen + 1);
	else
	{
		ft_memcpy(dest + dstlen, src, size - dstlen - 1);
		dest[size - 1] = '\0';
	}
	return dstlen + srclen;
}
