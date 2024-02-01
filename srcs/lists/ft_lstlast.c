/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 19:25:41 by reclaire          #+#    #+#             */
/*   Updated: 2023/09/26 22:07:11 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#ifdef FT_LISTS
t_list	*ft_lstlast(t_list *lst)
{
	t_list	*current;
	t_list	*previous;

	if (lst == NULL)
		__FTRETURN_ERR(NULL, FT_EINVPTR);

	current = lst;
	while (current != NULL)
	{
		previous = current;
		current = current->next;
	}
	
	__FTRETURN_OK(previous);
}
#endif