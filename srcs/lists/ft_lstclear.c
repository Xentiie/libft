/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 20:05:58 by reclaire          #+#    #+#             */
/*   Updated: 2024/11/26 02:20:59 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_int.h"
#include "libft/lists.h"

#include <stdlib.h>

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*old_elem;

	if (UNLIKELY(lst == NULL))
		FT_RET_ERR(, FT_EINVPTR);
	if (*lst == NULL)
		FT_RET_OK();

	while (*lst)
	{
		if (del)
			del((*lst)->content);
		old_elem = *lst;
		*lst = old_elem->next;
		free(old_elem);
	}
	*lst = NULL;

	FT_RET_OK();
}
