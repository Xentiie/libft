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
#if defined (FT_STD) && defined(FT_FILEIO)
void	ft_putchar_fd(U8 c, file fd)
{
	if (ft_fwrite(fd, &c, 1) == -1)
		__FTRETURN_ERR(, ft_errno);
	__FTRETURN_OK();
}
#endif