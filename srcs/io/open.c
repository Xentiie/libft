/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 13:47:45 by reclaire          #+#    #+#             */
/*   Updated: 2024/11/26 07:35:25 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file_private.h"

#include <stdlib.h>
#include <errno.h>

static bool parse_mode(const_string mode, bool *readable, bool *writeable, bool *append)
{
	*readable = FALSE;
	*writeable = FALSE;
	*append = FALSE;

	switch (*mode++)
	{
	case 'r':
		*readable = TRUE;
		break;
	case 'w':
		*writeable = TRUE;
		break;
	case 'a':
		*writeable = TRUE;
		*append = TRUE;
		break;
	default:
		return FALSE;
	}

	if (*mode == '+')
	{
		*readable = TRUE;
		*writeable = TRUE;
	}

	return TRUE;
}

#if defined(FT_OS_WIN)
#include <windows.h>

filedesc ft_open_old(const_string path, const_string mode)
{
	bool readable, writeable, append;
	S32 open_mode, create_mode;
	filedesc fd;

	if (path == NULL || mode == NULL)
		FT_RET_ERR((filedesc)-1, FT_EINVPTR);

	if (!parse_mode(mode, &readable, &writeable, &append))
		FT_RET_ERR((filedesc)-1, FT_EINVVAL);

	open_mode = readable ? GENERIC_READ : 0;
	if (writeable)
		open_mode |= GENERIC_WRITE;
	if (append)
		open_mode = FILE_APPEND_DATA;
	create_mode = (writeable || append) ? OPEN_ALWAYS : OPEN_EXISTING;

	if ((fd = CreateFileA(path, open_mode,
						  0,					 // Share mode (0 for exclusive access)
						  NULL,					 // Security attributes (NULL for default)
						  create_mode,			 // Creation disposition (open existing file)
						  FILE_ATTRIBUTE_NORMAL, // File attributes (normal file)
						  NULL					 // Template file (NULL for none)
						  )) == INVALID_HANDLE_VALUE)
		FT_RET_ERR((filedesc)-1, FT_ESYSCALL);
	FT_RET_OK(fd);
}

#else

#include <unistd.h>
#include <fcntl.h>
#if !defined(__USE_MISC)
#define __USE_MISC
#endif
#include <sys/stat.h>

filedesc ft_open(const_string path, const_string mode)
{
	bool readable, writeable, append;
	S32 open_mode, create_mode;
	filedesc fd;

	if (path == NULL || mode == NULL)
		FT_RET_ERR((filedesc)-1, FT_EINVPTR);

	if (!parse_mode(mode, &readable, &writeable, &append))
		FT_RET_ERR((filedesc)-1, FT_EINVVAL);

	if (readable && writeable)
		open_mode = O_RDWR;
	else
	{
		if (readable)
			open_mode = O_RDONLY;
		else if (writeable)
			open_mode = O_WRONLY;
	}

	create_mode = append ? O_CREAT | O_APPEND : (writeable ? O_CREAT | O_TRUNC : 0);

	if ((fd = open(path, open_mode | create_mode, DEFFILEMODE)) == -1)
		FT_RET_ERR((filedesc)-1, FT_ESYSCALL);
	FT_RET_OK(fd);
}
#endif

t_file *ft_fopen(const_string path, const_string mode)
{
	filedesc fd;
	t_file *out;

	if ((fd = ft_open(path, mode)) == (filedesc)-1)
		return NULL;
	if ((out = ft_fcreate(fd, mode)) == NULL)
		ft_close(fd);
	return out;
}

t_file *ft_fcreate(filedesc fd, const_string mode)
{
	bool readable, writeable, append;
	t_file *file;

	if (UNLIKELY((file = malloc(sizeof(t_file))) == NULL))
		goto exit_omem;

	if (!parse_mode(mode, &readable, &writeable, &append))
		goto exit_err;

	file->readable = readable;
	file->writeable = writeable;

	file->fd = fd;
	file->buff_cnt = 0;
	file->buff_size = 0;
	file->buff = NULL;
	file->buffering_mode = FT_IO_UNBUFFERED;

	errno = 0;
	if (isatty(file->fd))
		ft_fsetbuf(file, NULL, 0, FT_IO_LINE_BUFFERED);
	else
		ft_fsetbuf(file, NULL, 0, FT_IO_FULL_BUFFERED);
	if (errno == ENOTTY || errno == EINVAL)
		errno = 0;

	FT_RET_OK(file);

exit_omem:
	free(file);
	FT_RET_ERR(NULL, FT_EOMEM);
exit_err:
	free(file);
	FT_RET_ERR(NULL, ft_errno);
}
