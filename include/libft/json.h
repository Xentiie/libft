/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   json.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 16:57:57 by reclaire          #+#    #+#             */
/*   Updated: 2025/04/15 01:50:51 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(LIBFT_JSON_H)
#define LIBFT_JSON_H

#include "libft/libft.h"

enum e_json_error;
enum e_json_type;
struct s_json_object;
struct s_json_iterator;

enum e_json_error
{
	JSON_ERR_SYS,
	JSON_ERR_BAD_CHARACTER,
	JSON_ERR_DUPLICATE_MEMBER,
	JSON_ERR_BAD_STRING,
	JSON_ERR_MISSING_COMMA,
};

enum e_json_type
{
	/* DO NOT USE */
	JSON_NONE = 0,
	/* boolean */
	JSON_BLN,
	/* string */
	JSON_STR,
	/* numerical value */
	JSON_NUM,
	/* json object dictionnary */
	JSON_OBJ,
	/* json objects array */
	JSON_ARR,
	/* null */
	JSON_NUL,
};

struct s_json_object
{
	enum e_json_type type;

	union
	{
		string str;
		S64 num;
		bool boolean;

		struct s_json_ht *obj;

		struct
		{
			U64 len;
			U64 alloc;
			struct s_json_object **objs;
		} array;
	};
};

struct s_json_member
{
	struct s_json_member *next;
	const_string key;
	struct s_json_object *obj;
};

/*
Allocates a new json object, with undefined type. Cannot be used before any call to `ft_json_set_*`.
### On error
Sets ft_errno and returns `NULL`.
### ft_errno
- FT_EOMEM if out of memory
*/
struct s_json_object *ft_json_new();

/*
Sets the type to `JSON_BOOLEAN`, and sets the boolean value to `b`.
### On error
Sets ft_errno and returns `FALSE`.
### ft_errno
- FT_EINVOP if the type for this json object has already been set
*/
bool ft_json_set_bool(struct s_json_object *obj, bool b);

/*
Sets the type to `JSON_STRING`, and sets the string value to `str`.
### On error
Sets ft_errno and returns `FALSE`.
### ft_errno
- FT_EINVOP if the type for this json object has already been set
*/
bool ft_json_set_string(struct s_json_object *obj, const_string str);

/*
Sets the type to `JSON_STRING`, and sets the string value to `str`.
### On error
Sets ft_errno and returns `FALSE`.
### ft_errno
- FT_EINVOP if the type for this json object has already been set
*/
bool ft_json_set_num(struct s_json_object *obj, S64 num);

/*
Sets the type to `JSON_OBJ`, and initializes the hash table for this object.
### On error
Sets ft_errno and returns `FALSE`.
### ft_errno
- FT_EINVOP if the type for this json object has already been set
- FT_EOMEM if out of memory
*/
bool ft_json_set_obj(struct s_json_object *obj);

/*
Sets the type to `JSON_OBJ`, and initializes the array to all 0 values.
### On error
Sets ft_errno and returns `FALSE`.
### ft_errno
- FT_EINVOP if the type for this json object has already been set
- FT_EOMEM if out of memory
*/
bool ft_json_set_array(struct s_json_object *obj);

/*
Sets the type to `JSON_NUL`.
### On error
Sets ft_errno and returns `FALSE`.
### ft_errno
- FT_EINVOP if the type for this json object has already been set
*/
bool ft_json_set_null(struct s_json_object *obj);

/*
A combination of ft_json_new_object, ft_json_set_bool and ft_json_insert/ft_json_append
If `obj->type == JSON_ARR`, `key` is ignored and can be set to NULL
### On error
Sets ft_errno and returns `NULL`
### ft_errno
- FT_EINVOP if `obj->type != JSON_OBJ && obj->type != JSON_ARR`
- FT_EINVPTR if `obj->type == JSON_OBJ` and `key == NULL`
- FT_ERANGE if `obj->type == JSON_OBJ` and a value for `key` already exists
- FT_EOMEM if out of memory
For other errors check said functions.
*/
struct s_json_object *ft_json_add_bool(struct s_json_object *obj, const_string key, bool b);

/*
A combination of ft_json_new_object, ft_json_add_string and ft_json_insert/ft_json_append
If `obj->type == JSON_ARR`, `key` is ignored and can be set to NULL
### On error
Sets ft_errno and returns `NULL`
### ft_errno
- FT_EINVOP if `obj->type != JSON_OBJ && obj->type != JSON_ARR`
- FT_EINVPTR if `obj->type == JSON_OBJ` and `key == NULL`
- FT_ERANGE if `obj->type == JSON_OBJ` and a value for `key` already exists
- FT_EOMEM if out of memory
For other errors check said functions.
*/
struct s_json_object *ft_json_add_string(struct s_json_object *obj, const_string key, const_string str);

/*
A combination of ft_json_new_object, ft_json_add_num and ft_json_insert/ft_json_append
If `obj->type == JSON_ARR`, `key` is ignored and can be set to NULL
### On error
Sets ft_errno and returns `NULL`
### ft_errno
- FT_EINVOP if `obj->type != JSON_OBJ && obj->type != JSON_ARR`
- FT_EINVPTR if `obj->type == JSON_OBJ` and `key == NULL`
- FT_ERANGE if `obj->type == JSON_OBJ` and a value for `key` already exists
- FT_EOMEM if out of memory
For other errors check said functions.
*/
struct s_json_object *ft_json_add_num(struct s_json_object *obj, const_string key, S64 num);

