/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 15:54:03 by reclaire          #+#    #+#             */
/*   Updated: 2025/01/23 04:22:51 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_int.h"
#include "libft/maths.h"

#include <math.h>

S32	ft_wrap(S32 n, S32 min, S32 max)
{
	S32	range;

	range = max - min + 1;
	n = ((n - min) % range);
	if (n < 0)
		return (max + 1 + n);
	else
		return (min + n);
}

F64	ft_fwrap(F64 x, F64 min, F64 max)
{
	F64	f;

	if (x >= 0)
		f = min;
	else
		f = max;
	return (f + fmod(x, max - min));
}
