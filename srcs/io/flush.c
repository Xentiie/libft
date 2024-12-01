/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flush.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 11:48:16 by reclaire          #+#    #+#             */
/*   Updated: 2024/11/27 15:15:58 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file_private.h"

void ft_fflush(t_file *file)
{
	S64 ret;

	if (file->buff_cnt == 0 || file->buff == NULL)
		return;

	if ((ret = ft_write(file->fd, (char *)file->buff, file->buff_cnt)) < (S64)file->buff_cnt)
	{
		ft_errno = FT_EINVPTR;
		return;
	}
	file->buff_cnt = 0;
}
