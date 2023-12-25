/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_iswhitespace.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 21:54:27 by reclaire          #+#    #+#             */
/*   Updated: 2023/09/26 22:00:10 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#ifdef FT_STD
bool	ft_str_iswhitespace(string str)
{
	U64	i = 0;
	while (str[i])
	{
		if (!ft_iswhitespace(str[i]))
			return (FALSE);
		i++;
	}
	return (TRUE);
}
#endif