/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 15:52:44 by reclaire          #+#    #+#             */
/*   Updated: 2025/06/08 02:14:34 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_int.h"
#include "libft/strings.h"

#include <stdlib.h>

string	ft_strtrim(const_string s1, const_string set)
{
	U64		start;
	U64		end;
	string	new;

	start = 0;
	while (ft_strgetindex(set, s1[start]) != -1)
		start++;
	end = ft_strlen(s1) - 1;
	while (ft_strgetindex(set, s1[end]) != -1)
		end--;
	end++;
	if (start >= end)
	{
		new = ft_strdup("");
		if (new == NULL)
			FT_RET_ERR(NULL, ft_errno);
		FT_RET_OK(new);
	}

	new = ftalloc((end - start + 1) * sizeof(char));
	if (new == NULL)
		FT_RET_ERR(NULL, FT_EOMEM);
	
	ft_strlcpy(new, (char *)(s1 + start), end - start + 1);
	FT_RET_OK(new);
}
