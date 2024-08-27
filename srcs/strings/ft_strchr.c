/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 20:57:32 by reclaire          #+#    #+#             */
/*   Updated: 2024/02/11 23:05:21 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_int.h"

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
