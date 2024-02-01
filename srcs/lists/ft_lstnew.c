/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 16:42:40 by reclaire          #+#    #+#             */
/*   Updated: 2023/09/26 22:17:20 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#ifdef FT_LISTS
t_list	*ft_lstnew(void *content)
{
	t_list	*new = malloc(sizeof(t_list));
	if (new == NULL)
		__FTRETURN_ERR(NULL, FT_EOMEM);
	new->content = content;
	new->prev = NULL;
	new->next = NULL;
	__FTRETURN_OK(new);
}
#endif