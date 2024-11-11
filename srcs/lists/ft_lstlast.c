/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 19:25:41 by reclaire          #+#    #+#             */
/*   Updated: 2024/11/10 21:48:57 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_int.h"
#include "libft/lists.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*current;
	t_list	*previous;

	if (UNLIKELY(lst == NULL))
		__FTRETURN_ERR(NULL, FT_EINVPTR);

	current = lst;
	while (current != NULL)
	{
		previous = current;
		current = current->next;
	}
	
	__FTRETURN_OK(previous);
}
