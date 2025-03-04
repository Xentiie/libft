/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 09:02:03 by reclaire          #+#    #+#             */
/*   Updated: 2024/11/20 10:52:42 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_int.h"
#include "libft/crypt/sha.h"

#ifdef TEST
#include "libft/io.h"
#include "libft/limits.h"
#include <openssl/sha.h>
#endif

#define ROTATE_LEFT(x, n) (((x) << (n)) | ((x) >> (32 - (n))))

#define SHA_Ch(x, y, z) (((x) & ((y) ^ (z))) ^ (z))
#define SHA_Maj(x, y, z) (((x) & ((y) | (z))) | ((y) & (z)))
#define SHA_Parity(x, y, z) ((x) ^ (y) ^ (z))

static void sha1_transform(U32 state[5], const U8 block[64]);

void ft_sha1_init(struct s_sha1_state *state)
{
	state->len = 0;
	state->state[0] = 0x67452301;
	state->state[1] = 0xefcdab89;
	state->state[2] = 0x98badcfe;
	state->state[3] = 0x10325476;
	state->state[4] = 0xc3d2e1f0;
}

void ft_sha1_update(struct s_sha1_state *state, const void *input, U64 len)
{
	U8 *_input;
	U32 i;
	U32 index;
	U32 part_len;

	_input = (U8 *)input;
	index = (U32)((state->len / 8) % 64);
	state->len += ((U64)len * 8);

	part_len = 64 - index;

	if (len >= part_len)
	{
		ft_memcpy(&state->buffer[index], _input, part_len);
		sha1_transform(state->state, state->buffer);

		for (i = part_len; i + 63 < len; i += 64)
			sha1_transform(state->state, &_input[i]);
		index = 0;
	}
	else
		i = 0;

	ft_memcpy(&state->buffer[index], &_input[i], len - i);
}

void ft_sha1_final(struct s_sha1_state *state, U8 digest[20])
{
	static const U8 _padding[64] = {0x80, [1 ... 63] = 0};

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

	index = (U32)((state->len / 8) % 64);
	pad_len = (index < 56) ? (56 - index) : (120 - index);
	ft_sha1_update(state, _padding, pad_len);

	ft_sha1_update(state, bits, 8);

	for (int i = 0; i < 20; ++i)
		digest[i] = (U8)(state->state[i >> 2] >> (8 * (3 - (i & 0x03))));

	ft_bzero(state, sizeof(struct s_sha1_state));
}

static void sha1_transform(U32 state[5], const U8 block[64])
{
	const U32 K[4] = {0x5a827999, 0x6ed9eba1, 0x8f1bbcdc, 0xca62c1d6};
	S32 t;
	U32 tmp;
	U32 W[80];
	U32 A, B, C, D, E;

	for (t = 0; t < 16; t++)
	{
		W[t] = ((U32)block[t * 4]) << 24;
		W[t] |= ((U32)block[t * 4 + 1]) << 16;
		W[t] |= ((U32)block[t * 4 + 2]) << 8;
		W[t] |= ((U32)block[t * 4 + 3]);
	}

	for (t = 16; t < 80; t++)
		W[t] = ROTATE_LEFT(W[t - 3] ^ W[t - 8] ^ W[t - 14] ^ W[t - 16], 1);

	A = state[0];
	B = state[1];
	C = state[2];
	D = state[3];
	E = state[4];

	for (t = 0; t < 20; t++)
	{
		tmp = ROTATE_LEFT(A, 5) + SHA_Ch(B, C, D) + E + W[t] + K[0];
		E = D;
		D = C;
		C = ROTATE_LEFT(B, 30);
		B = A;
		A = tmp;
	}

	for (t = 20; t < 40; t++)
	{
		tmp = ROTATE_LEFT(A, 5) + SHA_Parity(B, C, D) + E + W[t] + K[1];
		E = D;
		D = C;
		C = ROTATE_LEFT(B, 30);
		B = A;
		A = tmp;
	}

	for (t = 40; t < 60; t++)
	{
		tmp = ROTATE_LEFT(A, 5) + SHA_Maj(B, C, D) + E + W[t] + K[2];
		E = D;
		D = C;
		C = ROTATE_LEFT(B, 30);
		B = A;
		A = tmp;
	}

	for (t = 60; t < 80; t++)
	{
		tmp = ROTATE_LEFT(A, 5) + SHA_Parity(B, C, D) + E + W[t] + K[3];
		E = D;
		D = C;
		C = ROTATE_LEFT(B, 30);
		B = A;
		A = tmp;
	}

	state[0] += A;
	state[1] += B;
	state[2] += C;
	state[3] += D;
	state[4] += E;
}

#ifdef TEST

#define TEST_OK()                         \
	do                                    \
	{                                     \
		ft_printf("[%03d] OK\n", test++); \
	} while (0)
#define TEST_FAIL()                                    \
	do                                                 \
	{                                                  \
		ft_printf("[%03d] FAIL\n\tft:   ", test++);    \
		for (U8 _i = 0; _i < sizeof(digests[0]); _i++) \
			ft_printf("%x ", digests[0][_i]);          \
		ft_printf("\n\tossl: ");                       \
		for (U8 _i = 0; _i < sizeof(digests[0]); _i++) \
			ft_printf("%x ", digests[1][_i]);          \
		ft_printf("\n");                               \
	} while (0)
#define DO_TEST()                                                  \
	do                                                             \
	{                                                              \
		if (ft_memcmp(digests[0], digests[1], sizeof(digests[0]))) \
			TEST_FAIL();                                           \
		else                                                       \
			TEST_OK();                                             \
	} while (0)

S32 main()
{
#define BUFSIZE 8192
#define DIGEST_SIZE 20

	const U64 max = U64_MAX;
	U8 buf[BUFSIZE] = {[0 ... BUFSIZE - 1] = 'a'};
	U8 digests[2][DIGEST_SIZE];
	U8 test = 1;

	SHA_CTX ctx;
	struct s_sha1_state state;

	{
		SHA1_Init(&ctx);
		SHA1_Update(&ctx, buf, sizeof(buf));
		SHA1_Final(digests[0], &ctx);

		ft_sha1_init(&state);
		ft_sha1_update(&state, buf, sizeof(buf));
		ft_sha1_final(&state, digests[1]);

		DO_TEST();
	}

	for (U8 j = 0; j < 16; j++)
	{
		SHA1_Init(&ctx);
		for (int i = 0; i < j; i++)
			SHA1_Update(&ctx, buf, sizeof(buf));
		SHA1_Final(digests[0], &ctx);

		ft_sha1_init(&state);
		for (int i = 0; i < j; i++)
			ft_sha1_update(&state, buf, sizeof(buf));
		ft_sha1_final(&state, digests[1]);

		DO_TEST();
	}
}

#endif
