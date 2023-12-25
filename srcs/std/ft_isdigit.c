/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 13:41:08 by reclaire          #+#    #+#             */
/*   Updated: 2023/09/26 21:53:30 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#ifdef FT_STD
bool	ft_isdigit(U8 c)
{
	if (c >= '0' && c <= '9')
		return (TRUE);
	return (FALSE);
}
#endif