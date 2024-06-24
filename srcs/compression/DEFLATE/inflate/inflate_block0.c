/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inflate_block0.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 21:08:00 by reclaire          #+#    #+#             */
/*   Updated: 2024/06/17 22:25:37 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inflate_int.h"

bool inflate_block_type0(t_deflate_stream *stream, S32 *err)
{
	U16 size;
	if (LIKELY(stream->bit_offset != 0))
	{
		stream->in_used++;
		stream->bit_offset = 0;
	}

	if (stream->save_state.type0.remaining_size == 0) // no previous block type 0 save state
	{ // Read size and check ~size

		if (CHK_IN_SIZE(4))
			__FTINFLATEERR(FT_INFLATE_E_IN_OMEM);

		size = *(U16 *)(stream->in + stream->in_used);
		
		U16 nsize = *(U16 *)(stream->in + stream->in_used + 2);
		if (UNLIKELY(size != ((~nsize) & 0xffff)))
			__FTINFLATEERR(FT_INFLATE_EINV_BLOCK_SIZE); // ERROR: INVALID SIZE ~SIZE

		IFDEBUG(
			printf("	size: %u\n", size);
			printf("	~size: %u\n", nsize);)
		
		stream->in_used += 4;
	}
	else
	{
		size = stream->save_state.type0.remaining_size;
		IFDEBUG(printf("	Remaining size: %u\n", size);)
	}

	if (UNLIKELY(stream->out_size - stream->out_used < size))
	{
		U64 remaining_buf_size = stream->out_size - stream->out_used;
		IFDEBUG(printf("	/!\\ Not enough space remaining in buffer, copying what's possible: %lub\n", remaining_buf_size);)
		ft_memcpy(stream->out + stream->out_used, stream->in + stream->in_used, remaining_buf_size);
		stream->in_used += remaining_buf_size;
		stream->out_used += remaining_buf_size;

		printf("%u %lu\n", size, remaining_buf_size);
		stream->save_state.type0.remaining_size = size - remaining_buf_size;
		IFDEBUG(printf("	/!\\ State saved\n");)

		__FTINFLATEERR(FT_INFLATE_E_OUT_OMEM); // ERROR: NOT ENOUGH SPACE
	}

	IFDEBUG(printf("	Enough space in buffer, copying everything: %ub\n", size);)
	ft_memcpy(stream->out + stream->out_used, stream->in + stream->in_used, size);
	stream->in_used += size;
	stream->out_used += size;

	return TRUE;
}
