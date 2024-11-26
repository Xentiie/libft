/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fcreate.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 22:50:27 by reclaire          #+#    #+#             */
/*   Updated: 2024/11/26 22:50:47 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file_private.h"

#include <errno.h>

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
