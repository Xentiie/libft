/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 16:55:27 by reclaire          #+#    #+#             */
/*   Updated: 2024/02/11 20:48:59 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft_int.h"

S32	handle_c(U8 c);
S32	handle_d(S32 i);
S32	handle_i(S32 i);
S32	handle_p(U64 p);
S32	handle_s(string str);
S32	handle_u(U64 i);
S32	handle_ux(U64 i);
S32	handle_x(U64 i);
S32	handle_vec2i(t_iv2 c);
S32	handle_vec3i(t_iv3 c);
S32	handle_vec4i(t_iv4 c);
S32	handle_vec2(t_v2 c);
S32	handle_vec3(t_v3 c);
S32	handle_vec4(t_v4 c);
#endif