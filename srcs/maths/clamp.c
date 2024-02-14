/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clamp.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 22:37:50 by reclaire          #+#    #+#             */
/*   Updated: 2024/02/11 20:51:27 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_int.h"

F32	ft_clampf(F32 min, F32 max, F32 v)
{
	if (v > max)
		return (max);
	if (v < min)
		return (min);
	return (v);
}

S32	ft_clamp(S32 min, S32 max, S32 v)
{
	if (v > max)
		return (max);
	if (v < min)
		return (min);
	return (v);
}
