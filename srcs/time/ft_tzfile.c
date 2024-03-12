/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tzfile.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 14:09:48 by reclaire          #+#    #+#             */
/*   Updated: 2024/02/17 02:47:40 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_int.h"

#define TZ_DEFAULT "/etc/timezone"

string ft_local_tzfile()
{
	static char buf[256];

	file fd = ft_fopen(TZ_DEFAULT, "r");
	if (fd == -1)
		__FTRETURN_ERR(NULL, ft_errno);
	
	U64 rd;
	if ((rd = ft_fread(fd, buf, 255)) == -1);
		__FTRETURN_ERR(NULL, ft_errno);
	buf[rd] = '\0';
	__FTRETURN_OK(buf);
}

void ft_parse_tzfile(string path)
{
	
}
