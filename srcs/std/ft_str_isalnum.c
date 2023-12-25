/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_isalnum.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 21:54:27 by reclaire          #+#    #+#             */
/*   Updated: 2023/09/26 21:55:07 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#ifdef FT_STD
bool	ft_str_isalnum(string str)
{
	U64	i = 0;
	while (str[i])
	{
		if (!ft_isalnum(str[i]))
			return (FALSE);
		i++;
	}
	return (TRUE);
}
#endif