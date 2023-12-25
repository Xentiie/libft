/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 20:05:58 by reclaire          #+#    #+#             */
/*   Updated: 2023/09/26 22:17:37 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#ifdef FT_LISTS
void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*old_elem;

	if (!lst || !(*lst))
		return ;
	while (*lst)
	{
		if (del)
			del((*lst)->content);
		old_elem = *lst;
		*lst = old_elem->next;
		free(old_elem);
	}
	*lst = NULL;
}
#endif