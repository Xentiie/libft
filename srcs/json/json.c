/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   json.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 05:30:40 by reclaire          #+#    #+#             */
/*   Updated: 2025/01/06 21:04:58 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _FT_RETURN

#include "libft_int.h"

#include "libft/json.h"

#include "libft/std.h"
#include "libft/limits.h"
#include "libft/strings.h"
#include "libft/io.h"

#include <stdlib.h>

// TODO: support float and exponant for numbers
// TODO: better errors support
// TODO: reallocate and rehash JSON_OBJ at some point

#define BUCKETS_INIT 16

struct s_json_member
{
	struct s_json_member *next;
	const_string key;
	struct s_json_object *obj;
};

struct s_json_ht
{
	struct s_json_member **buckets;
	U64 buckets_len;
};

static U64 hash_key(const_string str)
{
	U64 hash;
	S32 c;

	hash = 5381;
	while ((c = *str++))
		hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

	return hash;
}

static bool init_ht(struct s_json_object *obj)
{
	if (UNLIKELY((obj->obj = malloc(sizeof(struct s_json_ht))) == NULL))
		FT_RET_ERR(FALSE, FT_EOMEM);

	obj->obj->buckets_len = BUCKETS_INIT;
	if (UNLIKELY((obj->obj->buckets = malloc(sizeof(struct s_json_member *) * obj->obj->buckets_len)) == NULL))
	{
		free(obj->obj);
		FT_RET_ERR(FALSE, FT_EOMEM);
	}
	ft_bzero(obj->obj->buckets, sizeof(struct s_json_member *) * obj->obj->buckets_len);

	FT_RET_OK(TRUE);
}

static struct s_json_member **lookup_ht(struct s_json_ht *ht, const_string key)
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

static bool append_ht(struct s_json_member **node, const_string key, struct s_json_object *obj)
{
	struct s_json_member *new;

	if (UNLIKELY((new = malloc(sizeof(struct s_json_member))) == NULL))
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

static string parse_string(const_string ptr, U64 *i)
{
	U64 len;
	string out;

	if (ptr[*i] != '"')
		return NULL;

	len = *i + 1; /* skip initial '"' */
	while (ptr[len] && ptr[len] != '\"')
		len++;

	if (ptr[len] != '"')
		return NULL;

	if (UNLIKELY((out = ft_strndup(ptr + *i + 1, len - *i - 1)) == NULL))
		return NULL;

	*i = len + 1; /* skip last '"' */
	return out;
}

struct s_json_object *ft_json_new()
{
	struct s_json_object *obj;

	if (UNLIKELY((obj = malloc(sizeof(struct s_json_object))) == NULL))
		FT_RET_ERR(NULL, FT_EOMEM);
	ft_bzero(obj, sizeof(struct s_json_object));
	return obj;
}

bool ft_json_set_bool(struct s_json_object *obj, bool b)
{
	if (obj->type != JSON_NONE)
		FT_RET_ERR(FALSE, FT_EINVOP);
	obj->type = JSON_BOOL;
	obj->boolean = b;

	FT_RET_OK(TRUE);
}

bool ft_json_set_string(struct s_json_object *obj, const_string str)
{
	if (obj->type != JSON_NONE)
		FT_RET_ERR(FALSE, FT_EINVOP);
	obj->type = JSON_STRING;
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

	if (!init_ht(obj))
		FT_RET_ERR(FALSE, ft_errno);

	FT_RET_OK(TRUE);
}

bool ft_json_set_array(struct s_json_object *obj)
{
	if (obj->type != JSON_NONE)
		FT_RET_ERR(FALSE, FT_EINVOP);
	obj->type = JSON_ARRAY;

	obj->array.alloc = 0;
	obj->array.len = 0;
	obj->array.objs = NULL;

	FT_RET_OK(TRUE);
}

bool ft_json_set_null(struct s_json_object *obj)
{
	if (obj->type != JSON_NONE)
		FT_RET_ERR(FALSE, FT_EINVOP);
	obj->type = JSON_NULL;

	FT_RET_OK(TRUE);
}

struct s_json_object *ft_json_add_bool(struct s_json_object *obj, const_string key, bool b)
{
	struct s_json_object *new;

	if (obj->type != JSON_ARRAY && obj->type != JSON_OBJ)
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

	if (obj->type != JSON_ARRAY && obj->type != JSON_OBJ)
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

	if (obj->type != JSON_ARRAY && obj->type != JSON_OBJ)
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

	if (obj->type != JSON_ARRAY && obj->type != JSON_OBJ)
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

	if (obj->type != JSON_ARRAY && obj->type != JSON_OBJ)
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

