/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readfile.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 22:55:52 by reclaire          #+#    #+#             */
/*   Updated: 2023/09/26 22:17:42 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#ifdef FT_FILEIO

static S64	read_section(file fd, U64 read_size, string *out)
{
	char	*buffer;
	char	*tmp;
	S64		bytes_read;

	buffer = malloc((read_size + 1) * sizeof(char));
	if (buffer == NULL)
	{
		*out = NULL;
		__FTRETURN_ERR(-1, FT_EOMEM);
	}

	bytes_read = ft_fread(fd, buffer, read_size);
	if (bytes_read < 0)
	{
		free(buffer);
		__FTRETURN_ERR(-1, ft_errno);
	}
	buffer[bytes_read] = '\0';
	
	tmp = *out;
	*out = ft_strjoin(tmp, buffer);
	free(tmp);
	free(buffer);
	__FTRETURN_OK(bytes_read);
}

string	ft_readfile(file fd, U64 read_size)
{
	string	out;
	S64		bytes_read;

	out = ft_strdup("");
	if (!out)
		__FTRETURN_ERR(NULL, ft_errno);

	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read_section(fd, read_size, &out);
		if (!out)
			__FTRETURN_ERR(NULL, ft_errno);
	}

	__FTRETURN_OK(out);
}
#endif