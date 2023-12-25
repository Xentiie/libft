/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 14:25:16 by reclaire          #+#    #+#             */
/*   Updated: 2023/09/26 22:20:20 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#ifdef FT_STD
# include <unistd.h>
void	ft_putendl_fd(string s, int fd)
{
	ft_putstr_fd(s, fd);
	(void)!write(fd, "\n", 1);
}
#endif