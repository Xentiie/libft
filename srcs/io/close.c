/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 01:47:39 by reclaire          #+#    #+#             */
/*   Updated: 2024/11/26 20:47:26 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file_private.h"

#include <stdlib.h>

# if defined(FT_OS_WIN)
#  include <windows.h>
void	ft_close(filedesc fd)
{
	if (fd == ((filedesc)-1))
		FT_RET_ERR(, FT_EINVVAL);

	if (!CloseHandle(((HANDLE)fd)))
		FT_RET_ERR(, FT_ESYSCALL);

	FT_RET_OK();
}

/* socket close */
void	ft_sclose(filedesc fd)
{
	
}

# else
#  include <unistd.h>
void	ft_close(filedesc fd)
{
	close(fd);
	FT_RET_OK();
}

void	ft_sclose(filedesc fd)
{
	ft_close(fd);
}
# endif

void ft_fdestroy(t_file *file)
{
	ft_ffilelock(file);
	ft_fflush(file);
	free(file->buff);

	__ft_flockcleanup(file);
	free(file);
}

void ft_fclose(t_file *file)
{
	filedesc fd;

	fd = file->fd;
	ft_fdestroy(file);
	ft_close(fd);
}
