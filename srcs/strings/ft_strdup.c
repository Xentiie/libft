/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 14:51:38 by reclaire          #+#    #+#             */
/*   Updated: 2025/06/08 02:14:34 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_int.h"
#include "libft/strings.h"

#include <stdlib.h>

string ft_strdup(const_string str)
{
	return ft_strdup_l(str, NULL);
}

string ft_strdup_l(const_string str, U64 *len)
{
	U64 l;
	string dup;

	if (len == NULL)
		len = &l;

	if (UNLIKELY(str == NULL))
	{
		*len = 0;
		FT_RET_ERR(NULL, FT_EINVPTR);
	}

	*len = ft_strlen(str);
	if (UNLIKELY((dup = ftalloc(sizeof(U8) * ((*len) + 1))) == NULL))
	{
		*len = 0;
		FT_RET_ERR(NULL, FT_EOMEM);
	}

	ft_memcpy(dup, str, (*len) + 1);
	FT_RET_OK(dup);
}

string ft_strndup(const_string str, U64 n)
{
	return ft_strndup_l(str, n, NULL);
}

string ft_strndup_l(const_string str, U64 n, U64 *len)
{
	U64 l;
	string dup;

	if (UNLIKELY(str == NULL))
	{
		if (len)
			*len = 0;
		FT_RET_ERR(NULL, FT_EINVPTR);
	}

	l = 0;
	while (l < n && str[l])
		l++;

	if (UNLIKELY((dup = ftalloc((sizeof(U8) * (l + 1)))) == NULL))
	{
		if (len)
			*len = 0;
		FT_RET_ERR(NULL, FT_EOMEM);
	}

	ft_memcpy(dup, str, l);
	dup[l] = '\0';
	if (len)
		*len = l;
	FT_RET_OK(dup);
}
