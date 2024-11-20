/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 00:22:59 by reclaire          #+#    #+#             */
/*   Updated: 2024/11/20 11:06:09 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(FT_SHA_H)
#define FT_SHA_H

#include "../libft.h"

struct s_sha1_state
{
	U32 state[5];
	U64 len;
	U8 buffer[64];
};

struct s_sha256_state
{
	U32 state[8];
	U64 len;
	U8 buffer[64];
};

extern void ft_sha1_init(struct s_sha1_state *state);
extern void ft_sha1_update(struct s_sha1_state *state, const void *input, U64 len);
extern void ft_sha1_final(struct s_sha1_state *state, U8 digest[20]);

extern void ft_sha224_init(struct s_sha256_state *state);
extern void ft_sha224_update(struct s_sha256_state *state, const void *input, U64 len);
extern void ft_sha224_final(struct s_sha256_state *state, U8 digest[28]);

extern void ft_sha256_init(struct s_sha256_state *state);
extern void ft_sha256_update(struct s_sha256_state *state, const void *input, U64 len);
extern void ft_sha256_final(struct s_sha256_state *state, U8 digest[32]);

#endif
