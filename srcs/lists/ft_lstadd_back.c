/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 19:32:58 by reclaire          #+#    #+#             */
/*   Updated: 2024/02/11 20:50:33 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_int.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*current_last;

	if (lst == NULL)
		__FTRETURN_ERR(, FT_EINVPTR);
	if (lst)
	{
		if (*lst == NULL)
			*lst = new;
		else
		{
			current_last = ft_lstlast(*lst);
			current_last->next = new;
			new->prev = current_last;
		}
	}
	__FTRETURN_OK();
}