/*
A combination of ft_json_new_object, ft_json_add_obj and ft_json_insert/ft_json_append
If `obj->type == JSON_ARR`, `key` is ignored and can be set to NULL
### On error
Sets ft_errno and returns `NULL`
### ft_errno
- FT_EINVOP if `obj->type != JSON_OBJ && obj->type != JSON_ARR`
- FT_EINVPTR if `obj->type == JSON_OBJ` and `key == NULL`
- FT_ERANGE if `obj->type == JSON_OBJ` and a value for `key` already exists
- FT_EOMEM if out of memory
For other errors check said functions.
*/
struct s_json_object *ft_json_add_obj(struct s_json_object *obj, const_string key);

/*
A combination of ft_json_new_object, ft_json_add_array and ft_json_insert/ft_json_append
If `obj->type == JSON_ARR`, `key` is ignored and can be set to NULL
### On error
Sets ft_errno and returns `NULL`
### ft_errno
- FT_EINVOP if `obj->type != JSON_OBJ && obj->type != JSON_ARR`
- FT_EINVPTR if `obj->type == JSON_OBJ` and `key == NULL`
- FT_ERANGE if `obj->type == JSON_OBJ` and a value for `key` already exists
- FT_EOMEM if out of memory
For other errors check said functions.
*/
struct s_json_object *ft_json_add_array(struct s_json_object *obj, const_string key);

/*
A combination of ft_json_new_object, ft_json_add_null and ft_json_insert/ft_json_append
If `obj->type == JSON_ARR`, `key` is ignored and can be set to NULL
### On error
Sets ft_errno and returns `NULL`
### ft_errno
- FT_EINVOP if `obj->type != JSON_OBJ && obj->type != JSON_ARR`
- FT_EINVPTR if `obj->type == JSON_OBJ` and `key == NULL`
- FT_ERANGE if `obj->type == JSON_OBJ` and a value for `key` already exists
- FT_EOMEM if out of memory
For other errors check said functions.
*/
struct s_json_object *ft_json_add_null(struct s_json_object *obj, const_string key);

/*
Destroys a json object. Type specific:
- JSON_OBJ: destroys all the key/values recursively
- JSON_ARR: destroys all the arrays values recursively
### On error
Sets ft_errno
### ft_errno
- FT_EOMEM if out of memory
*/
void ft_json_destroy_object(struct s_json_object *obj);

/*
Parses the string `json`, which should represent a json object.
### On error
Sets `err` and ft_errno if needed, and returns `FALSE`.
If some weird errors appear in ft_errno, check breakpoints in debugger, since calls are made to other `ft_json_*` functions,
so errors could arise from them.
### err
- JSON_ERR_SYS: check ft_errno
- JSON_ERR_BAD_CHARACTER: an invalid character is present in the json
- JSON_ERR_DUPLICATE_MEMBER: a key appeared at least twice in a json object
- JSON_ERR_BAD_STRING: a string has no terminated double quotes
- JSON_ERR_MISSING_COMMA: couldn't find the comma :(
### ft_errno
- FT_EINVOP if the type for this json object has already been set
*/
struct s_json_object *ft_json_parse(const_string json, U64 *rd, enum e_json_error *err);

/*
Dumps the json object `obj` to a string. Caller gets ownership of returned string. Length of the string is put in `len`.
### On error
Sets ft_errno and returns `NULL`.
### ft_errno
- FT_EINVOP if some object in `obj` has an invalid type (`ft_json_set_*` has not been called !)
- FT_EOMEM if out of memory
*/
string ft_json_dump(struct s_json_object *obj, U64 *len);

/*
Searches for the value associated with `key`
### On error
Sets ft_errno and returns `NULL`.
### ft_errno
- FT_EINVOP if `obj->type` is not `JSON_OBJ`
- FT_ENOENT if no object associated with `key` has been found
*/
struct s_json_object *ft_json_get(struct s_json_object *obj, const_string key);

/*
Set the object `value` to the key `key`
### On error
Sets ft_errno and returns `FALSE`.
### ft_errno
- FT_EINVOP if `obj->type` is not `JSON_OBJ`
- FT_ERANGE if `key` is already used
- FT_EOMEM if out of memory
*/
bool ft_json_insert(struct s_json_object *obj, const_string key, struct s_json_object *value);

/*
Initializes a new json iterator
### On error
Sets ft_errno and returns `FALSE`.
### ft_errno
- FT_EINVOP if `obj->type` is not `JSON_OBJ`
- FT_EOMEM if out of memory
*/
struct s_json_iterator *ft_json_iter_init(struct s_json_object *obj);

/*
Resets an existing iterator. If `obj` is NULL then doesn't change the object associated with `it`
*/
void ft_json_iter_reset(struct s_json_iterator *it, struct s_json_object *obj);

/*
Returns the next member in the json object associated with `it`
Note:
Iterator store the next element, so you're free to destroy the element returned by this function,
as long as you don't destroy the next one.
*/
struct s_json_member *ft_json_iter(struct s_json_iterator *it);

/*
Cleanups ressources used by `it`
*/
void ft_json_iter_destroy(struct s_json_iterator *it);

/*
Appends the object `new` to the json array in `obj`
### On error
Sets ft_errno and returns `FALSE`.
### ft_errno
- FT_EINVOP if `obj->type` is not `JSON_ARR`
- FT_EOMEM if out of memory
*/
bool ft_json_append(struct s_json_object *obj, struct s_json_object *new);

/* Returns the error string for `err`, or NULL if no string */
const_string ft_json_strerror(enum e_json_error err);

#endif
