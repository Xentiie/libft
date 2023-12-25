/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 14:22:48 by reclaire          #+#    #+#             */
/*   Updated: 2023/09/26 21:52:41 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#ifdef FT_STD
# include <unistd.h>
void	ft_putchar_fd(U8 c, int fd)
{
	(void)!write(fd, &c, 1);
}
#endif