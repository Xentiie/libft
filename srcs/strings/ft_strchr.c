/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 20:57:32 by reclaire          #+#    #+#             */
/*   Updated: 2023/09/26 20:34:06 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#ifdef FT_STRINGS
const_string	ft_strchr(const_string s, U8 c)
{
	S32 i = 0;
	while (s[i])
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