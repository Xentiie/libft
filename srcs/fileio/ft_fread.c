/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fread.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 20:19:41 by reclaire          #+#    #+#             */
/*   Updated: 2024/02/26 23:11:52 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_int.h"

# if defined(FT_WIN)
#  include <windows.h>

U64	ft_fread(file fd, char *buffer, U64 size)
{
	U64 bytes_read = 0;
	if (ReadFile(fd, buffer, size, (LPDWORD)&bytes_read, NULL) == FALSE)
		__FTRETURN_ERR(-1, FT_ESYSCALL);

	__FTRETURN_OK(bytes_read);
}

# elif defined(FT_LINUX) || defined(FT_MAX)
#  include <unistd.h>

U64 ft_fread(file fd, char *buffer, U64 size)
{
	U64 bytes_read = read(fd, buffer, size);
	if (bytes_read == -1)
	{
		__FTRETURN_ERR(-1, FT_ESYSCALL);
	}

	__FTRETURN_OK(bytes_read);
}

# endif

