/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_open.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 13:47:45 by reclaire          #+#    #+#             */
/*   Updated: 2024/01/17 13:47:45 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#ifdef FT_FILEIO

# if !defined(FT_STRINGS)
#  error FT_STRINGS need to be defined for FT_FILEIO
# endif

# if defined(FT_WIN32)
#  include <windows.h>

file ft_fopen(string path, string mode)
{
	if (path == NULL || mode == NULL)
	{
		ft_errno = FT_EINVPTR;
		return ((file)-1);
	}

	S32 open_mode = 0;
	S32 create_mode = 0;

	switch (*mode++)
	{
	case 'r':
		open_mode = GENERIC_READ;
		create_mode = OPEN_EXISTING;
		break;
	case 'w':
		open_mode = GENERIC_WRITE;
		create_mode = OPEN_ALWAYS;
		break;
	case 'a':
		open_mode = FILE_APPEND_DATA;
		create_mode = OPEN_ALWAYS;
		break;
	default:
		ft_errno = FT_EINVVAL;
		return ((file)-1);
	}

	if (*mode == '+')
	{
		open_mode = GENERIC_READ | GENERIC_WRITE;
	}

	HANDLE hFile = CreateFileW(path, open_mode,
							  0,					 // Share mode (0 for exclusive access)
							  NULL,					 // Security attributes (NULL for default)
							  create_mode,			 // Creation disposition (open existing file)
							  FILE_ATTRIBUTE_NORMAL, // File attributes (normal file)
							  NULL					 // Template file (NULL for none)
	);

	if (hFile == INVALID_HANDLE_VALUE)
	{
		ft_errno = FT_ESYSCALL;
		return ((file)-1);
	}
	ft_errno = FT_OK;
	return hFile;
}

# else

#  include <unistd.h>
#  include <fcntl.h>
inline file ft_fopen(string path, S32 flags)
{
	S32 _flags = 0;
	if (flags & FT_FILEIO_READ)
		_flags |= GENERIC_READ;
	if (flags & FT_FILEIO_WRITE)
		_flags |= GENERIC_WRITE;

	file fd = open(path, flags);
	//TODO: check error
	
	ft_errno = FT_OK;
	return fd;
}
# endif

#endif