/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iswhitespace.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 13:41:08 by reclaire          #+#    #+#             */
/*   Updated: 2023/09/26 21:58:49 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#ifdef FT_STD
inline bool	ft_iswhitespace(U8 c)
{
	if (c == ' ' || c == '\t' || c == '\r' || c == '\n' || c == '\v' || c == '\f')
		return (TRUE);
	return (FALSE);
}
#endif