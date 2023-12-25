/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isrange.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 17:11:10 by reclaire          #+#    #+#             */
/*   Updated: 2023/09/26 22:11:07 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#ifdef FT_MATHS
int	ft_isrange(int i, int min, int max)
{
	if (i >= min && i <= max)
		return (1);
	return (0);
}
#endif