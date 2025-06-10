/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pad.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 01:48:30 by reclaire          #+#    #+#             */
/*   Updated: 2025/06/08 02:14:34 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_int.h"
#include "libft/strings.h"

#include <stdlib.h>

string	ft_lpad(string str, char c, U64 n)
{
	if (str == NULL)
		FT_RET_ERR(NULL, FT_EINVPTR);

	U64 size = ft_strlen(str);
	string out = ftalloc(sizeof(char) * (size + n + 1));
	if (out == NULL)
		FT_RET_ERR(NULL, FT_EOMEM);
	out[size + n] = '\0';

	ft_memset(out, c, n);
	ft_memcpy(out + n, str, size);
	FT_RET_OK(out);
}

string	ft_rpad(string str, char c, U64 n)
{
	if (str == NULL)
		FT_RET_ERR(NULL, FT_EINVPTR);

	U64 size = ft_strlen(str);
	string out = ftalloc(sizeof(char) * (size + n + 1));
	if (out == NULL)
		FT_RET_ERR(NULL, FT_EOMEM);
	out[size + n] = '\0';

	ft_memcpy(out, str, size);
	ft_memset(out + n, c, n);
	FT_RET_OK(out);
}
