/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 19:08:18 by reclaire          #+#    #+#             */
/*   Updated: 2024/11/26 02:20:59 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_int.h"
#include "libft/lists.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (UNLIKELY(new == NULL && ft_errno == FT_EOMEM))
		FT_RET_ERR(, ft_errno);
	if (UNLIKELY(lst == NULL || new == NULL))
		FT_RET_ERR(, FT_EINVPTR);
	
	if (*lst == NULL)
		*lst = new;
	else
	{
		if ((*lst)->prev)
		{
			new->prev = (*lst)->prev;
			(*lst)->prev->next = new;
		}
		(*lst)->prev = new;
		new->next = *lst;
		*lst = new;
	}

	FT_RET_OK();
}
