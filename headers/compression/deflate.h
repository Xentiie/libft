/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deflate.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 23:02:08 by reclaire          #+#    #+#             */
/*   Updated: 2024/06/27 14:48:34 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_DEFLATE_H
#define LIBFT_DEFLATE_H

#include "libft/_libft.h"

struct s_code
{
	U8 op;
	U8 nbits;
	U16 val;
};

struct s_inflate_data
{
	U64 hold;

	S8 block_type;
	U8 last;

	U8 *window;
	U8 *win_next;
	U64 window_size;

	S32 state;

	struct s_code *ll_codes;
	struct s_code *dist_codes;
	struct s_code code;
	U8 ll_codes_bits;
	U8 dist_codes_bits;
	U16 length;
	U16 dist;
};

typedef struct s_deflate_stream
{
	U8 *in;
	U64 in_size;
	U64 in_used;

	U8 *out;
	U64 out_size;
	U64 out_used;

	U8 bits;
	U32 crc32;

	union
	{
		struct s_inflate_data inflate;

		struct
		{

		} deflate;
	};

} t_deflate_stream;

#define FT_DEFLATE_WINDOW_SIZE 32768

#define FT_DEFLATE_BLOCK_TYPE_0 0
#define FT_DEFLATE_BLOCK_TYPE_1 1
#define FT_DEFLATE_BLOCK_TYPE_2 2

/*
Compresses a block of data.
Data is taken from `data_stream.in`, with at most `data_stream.in_size` bytes available,
and compressed data is put in `data_stream.out`

### On error
Sets ft_errno and returns FALSE.
### ft_errno
- FT_EINVOP if there isn't enough space to make the smallest block possible
- FT_EINVVAL if `block_type` is 0 (uncompressed) and the amount of bytes to compress is bigger than `U16_MAX`
### Note
If failure, the `data_stream` will be compromised, and cannot be used again
### TODO
Don't compromise the stream
More tests with small buffer size
*/
bool ft_deflate_next_block(t_deflate_stream *data_stream, U64 block_max_size, U8 is_last, U8 block_type);

/*
Ends the compression and cleanup.

### On error
Sets ft_errno and returns FALSE.
### ft_errno
- FT_EINVOP if there isn't enough space in the output buffer
### TODO
*/
bool ft_deflate_end(t_deflate_stream *stream);


/*
Inits a t_deflate_stream for decompression
*/
void ft_inflate_init(t_deflate_stream *stream);

/*
Decompresses data in the DEFLATE format.
Compressed data is taken from `stream.in`, and decompressed data is put in `stream.out`.

### Return values
- `FT_INFLATE_RET_NOT_DONE` if there is more data to process
- `FT_INFLATE_RET_DONE` if there is no more data to process
- `FT_INFLATE_RET_OMEM` if there was an error allocating the window buffer
- `FT_INFLATE_RET_INVALID_IN_SIZE` if `stream.in_used < stream.in_size`
- `FT_INFLATE_RET_INVALID_OUT_SIZE` if `stream.out_used < stream.out_size`
### On error
Returns a negative value, corresponding to the error.
### TODO
*/
S32 ft_inflate(t_deflate_stream *stream);

/*
Cleanup
*/
void ft_inflate_end(t_deflate_stream *stream);

#define FT_INFLATE_RET_NOT_DONE 1
#define FT_INFLATE_RET_DONE 0
#define FT_INFLATE_RET_OMEM -1
#define FT_INFLATE_RET_INVALID_IN_SIZE -2
#define FT_INFLATE_RET_INVALID_OUT_SIZE -3

#endif