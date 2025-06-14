/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readfile.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 22:55:52 by reclaire          #+#    #+#             */
/*   Updated: 2025/06/08 02:14:14 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file_private.h"

#include <stdlib.h>

U8 *__readfile_impl(filedesc fd, U64 *out_size, bool append_0)
{
	S64 rd, total_rd;
	U8 buffer[32768];
	U64 alloc;
	U8 *data, *tmp;

	alloc = sizeof(buffer);
	if (UNLIKELY((data = ftalloc(sizeof(U8) * alloc)) == NULL))
		goto exit_err;

	total_rd = 0;
	while ((rd = ft_read(fd, (char *)buffer, sizeof(buffer))) > 0)
	{
		if ((S64)alloc < (total_rd + rd))
		{
			if (UNLIKELY((tmp = ftalloc(sizeof(U8) * alloc * 2)) == NULL))
				goto exit_err_cleanup;
			ft_memcpy(tmp, data, total_rd);
			free(data);
			data = tmp;
			alloc *= 2;
		}
		ft_memcpy(data + total_rd, buffer, rd);
		total_rd += rd;
	}

	if (rd == -1)
		goto exit_err_cleanup;

	if ((S64)alloc > total_rd)
	{
		if (UNLIKELY((tmp = ftalloc(sizeof(U8) * (total_rd + append_0))) == NULL))
			goto exit_err_cleanup;
		ft_memcpy(tmp, data, total_rd);
		free(data);
		data = tmp;
	}

	if (append_0)
	{
		data[total_rd] = '\0';
		total_rd++;
	}

	if (out_size)
		*out_size = total_rd;
	FT_RET_OK(data);
exit_err_cleanup:
	free(data);
exit_err:
	if (out_size)
		*out_size = 0;
	FT_RET_ERR(NULL, FT_EOMEM);
}

U8 *ft_readfile(filedesc fd, U64 *out_size)
{
	return __readfile_impl(fd, out_size, FALSE);
}

U8 *ft_freadfile(t_file *file, U64 *out_size)
{
	U8 *out;

	if (UNLIKELY(!ft_ffilelock(file)))
		return NULL;
	out = __readfile_impl(file->fd, out_size, !file->binary_mode);
	ft_ffileunlock(file);

	return out;
}
