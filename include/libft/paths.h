/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 19:49:34 by reclaire          #+#    #+#             */
/*   Updated: 2025/01/02 23:26:18 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(LIBFT_PATH_H)
#define LIBFT_PATH_H

#include "libft.h"
#include "libft/lists.h"

/*
//TODO: doc
Parses a path, and puts result in the chained list pointed to by `lst`.
Note:
- Removes any duplicate '/'
- If an error occurs (such as out of memory), `lst` may contain some allocated strings

Examples:
- `path/to///something` -> `path/to/something`
*/
bool ft_path_parse(t_list **lst, const_string path);

/*
//TODO: doc
Edits path to make it partially absolute:
- Removes any '.'
- Resolves '..' if possible

This function doesn't make any syscalls to try and fully resolve relative the path
*/
void ft_path_partial_absolute(t_list **path);

/*
Returns the filename of a path, meaning the last part of the path.
### On error
Sets ft_errno and returns NULL.
### ft_errno
- FT_EINVPTR if 'path' is NULL
- FT_EOMEM if out of memory
*/
string ft_path_filename(const_string path);

/*
Returns the dirname of a path, meaning everything except the last part of the path.
### On error
Sets ft_errno and returns NULL.
### ft_errno
- FT_EINVPTR if 'path' is NULL
- FT_EOMEM if out of memory
*/
string ft_path_dirname(const_string path);

/*
Returns TRUE if the specified path contains no unauthorized characters for current OS
### On error
Sets ft_errno and returns NULL.
### ft_errno
- FT_EINVPTR if 'path' is NULL
- FT_ENOENT if current OS isn't supported
*/
bool ft_path_valid(const_string path);

/*
Returns TRUE if the specified path contains no unauthorized characters for specifed OS `target`
### On error
Sets ft_errno and returns NULL.
### ft_errno
- FT_EINVPTR if 'path' is NULL
- FT_ENOENT if specified OS isn't supported
*/
bool ft_path_valid2(const_string path, S32 target);

/*
//TODO: do
*/
bool ft_path_expanduser(const_string path);

#endif