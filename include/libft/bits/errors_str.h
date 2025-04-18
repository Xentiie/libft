/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_str.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 20:41:37 by reclaire          #+#    #+#             */
/*   Updated: 2025/04/15 02:33:53 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(FT_BITS_ERRORS_STR_H)
#define FT_BITS_ERRORS_STR_H

#include "libft/bits/ft_return.h"
#include "libft/bits/static_array_len.h"

#include "libft/macros.h"
#include "libft/types.h"

#define __unpack_error_entry(name, desc) {name, desc}
#define __unpack_error_entry_helper(packed) __unpack_error_entry packed
/*
Defines a static array of error entries.
`entries_var_name` is the array's name
__VA_ARGS__ is the array of error entries tuple. Should be formatted like this:
	[FT_OK] = { "FT_OK", "No error" }, [FT_EOMEM] = { "FT_EOMEM", "Out of memory" }, ...
*/
#define FT_DEFINE_ERROR_ENTRIES(entries_var_name, ...) \
	static struct                                      \
	{                                                  \
		string name;                                   \
		string desc;                                   \
	} entries_var_name[] = {__VA_ARGS__}

/*
Defines the body of a strerror like function. The function must return a `const_string`, and must have a variable
`S32 err` declared before the macro invocation (either as a function parameter, or a variable).

`entries_var_name` is the name of the errors entries array, that should be created using `FT_DEFINE_ERROR_ENTRIES`
*/
#define FT_DEFINE_STRERROR(entries_var_name)          \
	if (err < 0)                                      \
		FT_RET_ERR((NULL), FT_ERANGE);                \
	if (err > (S64)(statarray_len(entries_var_name))) \
		FT_RET_ERR((NULL), FT_ENOENT);                \
	return (entries_var_name)[err].desc;

/*
Defines the body of a strerrorname like function. The function must return a `const_string`, and must have a variable
`S32 err` declared before the macro invocation (either as a function parameter, or a variable).

`entries_var_name` is the name of the errors entries array, that should be created using `FT_DEFINE_ERROR_ENTRIES`
*/
#define FT_DEFINE_STRERRORNAME(entries_var_name)      \
	if (err < 0)                                      \
		FT_RET_ERR((NULL), FT_ERANGE);                \
	if (err > (S64)(statarray_len(entries_var_name))) \
		FT_RET_ERR((NULL), FT_ENOENT);                \
	return entries[err].name;

#endif
