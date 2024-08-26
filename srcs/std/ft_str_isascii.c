/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_isascii.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 21:54:27 by reclaire          #+#    #+#             */
/*   Updated: 2024/02/11 23:04:26 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_int.h"

bool	ft_str_isascii(string str)
{
	U64	i = 0;
	while (str[i])
	{
		if (!ft_isascii(str[i]))
			return (FALSE);
		i++;
	}
	return (TRUE);
}
