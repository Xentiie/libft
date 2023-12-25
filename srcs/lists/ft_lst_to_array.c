/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_to_array.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 01:21:21 by reclaire          #+#    #+#             */
/*   Updated: 2023/09/26 22:06:23 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#if defined(FT_LISTS) && defined(FT_ARRAYS)
int	ft_lst_to_array(t_list *lst, t_array array, U64 elem_size)
{
	t_list	*curr;
	int		i;

	if (!lst)
		return -1;
	curr = lst;
	i = 0;
	while (curr)
	{
		ft_array_append(array, (ft_memdup)(curr->content, elem_size), NULL);
		curr = curr->next;
		i++;
	}
	return 0;
}
#endif