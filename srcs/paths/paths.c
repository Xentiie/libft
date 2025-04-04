/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 05:54:01 by reclaire          #+#    #+#             */
/*   Updated: 2025/03/20 14:36:21 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "forbidden_chars.h"
#include "libft_int.h"
#include "libft/paths.h"
#include "libft/strings.h"
#include "libft/io.h"

#include <stdlib.h>

string ft_path_filename(const_string path)
{
	const_string sv;
	U64 l;

	if (UNLIKELY(path == NULL))
		FT_RET_ERR(NULL, FT_EINVPTR);

	sv = path;
	l = ft_strlen(path);
	path = &path[l - 1];

	while (path > (sv - 1) && *(path - 1) != '/')
		path--;
	return ft_strdup(path);
}

//TODO: test
string ft_path_dirname(const_string path)
{
	U64 l;
	string out;

	if (UNLIKELY(path == NULL))
		FT_RET_ERR(NULL, FT_EINVPTR);

	l = ft_strlen(path);
	while (l && path[l - 1] != '/')
		l--;
	if (l == 0)
		return "";
	while (l && path[l - 1] == '/')
		l--;

	if (UNLIKELY((out = malloc(sizeof(char) * (l + 2))) == NULL))
		FT_RET_ERR(NULL, FT_EOMEM);
	ft_memcpy(out, path, l);
	out[l] = '/';
	out[l + 1] = '\0';

	FT_RET_OK(out);
}

bool ft_path_valid(const_string path)
{
	return ft_path_valid2(path, 0);
}

bool ft_path_valid2(const_string path, S32 target)
{
	const_string forbidden_chars;

	if (UNLIKELY(path == NULL))
		FT_RET_ERR(FALSE, FT_EINVPTR);

	if (target == 0)
	{
#if defined(FT_OS_WINDOWS)
		target = FT_TARGET_WIN;
#elif defined(FT_OS_LINUX)
		target = FT_TARGET_LINUX;
#else
		target = -1;
#endif
	}

	if (UNLIKELY((forbidden_chars = get_forbidden_chars(target)) == NULL))
		FT_RET_ERR(FALSE, FT_ENOENT);
	while (*path)
	{
		if (ft_strchr(forbidden_chars, *path))
			return FALSE;
		path++;
	}
	return TRUE;
}
