/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 14:51:38 by reclaire          #+#    #+#             */
/*   Updated: 2024/02/11 23:05:34 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_int.h"

string	ft_strdup(const_string str)
{
	if (str == NULL)
		__FTRETURN_ERR(NULL, FT_EINVPTR);

	U64 l = ft_strlen(str);
	string dup = malloc((l + 1) * sizeof(U8));
	if (dup == NULL)
		__FTRETURN_ERR(NULL, FT_EOMEM);

	U64 c = 0;
	while (c < l)
	{
		dup[c] = str[c];
		c++;
	}
	dup[c] = '\0';

	__FTRETURN_OK(dup);
}
