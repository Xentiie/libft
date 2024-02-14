/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 17:28:10 by reclaire          #+#    #+#             */
/*   Updated: 2024/02/12 17:18:46 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_int.h"

static void swap(t_list *lst1, t_list *lst2) //marche pas parce que ca fout la merde avec les refs curr et curr->next en dessous :O
{
	t_list tmp = *lst2;

	lst2->prev = lst1->prev;
	lst2->next = lst1->next;

	lst1->prev = tmp.prev;
	lst1->next = tmp.prev;
}

static void swap_inplace(t_list *lst1, t_list *lst2)
{
	void *tmp = lst1->content;
	lst1->content = lst2->content;
	lst2->content = tmp;
}




void ft_lstsort(t_list **pp, S32 (*key)(void *, void *))
{
    // p always points to the head of the list
    t_list *p = *pp;
    *pp = NULL;

    while (p)
    {
        t_list **lhs = &p;
        t_list **rhs = &p->next;
        bool swapped = FALSE;

        // keep going until qq holds the address of a null pointer
        while (*rhs)
        {
            // if the left side is greater than the right side
            if (key((*lhs)->content, (*rhs)->content) > 0)
            {
                // swap linked node ptrs, then swap *back* their next ptrs
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
            {   // no swap. advance both pointer-pointers
                lhs = rhs;
                rhs = &(*rhs)->next;
            }
        }

        // link last node to the sorted segment
        *rhs = *pp;

        // if we swapped, detach the final node, terminate the list, and continue.
        if (swapped)
        {
            // take the last node off the list and push it into the result.
            *pp = *lhs;
            *lhs = NULL;
        }

        // otherwise we're done. since no swaps happened the list is sorted.
        // set the output parameter and terminate the loop.
        else
        { 
            *pp = p;
            break;
        }
    }
}


/*
void	ft_lstsort(t_list **lst, S32 (*key)(void *, void *))
{
	if (!lst || !key)
		__FTRETURN_ERR(, FT_EINVPTR);

	if (!(*lst))
		__FTRETURN_OK();

	t_list *c1 = *lst;
	t_list *c2;
	while (c1)
	{
		c2 = c1;
		while (c2->next)
		{
			if (key(c2->content, c2->next->content) > 0)
			{
				void *tmp = c2->content;
				c2->content = c2->next->content;
				c2->next->content = tmp;
			}
			c2 = c2->next;
		}
		c1 = c1->next;
	}
	__FTRETURN_OK();
}
*/
