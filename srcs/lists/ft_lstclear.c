/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 20:05:58 by reclaire          #+#    #+#             */
/*   Updated: 2024/02/11 20:50:32 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_int.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*old_elem;

	if (lst == NULL || *lst == NULL)
		__FTRETURN_ERR(, FT_EINVPTR);
	
	while (*lst)
	{
		if (del)
			del((*lst)->content);
		old_elem = *lst;
		*lst = old_elem->next;
		free(old_elem);
	}
	*lst = NULL;

	__FTRETURN_OK();
}
