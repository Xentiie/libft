/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ht.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 01:45:12 by reclaire          #+#    #+#             */
/*   Updated: 2025/06/08 02:14:28 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "json_private.h"

#include "libft/strings.h"

#include <stdlib.h>

#define BUCKETS_INIT 16

static U64 hash_key(const_string str)
{
	U64 hash;
	S32 c;

	hash = 5381;
	while ((c = *str++))
		hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

	return hash;
}

struct s_json_ht *__ftjson_init_ht()
{
	struct s_json_ht *ht;

	if (UNLIKELY((ht = ftalloc(sizeof(struct s_json_ht))) == NULL))
		FT_RET_ERR(NULL, FT_EOMEM);

	ht->buckets_len = BUCKETS_INIT;
	if (UNLIKELY((ht->buckets = ftalloc(sizeof(struct s_json_member *) * ht->buckets_len)) == NULL))
	{
		free(ht);
		FT_RET_ERR(NULL, FT_EOMEM);
	}
	ft_bzero(ht->buckets, sizeof(struct s_json_member *) * ht->buckets_len);

	FT_RET_OK(ht);
}

void __ftjson_cleanup_ht(struct s_json_ht *ht)
{
	free(ht->buckets);
	free(ht);
}

struct s_json_member **__ftjson_lookup_ht(struct s_json_ht *ht, const_string key)
{
	struct s_json_member **curr;
	U32 hash;

	hash = hash_key(key);
	for (curr = &ht->buckets[hash % ht->buckets_len]; *curr; curr = &((*curr)->next))
	{
		if (!ft_strcmp((*curr)->key, key))
			break;
	}
	return curr;
}

bool __ftjson_insert_ht(struct s_json_member **node, const_string key, struct s_json_object *obj)
{
	struct s_json_member *new;

	if (UNLIKELY((new = ftalloc(sizeof(struct s_json_member))) == NULL))
		FT_RET_ERR(FALSE, FT_EOMEM);

	if (UNLIKELY((new->key = ft_strdup(key)) == NULL))
	{
		free(new);
		FT_RET_ERR(FALSE, FT_EOMEM);
	}

	new->next = NULL;
	new->obj = obj;
	*node = new;

	FT_RET_OK(TRUE);
}
