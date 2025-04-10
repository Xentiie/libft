/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 13:38:25 by reclaire          #+#    #+#             */
/*   Updated: 2025/04/01 02:48:11 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_int.h"

U64	ft_strlen(const_string s)
{
	U64	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return i;
}

U64 ft_strnlen(const_string s, U64 maxlen)
{
	U64	i;

	i = 0;
	while (i < maxlen && s[i] != '\0')
		i++;
	return i;
}
