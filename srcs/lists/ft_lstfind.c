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
t_list	*ft_lstfind(t_list *lst, bool (*f)(void *, void *), void *ref)
{
	t_list	*curr;

	if (!f || !lst)
	{
		return (NULL);
	}
	curr = lst;
	while (curr)
	{
		if (f(curr->content, ref))
			return (curr);
		curr = curr->next;
	}
	return (NULL);
}
#endif