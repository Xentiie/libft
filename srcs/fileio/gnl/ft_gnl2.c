/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gnl2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 14:09:38 by reclaire          #+#    #+#             */
/*   Updated: 2023/09/26 20:48:05 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_gnl.h"
#ifdef FT_FILE_IO

void	save_remaining2(t_list *s)
{
	((t_save *)(s->content))->save = save_remaining(
			((t_save *)(s->content))->save);
}

t_list	*gnl_addback(t_list **lst, int fd)
{
	t_list	*current_last;
	t_list	*new;
	t_list	*previous;

	new = malloc(sizeof(t_list));
	new->content = gnl_lstnew(fd);
	new->next = NULL;
	current_last = *lst;
	if (*lst == NULL)
		*lst = new;
	else
	{
		while (current_last != NULL)
		{
			previous = current_last;
			current_last = current_last->next;
		}
		previous->next = new;
	}
	return (new);
}

t_save	*gnl_lstnew(int fd)
{
	t_save	*new;

	new = malloc(sizeof(t_save));
	new->fd = fd;
	new->save = malloc(sizeof(char));
	(new->save)[0] = '\0';
	return (new);
}

void	gnl_lstfree(t_list **first, int fd)
{
	t_list	*current;
	t_list	*previous;

	current = *first;
	previous = NULL;
	while (current)
	{
		if (((t_save *)(current->content))->fd == fd)
			break ;
		previous = current;
		current = current->next;
	}
	if (!previous)
	{
		if (current->next)
			*first = current->next;
		else
			*first = NULL;
	}
	else
		previous->next = current->next;
	free(((t_save *)(current->content))->save);
	free(current->content);
	free(current);
}

char	*ft_gnl_readfile(int fd, int read_size)
{
	char	*buffer;
	char	*out;
	char	*tmp;
	int		bytes_read;

	bytes_read = 1;
	out = malloc(sizeof(char));
	out[0] = '\0';
	while (bytes_read > 0)
	{
		buffer = malloc((read_size + 1) * sizeof(char));
		bytes_read = read(fd, buffer, read_size);
		if (bytes_read == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		tmp = out;
		out = ft_strjoin(tmp, buffer);
		free(tmp);
		free(buffer);
	}
	return (out);
}
#endif