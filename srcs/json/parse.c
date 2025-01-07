/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 01:48:49 by reclaire          #+#    #+#             */
/*   Updated: 2025/01/07 02:12:11 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "json_private.h"

#include "libft/strings.h"

#include <stdlib.h>

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
				free(ptr);
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
