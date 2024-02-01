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

bool ft_lstremoveif(t_list **lst, void (*del)(void *),
					bool (*f)(), void *ref)
{
	t_list *prev;
	t_list *curr;
	bool found = FALSE;

	if (lst == NULL || f == NULL)
		__FTRETURN_ERR(FALSE, FT_EINVPTR);

	curr = *lst;
	prev = NULL;
	while (curr)
	{
		if (f(curr->content, ref))
		{
			if (prev == NULL)
				(*lst) = curr->next;
			else
				prev->next = curr->next;
			ft_lstdelone(curr, del);
			if (ft_errno != FT_OK)
				__FTRETURN_ERR(FALSE, ft_errno);
			found = TRUE;
		}
		prev = curr;
		curr = curr->next;
	}
	__FTRETURN_OK(found);
}
#endif