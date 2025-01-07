/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 15:37:41 by reclaire          #+#    #+#             */
/*   Updated: 2024/12/31 16:07:08 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_int.h"
#include "libft/lists.h"
#include "libft/strings.h"

bool ft_path_parse(t_list **lst, const_string path)
{
	U64 i;
	U64 st;
	t_list *new;
	string part;

	i = 0;
	st = 0;
	while (path[i])
	{
		while (path[i] != '/')
		{
			if (!path[i])
				goto end;
			i++;
		}

		if (UNLIKELY((part = ft_substr(path, st, i - st)) == NULL))
			return FALSE;
		if (UNLIKELY((new = ft_lstnew(part)) == NULL))
			return FALSE;
		ft_lstadd_back(lst, new);
		i++;
		while (path[i] == '/')
			i++;
		st = i;
	}

end:
	if (st < i)
	{
		if (UNLIKELY((part = ft_substr(path, st, i - st)) == NULL))
			return FALSE;
		if (UNLIKELY((new = ft_lstnew(part)) == NULL))
			return FALSE;
		ft_lstadd_back(lst, new);
	}

	return TRUE;
}
