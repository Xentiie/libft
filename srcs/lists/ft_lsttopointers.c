/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lsttopointers.c                         :+:      :+:    :+:   */
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
void	**ft_lsttopointers(t_list *lst)
{
	int		lst_len;
	void	**out;
	t_list	*curr;
	int		i;

	if (lst == NULL)
		__FTRETURN_ERR(NULL, FT_EINVPTR);
	
	lst_len = ft_lstsize(lst);
	out = malloc(sizeof(void *) * (lst_len + 1));
	if (out == NULL)
		__FTRETURN_ERR(NULL, FT_EOMEM);

	curr = lst;
	i = 0;
	while (curr)
	{
		out[i] = curr->content;
		curr = curr->next;
		i++;
	}
	out[i] = NULL;
	__FTRETURN_OK(out);
}
#endif