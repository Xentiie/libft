/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path_clean.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 03:33:50 by reclaire          #+#    #+#             */
/*   Updated: 2024/12/31 16:02:43 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_int.h"
#include "libft/lists.h"

#include <stdlib.h>

void ft_path_partial_absolute(t_list **path)
{
	t_list *curr;
	t_list *nxt;
	string p;
	string p_prev;

	curr = *path;
	while (curr)
	{
		nxt = curr->next;
		p = (string)curr->content;

		if (p[0] == '.' && p[1] == '\0')
			/* remove useless '.' */
			ft_lstremove(path, curr, free);
		else if (p[0] == '.' && p[1] == '.' && p[2] == '\0' && curr->prev)
		{ /* remove '..' */
			p_prev = curr->prev->content;
			if (!(p_prev[0] == '.' && p[1] == '.' && p[2] == '\0'))
			{
				ft_lstremove(path, curr->prev, free);
				ft_lstremove(path, curr, free);
			}
		}
		curr = nxt;
	}
}
