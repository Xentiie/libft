/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 16:42:40 by reclaire          #+#    #+#             */
/*   Updated: 2024/11/26 02:20:59 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_int.h"
#include "libft/lists.h"

#include <stdlib.h>

t_list	*ft_lstnew(void *content)
{
	t_list *new;

	if (UNLIKELY((new = malloc(sizeof(t_list))) == NULL))
		FT_RET_ERR(NULL, FT_EOMEM);
	new->content = content;
	new->prev = NULL;
	new->next = NULL;
	FT_RET_OK(new);
}
