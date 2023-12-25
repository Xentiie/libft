/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 15:39:44 by reclaire          #+#    #+#             */
/*   Updated: 2023/09/26 22:16:42 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#ifdef FT_STRINGS
string ft_substr(const_string s, U64 start, U64 len)
{
	string	r;

	if (ft_strlen(s) <= start)
		return (ft_memdup(&(char){0}, 1));
	r = malloc(sizeof(char) * (len + 1));
	ft_strlcpy(r, (s + start), len + 1);
	return (r);
}
#endif