/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 20:13:02 by reclaire          #+#    #+#             */
/*   Updated: 2024/11/26 02:20:59 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_int.h"
#include "libft/lists.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (UNLIKELY(lst == NULL || f == NULL))
		FT_RET_ERR(, FT_EINVPTR);

	while (lst)
	{
		f(lst->content);
		lst = lst->next;
	}

	FT_RET_OK();
}
