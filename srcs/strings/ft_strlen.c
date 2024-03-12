/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 13:38:25 by reclaire          #+#    #+#             */
/*   Updated: 2024/02/17 03:29:21 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_int.h"

U64	ft_strlen(const_string s)
{
	U64	n = 0;
	while (s[n] != '\0')
		n++;
	return (n);
}

U64	ft_wstrlen(const_wstring s)
{
	U64	n = 0;
	while (s[n] != L'\0')
		n++;
	return (n);
}
