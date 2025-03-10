/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trigo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 05:05:05 by reclaire          #+#    #+#             */
/*   Updated: 2025/03/10 23:49:45 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_int.h"

#include "libft/maths.h"

extern t_v2 ft_sin2(t_v2 v);
extern t_v3 ft_sin3(t_v3 v);
extern t_v4 ft_sin4(t_v4 v);
extern t_iv2 ft_isin2(t_iv2 v);
extern t_iv3 ft_isin3(t_iv3 v);
extern t_iv4 ft_isin4(t_iv4 v);

extern t_v2 ft_cos2(t_v2 v);
extern t_v3 ft_cos3(t_v3 v);
extern t_v4 ft_cos4(t_v4 v);
extern t_iv2 ft_icos2(t_iv2 v);
extern t_iv3 ft_icos3(t_iv3 v);
extern t_iv4 ft_icos4(t_iv4 v);

extern F32 ft_degrees(F32 radians);
extern t_v2 ft_degrees2(t_v2 radians);
extern t_v3 ft_degrees3(t_v3 radians);
extern t_v4 ft_degrees4(t_v4 radians);
extern t_iv2 ft_idegrees2(t_iv2 radians);
extern t_iv3 ft_idegrees3(t_iv3 radians);
extern t_iv4 ft_idegrees4(t_iv4 radians);

extern F32 ft_radians(F32 degrees);
extern t_v2 ft_radians2(t_v2 degrees);
extern t_v3 ft_radians3(t_v3 degrees);
extern t_v4 ft_radians4(t_v4 degrees);
extern t_iv2 ft_iradians2(t_iv2 degrees);
extern t_iv3 ft_iradians3(t_iv3 degrees);
extern t_iv4 ft_iradians4(t_iv4 degrees);
