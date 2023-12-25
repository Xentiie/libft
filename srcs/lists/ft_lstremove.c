/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstremove.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 18:30:13 by reclaire          #+#    #+#             */
/*   Updated: 2023/09/26 22:06:41 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#ifdef FT_LISTS
bool	ft_lstremove(t_list **lst, t_list *elem, void (*del)(void *))
{
	t_list	*prev;
	t_list	*curr;

	if (!lst || !(*lst) || !elem)
		return (-1);
	curr = (*lst);
	prev = NULL;
	while (curr)
	{
		if (elem == curr)
		{
			if (prev == NULL)
				(*lst) = curr->next;
			else
				prev->next = curr->next;
			ft_lstdelone(curr, del);
			return (TRUE);
		}
		prev = curr;
		curr = curr->next;
	}
	return (FALSE);
}
#endif