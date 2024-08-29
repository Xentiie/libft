/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_isflt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 21:18:11 by reclaire          #+#    #+#             */
/*   Updated: 2024/08/29 18:39:43 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_int.h"

bool	ft_str_isflt(string str)
{
	while (*str == '-' || *str == '+')
		str++;

	while (*str && ft_isdigit(*str))
		str++;

	if (*str == '\0')
		return TRUE;

	if (*str == '.')
		return ft_str_isdigit(++str);
	else
		return FALSE;
}
