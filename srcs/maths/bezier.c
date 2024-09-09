/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bezier.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 23:24:53 by reclaire          #+#    #+#             */
/*   Updated: 2024/06/09 23:26:07 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_int.h"

v2f ft_bezier_interp(v2f p1, v2f p2, v2f p3, F32 t)
{
	v2f tmpa = ft_lerp2(p1, p2, t);
	v2f tmpb = ft_lerp2(p2, p3, t);
	return ft_lerp2(tmpa, tmpb, t);
}
