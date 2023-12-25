/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 09:56:23 by estarck           #+#    #+#             */
/*   Updated: 2023/09/26 19:59:00 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#ifdef FT_STRINGS
string	ft_strcat(string dest, const_string src)
{
	U64	idest = 0;
	U64	isrc = 0;
	while (dest[idest] != '\0')
		idest++;
	while (src[isrc] != '\0')
	{
		dest[idest] = src[isrc];
		idest++;
		isrc++;
	}
	dest[idest] = '\0';
	return (dest);
}
#endif