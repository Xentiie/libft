/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gnl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 18:25:42 by reclaire          #+#    #+#             */
/*   Updated: 2023/09/26 20:47:55 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "ft_gnl.h"
#ifdef FT_FILE_IO

# define BUFFER_SIZE 4096

static t_list	*g_save_list;

static char	*get_line(char *save)
{
	char	*dst;
	int		i;

	i = 0;
	if (save == NULL)
		return (NULL);
	while (save[i] != '\n' && save[i] != '\0')
		i++;
	if (save[0] == '\0')
		return (NULL);
	dst = malloc(sizeof(char) * i + 2);
	i = 0;
	while (save[i] != '\n' && save[i])
	{
		dst[i] = save[i];
		i++;
	}
	if (save[i] == '\n')
		dst[i++] = '\n';
	dst[i] = '\0';
	return (dst);
}

char	*save_remaining(char	*save)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (save == NULL)
		return (NULL);
	while (save[i] != '\n' && save[i] != '\0')
		i++;
	if (save[i] == '\0')
	{
		free (save);
		return (NULL);
	}
	tmp = malloc(sizeof(char) * (ft_strlen(save) - i));
	i++;
	while (save[i] != '\0')
		tmp[j++] = save[i++];
	tmp[j] = '\0';
	free(save);
	return (tmp);
}

static int	gnl_read(char *buffer, t_list *current, t_list **save_list, int fd)
{
	int		read_result;
	char	*tmp;

	if (!buffer)
		return (-2);
	read_result = read(fd, buffer, BUFFER_SIZE);
	if (read_result == -1 || !((t_save *)(current->content))->save)
	{
		free(buffer);
		gnl_lstfree(save_list, fd);
		return (-2);
	}
	buffer[read_result] = '\0';
	tmp = ((t_save *)(current->content))->save;
	((t_save *)(current->content))->save = ft_strjoin(tmp, buffer);
	free(tmp);
	free(buffer);
	return (read_result);
}

t_list	*ft_gnl_save(void)
{
	return (g_save_list);
}

string	ft_gnl(int fd)
{
	t_list			*current;
	char			*buffer;
	char			*tmp;
	int				read_result;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	current = get_save(&g_save_list, fd);
	read_result = 1;
	while (read_result != 0)
	{
		buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
		read_result = gnl_read(buffer, current, &g_save_list, fd);
		if (read_result == -2)
			return (NULL);
		if (ft_strchr(((t_save *)(current->content))->save, (int) '\n'))
			break ;
	}
	tmp = get_line(((t_save *)(current->content))->save);
	save_remaining2(current);
	if (!tmp)
		gnl_lstfree(&g_save_list, fd);
	return (tmp);
}
#endif