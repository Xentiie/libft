/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fsetbuf.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 08:50:16 by reclaire          #+#    #+#             */
/*   Updated: 2024/12/03 06:04:23 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file_private.h"

#include <stdlib.h>

#if defined(_FT_BUFSIZ)
U64 _ft_bufsiz = _FT_BUFSIZ;
#else
U64 _ft_bufsiz = 8192;
#endif

/*
Si buf == NULL:
	Si size == 0 et buff_size != _ft_bufsiz : reset buffer size to _ft_bufsiz

*/

bool ft_fsetbuf(t_file *f, U8 *buf, U64 size, S16 bufmode)
{
	U64 new_size;
	U8 *new;

	switch (bufmode)
	{
	case FT_IO_UNBUFFERED:
		ft_fflush(f);
		free(f->buff);
		f->buff = NULL;
		f->buff_size = 0;
		break;

	case FT_IO_LINE_BUFFERED:
	case FT_IO_FULL_BUFFERED:
		if (buf == NULL)
		{
			if (f->buff != NULL && (size == f->buff_size || size == 0))
				break;

			ft_fflush(f);
			free(f->buff);
			new_size = size == 0 ? _ft_bufsiz : size;
			if (UNLIKELY((new = malloc(sizeof(U8) * new_size)) == NULL))
				FT_RET_ERR(FALSE, FT_EOMEM);
			f->buff = new;
			f->buff_size = new_size;
		}
		else
		{
			if (size == 0)
				FT_RET_ERR(FALSE, FT_EINVVAL);
			ft_fflush(f);
			free(f->buff);
			f->buff = buf;
			f->buff_size = size;
		}

		ft_bzero(f->buff, f->buff_size);
		break;
	}

	if (bufmode > 0)
		f->buffering_mode = bufmode;
	FT_RET_OK(TRUE);
}
