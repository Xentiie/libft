/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deflate.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 23:02:08 by reclaire          #+#    #+#             */
/*   Updated: 2024/06/20 17:19:56 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_DEFLATE_H
#define LIBFT_DEFLATE_H

#include "libft/_libft.h"

typedef union u_deflate_stream_save_state
{
	struct
	{
		U16 remaining_size;
	} type0;

	struct
	{
		U64 working_bytes;
	} type1;

	struct
	{
		U8 working_byte;

		U16 *ll_codes;
		U16 *dist_codes;
	} type2;

} t_deflate_stream_save_state;

typedef struct s_deflate_stream
{
	U8 *in;
	U64 in_size;
	U64 in_used;

	U8 *out;
	U64 out_size;
	U64 out_used;

	U32 crc32;
	U8 bit_offset;

	S8 block_type;
	U8 last;

	U8 *window;
	U64 window_size;

	S8 state;

	t_deflate_stream_save_state save_state;
} t_deflate_stream;

#define FT_DEFLATE_WINDOW_SIZE 32768

#define FT_DEFLATE_BLOCK_TYPE_0 0
#define FT_DEFLATE_BLOCK_TYPE_1 1
#define FT_DEFLATE_BLOCK_TYPE_2 2

#define FT_INFLATE_E_OUT_OMEM 1			/* No enough space in out buffer */
#define FT_INFLATE_E_IN_OMEM 2			/* Not enough data in the input buffer to parse a block */
#define FT_INFLATE_EINV_BLOCK_SIZE 3	/* Invalid block size/~size in a block type 1 */
#define FT_INFLATE_EINV_LENGTH_CODE 4	/* Invalid length code */
#define FT_INFLATE_EINV_DISTANCE 5		/* Invalid distance (not enough characters in buffer) */
#define FT_INFLATE_EINV_BLOCK_TYPE 6	/* Invalid block type (should be 0/1/2) */
#define FT_INFLATE_EINV_CL_CODES_TREE 7 /* An error occurred while building the cl code's huffman tree */
#define FT_INFLATE_EINV_CL_CODES 8		/* A decoded CL code is invalid */

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
Decompresses a block of data.
Compressed data is taken from `data_stream.in`, with at most `data_stream.in_size` bytes available,
and decompressed data is put in `data_stream.out`

Returns TRUE if there is more data to decompress, FALSE otherwise


Minimum values:
Any block: 2 bytes (block header)
type 0: 4 bytes (block type 0 size/nsize)

### On error
Sets ft_errno, sets `err` if not NULL and returns FALSE.
### ft_errno
- FT_EINVOP if there has been an error while decompressing. More information can be retrieved from `err`
### TODO
*/
bool ft_inflate(t_deflate_stream *stream, S32 *err);

/*
Decompresses `data`, and returns decompressed data. The returned pointer is malloc'ed.

### On error
Sets ft_errno, sets `err` if not NULL and returns NULL.
### ft_errno
- FT_EOMEM if out of memory.
- See ft_inflate_next_block
### TODO
*/
U8 *ft_inflate_quick(U8 *data, U64 data_len, t_deflate_stream *out_stream, S32 *err);

/*
Returns the error description associated with error code `err`.

### On error
Sets ft_errno and returns NULL.
### ft_errno
- FT_ERANGE if `err < 0` or `err > max_error`
### TODO
*/
const_string ft_inflate_strerror(S32 err);

/*
Returns the error name associated with error code `err`.

### On error
Sets ft_errno and returns NULL.
### ft_errno
- FT_ERANGE if `err < 0` or `err > max_error`
### TODO
*/
const_string ft_inflate_errortostr(S32 err);

/*
Returns the error code associated with error name `name`.

### On error
Sets ft_errno and returns -1.
### ft_errno
- FT_EINVPTR if `name` is NULL
- FT_ENOENT if no error code was found
### TODO
*/
S32 ft_inflate_strtoerror(const_string name);

/*
Inits a `t_deflate_stream`. A stream shouldn't be initialized manually
*/
#define ft_deflate_init_stream(_in, _in_size, _out, _out_size) ((t_deflate_stream){ \
	.in = _in,                                                                      \
	.in_size = _in_size,                                                            \
	.in_used = 0,                                                                   \
                                                                                    \
	.out = _out,                                                                    \
	.out_size = _out_size,                                                          \
	.out_used = 0,                                                                  \
                                                                                    \
	.crc32 = 0,                                                                     \
	.bit_offset = 0,                                                                \
                                                                                    \
	.block_type = -1,                                                               \
	.last = FALSE,                                                                  \
                                                                                    \
	.window = NULL,                                                                 \
	.window_size = 0,                                                               \
                                                                                    \
	.save_state = {0}})



struct s_code
{
	U16 code;
	U8 nbits;
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

	union
	{
		struct
		{
			U16 length;
		} type0;

		struct
		{
			struct s_code *ll_codes;

			U16 length_code_i;
			U16 extra_length;
			U16 dist_code;
			U16 extra_dist;
		} type12;

	} blk_data;
};

typedef struct s_deflate_stream2
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

} t_deflate_stream2;

void ft_inflate_init(t_deflate_stream2 *stream);
S32 ft_inflate2(t_deflate_stream2 *stream);

#define FT_INFLATE_RET_NOT_DONE 1
#define FT_INFLATE_RET_DONE 0
#define FT_INFLATE_RET_OMEM -1
#define FT_INFLATE_RET_INVALID_IN_SIZE -2
#define FT_INFLATE_RET_INVALID_OUT_SIZE -3

#endif