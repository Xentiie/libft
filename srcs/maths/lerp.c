/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lerp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 22:29:36 by reclaire          #+#    #+#             */
/*   Updated: 2025/03/10 23:51:15 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_int.h"

#include "libft/maths.h"

extern F32 ft_lerp(F32 a, F32 b, F32 t);
extern t_v2 ft_lerp2(t_v2 a, t_v2 b, F32 t);
extern t_v3 ft_lerp3(t_v3 v_1, t_v3 v_2, F32 t);
extern t_v4 ft_lerp4(t_v4 v_1, t_v4 v_2, F32 t);

extern S32 ft_lerp_i(S32 a, S32 b, F32 t);
extern t_iv2 ft_lerp2_i(t_iv2 a, t_iv2 b, F32 t);
extern t_iv3 ft_lerp3_i(t_iv3 v_1, t_iv3 v_2, F32 t);
extern t_iv4 ft_lerp4_i(t_iv4 v_1, t_iv4 v_2, F32 t);

extern F32 ft_invlerp(F32 a, F32 b, F32 t);
extern t_v2 ft_invlerp2(t_v2 a, t_v2 b, t_v2 t);
extern t_v3 ft_invlerp3(t_v3 v_1, t_v3 v_2, t_v3 t);
extern t_v4 ft_invlerp4(t_v4 v_1, t_v4 v_2, t_v4 t);

extern F32 ft_invlerp_i(S32 a, S32 b, S32 t);
extern t_v2 ft_invlerp2_i(t_iv2 a, t_iv2 b, t_iv2 t);
extern t_v3 ft_invlerp3_i(t_iv3 v_1, t_iv3 v_2, t_iv3 t);
extern t_v4 ft_invlerp4_i(t_iv4 v_1, t_iv4 v_2, t_iv4 t);
