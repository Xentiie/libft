/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 13:40:56 by reclaire          #+#    #+#             */
/*   Updated: 2024/11/18 04:08:06 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file.h"
#include "libft/io.h"
#include "libft/strings.h"

#if defined(FT_OS_WIN)
#include <windows.h>

S64 ft_write(filedesc fd, char *buffer, U64 size)
{
	S64 bytes_read = 0;
	if (WriteFile(fd, buffer, size, (LPDWORD)&bytes_read, NULL) == FALSE)
		__FTRETURN_ERR(-1, FT_ESYSCALL);

	__FTRETURN_OK(bytes_read);
}

#elif defined(FT_OS_LINUX) || defined(FT_OS_MAC)
#include <unistd.h>

S64 ft_write(filedesc fd, char *buffer, U64 size)
{
	S64 bytes_read = write(fd, buffer, size);
	if (bytes_read == -1)
	{
		__FTRETURN_ERR(-1, FT_ESYSCALL);
	}

	__FTRETURN_OK(bytes_read);
}

#endif

S64 ft_fwrite(t_file *file, char *buffer, U64 size)
{
	S64 ret;

	if (UNLIKELY(!ft_ffilelock(file)))
		return -1;

	if (!file->buffered)
		ret = ft_write(file->fd, buffer, size);
	else
	{
		if ((file->buff_cnt + size) < file->buff_size)
		{
			ft_memcpy(file->buff + file->buff_cnt, buffer, size);
			file->buff_cnt += size;
			if (ft_strnchr(buffer, '\n', size))
			{
				ft_fflush(file);
				ret = ft_errno == 0 ? (S64)size : -1;
			}
			else
				ret = (S64)size;
		}
		else
		{
			ft_fflush(file);
			ret = ft_errno == 0 ? ft_write(file->fd, buffer, size) : -1;
		}
	}
	ft_ffileunlock(file);
	return ret;
}
