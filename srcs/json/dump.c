/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dump.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 01:43:28 by reclaire          #+#    #+#             */
/*   Updated: 2025/06/08 02:14:26 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "json_private.h"

#include "libft/limits.h"
#include "libft/strings.h"

#include <stdlib.h>

static bool __json_dump_grow(string *out, U64 *alloc, U64 *len, U64 strlen)
{
	string new;

	if (*len + strlen >= *alloc)
	{
		if (UNLIKELY((new = ftalloc(sizeof(U8) * *alloc * 2)) == NULL))
			FT_RET_ERR(FALSE, FT_EOMEM);
		ft_memcpy(new, *out, *len);
		free(*out);
		*out = new;
		*alloc *= 2;
	}

	FT_RET_OK(TRUE);
}

static bool __json_dump_append(string *out, U64 *alloc, U64 *len, const_string str,
							   U64 strlen)
{
	if (strlen == 0)
		strlen = ft_strlen(str);
	strlen++; /* null char */

	if (!__json_dump_grow(out, alloc, len, strlen))
		FT_RET_ERR(FALSE, ft_errno);

	ft_memcpy(*out + *len, str, strlen);
	*len += strlen - 1;
	FT_RET_OK(TRUE);
}

static bool __json_dump(string *out, U64 *alloc, U64 *len, struct s_json_object *obj)
{
	struct s_json_member *curr;
	bool				  comma;

#define _JSON_APPEND(_str, _len)                                                         \
	do                                                                                   \
	{                                                                                    \
		if (!__json_dump_append(out, alloc, len, _str, _len))                            \
			FT_RET_ERR(FALSE, ft_errno);                                                 \
	} while (0);

	switch (obj->type)
	{
	case JSON_OBJ:
		comma = FALSE;
		_JSON_APPEND("{", 1);
		for (U64 i = 0; i < obj->obj->buckets_len; i++)
		{
			curr = obj->obj->buckets[i];
			while (curr)
			{
				if (comma)
					_JSON_APPEND(",", 1);
				_JSON_APPEND("\"", 1);
				_JSON_APPEND(curr->key, 0);
				_JSON_APPEND("\":", 2);
				if (!__json_dump(out, alloc, len, curr->obj))
					FT_RET_ERR(FALSE, ft_errno);
				comma = TRUE;
				curr = curr->next;
			}
		}
		_JSON_APPEND("}", 1);
		break;

	case JSON_ARR:
		_JSON_APPEND("[", 1);
		for (U64 i = 0; i < obj->array.len; i++)
		{
			if (!__json_dump(out, alloc, len, obj->array.objs[i]))
				FT_RET_ERR(FALSE, ft_errno);
			if (i + 1 != obj->array.len)
				_JSON_APPEND(",", 1);
		}
		_JSON_APPEND("]", 1);
		break;

	case JSON_BLN:
		if (obj->boolean)
		{
			_JSON_APPEND("true", 4);
		}
		else
		{
			_JSON_APPEND("false", 5);
		}
		break;

	case JSON_NUM:;
		U64 n_digits = _ft_utoa(NULL, 0, 0, obj->num, NULL, S64_MAX);
		if (!__json_dump_grow(out, alloc, len, n_digits + 1))
			FT_RET_ERR(FALSE, ft_errno);
		*len += _ft_utoa(NULL, 0, n_digits, obj->num, *out + *len, S64_MAX);
		(*out)[*len] = '\0';
		break;

	case JSON_STR:
		_JSON_APPEND("\"", 1);
		_JSON_APPEND(obj->str, 0);
		_JSON_APPEND("\"", 1);
		break;

	case JSON_NUL:
		_JSON_APPEND("false", 5);
		break;

	default:
		FT_RET_ERR(FALSE, FT_EINVOP);
	}

	return TRUE;
}

string ft_json_dump(struct s_json_object *obj, U64 *len)
{
	string out;
	string tmp;
	U64	   l;
	U64	   alloc;

	alloc = 1024;
	if (UNLIKELY((out = ftalloc(sizeof(U8) * alloc)) == NULL))
		FT_RET_ERR(NULL, FT_EOMEM);
	*out = '\0';

	if (len == NULL)
		len = &l;

	*len = 0;
	if (!__json_dump(&out, &alloc, len, obj))
	{
		free(out);
		FT_RET_ERR(NULL, ft_errno);
	}

	if (*len < alloc)
	{
		if (UNLIKELY((tmp = ft_strdup_l(out, len)) == NULL))
		{
			free(out);
			FT_RET_ERR(NULL, FT_EOMEM);
		}
		free(out);
		out = tmp;
	}

	return out;
}
