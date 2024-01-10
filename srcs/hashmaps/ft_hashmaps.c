/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hashmaps.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 01:40:37 by reclaire          #+#    #+#             */
/*   Updated: 2024/01/10 11:16:32 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
https://web.archive.org/web/20160329102146/http://elliottback.com/wp/hashmap-implementation-in-c/
Code by Elliott Back
*/

/*
 * Generic map implementation. This class is thread-safe.
 * free() must be invoked when only one thread has access to the hashmap.
 */
#include <stdlib.h>
#include "libft.h"
#ifdef FT_HASHMAPS
# include <stdio.h>
# include <pthread.h>

# define INITIAL_SIZE 1024

typedef struct _hashmap_element
{
	U8	*key;
	int	in_use;
	t_hash_any data;
} hashmap_element;

// A hashmap has some maximum size and current size,
// as well as the data to hold.
typedef struct _hashmap_map
{
	int				table_size;
	int				size;
	unsigned int	(*key_hash)(void *);
	U64				key_len;
	hashmap_element	*data;
	U64				elem_len;
	t_array			keys;
	pthread_mutex_t	lock;
} hashmap_map;

int ft_hash_cpy(t_hash_map in, void *key_ptr, t_hash_any value);



/*
 * Return an empty hashmap, or NULL on failure.
 */
t_hash_map ft_hash_init(unsigned int (*key_hash)(void *), U64 key_len, U64 elem_len)
{
	hashmap_map *m = malloc(sizeof(hashmap_map));
	if (!m)
		return NULL;

	m->data = malloc(INITIAL_SIZE * sizeof(hashmap_element));
	ft_bzero(m->data, INITIAL_SIZE * sizeof(hashmap_element));
	if (!m->data)
	{
		free(m);
		return NULL;
	}

	if (pthread_mutex_init(&m->lock, NULL) != 0)
	{
		free(m->data);
		free(m);
		return NULL;
	}

	m->keys = ft_array_new(elem_len);
	if (ft_errno != FT_OK)
	{
		pthread_mutex_destroy(&m->lock);
		free(m->data);
		free(m);
		return NULL;
	}	

	m->key_hash = key_hash;
	m->key_len = key_len;
	m->table_size = INITIAL_SIZE;
	m->elem_len = elem_len;
	m->size = 0;
	return m;
}

/*
 * Return the integer of the location in data
 * to store the point to the item, or FT_MAP_FULL.
 */
int ft_hash_find(t_hash_map in, void *key)
{
	hashmap_map *m = (hashmap_map *)in;

	if (m->size == m->table_size)
		return FT_MAP_FULL;

	U32 curr;
	if (m->key_hash)
		curr = m->key_hash(key) % m->table_size;
	else
		curr = ft_hash_buffer(key, m->key_len) % m->table_size;

	for (int i = 0; i < m->table_size; i++)
	{
		if (m->data[curr].in_use == 0)
			return curr;

		if (ft_strncmp((string)(m->data[curr].key), key, m->key_len) == 0 && m->data[curr].in_use == 1)
			return curr;

		curr = (curr + 1) % m->table_size;
	}

	return FT_MAP_FULL;
}

/*
 * Doubles the size of the hashmap, and rehashes all the elements
 */
int ft_hash_rehash(t_hash_map in)
{
	int				old_size;
	hashmap_element	*curr;

	hashmap_map		*m =	(hashmap_map *)in;
	hashmap_element	*temp = malloc(2 * m->table_size * sizeof(hashmap_element));
	if (!temp)
		return FT_OMEM;

	/* Update the array */
	curr = m->data;
	m->data = temp;

	/* Update the size */
	old_size = m->table_size;
	m->table_size = 2 * m->table_size;
	m->size = 0;

	/* Rehash the elements */
	for (int i = 0; i < old_size; i++)
	{
		int status = ft_hash_cpy(m, curr[i].key, curr[i].data);
		if (status != FT_OK)
			return status;
	}

	free(curr);
	return FT_OK;
}

int ft_hash_cpy(t_hash_map in, void *key_ptr, t_hash_any value)
{
	int			index;
	hashmap_map	*m = (hashmap_map *)in;

	/* Find a place to put our value */
	index = ft_hash_find(in, key_ptr);
	while (index == FT_MAP_FULL)
	{
		if (ft_hash_rehash(in) == FT_OMEM)
			return FT_OMEM;
		index = ft_hash_find(in, key_ptr);
	}

	/* Set the data */
	m->data[index].data = value;
	m->data[index].key = key_ptr;
	m->data[index].in_use = 1;
	m->size++;

	return FT_OK;
}

/*
 * Add a pointer to the hashmap with some key
 */
