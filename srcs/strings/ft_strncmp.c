/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 09:56:23 by estarck           #+#    #+#             */
/*   Updated: 2023/09/26 20:34:51 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#ifdef FT_STRINGS
S32	ft_strncmp(const_string s1, const_string s2, U64 n)
{
	if (n == 0)
		return 0;

	U32 i = 0;
	while ((i < n - 1) &&
		s1[i] &&
		s1[i] == s2[i] &&
		s1[i] != '\0' &&
		s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}
#endif