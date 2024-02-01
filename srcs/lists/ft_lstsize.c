/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 19:11:27 by reclaire          #+#    #+#             */
/*   Updated: 2023/09/26 22:07:06 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#ifdef FT_LISTS
U64	ft_lstsize(t_list *lst)
{
	t_list	*current;

	U64 size = 0;
	current = lst;
	while (current)
	{
		size++;
		current = current->next;
	}
	__FTRETURN_OK(size);
}
#endif