int ft_hash_put(t_hash_map in, void *key, t_hash_any value)
{
	int			index;
	hashmap_map	*m = (hashmap_map *)in;

	/* Find a place to put our value */
	index = ft_hash_find(in, key);
	while (index == FT_MAP_FULL)
	{
		if (ft_hash_rehash(in) == FT_OMEM)
			return FT_OMEM;	
		index = ft_hash_find(in, key);
	}

	/* Set the data */
	m->data[index].data = value;
	m->data[index].key = ft_memdup(key, m->key_len);
	if (!m->data[index].key)
		return FT_OMEM;

	ft_array_append(m->keys, key);
	if (ft_errno != FT_OK)
		return FT_OMEM;

	m->data[index].in_use = 1;
	m->size++;

	return FT_OK;
}

/*
 * Get your pointer out of the hashmap with a key
 */
int ft_hash_get(t_hash_map in, void *key, t_hash_any *arg)
{
	U32			curr;
	hashmap_map	*m = (hashmap_map *)in;

	pthread_mutex_lock(&m->lock);

	if (m->key_hash)
		curr = m->key_hash(key) % m->table_size;
	else
		curr = ft_hash_buffer(key, m->key_len) % m->table_size;

	/* Linear probing, if necessary */
	for (int i = 0; i < m->table_size; i++)
	{
		if (m->data[curr].in_use == 1 && !ft_memcmp(m->data[curr].key, key, m->key_len))
		{
			*arg = m->data[curr].data;
			pthread_mutex_unlock(&m->lock);
			return FT_OK;
		}
		curr = (curr + 1) % m->table_size;
	}

	*arg = NULL;
	pthread_mutex_unlock(&m->lock);;
	return FT_MAP_MISSING;
}

/*
 * Get a random element from the hashmap
 */
int ft_hash_get_one(t_hash_map in, t_hash_any *arg, int remove)
{
	hashmap_map *m = (hashmap_map *)in;
	if (m->size <= 0)
		return FT_MAP_MISSING;

	pthread_mutex_lock(&m->lock);

	/* Linear probing */
	for (int i = 0; i < m->table_size; i++)
	{
		if (m->data[i].in_use != 0)
		{
			*arg = (t_hash_any)(m->data[i].data);
			if (remove)
			{
				m->data[i].in_use = 0;
				free(m->data[i].key);
				m->size--;
			}
			pthread_mutex_unlock(&m->lock);;
			return FT_OK;
		}
	}

	pthread_mutex_unlock(&m->lock);;
	return FT_MAP_MISSING;
}

/*
 * Iterate the function parameter over each element in the hashmap.  The
 * additional t_hash_any argument is passed to the function as its first
 * argument and the hashmap element is the second.
 */
int ft_hash_iterate(t_hash_map in, int (*f)(t_hash_any item, t_hash_any elem), t_hash_any item)
{
	hashmap_map	*m = (hashmap_map *)in;
	if (m->size <= 0)
		return FT_MAP_MISSING;

	pthread_mutex_lock(&m->lock);

	/* Linear probing */
	for (int i = 0; i < m->table_size; i++)
	{
		if (m->data[i].in_use != 0)
		{
			t_hash_any data = (t_hash_any)(m->data[i].data);
			int status = f(item, data);
			if (status != FT_OK)
			{
				pthread_mutex_unlock(&m->lock);;
				return status;
			}
		}
	}

	/* Unlock */
	pthread_mutex_unlock(&m->lock);;

	return FT_OK;
}

/*
 * Remove an element with that key from the map. TODO DOES NOT REMOVE KEY IN KEYS
 */
int ft_hash_remove(t_hash_map in, void *key)
{
	U32 curr;
	hashmap_map *m = (hashmap_map *)in;
	pthread_mutex_lock(&m->lock);

	if (m->key_hash)
		curr = m->key_hash(key) % m->table_size;
	else
		curr = ft_hash_buffer(key, m->key_len) % m->table_size;

	/* Linear probing, if necessary */
	for (int i = 0; i < m->table_size; i++)
	{
		if (m->data[curr].key == key && m->data[curr].in_use == 1)
		{
			/* Blank out the fields */
			m->data[curr].in_use = 0;
			m->data[curr].data = NULL;
			free(m->data[curr].key);

			/* Reduce the size */
			m->size--;
			pthread_mutex_unlock(&m->lock);
			return FT_OK;
		}
		curr = (curr + 1) % m->table_size;
	}

	/* Unlock */
	pthread_mutex_unlock(&m->lock);;

	/* Data not found */
	return FT_MAP_MISSING;
}

/* Deallocate the hashmap */
t_hash_code ft_hash_free(t_hash_map in)
{
	hashmap_map *m = (hashmap_map *)in;

	for (int i = 0; i < m->table_size; i++)
	{
		if (m->data[i].in_use != 0)
			free(m->data[i].key);
	}

	if (pthread_mutex_destroy(&m->lock) != 0)
		return FT_MAP_MISSING;
	free(m->data);
	free(m);
	return FT_OK;
}
#endif