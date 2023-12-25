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
#ifdef FT_FILE_IO
# include <unistd.h>

static S64	read_section(file fd, U64 read_size, string *out)
{
	char	*buffer;
	char	*tmp;
	S64		bytes_read;

	buffer = malloc((read_size + 1) * sizeof(char));
	if (!buffer)
	{
		*out = NULL;
		return 0;
	}
	bytes_read = read(fd, buffer, read_size);
	if (bytes_read < 0)
	{
		free(buffer);
		return (bytes_read);
	}
	buffer[bytes_read] = '\0';
	tmp = *out;
	*out = ft_strjoin(tmp, buffer);
	free(tmp);
	free(buffer);
	return (bytes_read);
}

string	ft_readfile(file fd, U64 read_size)
{
	string	out;
	S64		bytes_read;

	out = ft_strdup(""); if (!out) return NULL;
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read_section(fd, read_size, &out);
		if (!out) return (NULL);
	}
	return (out);
}
#endif