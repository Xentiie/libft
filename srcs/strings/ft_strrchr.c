/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 20:57:32 by reclaire          #+#    #+#             */
/*   Updated: 2023/09/26 20:34:29 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#ifdef FT_STRINGS
const_string	ft_strrchr(const_string s, U8 c)
{
	const_string	a;

	a = NULL;
	while (*s != '\0')
	{
		if (*s == c)
			a = (char *)s;
		s++;
	}
	if (*s == c)
		a = (char *)s;
	return (a);
}
#endif