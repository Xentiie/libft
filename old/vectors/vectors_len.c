/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors_len.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 14:34:29 by reclaire          #+#    #+#             */
/*   Updated: 2023/08/15 18:41:11 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

inline int	vlen2i(t_iv2 a)
{
	return (a.x * a.y);
}

inline float	vlen2(t_v2 a)
{
	return (a.x * a.y);
}
