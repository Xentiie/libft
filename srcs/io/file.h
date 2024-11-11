/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 00:50:06 by reclaire          #+#    #+#             */
/*   Updated: 2024/11/09 23:09:42 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(FILE_H)
#define FILE_H

#define _GNU_SOURCE
#include "libft_int.h"
#include <pthread.h>

#if defined(FT_OS_WIN)
#include <windows.h>
#endif

typedef struct s_file
{
	char *buff;
	U64 buff_size;
	U64 buff_cnt;
	bool buffered;
	filedesc fd;
}	t_file;

/*
cleanup lock in lock ht, called from ft_fclose
*/
bool __ft_flockcleanup(t_file *fp);

#endif
