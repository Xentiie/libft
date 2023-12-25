/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gnl3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 06:36:17 by estarck           #+#    #+#             */
/*   Updated: 2023/09/26 20:48:14 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "ft_gnl.h"
#ifdef FT_FILE_IO
#define BUFFER_SIZE 1

t_list	*get_save(t_list **save_list, int fd)
{
	t_list	*current;

	if (!(*save_list))
	{
		(*save_list) = malloc(sizeof(t_list));
		(*save_list)->content = gnl_lstnew(fd);
		(*save_list)->next = NULL;
	}
	current = *save_list;
	while (current)
	{
		if (((t_save *)(current->content))->fd == fd)
			break ;
		current = current->next;
	}
	if (!current)
		current = gnl_addback(save_list, fd);
	return (current);
}
#endif