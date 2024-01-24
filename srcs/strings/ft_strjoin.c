/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 15:42:29 by reclaire          #+#    #+#             */
/*   Updated: 2023/09/26 22:16:16 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#ifdef FT_STRINGS
string	ft_strjoin(const_string s1, const_string s2)
{
	U64		s1_len;
	U64		s2_len;
	U64		i;
	string	new;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	new = malloc((s1_len + s2_len + 1) * sizeof(char));
	if (new == NULL)
		__FTRETURN_ERR(NULL, FT_EOMEM);

	i = 0;
	while (i < s1_len)
	{
		new[i] = s1[i];
		i++;
	}
	while (i < s2_len + s1_len)
	{
		new[i] = s2[i - s1_len];
		i++;
	}
	new[i] = '\0';
	__FTRETURN_OK(new);
}
#endif