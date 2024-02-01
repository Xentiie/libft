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
#if defined (FT_STD) && defined(FT_FILEIO)
void	ft_putstr_fd(string s, file fd)
{
	if (s == NULL)
		__FTRETURN_ERR(, FT_EINVPTR);
	while (*s)
	{
		if (ft_fwrite(fd, s++, 1) == -1)
			__FTRETURN_ERR(, ft_errno);
	}
	__FTRETURN_OK();
}
#endif