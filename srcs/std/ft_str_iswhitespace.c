/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_iswhitespace.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 21:54:27 by reclaire          #+#    #+#             */
/*   Updated: 2024/02/11 23:04:40 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_int.h"

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
