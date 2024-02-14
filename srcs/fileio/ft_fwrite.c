/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fwrite.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 13:40:56 by reclaire          #+#    #+#             */
/*   Updated: 2024/02/11 20:29:46 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_int.h"

# if defined(FT_WIN32)
#  include <windows.h>

U64	ft_fwrite(file fd, char *buffer, U64 size)
{
	U64 bytes_read = 0;
	if (WriteFile(fd, buffer, size, (LPDWORD)&bytes_read, NULL) == FALSE)
		__FTRETURN_ERR(-1, FT_ESYSCALL);

	__FTRETURN_OK(bytes_read);
}

# elif defined(FT_LINUX) || defined(FT_OSX)
#  include <unistd.h>

U64 ft_fwrite(file fd, char *buffer, U64 size)
{
	U64 bytes_read = write(fd, buffer, size);
	if (bytes_read == -1)
	{
		__FTRETURN_ERR(-1, FT_ESYSCALL);
	}

	__FTRETURN_OK(bytes_read);
}

# endif
