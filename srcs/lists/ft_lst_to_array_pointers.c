/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_to_array_pointers.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 07:06:20 by estarck           #+#    #+#             */
/*   Updated: 2023/09/27 16:43:17 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#ifdef FT_LISTS
void	**ft_lst_to_array_pointers(t_list *lst)
{
	int		lst_len;
	void	**out;
	t_list	*curr;
	int		i;

	if (!lst)
		return NULL;
	lst_len = ft_lstsize(lst);
	out = malloc(sizeof(void *) * (lst_len + 1));
	curr = lst;
	i = 0;
	while (curr)
	{
		out[i] = curr->content;
		curr = curr->next;
		i++;
	}
	out[i] = NULL;
	return (out);
}
#endif