/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inflate.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 11:07:21 by reclaire          #+#    #+#             */
/*   Updated: 2024/06/27 14:49:47 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/std.h"
#include "libft/compression/deflate.h"
#include "libft/maths.h"
#include "libft/ansi.h"
#include "fixed_codes.h"
#include <stdlib.h>

#ifdef DEBUG
#include <stdio.h>
#define IFDEBUG(...) \
	do               \
	{                \
		__VA_ARGS__; \
	} while (0);
#else
#define IFDEBUG(...)
#endif

// clang-format off
enum e_inf_state {
	INV = -1,
	BLK_HEAD,
		RD_UNCOMPRESS,
			UNCOMPRESS_CPY,

		RD_CODE,

		LIT,

		RD_EXTRA_LEN,
		RD_DIST,
		RD_EXTRA_DIST,

		CPY_BACKREF
};
// clang-format on

/* Load registers with state in inflate() for speed */
#define LOAD()                                             \
	do                                                     \
	{                                                      \
		if (UNLIKELY(stream->in_used > stream->in_size))   \
			return FT_INFLATE_RET_INVALID_IN_SIZE;         \
		if (UNLIKELY(stream->out_used > stream->out_used)) \
			return FT_INFLATE_RET_INVALID_OUT_SIZE;        \
		have = stream->in_size - stream->in_used;          \
		left = stream->out_size - stream->out_used;        \
		next = stream->in + stream->in_used;               \
		hold = inf_data->hold;                             \
		bits = stream->bits;                               \
		code = inf_data->code;             \
	} while (0)

/* Restore stream from registers in inflate() */
#define RESTORE()                                                         \
	do                                                                    \
	{                                                                     \
		stream->in_used += (stream->in_size - stream->in_used) - have;    \
		stream->out_used += (stream->out_size - stream->out_used) - left; \
		inf_data->hold = hold;                                            \
		stream->bits = bits;                                              \
		inf_data->code = code;                            \
	} while (0)

/* Clear the input bit accumulator */
#define INITBITS() \
	do             \
	{              \
		hold = 0;  \
		bits = 0;  \
	} while (0)

/* Get a byte of input into the bit accumulator, or return from inflate()
   if there is no input available. */
#define PULLBYTE()                                \
	do                                            \
	{                                             \
		if (have == 0)                            \
			goto inflate_leave;                   \
		have--;                                   \
		hold += (unsigned long)(*next++) << bits; \
		bits += 8;                                \
	} while (0)

/* Assure that there are at least n bits in the bit accumulator.  If there is
   not enough available input to do that, then return from inflate(). */
#define NEEDBITS(n)                  \
	do                               \
	{                                \
		while (bits < (unsigned)(n)) \
			PULLBYTE();              \
	} while (0)

/* Return the low n bits of the bit accumulator (n < 16) */
#define BITS(n) \
	((unsigned)hold & ((1U << (n)) - 1))

/* Remove n bits from the bit accumulator */
#define DROPBITS(n)            \
	do                         \
	{                          \
		hold >>= (n);          \
		bits -= (unsigned)(n); \
	} while (0)

/* Remove zero to seven bits as needed to go to a byte boundary */
#define BYTEBITS()         \
	do                     \
	{                      \
		hold >>= bits & 7; \
		bits -= bits & 7;  \
	} while (0)