	if (obj->type != JSON_ARRAY && obj->type != JSON_OBJ)
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

void ft_json_destroy_object(struct s_json_object *obj)
{
	struct s_json_member *nxt;

	switch (obj->type)
	{
	case JSON_STRING:
		free(obj->str);
		break;

	case JSON_OBJ:
		for (U64 i = 0; i < BUCKETS_INIT; i++)
		{
			for (struct s_json_member *curr = obj->obj->buckets[i]; curr; curr = nxt)
			{
				ft_json_destroy_object(curr->obj);
				free((void *)curr->key);
				nxt = curr->next;
				free(curr);
			}
		}
		free(obj->obj);
		break;

	case JSON_ARRAY:
		for (U64 i = 0; i < obj->array.len; i++)
			ft_json_destroy_object(obj->array.objs[i]);
		free(obj->array.objs);
		break;

	default:
		break;
	}

	free(obj);
}

/*
FT_EINVOP: invalid `obj->type`
FT_ERANGE: key already present
FT_EOMEM: out of memory
*/
bool ft_json_insert(struct s_json_object *obj, const_string key, struct s_json_object *value)
{
	struct s_json_member **lookup;

	if (obj->type != JSON_OBJ)
		FT_RET_ERR(FALSE, FT_EINVOP);

	lookup = lookup_ht(obj->obj, key);
	if ((*lookup) != NULL)
		/* key already present */
		FT_RET_ERR(FALSE, FT_ERANGE);

	if (!append_ht(lookup, key, value))
		return FALSE;

	FT_RET_OK(TRUE);
}

/*
FT_ENOENT: key not found
*/
struct s_json_object *ft_json_get(struct s_json_object *obj, const_string key)
{
	struct s_json_member **lookup;

	if (obj->type != JSON_OBJ)
		FT_RET_ERR(FALSE, FT_EINVOP);

