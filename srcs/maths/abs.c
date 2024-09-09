/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   abs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 00:16:09 by reclaire          #+#    #+#             */
/*   Updated: 2024/02/11 20:50:48 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_int.h"
#include <math.h>

S32 ft_abs(S32 n) { return abs(n); }
F32 ft_fabs(F32 n) { return fabs(n); }
v2f ft_abs2(v2f n) { return (v2f){fabs(n[0]), fabs(n[1])}; }
v3f ft_abs3(v3f n) { return (v3f){fabs(n[0]), fabs(n[1]), fabs(n[2])}; }
v4f ft_abs4(v4f n) { return (v3f){fabs(n[0]), fabs(n[1]), fabs(n[2]), fabs(n[3])}; }
v2i ft_iabs2(v2i n) { return (v2i){abs(n[0]), abs(n[1])}; }
v3i ft_iabs3(v3i n) { return (v3i){abs(n[0]), abs(n[1]), abs(n[2])}; }
v4i ft_iabs4(v4i n) { return (v4i){abs(n[0]), abs(n[1]), abs(n[2]), abs(n[3])}; }
