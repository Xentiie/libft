/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 19:08:18 by reclaire          #+#    #+#             */
/*   Updated: 2023/09/26 22:06:56 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#ifdef FT_LISTS
void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!lst)
		return ;
	if (!(*lst))
	{
		(*lst) = new;
		return ;
	}
	(*lst)->prev = new;
	new->next = *lst;
	*lst = new;
}
#endif