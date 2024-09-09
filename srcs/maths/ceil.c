/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ceil.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 03:48:47 by reclaire          #+#    #+#             */
/*   Updated: 2024/09/08 03:48:47 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_int.h"
#include <math.h>

F32 ft_ceil(F32 n) { return ceil(n); }

v2f ft_ceil2(v2f n) { return (v2f){ceil(n[0]), ceil(n[1])}; }
v3f ft_ceil3(v3f n) { return (v3f){ceil(n[0]), ceil(n[1]), ceil(n[2])}; }
v4f ft_ceil4(v4f n) { return (v4f){ceil(n[0]), ceil(n[1]), ceil(n[2]), ceil(n[3])}; }
