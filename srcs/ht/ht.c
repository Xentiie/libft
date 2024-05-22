/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ht.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 23:04:48 by reclaire          #+#    #+#             */
/*   Updated: 2024/05/22 02:40:34 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_int.h"

t_ht *ft_new_hash_table(U64 elem_size, U64 init_size, U64 (*hash)(void *elem))
{
	t_ht *table = malloc(sizeof(t_ht));
	if (UNLICKELY(table == NULL))
		__FTRETURN_ERR(NULL, FT_EOMEM);
	table->elem_size = elem_size;
	table->buckets_alloc = MAX(init_size, 1);
	table->buckets_count = 0;
	table->hash = hash;

	table->buckets = malloc(sizeof(t_hash_bucket) * table->buckets_alloc);
	if (UNLICKELY(table->buckets == NULL))
	{
		free(table);
		__FTRETURN_ERR(NULL, FT_EOMEM);
	}
	for (U64 i = 0; i < init_size; i++)
	{
		table->buckets[i].data_alloc = 1;
		table->buckets[i].count = 0;
		table->buckets[i].data = malloc(sizeof(U8) * table->elem_size);
		if (UNLICKELY(table->buckets[i].data == NULL))
		{
			for (U64 j = 0; j < i; j++)
				free(table->buckets[j].data);
			free(table->buckets);
			free(table);
			__FTRETURN_ERR(NULL, FT_EOMEM);
		}
	}

	__FTRETURN_OK(table);
}

void ft_hash_free(t_ht *table)
{
	for (U64 i = 0; i < table->buckets_alloc; i++)
		free(table->buckets[i].data);
	free(table->buckets);
	free(table);
}





static bool init_bucket(t_ht *table, t_hash_bucket *bucket)
{
	bucket->count = 0;
	bucket->data_alloc = 1;
	bucket->data = malloc(table->elem_size * sizeof(U8));
	if (UNLICKELY(bucket->data == NULL))
		return FALSE;
	return TRUE;
}

static bool grow_bucket_if_needed(t_ht *table, t_hash_bucket *bucket)
{
	if (bucket->count + 1 > bucket->data_alloc)
	{
		void *new_data = malloc(sizeof(U8) * bucket->data_alloc * 2);
		if (UNLICKELY(new_data == NULL))
			return FALSE;
		ft_memcpy(new_data, bucket->data, bucket->count * table->elem_size * sizeof(U8));
		free(bucket->data);
		bucket->data = new_data;
		bucket->data_alloc *= 2;
	}
	return TRUE;
}

static bool add_to_bucket(t_ht *table, t_hash_bucket *bucket, void *elem)
{
	if (UNLICKELY(!grow_bucket_if_needed(table, bucket)))
		return FALSE;
	ft_memcpy(bucket->data + bucket->count * table->elem_size * sizeof(U8), elem, table->elem_size * sizeof(U8));
	bucket->count++;
	return TRUE;
}




static bool grow_buckets_if_needed(t_ht *table)
{
	if (table->buckets_count + 1 > table->buckets_alloc / 2)
	{
		t_hash_bucket *new_buckets = malloc(sizeof(U8) * table->buckets_alloc * 2);
		if (UNLICKELY(new_buckets == NULL))
			return FALSE;

		for (U64 i = 0; i < table->buckets_alloc * 2; i++)
		{
			if (UNLICKELY(!init_bucket(table, &new_buckets[i])))
			{
				for (U64 j = table->buckets_alloc; j < i; j++)
					free(new_buckets[j].data);
				free(new_buckets);
				return FALSE;
			}
		}

		table->buckets_alloc *= 2;

		for (U64 i = 0; i < table->buckets_count; i++)
		{
			U64 hash = table->hash(table->buckets[i].data) % table->buckets_alloc;
			
			for (U64 j = 0; j < table->buckets[i].count; j++)
				if (UNLICKELY(!add_to_bucket(table, &new_buckets[hash], table->buckets[i].data + j * table->elem_size * sizeof(U8))))
					return FALSE;
		}

		free(table->buckets);
		table->buckets = new_buckets;
	}

	return TRUE;
}

static void *find_in_bucket(t_ht *table, t_hash_bucket *bucket, void *elem)
{
	U64 i = 0;
	while (i < bucket->count && ft_memcmp(elem, bucket->data + i * table->elem_size * sizeof(U8), table->elem_size))
		i++;
	if (UNLICKELY(i == bucket->count))
		return NULL;
	else
		return bucket->data + i * table->elem_size * sizeof(U8);
}

void *ft_hash_get(t_ht *table, void *elem)
{
	t_hash_bucket *bucket = ft_hash_get_bucket(table, elem);
	return find_in_bucket(table, bucket, elem);
}

t_hash_bucket *ft_hash_get_bucket(t_ht *table, void *elem)
{
	U64 hash = table->hash(elem) % table->buckets_alloc;
	return &table->buckets[hash];
}




void ft_hash_insert(t_ht *table, void *elem)
{
	U64 hash = table->hash(elem);

	t_hash_bucket *bucket = &table->buckets[hash % table->buckets_alloc];
	void *find = find_in_bucket(table, bucket, elem);

	if (find == NULL)
	{
		if (UNLICKELY(!grow_buckets_if_needed(table)))
			__FTRETURN_ERR(, FT_EOMEM);
		bucket = &table->buckets[hash % table->buckets_alloc];
		if (UNLICKELY(!add_to_bucket(table, bucket, elem)))
			__FTRETURN_ERR(, FT_EOMEM);
	}
	else
		if (UNLICKELY(!add_to_bucket(table, bucket, elem)))
			__FTRETURN_ERR(, FT_EOMEM);
	__FTRETURN_OK();
}
