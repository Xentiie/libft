/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 14:14:52 by reclaire          #+#    #+#             */
/*   Updated: 2023/09/26 21:53:15 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#ifdef FT_STD
bool	ft_isalnum(U8 c)
{
	if ((c >= '0' && c <= '9') || ft_isalpha(c))
		return (TRUE);
	return (FALSE);
}
#endif