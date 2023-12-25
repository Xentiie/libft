/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 13:41:08 by reclaire          #+#    #+#             */
/*   Updated: 2023/09/26 21:53:35 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#ifdef FT_STD
bool	ft_isprint(U8 c)
{
	if (c >= 32 && c <= 126)
		return (TRUE);
	return (FALSE);
}
#endif