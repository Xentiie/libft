/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 14:51:38 by reclaire          #+#    #+#             */
/*   Updated: 2023/09/26 22:16:34 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#ifdef FT_STRINGS
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

	__FTRETURN_OK(dup);
}
#endif