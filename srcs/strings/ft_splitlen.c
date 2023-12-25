/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitlen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 15:06:47 by reclaire          #+#    #+#             */
/*   Updated: 2023/09/26 20:36:03 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#ifdef FT_STRINGS
U64	ft_splitlen(const_string *split)
{
	U64	i = 0;
	while (split[i])
		i++;
	return i;
}
#endif