S32 ft_inflate2(t_deflate_stream *stream)
{
	U64 hold;		// bit accumulator
	U64 have, left; // remaining in, remaining out
	U8 bits;		// bit counter
	U8 *next;
	U16 to_cpy;
	struct s_code code;
	struct s_inflate_data *inf_data = &stream->inflate;

	LOAD();

	if (inf_data->window == NULL)
	{
		inf_data->window = malloc(sizeof(U8) * FT_DEFLATE_WINDOW_SIZE);
		if (UNLIKELY(inf_data->window == NULL))
			return FT_INFLATE_RET_OMEM;
		ft_memset(inf_data->window, 0, sizeof(U8) * FT_DEFLATE_WINDOW_SIZE);
		inf_data->window_size = 0;
		inf_data->win_next = inf_data->window;

		inf_data->hold = 0;
	}

	while (TRUE)
	{
		switch (inf_data->state)
		{
		case BLK_HEAD:
			IFDEBUG(printf("Reading block:\n"))
			NEEDBITS(3);

			inf_data->last = BITS(1);
			IFDEBUG(printf("	last: %s\n", inf_data->last ? "yes" : "no"))

			DROPBITS(1);
			switch (BITS(2))
			{
			case 0:
				IFDEBUG(printf("	block type: uncompressed\n"))
				inf_data->state = RD_UNCOMPRESS;
				break;

			case 1:
				IFDEBUG(printf("	block type: fixed\n"))
				inf_data->ll_codes = (struct s_code *)fixed_ll_codes;
				inf_data->dist_codes = (struct s_code *)fixed_dist_codes;
				inf_data->ll_codes_bits = 9;
				inf_data->dist_codes_bits = 5;
				inf_data->state = RD_CODE;
				break;

			case 2:
				IFDEBUG(printf("	block type: dynamic\n"))
				inf_data->state = 0; // TODO
				break;

			case 3:
				IFDEBUG(printf("	block type: INVALID\n"))
				// TODO
				DROPBITS(2);
				goto inflate_leave;
			}
			DROPBITS(2);
			break;

		case RD_UNCOMPRESS:
			BYTEBITS();
			NEEDBITS(32);

			if ((hold & 0xFFFF) != ((hold >> 16) ^ 0xFFFF))
			{
				// TODO
				IFDEBUG(printf("	invalid size/~size\n"))
				goto inflate_leave;
			}
			inf_data->length = hold & 0xFFFF;
			IFDEBUG(printf("	size: %u\n", inf_data->length))
			inf_data->state = UNCOMPRESS_CPY;
			/* fallthrough */

		case UNCOMPRESS_CPY:;
			to_cpy = inf_data->length;
			if (to_cpy)
			{
				if (to_cpy > have)
					to_cpy = have;
				if (to_cpy > left)
					to_cpy = left;
				if (to_cpy == 0)
					goto inflate_leave;
				IFDEBUG(printf("	copying %u bytes\n", to_cpy))
				ft_memcpy(stream->out + stream->out_used, next, to_cpy);

				have -= to_cpy;
				left -= to_cpy;
				inf_data->length -= to_cpy;

				next += to_cpy;
				stream->out_used += to_cpy;
				inf_data->window_size += to_cpy;
				break;
			}
			inf_data->state = BLK_HEAD;
			break;

		case RD_CODE:
			while (TRUE)
			{
				code = inf_data->ll_codes[BITS(inf_data->ll_codes_bits)];
				if (code.nbits <= bits)
					break;
				PULLBYTE();
			}
			DROPBITS(code.nbits);

			switch (code.op >> 4)
			{
			case 0x80 >> 4:
				// Literal
				inf_data->state = LIT;
				break;
			case 0x40 >> 4:
				// Backref
				IFDEBUG(printf("	Backref:\n		base length: %u\n", code.val))
				inf_data->length = code.val;
				inf_data->state = RD_EXTRA_LEN;
				break;
			case 0x20 >> 4:
				// Code 256
				IFDEBUG(printf("	End of block marker found\n"))
				inf_data->state = BLK_HEAD;
				break;
			default:
				IFDEBUG(printf("	Error: invalid code\n"))
				inf_data->state = INV;
				break;
			}
			break;

		case RD_EXTRA_LEN:
			NEEDBITS(code.op & 0xF);
			IFDEBUG(printf("		extra length: %u\n", BITS(code.op & 0xF)));
			inf_data->length += BITS(code.op & 0xF);
			DROPBITS(code.op & 0xF);
			inf_data->state = RD_DIST;
			/* fallthrough */

		case RD_DIST:

			while (TRUE)
			{
				code = inf_data->dist_codes[BITS(inf_data->dist_codes_bits)];
				if (code.nbits <= bits)
					break;
				PULLBYTE();
			}
			DROPBITS(code.nbits);
			inf_data->dist = code.val;
			IFDEBUG(printf("		base dist: %u\n", inf_data->dist))
			inf_data->state = RD_EXTRA_DIST;
			/* fallthrough */

		case RD_EXTRA_DIST:
			NEEDBITS(code.op & 0xF);
			inf_data->dist += BITS(code.op & 0xF);
			IFDEBUG(printf("		extra dist: %u\n", inf_data->dist))
			DROPBITS(code.op & 0xF);

			IFDEBUG(printf("		FULL: %u:%u\n", inf_data->length, inf_data->dist))
			inf_data->state = CPY_BACKREF;
			/* fallthrough */

		case CPY_BACKREF:
			if (inf_data->dist > inf_data->window_size)
			{
				IFDEBUG(printf("	INVALID BACKREF: too far back\n"))
				inf_data->state = INV;
				break;
			}
			if (inf_data->length == 0)
			{
				inf_data->state = RD_CODE;
				break;
			}
			if (left == 0)
				goto inflate_leave;

			to_cpy = inf_data->length;

			U8 *start_cpy = inf_data->win_next - inf_data->dist;
			if (inf_data->win_next < inf_data->window)
			{
				start_cpy += FT_DEFLATE_WINDOW_SIZE;
				to_cpy = FT_DEFLATE_WINDOW_SIZE - (inf_data->win_next - inf_data->window) - 1;
			}

			if (to_cpy > left)
				to_cpy = left;
			if (to_cpy == 0)
				goto inflate_leave;


			for (U64 i = 0; i < to_cpy; i++)
			{
				*(stream->out + stream->out_used++) = *start_cpy;
				*inf_data->win_next++ = *start_cpy++;
			}

			inf_data->length -= to_cpy;
			left -= to_cpy;
			inf_data->window_size += to_cpy;

			if (inf_data->win_next >= inf_data->window + FT_DEFLATE_WINDOW_SIZE)
				inf_data->win_next = inf_data->window;

			break;

		case LIT:
			if (left == 0)
				goto inflate_leave;

			if (inf_data->win_next - inf_data->window >= FT_DEFLATE_WINDOW_SIZE)
				inf_data->win_next = inf_data->window;

			*inf_data->win_next++ = (U8)code.val;
			inf_data->window_size++;

			*(stream->out + stream->out_used) = (U8)code.val;
			stream->out_used++;
			left--;

			IFDEBUG(
				if (ft_isprint(code.val))
					printf("	lit: %c\n", code.val);
				else printf("	lit: %#x\n", code.val);)
			inf_data->state = RD_CODE;
			break;

		case INV:
			RESTORE();
			return FT_INFLATE_RET_DONE; // TODO: change
		}

		if (inf_data->state == BLK_HEAD && inf_data->last)
		{
			RESTORE();
			return FT_INFLATE_RET_DONE;
		}
	}

inflate_leave:
	RESTORE();
	return FT_INFLATE_RET_NOT_DONE;
}

void ft_inflate_init(t_deflate_stream *stream)
{
	ft_memset(stream, 0, sizeof(t_deflate_stream));
}

void ft_inflate_end(t_deflate_stream *stream)
{
	free(stream->inflate.window);
}
