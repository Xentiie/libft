/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 22:56:32 by reclaire          #+#    #+#             */
/*   Updated: 2024/11/18 00:24:16 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(FT_MD5_H)
#define FT_MD5_H

#include "../_libft.h"

struct s_md5_state
{
	U32 state[4];
	U64 len;
	U8 buffer[64];
};

void ft_md5_init(struct s_md5_state *state);
void ft_md5_update(struct s_md5_state *state, const void *input, U64 len);
void ft_md5_final(struct s_md5_state *state, U8 digest[16]);

#endif