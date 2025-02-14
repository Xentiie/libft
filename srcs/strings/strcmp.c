/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strcmp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 09:19:11 by reclaire          #+#    #+#             */
/*   Updated: 2025/01/30 01:29:50 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_int.h"

S32	ft_strcmp(const_string s1, const_string s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return *s1 - *s2;
		s1++;
		s2++;
	}
	return (!*s1 && *s2) ? -*s2 : (((*s1 && !*s2)) ? *s1 : 0);
}

S32	ft_strncmp(const_string s1, const_string s2, U64 n)
{
	U32 i;

	if (n == 0)
		return 0;
	i = 0;
	while ((i < n - 1) &&
		s1[i] &&
		s2[i] &&
		s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

S32 ft_strcasecmp(const_string s1, const_string s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return *s1 - *s2;
		s1++;
		s2++;
	}
	return (!*s1 && *s2) ? -*s2 : (((*s1 && !*s2)) ? *s1 : 0);
}

S32 ft_strncasecmp(const_string s1, const_string s2, U64 n)
{
	
}
