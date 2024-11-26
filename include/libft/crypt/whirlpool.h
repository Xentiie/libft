/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   whirlpool.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 04:00:16 by reclaire          #+#    #+#             */
/*   Updated: 2024/11/19 04:06:02 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(FT_WHIRLPOOL_H)
#define FT_WHIRLPOOL_H

#include "../libft.h"

struct s_whirlpool_state
{
	U64 state[8];
	U64 len;
	U8 buffer[64];
};

extern void ft_whirlpool_init(struct s_whirlpool_state *state);
extern void ft_whirlpool_update(struct s_whirlpool_state *state, const void *input, U64 len);
extern void ft_whirlpool_final(struct s_whirlpool_state *state, U8 digest[64]);

#endif