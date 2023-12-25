/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 14:51:38 by reclaire          #+#    #+#             */
/*   Updated: 2023/09/26 22:16:34 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#ifdef FT_STRINGS
string	ft_strdup(const_string s1)
{
	int		l;
	string	dup;

	l = 0;
	while (s1[l] != '\0')
		l++;
	dup = malloc((l + 1) * sizeof(U8));
	if (!dup)
		return NULL;
	dup[l] = '\0';
	l = 0;
	while (s1[l] != '\0')
	{
		dup[l] = s1[l];
		l++;
	}
	return (dup);
}
#endif