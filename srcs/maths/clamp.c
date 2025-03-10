/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clamp.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 22:37:50 by reclaire          #+#    #+#             */
/*   Updated: 2025/03/10 23:48:49 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_int.h"

#include "libft/maths.h"

extern F32 ft_fmin(F32 a, F32 b);
extern S32 ft_min(S32 a, S32 b);
extern F32 ft_fmax(F32 a, F32 b);
extern S32 ft_max(S32 a, S32 b);

extern F32 ft_ceil(F32 n);
extern t_v2 ft_ceil2(t_v2 n);
extern t_v3 ft_ceil3(t_v3 n);
extern t_v4 ft_ceil4(t_v4 n);

extern F32 ft_floor(F32 n);
extern t_v2 ft_floor2(t_v2 n);
extern t_v3 ft_floor3(t_v3 n);
extern t_v4 ft_floor4(t_v4 n);

extern F32 ft_clampf(F32 min, F32 max, F32 v);
extern S32 ft_clamp(S32 min, S32 max, S32 v);
