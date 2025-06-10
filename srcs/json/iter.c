/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iter.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 01:49:56 by reclaire          #+#    #+#             */
/*   Updated: 2025/06/08 02:14:34 by reclaire         ###   ########.fr       */
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

	if (UNLIKELY((it = ftalloc(sizeof(struct s_json_iterator))) == NULL))
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
	struct s_json_member *ret;

	//ft_printf("Entering Iter\n");
	if (it->i >= it->obj->obj->buckets_len)
	{
		//ft_printf("Iter done\n");	
		return NULL;
	}

	if (it->curr == NULL)
	{ /* choose next bucket */
		//ft_printf("Choosing next bucket\n");
		while (it->i < it->obj->obj->buckets_len && (it->curr = it->obj->obj->buckets[it->i]) == NULL)
			it->i++;
		return ft_json_iter(it);
	}
	ret = it->curr;
	it->curr = it->curr->next;
	if (it->curr == NULL)
		it->i++;

	//ft_printf("Returning: ret=%s curr=%p\n", ret->key, it->curr);

	return ret;

	if (it->curr == NULL)
	{ /* choose next bucket */
		while (it->i < it->obj->obj->buckets_len && (it->curr = it->obj->obj->buckets[it->i]) == NULL)
			it->i++;
		return it->curr;
	}
	else
	{
		if (it->curr->next == NULL)
		{
			it->i++;
			it->curr = NULL;
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
