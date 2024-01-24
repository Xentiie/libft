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

bool	ft_lstremove2(t_list **lst, void *content, void (*del)(void *))
{
	t_list	*prev;
	t_list	*curr;

	if (lst == NULL)
		__FTRETURN_ERR(FALSE, FT_EINVPTR);

	curr = *lst;
	prev = NULL;
	while (curr)
	{
		if (content == curr->content)
		{
			if (prev == NULL)
				(*lst) = curr->next;
			else
				prev->next = curr->next;
			ft_lstdelone(curr, del);
			if (ft_errno != FT_OK)
				__FTRETURN_ERR(FALSE, ft_errno);

			__FTRETURN_OK(TRUE);
		}
		prev = curr;
		curr = curr->next;
	}
	__FTRETURN_OK(FALSE);
}

bool	ft_lstremove(t_list **lst, t_list *elem, void (*del)(void *))
{
	t_list	*prev;
	t_list	*curr;

	if (lst == NULL || elem == NULL)
		__FTRETURN_ERR(FALSE, FT_EINVPTR);

	curr = *lst;
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
			if (ft_errno != FT_OK)
				__FTRETURN_ERR(FALSE, ft_errno);

			__FTRETURN_OK(TRUE);
		}
		prev = curr;
		curr = curr->next;
	}
	__FTRETURN_OK(FALSE);
}
#endif