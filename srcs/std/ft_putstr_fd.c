/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 14:24:08 by reclaire          #+#    #+#             */
/*   Updated: 2023/09/26 22:20:13 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#ifdef FT_STD
# include <unistd.h>
void	ft_putstr_fd(string s, int fd)
{
	if (s == NULL)
		return ;
	while (*s != '\0')
		(void)!write(fd, s++, 1);
}
#endif