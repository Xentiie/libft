/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 20:57:32 by reclaire          #+#    #+#             */
/*   Updated: 2023/09/26 20:34:12 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#ifdef FT_STRINGS
const_string	ft_strnchr(const_string s, U8 c, U64 len)
{
	U64	i = 0;
	while (s[i] && i < len)
	{
		if (s[i] == c)
			return (s+i);
		i++;
	}
	if (s[i] == c)
		return (s+i);
	return (NULL);
}
#endif