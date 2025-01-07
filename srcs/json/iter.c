/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iter.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 01:49:56 by reclaire          #+#    #+#             */
/*   Updated: 2025/01/07 02:03:19 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "json_private.h"

#include <stdlib.h>

struct s_json_iterator
{
	struct s_json_object *obj;
	struct s_json_member *curr;
	U64 i;
};

struct s_json_iterator *ft_json_iter_init(struct s_json_object *obj)
{
	struct s_json_iterator *it;

	if (obj->type != JSON_OBJ)
		FT_RET_ERR(FALSE, FT_EINVOP);

	if (UNLIKELY((it = malloc(sizeof(struct s_json_iterator))) == NULL))
		FT_RET_ERR(FALSE, FT_EOMEM);

	ft_json_iter_reset(it, obj);
	FT_RET_OK(it);
}

void ft_json_iter_reset(struct s_json_iterator *it, struct s_json_object *obj)
{
	if (obj != NULL)
		it->obj = obj;
	it->curr = NULL;
	it->i = 0;
}

struct s_json_member *ft_json_iter(struct s_json_iterator *it)
{
	if (it->i >= it->obj->obj->buckets_len)
		return NULL;

	if (it->curr == NULL)
	{
		it->curr = it->obj->obj->buckets[it->i];
		return it->curr;
	}
	else
	{
		if (it->curr->next == NULL)
		{
			it->i++;
			return ft_json_iter(it);
		}
		else
		{
			it->curr = it->curr->next;
			return it->curr;
		}
	}
}

void ft_json_iter_destroy(struct s_json_iterator *it)
{
	free(it);
}
