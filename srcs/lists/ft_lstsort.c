/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 17:28:10 by reclaire          #+#    #+#             */
/*   Updated: 2024/05/16 22:10:33 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_int.h"
#include <alloca.h>

void ft_lstsort(t_list **pp, S32 (*key)(void *, void *))
{
	t_list *p = *pp;
	*pp = NULL;

	while (p)
	{
		t_list **lhs = &p;
		t_list **rhs = &p->next;
		bool swapped = FALSE;

		while (*rhs)
		{
			if (key((*lhs)->content, (*rhs)->content) > 0)
			{
				void *tmp = *rhs;
				*rhs = *lhs;
				*lhs = tmp;

				tmp = (*rhs)->next;
				(*rhs)->next = (*lhs)->next;
				(*lhs)->next = tmp;

				lhs = &(*lhs)->next;
				swapped = TRUE;
			}
			else
			{
				lhs = rhs;
				rhs = &(*rhs)->next;
			}
		}
		*rhs = *pp;

		if (swapped)
		{
			*pp = *lhs;
			*lhs = NULL;
		}
		else
		{
			*pp = p;
			break;
		}
	}
}

static S32 (*current_key)(void *, void *);
static S32 k(void *a, void *b)
{
	return current_key(a, b);
}

void ft_lstsort2(t_list **pp, S32 (*key)(void *, void *))
{
	current_key = key;
	
	U64 cnt = ft_lstsize(*pp);
	t_list **arr = alloca(sizeof(t_list *) * cnt);
	
	U64 i = 0;
	t_list *curr = *pp;
	while (curr)
	{
		arr[i] = curr;
		i++;
		curr = curr->next;
	}

	*pp = arr[0];
	curr = *pp;
	curr->prev = NULL;
	for (i = 1; i < cnt; i++)
	{
		curr->next = arr[i];
		curr = arr[i];
		curr->prev = arr[i - 1];
	}
	curr->next = NULL;
}
