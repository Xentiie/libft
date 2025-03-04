/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfind.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 23:41:52 by reclaire          #+#    #+#             */
/*   Updated: 2024/11/26 02:20:53 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_int.h"
#include "libft/lists.h"

t_list	*ft_lstfind2(t_list *lst, void *ptr)
{
	t_list	*curr;

	curr = lst;
	while (curr)
	{
		if (curr->content == ptr)
			FT_RET_OK(curr);
		curr = curr->next;
	}

	FT_RET_OK(NULL);
}

t_list	*ft_lstfind(t_list *lst, bool (*f)(void *, void *), void *ref)
{
	t_list	*curr;

	curr = lst;
	while (curr)
	{
		if (f(curr->content, ref))
			FT_RET_OK(curr);
		curr = curr->next;
	}

	FT_RET_OK(NULL);
}
