/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 13:40:56 by reclaire          #+#    #+#             */
/*   Updated: 2025/04/14 20:24:51 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file_private.h"

#include "libft/strings.h"

#if FT_OS_WINDOWS
#include <windows.h>

S64 ft_write(filedesc fd, void *buffer, U64 size)
{
	S64 bytes_read;

	bytes_read = 0;
	if (WriteFile(fd, buffer, size, (LPDWORD)&bytes_read, NULL) == FALSE)
		FT_RET_ERR(-1, FT_ESYSCALL);

	FT_RET_OK(bytes_read);
}

#elif FT_OS_POSIX

S64 ft_write(filedesc fd, void *buffer, U64 size)
{
	S64 bytes_read;

	if ((bytes_read = write(fd, buffer, size)) == -1)
		FT_RET_ERR(-1, FT_ESYSCALL);
	FT_RET_OK(bytes_read);
}

#endif

S64 ft_fwrite(t_file *file, void *buffer, U64 size)
{
	S64 ret;

	if (size == 0)
		return 0;

	if (UNLIKELY(!ft_ffilelock(file)))
		return -1;
	ret = ft_fwrite_unlocked(file, buffer, size);
	ft_ffileunlock(file);
	return ret;
}

S64 ft_fwrite_unlocked(t_file *file, void *buffer, U64 size)
{

	if (!file->writeable)
		FT_RET_ERR(-1, FT_EINVVAL);

	if (file->buffering_mode == FT_IO_UNBUFFERED)
		return ft_write(file->fd, buffer, size);

	if ((file->buff_cnt + size) < file->buff_size)
	{
		// TODO: memcpy + memchr = pas opti
#if 0
		U64 n;
		//TODO: lol marche pas
		if (file->buffering_mode == FT_IO_LINE_BUFFERED)
		{
			n = file->buff_cnt;
			for (U64 i = 0; i < size; i++, n++)
			{
				file->buff[n] = ((U8 *)buffer)[i];
				if (file->buff[n] == '\n')
				{
					file->buff_cnt = n + 1;
					ft_fflush(file);
					if (ft_errno != FT_OK)
						FT_RET_ERR(-1, ft_errno);
					n = 0;
				}
			}
			file->buff_cnt = n - 1;
		}
		else
		{
			ft_memcpy(file->buff + file->buff_cnt, buffer, size);
			file->buff_cnt += size;
		}
#else
		ft_memcpy(file->buff + file->buff_cnt, buffer, size);
		file->buff_cnt += size;
		if (file->buffering_mode == FT_IO_LINE_BUFFERED && ft_memchr(buffer, '\n', size))
		{
			ft_fflush(file);
			if (ft_errno != FT_OK)
				FT_RET_ERR(-1, ft_errno);
		}
#endif

		FT_RET_OK((S64)size);
	}
	else
	{
		ft_fflush(file);
		if (ft_errno != FT_OK)
			FT_RET_ERR(-1, ft_errno);
		return ft_write(file->fd, buffer, size);
	}
}
