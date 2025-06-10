/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   json.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 05:30:40 by reclaire          #+#    #+#             */
/*   Updated: 2025/06/08 02:14:34 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "json_private.h"

#include "libft/std.h"
#include "libft/limits.h"
#include "libft/strings.h"
#include "libft/io.h"

#include <stdlib.h>

struct s_json_object *ft_json_new()
{
	struct s_json_object *obj;

	if (UNLIKELY((obj = ftalloc(sizeof(struct s_json_object))) == NULL))
		FT_RET_ERR(NULL, FT_EOMEM);
	ft_bzero(obj, sizeof(struct s_json_object));
	return obj;
}

bool ft_json_set_bool(struct s_json_object *obj, bool b)
{
	if (obj->type != JSON_NONE)
		FT_RET_ERR(FALSE, FT_EINVOP);
	obj->type = JSON_BLN;
	obj->boolean = b;

	FT_RET_OK(TRUE);
}

bool ft_json_set_string(struct s_json_object *obj, const_string str)
{
	if (obj->type != JSON_NONE)
		FT_RET_ERR(FALSE, FT_EINVOP);
	obj->type = JSON_STR;
	if (UNLIKELY((obj->str = ft_strdup(str)) == NULL))
		FT_RET_ERR(FALSE, FT_EOMEM);

	FT_RET_OK(TRUE);
}

bool ft_json_set_num(struct s_json_object *obj, S64 num)
{
	if (obj->type != JSON_NONE)
		FT_RET_ERR(FALSE, FT_EINVOP);
	obj->type = JSON_NUM;
	obj->num = num;

	FT_RET_OK(TRUE);
}

bool ft_json_set_obj(struct s_json_object *obj)
{
	if (obj->type != JSON_NONE)
		FT_RET_ERR(FALSE, FT_EINVOP);
	obj->type = JSON_OBJ;

	if (UNLIKELY((obj->obj = __ftjson_init_ht()) == NULL))
		FT_RET_ERR(FALSE, ft_errno);

	FT_RET_OK(TRUE);
}

bool ft_json_set_array(struct s_json_object *obj)
{
	if (obj->type != JSON_NONE)
		FT_RET_ERR(FALSE, FT_EINVOP);
	obj->type = JSON_ARR;

	obj->array.alloc = 0;
	obj->array.len = 0;
	obj->array.objs = NULL;

	FT_RET_OK(TRUE);
}

bool ft_json_set_null(struct s_json_object *obj)
{
	if (obj->type != JSON_NONE)
		FT_RET_ERR(FALSE, FT_EINVOP);
	obj->type = JSON_NUL;

	FT_RET_OK(TRUE);
}

struct s_json_object *ft_json_add_bool(struct s_json_object *obj, const_string key, bool b)
{
	struct s_json_object *new;

	if (obj->type != JSON_ARR && obj->type != JSON_OBJ)
		FT_RET_ERR(NULL, FT_EINVOP);

	if (obj->type == JSON_OBJ && key == NULL)
		FT_RET_ERR(NULL, FT_EINVPTR);

	if (UNLIKELY((new = ft_json_new()) == NULL))
		FT_RET_ERR(NULL, ft_errno);
	if (!ft_json_set_bool(new, b))
		FT_RET_ERR(NULL, ft_errno);
	if (obj->type == JSON_OBJ)
	{
		if (!ft_json_insert(obj, key, new))
			FT_RET_ERR(NULL, ft_errno);
	}
	else
	{
		if (!ft_json_append(obj, new))
			FT_RET_ERR(NULL, ft_errno);
	}

	FT_RET_OK(new);
}

struct s_json_object *ft_json_add_string(struct s_json_object *obj, const_string key, const_string str)
{
	struct s_json_object *new;

	if (obj->type != JSON_ARR && obj->type != JSON_OBJ)
		FT_RET_ERR(NULL, FT_EINVOP);

	if (obj->type == JSON_OBJ && key == NULL)
		FT_RET_ERR(NULL, FT_EINVPTR);

	if (UNLIKELY((new = ft_json_new()) == NULL))
		FT_RET_ERR(NULL, ft_errno);
	if (!ft_json_set_string(new, str))
		FT_RET_ERR(NULL, ft_errno);
	if (obj->type == JSON_OBJ)
	{
		if (!ft_json_insert(obj, key, new))
			FT_RET_ERR(NULL, ft_errno);
	}
	else
	{
		if (!ft_json_append(obj, new))
			FT_RET_ERR(NULL, ft_errno);
	}

	FT_RET_OK(new);
}

struct s_json_object *ft_json_add_num(struct s_json_object *obj, const_string key, S64 num)
{
	struct s_json_object *new;

	if (obj->type != JSON_ARR && obj->type != JSON_OBJ)
		FT_RET_ERR(NULL, FT_EINVOP);

	if (obj->type == JSON_OBJ && key == NULL)
		FT_RET_ERR(NULL, FT_EINVPTR);

	if (UNLIKELY((new = ft_json_new()) == NULL))
		FT_RET_ERR(NULL, ft_errno);
	if (!ft_json_set_num(new, num))
		FT_RET_ERR(NULL, ft_errno);
	if (obj->type == JSON_OBJ)
	{
		if (!ft_json_insert(obj, key, new))
			FT_RET_ERR(NULL, ft_errno);
	}
	else
	{
		if (!ft_json_append(obj, new))
			FT_RET_ERR(NULL, ft_errno);
	}

	FT_RET_OK(new);
}

struct s_json_object *ft_json_add_obj(struct s_json_object *obj, const_string key)
{
	struct s_json_object *new;

	if (obj->type != JSON_ARR && obj->type != JSON_OBJ)
		FT_RET_ERR(NULL, FT_EINVOP);

	if (obj->type == JSON_OBJ && key == NULL)
		FT_RET_ERR(NULL, FT_EINVPTR);

	if (UNLIKELY((new = ft_json_new()) == NULL))
		FT_RET_ERR(NULL, ft_errno);
	if (!ft_json_set_obj(new))
		FT_RET_ERR(NULL, ft_errno);
	if (obj->type == JSON_OBJ)
	{
		if (!ft_json_insert(obj, key, new))
			FT_RET_ERR(NULL, ft_errno);
	}
	else
	{
		if (!ft_json_append(obj, new))
			FT_RET_ERR(NULL, ft_errno);
	}

	FT_RET_OK(new);
}

struct s_json_object *ft_json_add_array(struct s_json_object *obj, const_string key)
{
	struct s_json_object *new;

	if (obj->type != JSON_ARR && obj->type != JSON_OBJ)
		FT_RET_ERR(NULL, FT_EINVOP);

	if (obj->type == JSON_OBJ && key == NULL)
		FT_RET_ERR(NULL, FT_EINVPTR);

	if (UNLIKELY((new = ft_json_new()) == NULL))
		FT_RET_ERR(NULL, ft_errno);
	if (!ft_json_set_array(new))
		FT_RET_ERR(NULL, ft_errno);
	if (obj->type == JSON_OBJ)
	{
		if (!ft_json_insert(obj, key, new))
			FT_RET_ERR(NULL, ft_errno);
	}
	else
	{
		if (!ft_json_append(obj, new))
			FT_RET_ERR(NULL, ft_errno);
	}

	FT_RET_OK(new);
}

struct s_json_object *ft_json_add_null(struct s_json_object *obj, const_string key)
{
	struct s_json_object *new;

	if (obj->type != JSON_ARR && obj->type != JSON_OBJ)
		FT_RET_ERR(NULL, FT_EINVOP);

	if (obj->type == JSON_OBJ && key == NULL)
		FT_RET_ERR(NULL, FT_EINVPTR);

	if (UNLIKELY((new = ft_json_new()) == NULL))
		FT_RET_ERR(NULL, ft_errno);
	if (!ft_json_set_null(new))
		FT_RET_ERR(NULL, ft_errno);
	if (obj->type == JSON_OBJ)
	{
		if (!ft_json_insert(obj, key, new))
			FT_RET_ERR(NULL, ft_errno);
	}
	else
	{
		if (!ft_json_append(obj, new))
			FT_RET_ERR(NULL, ft_errno);
	}

	FT_RET_OK(new);
}

bool ft_json_insert(struct s_json_object *obj, const_string key, struct s_json_object *value)
{
	struct s_json_member **lookup;

	if (obj->type != JSON_OBJ)
		FT_RET_ERR(FALSE, FT_EINVOP);

	lookup = __ftjson_lookup_ht(obj->obj, key);
	if ((*lookup) != NULL)
		/* key already present */
		FT_RET_ERR(FALSE, FT_ERANGE);

	if (!__ftjson_insert_ht(lookup, key, value))
		return FALSE;

	FT_RET_OK(TRUE);
}

