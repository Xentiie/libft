/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 18:19:15 by reclaire          #+#    #+#             */
/*   Updated: 2024/02/11 23:14:27 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_int.h"

string	ft_strmapi(const_string s, U8 (*f)(U64, U8))
{
	string	new;

	new = ft_strdup(s);
	if (!new)
		return (NULL);

	U64	i = 0;
	while (s[i] != '\0')
	{
		new[i] = f(i, s[i]);
		i++;
	}
	return (new);
}
