/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfind.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 23:41:52 by reclaire          #+#    #+#             */
/*   Updated: 2023/09/26 22:07:32 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#ifdef FT_LISTS

t_list	*ft_lstfind2(t_list *lst, void *ptr)
{
	t_list	*curr;

	if (lst == NULL)
		__FTRETURN_ERR(NULL, FT_EINVPTR);

	curr = lst;
	while (curr)
	{
		if (curr->content == ptr)
			__FTRETURN_OK(curr);
		curr = curr->next;
	}

	__FTRETURN_OK(NULL);
}

t_list	*ft_lstfind(t_list *lst, bool (*f)(void *, void *), void *ref)
{
	t_list	*curr;

	if (f == NULL || lst == NULL)
		__FTRETURN_ERR(NULL, FT_EINVPTR);

	curr = lst;
	while (curr)
	{
		if (f(curr->content, ref))
			__FTRETURN_OK(curr);
		curr = curr->next;
	}

	__FTRETURN_OK(NULL);
}
#endif