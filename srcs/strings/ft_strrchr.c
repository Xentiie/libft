/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 20:57:32 by reclaire          #+#    #+#             */
/*   Updated: 2024/02/11 23:09:35 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_int.h"

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
