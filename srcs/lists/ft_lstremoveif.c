/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstremoveif.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 02:05:10 by reclaire          #+#    #+#             */
/*   Updated: 2023/10/09 22:03:06 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#ifdef FT_LISTS

static void	ft_lstremoveif2(t_list **lst, t_list *prev,
		t_list *curr, void (*del)(void *))
{
	if (prev == NULL)
		(*lst) = curr->next;
	else
	{
		prev->next = curr->next;
		if (ft_lstsize(prev) == 1)
			prev->next = NULL;
	}
	ft_lstdelone(curr, del);
}

bool	ft_lstremoveif(t_list **lst, void (*del)(void *),
			bool (*f)(), void *ref)
{
	t_list	*prev;
	t_list	*curr;
	bool	found = FALSE;

	if (!f || !lst || !(*lst))
		return (-1);
	curr = (*lst);
	prev = NULL;
	while (curr)
	{
		if (f(curr->content, ref))
		{
			ft_lstremoveif2(lst, prev, curr, del);
			found = TRUE;
		}
		prev = curr;
		curr = curr->next;
	}
	return (found);
}
#endif