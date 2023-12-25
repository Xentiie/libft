/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 18:19:15 by reclaire          #+#    #+#             */
/*   Updated: 2023/09/26 20:35:27 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#ifdef FT_STRINGS
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
#endif