/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 20:02:15 by reclaire          #+#    #+#             */
/*   Updated: 2023/09/26 22:17:31 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#ifdef FT_LISTS
void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (lst == NULL)
		__FTRETURN_ERR(, FT_EINVPTR);

	if (del)
		del(lst->content);
	free(lst);

	__FTRETURN_OK();
}
#endif