/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clamp.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 22:37:50 by reclaire          #+#    #+#             */
/*   Updated: 2025/01/23 04:23:43 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_int.h"
#include "libft/maths.h"

F64	ft_clampf(F64 min, F64 max, F64 v)
{
	return ft_fmax(min, ft_fmin(max, v));
}

S32	ft_clamp(S32 min, S32 max, S32 v)
{
	return ft_imax(min, ft_imin(max, v));
}
