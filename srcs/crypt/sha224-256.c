/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha224-256.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 02:27:41 by reclaire          #+#    #+#             */
/*   Updated: 2024/11/19 03:33:45 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_int.h"
#include "libft/crypt/sha.h"

#define ROTATE_LEFT(x, n) (((x) << (n)) | ((x) >> (32 - (n))))
#define ROTATE_RIGHT(x, n) (((x) >> (n)) | ((x) << (32 - (n))))

#define SHA_Ch(x, y, z) (((x) & ((y) ^ (z))) ^ (z))
#define SHA_Maj(x, y, z) (((x) & ((y) | (z))) | ((y) & (z)))
#define SHA256_SIGMA0(word) (ROTATE_RIGHT(word, 2) ^ ROTATE_RIGHT(word, 13) ^ ROTATE_RIGHT(word, 22))
#define SHA256_SIGMA1(word) (ROTATE_RIGHT(word, 6) ^ ROTATE_RIGHT(word, 11) ^ ROTATE_RIGHT(word, 25))
#define SHA256_sigma0(word) (ROTATE_RIGHT(word, 7) ^ ROTATE_RIGHT(word, 18) ^ (word >> 3))
#define SHA256_sigma1(word) (ROTATE_RIGHT(word, 17) ^ ROTATE_RIGHT(word, 19) ^ (word >> 10))

static void sha256_transform(U32 state[8], const U8 block[64]);

void ft_sha256_init(struct s_sha256_state *state)
{
	state->len = 0;
	state->state[0] = 0x6a09e667;
	state->state[1] = 0xbb67ae85;
	state->state[2] = 0x3c6ef372;
	state->state[3] = 0xa54ff53a;
	state->state[4] = 0x510e527f;
	state->state[5] = 0x9b05688c;
	state->state[6] = 0x1f83d9ab;
	state->state[7] = 0x5be0cd19;
}

void ft_sha224_init(struct s_sha256_state *state)
{
	state->len = 0;
	state->state[0] = 0xc1059ed8;
	state->state[1] = 0x367cd507;
	state->state[2] = 0x3070dd17;
	state->state[3] = 0xf70e5939;
	state->state[4] = 0xffc00b31;
	state->state[5] = 0x68581511;
	state->state[6] = 0x64f98fa7;
	state->state[7] = 0xbefa4fa4;
}

void ft_sha256_update(struct s_sha256_state *state, const void *input, U64 len)
{
	U8 *_input;
	U32 i;
	U32 index;
	U32 part_len;

	_input = (U8 *)input;
	index = (U32)((state->len >> 3) & 0x3F);
	state->len += ((U64)len << 3);

	part_len = 64 - index;

	if (len >= part_len)
	{
		ft_memcpy(&state->buffer[index], _input, part_len);
		sha256_transform(state->state, state->buffer);

		for (i = part_len; i + 63 < len; i += 64)
			sha256_transform(state->state, &_input[i]);
		index = 0;
	}
	else
		i = 0;

	ft_memcpy(&state->buffer[index], &_input[i], len - i);
}

void ft_sha224_update(struct s_sha256_state *state, const void *input, U64 len) __attribute__ ((alias ("ft_sha256_update")));

void ft_sha256_final2(struct s_sha256_state *state, U8 digest[32])
{
	static const U8 _padding[64] = {
		0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	U8 bits[8];
	U32 index;
	U32 pad_len;

	bits[0] = (U8)(state->len >> 56);
	bits[1] = (U8)(state->len >> 48);
	bits[2] = (U8)(state->len >> 40);
	bits[3] = (U8)(state->len >> 32);
	bits[4] = (U8)(state->len >> 24);
	bits[5] = (U8)(state->len >> 16);
	bits[6] = (U8)(state->len >> 8);
	bits[7] = (U8)(state->len);

	index = (U32)((state->len >> 3) & 0x3f);
	pad_len = (index < 56) ? (56 - index) : (120 - index);
	ft_sha256_update(state, _padding, pad_len);

	ft_sha256_update(state, bits, 8);

	for (int i = 0; i < 32; ++i)
		digest[i] = (U8)(state->state[i >> 2] >> (8 * (3 - (i & 0x03))));

	ft_bzero(state, sizeof(struct s_sha256_state));
}

void ft_sha256_final(struct s_sha256_state *state, U8 digest[32])
{
	U32 index;
	U64 *msg64;

	index = (U32)((state->len >> 3) & 0x3F);
	msg64 = (U64 *)state->buffer;
	state->buffer[index++] = 0x80;
	if (index > 32)
	{
		while (index < 64)
			state->buffer[index++] = 0;
		sha256_transform(state->state, (U8 *)msg64);
		index = 0;
	}
	while (index < 56)
		state->buffer[index++] = 0;
	msg64[7] = __builtin_bswap64(state->len);
	sha256_transform(state->state, (U8 *)msg64);

	for (U8 i = 0; i < 32; ++i)
		digest[i] = (U8)(state->state[i >> 2] >> (8 * (3 - (i & 0x03))));

	ft_bzero(state, sizeof(struct s_sha256_state));
}

void ft_sha224_final(struct s_sha256_state *state, U8 digest[28])
{
	static const U8 _padding[64] = {
		0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	U8 bits[8];
	U32 index;
	U32 pad_len;

	bits[0] = (U8)(state->len >> 56);
	bits[1] = (U8)(state->len >> 48);
	bits[2] = (U8)(state->len >> 40);
	bits[3] = (U8)(state->len >> 32);
	bits[4] = (U8)(state->len >> 24);
	bits[5] = (U8)(state->len >> 16);
	bits[6] = (U8)(state->len >> 8);
	bits[7] = (U8)(state->len);

	index = (U32)((state->len >> 3) & 0x3f);
	pad_len = (index < 56) ? (56 - index) : (120 - index);
	ft_sha256_update(state, _padding, pad_len);

	ft_sha256_update(state, bits, 8);

	for (int i = 0; i < 28; ++i)
		digest[i] = (U8)(state->state[i >> 2] >> (8 * (3 - (i & 0x03))));

	ft_bzero(state, sizeof(struct s_sha256_state));
}

static void sha256_transform(U32 state[8], const U8 block[64])
{
	static const U32 K[64] = {
		0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b,
		0x59f111f1, 0x923f82a4, 0xab1c5ed5, 0xd807aa98, 0x12835b01,
		0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7,
		0xc19bf174, 0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
		0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da, 0x983e5152,
		0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147,
		0x06ca6351, 0x14292967, 0x27b70a85, 0x2e1b2138, 0x4d2c6dfc,
		0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
		0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819,
		0xd6990624, 0xf40e3585, 0x106aa070, 0x19a4c116, 0x1e376c08,
		0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f,
		0x682e6ff3, 0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
		0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2};
	int t, t4;
	U32 tmp1, tmp2;
	U32 W[64];
	U32 A, B, C, D, E, F, G, H;

	for (t = t4 = 0; t < 16; t++, t4 += 4)
		W[t] = (((U32)block[t4]) << 24) |
			   (((U32)block[t4 + 1]) << 16) |
			   (((U32)block[t4 + 2]) << 8) |
			   (((U32)block[t4 + 3]));

	for (t = 16; t < 64; t++)
		W[t] = SHA256_sigma1(W[t - 2]) + W[t - 7] +
			   SHA256_sigma0(W[t - 15]) + W[t - 16];

	A = state[0];
	B = state[1];
	C = state[2];
	D = state[3];
	E = state[4];
	F = state[5];
	G = state[6];
	H = state[7];

	for (t = 0; t < 64; t++)
	{
		tmp1 = H + SHA256_SIGMA1(E) + SHA_Ch(E, F, G) + K[t] + W[t];
		tmp2 = SHA256_SIGMA0(A) + SHA_Maj(A, B, C);
		H = G;
		G = F;
		F = E;
		E = D + tmp1;
		D = C;
		C = B;
		B = A;
		A = tmp1 + tmp2;
	}

	state[0] += A;
	state[1] += B;
	state[2] += C;
	state[3] += D;
	state[4] += E;
	state[5] += F;
	state[6] += G;
	state[7] += H;
}