struct s_json_object *ft_json_get(struct s_json_object *obj, const_string key)
{
	struct s_json_member **lookup;

	if (obj->type != JSON_OBJ)
		FT_RET_ERR(FALSE, FT_EINVOP);

	lookup = __ftjson_lookup_ht(obj->obj, key);
	if ((*lookup) == NULL)
		/* key not found */
		FT_RET_ERR(NULL, FT_ENOENT);
	FT_RET_OK((*lookup)->obj);
}

bool ft_json_append(struct s_json_object *obj, struct s_json_object *new)
{
	struct s_json_object **new_objs;

	if (obj->type != JSON_ARR)
		FT_RET_ERR(FALSE, FT_EINVOP);

	if (obj->array.objs == NULL || obj->array.len == 0)
	{
		obj->array.len = 0;
		obj->array.alloc = 4;
		if (UNLIKELY((obj->array.objs = ftalloc(sizeof(struct s_json_object *) * obj->array.alloc)) == NULL))
			FT_RET_ERR(FALSE, FT_EOMEM);
	}
	else if (obj->array.len >= obj->array.alloc)
	{
		if (UNLIKELY((new_objs = ftalloc(sizeof(struct s_json_object *) * obj->array.alloc * 2)) == NULL))
			FT_RET_ERR(FALSE, FT_EOMEM);
		ft_memcpy(new_objs, obj->array.objs, sizeof(struct s_json_object *) * obj->array.len);
		free(obj->array.objs);
		obj->array.objs = new_objs;
		obj->array.alloc *= 2;
	}

	obj->array.objs[obj->array.len] = new;
	obj->array.len++;

	FT_RET_OK(TRUE);
}

void ft_json_destroy_object(struct s_json_object *obj)
{
	struct s_json_member *member;
	struct s_json_iterator *it;

	switch (obj->type)
	{
	case JSON_STR:
		free(obj->str);
		break;

	case JSON_OBJ:
		if (UNLIKELY((it = ft_json_iter_init(obj)) == NULL))
			FT_RET_ERR(, ft_errno);
		while ((member = ft_json_iter(it)) != NULL)
		{
			//ft_printf("Free: %p (%p) %s\n", member, member->key, member->key);
			ft_json_destroy_object(member->obj);
			free((void *)member->key);
			free(member);
		}
		ft_json_iter_destroy(it);
		__ftjson_cleanup_ht(obj->obj);
		break;

	case JSON_ARR:
		for (U64 i = 0; i < obj->array.len; i++)
			ft_json_destroy_object(obj->array.objs[i]);
		free(obj->array.objs);
		break;

	default:
		break;
	}

	free(obj);
}
