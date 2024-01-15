/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_array.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 18:22:04 by reclaire          #+#    #+#             */
/*   Updated: 2024/01/10 11:16:47 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#ifdef FT_ARRAYS
# include <math.h>

typedef struct _s_array_segment
{
	U64						count;
	U64						size;
	void					*data;
	struct _s_array_segment	*next;
	struct _s_array_segment	*prev;
}	_t_array_segment;

typedef struct _s_array
{
	U64					elem_size;
	U64					count;
	U64					curr_segment_size;
	_t_array_segment	*curr_seg;
	_t_array_segment	*first;
	_t_array_segment	*last;
}	_t_array;

/*
Inits a new array segment at 'out' of size 'seg_size'.
ft_perror:
	FT_OK: Success
	FT_OMEM: Memory allocation error
*/
void	ft_array_new_segment(U64 seg_size, _t_array_segment **out)
{
	_t_array_segment *new = malloc(sizeof(_t_array_segment));

#ifdef FT_ERRCHECK
	if (!new)
	{
		ft_errno = FT_OMEM;
		return;
	}
#endif

	new->data = malloc(seg_size);
#ifdef FT_ERRCHECK
	if (!new->data)
	{
		ft_errno = FT_OMEM;
		free(new);
		return;
	}
#endif
	new->count = 0;
	new->size = seg_size;
	new->next = NULL;
	new->prev = NULL;
	*out = new;
}

void	ft_array_append_segment(_t_array *arr, _t_array_segment *seg)
{
#ifdef FT_ERRCHECK
	if (!seg)
		return;
#endif
	if (!arr->first)
	{
		arr->first = seg;
		arr->last = seg;
	}
	else
	{
		seg->prev = arr->last;
		arr->last->next = seg;
		arr->last = seg;
	}
}

t_array	ft_array_new(U64 elem_size)
{
	_t_array	*arr = malloc(sizeof(_t_array));
#ifdef FT_ERRCHECK
	if (!arr)
	{
		ft_errno = FT_OMEM;
		return NULL;
	}
#endif

	arr->count = 0;
	arr->elem_size = elem_size;
	arr->first = NULL;
	arr->last = NULL;
	arr->curr_segment_size = elem_size * 2;

	_t_array_segment *new_seg = NULL;
	ft_array_new_segment(arr->curr_segment_size, &new_seg);
#ifdef FT_ERRCHECK
	if (ft_errno != FT_OK || new_seg == NULL)
	{
		free(arr);
		return NULL;
	}
#endif

	arr->curr_seg = new_seg;
	arr->first = new_seg;
	arr->last = new_seg;

	return (t_array)arr;
}

bool			ft_array_iter(t_array array, bool (*f)(void *))
{
	_t_array	*arr = (_t_array *)array;

	_t_array_segment *curr = arr->first;
	while (curr)
	{
		_t_array_segment *next = curr->next;
		if (f(curr->data) == FALSE) {
			return FALSE;
		}
		curr = next;
	}
	return TRUE;
}

void			ft_array_free(t_array array)
{
	_t_array	*arr = (_t_array *)array;

	_t_array_segment *curr = arr->first;
	while (curr)
	{
		_t_array_segment *next = curr->next;
		free(curr->data);
		free(curr);
		curr = next;
	}
	free(arr);
}

void	*ft_array_append(t_array array, void *elem)
{
	_t_array	*arr = (_t_array *)array;

	if (arr->curr_seg->size < (arr->curr_seg->count + 1) * arr->elem_size)
	{
		if (arr->curr_seg->next)
		{
			arr->curr_seg = arr->curr_seg->next;
			return ft_array_append(array, elem);
		}
		
		U64 			new_size = arr->curr_segment_size*2;
		_t_array_segment	*new_seg = NULL;
		ft_array_new_segment(new_size, &new_seg);
#ifdef FT_ERRCHECK
		if (ft_errno != FT_OK)
			return NULL;
#endif

		ft_array_append_segment(arr, new_seg);
		arr->curr_segment_size = new_size;
		arr->curr_seg = new_seg;
	}

	void *dest = (U64)arr->curr_seg->data + (arr->curr_seg->count * arr->elem_size);
	ft_memcpy(dest, elem, arr->elem_size);
	arr->curr_seg->count++;
	arr->count++;

	return dest;
}

void			*ft_array_pop(t_array array)
{
	_t_array	*arr = (_t_array *)array;

	_t_array_segment *curr = arr->curr_seg;
	printf("Curr seg: %p\n", curr);

	int skipped = 0;
	while (curr && curr->count == 0 && ++skipped)
		curr = curr->prev;
	printf("Skipped empty: %d %p\n", skipped, curr);
	
#ifdef FT_ERRCHECK
	if (!curr)
	{
		ft_errno = FT_ERROR;
		return NULL;
	}
#endif

	printf("Count: %lld\n", curr->count);

	void *content = ft_memdup((U64)curr->data + (curr->count-1)*arr->elem_size, arr->elem_size);
#ifdef FT_ERRCHECK
	if (!content)
	{
		ft_errno = FT_OMEM;
		return NULL;
	}
#endif

	curr->count--;
	if (curr->count == 0 && curr->prev)
		arr->curr_seg = curr->prev;
	return content;
}

void	*ft_array_get(t_array array, U64 index)
{
	_t_array	*arr = (_t_array *)array;

	if (index == 0 || index == 1)
	{
		if (arr->first)
			return (U64)arr->first->data + arr->elem_size * index;
		else
			return NULL;
	}

	U32	l2 = log2(index + 2) - 1;
	_t_array_segment *curr = arr->first;
	U32 n = 0;
	if (l2 > 0)
	{
		while (curr)
		{
			if (n == l2) break;
			curr = curr->next;
			n++;
		}
	}
	U64 seg_index = 2 - curr->size / arr->elem_size + index;
	if (!curr)
		return NULL;
	return (U64)curr->data + seg_index*arr->elem_size;
}

U64		ft_array_count(t_array array)
{
	return ((_t_array *)array)->count;
}

U64		ft_array_count_bytes(t_array array)
{
	return ((_t_array *)array)->count * ((_t_array *)array)->elem_size;
}

void	*ft_array_to_buff(t_array array)
{
	_t_array	*arr = (_t_array *)array;
	
	void *out = malloc(ft_array_count_bytes(array));
#ifdef FT_ERRCHECK
	if (!out)
	{
		ft_errno = FT_OMEM;
		return NULL;
	}
#endif

	_t_array_segment *seg = arr->first;
	U64 offs = 0;
	while (seg)
	{
		ft_memcpy((U64)out + offs, seg->data, seg->count * arr->elem_size);
		offs += seg->count * arr->elem_size;
		seg = seg->next;
	}
	return out;
}

void ft_array_cpy_buff(t_array array, void *buff)
{
	_t_array	*arr = (_t_array *)array;
	
	_t_array_segment *seg = arr->first;
	U64 offs = 0;
	while (seg)
	{
		ft_memcpy((U64)buff + offs, seg->data, seg->count * arr->elem_size);
		offs += seg->count * arr->elem_size;
		seg = seg->next;
	}
}

void	ft_array_clear(t_array array)
{
	_t_array	*arr = (_t_array *)array;
	_t_array_segment	*curr = arr->first;
	while (curr)
	{
		curr->count = 0;
		curr = curr->next;
	}
	arr->curr_seg = arr->first;
	arr->count = 0;
}
#endif