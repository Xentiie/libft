/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 20:19:41 by reclaire          #+#    #+#             */
/*   Updated: 2025/03/20 14:36:21 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file_private.h"
#include <errno.h>

# if defined(FT_OS_WINDOWS)
#  include <windows.h>

S64	ft_read(filedesc fd, void *buffer, U64 size)
{
	S64 bytes_read = 0;
	if (UNLIKELY(ReadFile(fd, buffer, size, (LPDWORD)&bytes_read, NULL) == FALSE))
		FT_RET_ERR(-1, FT_ESYSCALL);
	FT_RET_OK(bytes_read);
}

# elif defined(FT_OS_LINUX) || defined(FT_OS_MAC)
#  include <unistd.h>

S64 ft_read(filedesc fd, void *buffer, U64 size)
{
	if (buffer == NULL)
		FT_RET_ERR(-1, FT_EINVPTR);
	S64 bytes_read = read(fd, buffer, size);
	if (UNLIKELY(bytes_read == -1))
		FT_RET_ERR(-1, FT_ESYSCALL);
	FT_RET_OK(bytes_read);
}

# endif

S64 ft_fread(t_file *file, void *buffer, U64 size)
{
	S64 ret;

	if (UNLIKELY(!ft_ffilelock(file)))
		return -1;
	ret = ft_fread_unlocked(file, buffer, size);
	ft_ffileunlock(file);
	return ret;
}

S64 ft_fread_unlocked(t_file *file, void *buffer, U64 size)
{
	if (!file->readable)
		FT_RET_ERR(-1, FT_EINVVAL);
	return ft_read(file->fd, buffer, size);
}
