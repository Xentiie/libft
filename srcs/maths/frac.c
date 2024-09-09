/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frac.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 03:48:22 by reclaire          #+#    #+#             */
/*   Updated: 2024/09/08 03:48:22 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_int.h"

inline F32	ft_frac(F32 v)
{
	return (v - ((long)v));
}

inline v2f	ft_frac2(v2f v)
{
	return (v2f){ft_frac(v[0]), ft_frac(v[1])};
}

inline v3f	ft_frac3(v3f v)
{
	return (v3f){ft_frac(v[0]), ft_frac(v[1]), ft_frac(v[2])};
}

inline v4f	ft_frac4(v4f v)
{
	return (v4f){ft_frac(v[0]), ft_frac(v[1]), ft_frac(v[2]), ft_frac(v[3])};
}
