/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstremove.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 18:30:13 by reclaire          #+#    #+#             */
/*   Updated: 2024/11/26 02:20:59 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_int.h"
#include "libft/lists.h"

bool	ft_lstremove2(t_list **lst, void *content, void (*del)(void *))
{
	t_list	*prev;
	t_list	*curr;

	if (UNLIKELY(lst == NULL))
		FT_RET_ERR(FALSE, FT_EINVPTR);

	curr = *lst;
	prev = NULL;
	while (curr)
	{
		if (content == curr->content)
		{
			if (prev == NULL)
			{
				(*lst) = curr->next;
				(*lst)->prev = NULL;
			}
			else
			{
				prev->next = curr->next;
				if (prev->next)
					prev->next->prev = prev;
			}

			ft_lstdelone(curr, del);
			if (ft_errno != FT_OK)
				FT_RET_ERR(FALSE, ft_errno);

			FT_RET_OK(TRUE);
		}
		prev = curr;
		curr = curr->next;
	}
	FT_RET_OK(FALSE);
}

bool	ft_lstremove(t_list **lst, t_list *elem, void (*del)(void *))
{
	t_list	*prev;
	t_list	*curr;

	if (UNLIKELY(lst == NULL || elem == NULL))
		FT_RET_ERR(FALSE, FT_EINVPTR);

	curr = *lst;
	prev = NULL;
	while (curr)
	{
		if (elem == curr)
		{
			if (prev == NULL)
			{
				(*lst) = curr->next;
				if (*lst)
					(*lst)->prev = NULL;
			}
			else
			{
				prev->next = curr->next;
				if (prev->next)
					prev->next->prev = prev;
			}

			ft_lstdelone(curr, del);
			if (ft_errno != FT_OK)
				FT_RET_ERR(FALSE, ft_errno);

			FT_RET_OK(TRUE);
		}
		prev = curr;
		curr = curr->next;
	}
	FT_RET_OK(FALSE);
}


bool	ft_lst_softremove(t_list **lst, t_list *elem)
{
	t_list	*prev;
	t_list	*curr;

	if (UNLIKELY(lst == NULL || elem == NULL))
		FT_RET_ERR(FALSE, FT_EINVPTR);

	curr = *lst;
	prev = NULL;
	while (curr)
	{
		if (elem == curr)
		{
			if (prev == NULL)
			{
				(*lst) = curr->next;
				if (*lst)
					(*lst)->prev = NULL;
			}
			else
			{
				prev->next = curr->next;
				if (prev->next)
					prev->next->prev = prev;
			}

			FT_RET_OK(TRUE);
		}
		prev = curr;
		curr = curr->next;
	}
	FT_RET_OK(FALSE);
}
