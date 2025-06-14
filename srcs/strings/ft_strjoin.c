/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 15:42:29 by reclaire          #+#    #+#             */
/*   Updated: 2025/06/08 02:14:34 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_int.h"
#include "libft/strings.h"

#include <stdlib.h>

string	ft_strjoin(const_string s1, const_string s2)
{
	string	str;

	str = ftalloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (str == NULL)
		FT_RET_ERR(NULL, FT_EOMEM);
	str[0] = '\0';
	ft_strcat(str, s1);
	ft_strcat(str, s2);

	FT_RET_OK(str);
}