	lookup = lookup_ht(obj->obj, key);
	if ((*lookup) == NULL)
		/* key not found */
		FT_RET_ERR(NULL, FT_ENOENT);
	FT_RET_OK((*lookup)->obj);
}

bool ft_json_append(struct s_json_object *obj, struct s_json_object *new)
{
	struct s_json_object **new_objs;

	if (obj->type != JSON_ARRAY)
		FT_RET_ERR(FALSE, FT_EINVOP);

	if (obj->array.objs == NULL || obj->array.len == 0)
	{
		obj->array.len = 0;
		obj->array.alloc = 4;
		if (UNLIKELY((obj->array.objs = malloc(sizeof(struct s_json_object *) * obj->array.alloc)) == NULL))
			FT_RET_ERR(FALSE, FT_EOMEM);
	}
	else if (obj->array.len >= obj->array.alloc)
	{
		if (UNLIKELY((new_objs = malloc(sizeof(struct s_json_object *) * obj->array.alloc * 2)) == NULL))
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

struct s_json_object *ft_json_parse(const_string json, U64 *rd, enum e_json_error *err)
{
#define SKIP_WHITESPACES()           \
	while (ft_iswhitespace(json[i])) \
	i++

	U64 i;
	U64 j;
	U64 ret_rd;
	S64 num;
	bool expect_comma;

	struct s_json_object *obj;
	struct s_json_object *new_member;
	string ptr;

	i = 0;
	if (UNLIKELY((obj = ft_json_new()) == NULL))
	{
		*err = JSON_ERR_SYS;
		return NULL;
	}

	SKIP_WHITESPACES();

	if (json[i] == '{')
	{
		i++;
		SKIP_WHITESPACES();
		ft_json_set_obj(obj);

		expect_comma = FALSE;
		while (json[i] != '}')
		{
			if (expect_comma)
			{
				if (json[i] != ',')
				{
					*err = JSON_ERR_MISSING_COMMA;
					goto exit_err;
				}
				i++;
				SKIP_WHITESPACES();
			}

			if (UNLIKELY((ptr = parse_string(json, &i)) == NULL))
			{
				if (ft_errno != FT_OK)
					*err = JSON_ERR_SYS;
				else
					*err = JSON_ERR_BAD_STRING;
				goto exit_err;
			}
			SKIP_WHITESPACES();

			if (json[i] != ':')
			{
				*err = JSON_ERR_BAD_CHARACTER;
				goto exit_err;
			}
			i++;
			SKIP_WHITESPACES();

			if (UNLIKELY((new_member = ft_json_parse(json + i, &ret_rd, err)) == NULL))
			{
				free(ptr);
				goto exit_err;
			}

			if (!ft_json_insert(obj, ptr, new_member))
			{
				ft_debug_break();
				*err = JSON_ERR_SYS;
				goto exit_err;
			}
			i += ret_rd;
			SKIP_WHITESPACES();

			expect_comma = TRUE;
		}
		i++;
	}
	else if (json[i] == '[')
	{
		i++;
		SKIP_WHITESPACES();
		ft_json_set_array(obj);

		expect_comma = FALSE;
		while (json[i] != ']')
		{
			if (expect_comma)
			{
				if (json[i] != ',')
				{
					*err = JSON_ERR_MISSING_COMMA;
					goto exit_err;
				}
				i++;
				SKIP_WHITESPACES();
			}

			if (UNLIKELY((new_member = ft_json_parse(json + i, &ret_rd, err)) == NULL))
				goto exit_err;
			if (!ft_json_append(obj, new_member))
			{
				*err = JSON_ERR_SYS;
				goto exit_err;
			}
			i += ret_rd;
			SKIP_WHITESPACES();

			expect_comma = TRUE;
		}
		i++;
	}
	else if (json[i] == '"')
	{
		if (UNLIKELY((ptr = parse_string(json, &i)) == NULL))
		{
			if (ft_errno != FT_OK)
				*err = JSON_ERR_SYS;
			else
				*err = JSON_ERR_BAD_STRING;
			goto exit_err;
		}
		if (!ft_json_set_string(obj, ptr))
		{
			*err = JSON_ERR_SYS;
			goto exit_err;
		}
		free(ptr);
	}
	else if (ft_isdigit(json[i]))
	{
		// TODO: ca pue la merde tres fort tout ca, l'unique solution c'est un strtol costaud
		j = i;
		while (json[i] && ft_isdigit(json[i]))
			i++;

		if (UNLIKELY((ptr = ft_strndup(json + j, i - j)) == NULL))
		{
			*err = JSON_ERR_SYS;
			goto exit_err;
		}

		num = ft_atoi(ptr);
		free(ptr);
		if (!ft_json_set_num(obj, num))
		{
			*err = JSON_ERR_SYS;
			goto exit_err;
		}
	}
	else if (!ft_strncmp(json, "true", 4))
	{
		if (!ft_json_set_bool(obj, TRUE))
		{
			*err = JSON_ERR_SYS;
			goto exit_err;
		}
		i += 4;
	}
	else if (!ft_strncmp(json, "false", 5))
	{
		if (!ft_json_set_bool(obj, FALSE))
		{
			*err = JSON_ERR_SYS;
			goto exit_err;
		}
		i += 5;
	}
	else if (!ft_strncmp(json, "null", 4))
	{
		if (!ft_json_set_null(obj))
		{
			*err = JSON_ERR_SYS;
			goto exit_err;
		}
		i += 4;
	}
	else
	{
		*err = JSON_ERR_BAD_CHARACTER;
		goto exit_err;
	}

	*rd = i;
	return obj;

exit_err:
	*rd = i;
	ft_json_destroy_object(obj);
	return NULL;
}

static bool __json_dump_grow(string *out, U64 *alloc, U64 *len, U64 strlen)
{
	string new;

	if (*len + strlen >= *alloc)
	{
		if (UNLIKELY((new = malloc(sizeof(U8) * *alloc * 2)) == NULL))
			FT_RET_ERR(FALSE, FT_EOMEM);
		ft_memcpy(new, *out, *len);
		free(*out);
		*out = new;
		*alloc *= 2;
	}

	FT_RET_OK(TRUE);
}

static bool __json_dump_append(string *out, U64 *alloc, U64 *len, const_string str, U64 strlen)
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
	bool comma;

#define _JSON_APPEND(_str, _len)                              \
	do                                                        \
	{                                                         \
		if (!__json_dump_append(out, alloc, len, _str, _len)) \
			FT_RET_ERR(FALSE, ft_errno);                      \
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
					if (!__json_dump_append(out, alloc, len, ",", 1))
						do
						{
							(*__ft_errno_location()) = (*__ft_errno_location());
							return 0;
						} while (0);
				// if (comma)
				//	_JSON_APPEND(",", 1);
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

	case JSON_ARRAY:
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

	case JSON_BOOL:
		if (obj->boolean)
		{
			_JSON_APPEND("true", 4);
		}
		else
		{
			_JSON_APPEND("false", 5);
		}
		break;

	case JSON_NUM:
		U64 n_digits = _ft_utoa(NULL, 0, 0, obj->num, NULL, S64_MAX);
		if (!__json_dump_grow(out, alloc, len, n_digits + 1))
			FT_RET_ERR(FALSE, ft_errno);
		*len += _ft_utoa(NULL, 0, n_digits, obj->num, *out + *len, S64_MAX);
		(*out)[*len] = '\0';
		break;

	case JSON_STRING:
		_JSON_APPEND("\"", 1);
		_JSON_APPEND(obj->str, 0);
		_JSON_APPEND("\"", 1);
		break;

	case JSON_NULL:
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
	U64 alloc;

	alloc = 1024;
	if (UNLIKELY((out = malloc(sizeof(U8) * alloc)) == NULL))
		FT_RET_ERR(NULL, FT_EOMEM);
	*out = '\0';

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

static const_string errors_str[] = {
	"JSON_ERR_SYS",
	"JSON_ERR_BAD_CHARACTER",
	"JSON_ERR_DUPLICATE_MEMBER",
	"JSON_ERR_BAD_STRING",
	"JSON_ERR_MISSING_COMMA",
};

const_string ft_json_strerror(enum e_json_error err)
{
	if (err < 0 || err >= (sizeof(errors_str) / sizeof(errors_str[0])))
		return NULL;

	if (err == JSON_ERR_SYS)
		return ft_strerror2();

	return errors_str[err];
}
