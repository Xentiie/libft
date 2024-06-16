/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deflate.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 23:02:08 by reclaire          #+#    #+#             */
/*   Updated: 2024/06/14 16:01:42 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_DEFLATE_H
#define LIBFT_DEFLATE_H

#include "libft/_libft.h"

typedef union u_deflate_stream_save_state
{
	struct {
		U8 block_type; // -1 because 0 == no save state
		U8 last;
	} base;

	struct
	{
		U8 block_type;
		U8 last;
		U16 remaining_size;
	} type0;

	struct
	{
		U8 block_type;
		U8 last;
		U64 working_bytes;
	} type1;

	struct
	{
		U8 block_type;
		U8 last;
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

	t_deflate_stream_save_state save_state;
} t_deflate_stream;

#define DEFLATE_BLOCK_TYPE_0 0
#define DEFLATE_BLOCK_TYPE_1 1
#define DEFLATE_BLOCK_TYPE_2 2

#define FT_INFLATE_EOMEM 1			  /* No enough space in out buffer */
#define FT_INFLATE_EINV_BLOCK_SIZE 2  /* Invalid block size/~size in a block type 1 */
#define FT_INFLATE_EINV_LENGTH_CODE 3 /* Invalid length code */
#define FT_INFLATE_EINV_DISTANCE 4	  /* Invalid distance (not enough characters in buffer) */
#define FT_INFLATE_EINV_BLOCK_TYPE 5  /* Invalid block type (should be 0/1/2) */
#define FT_INFLATE_EINV_INPUT_BUFFER_SIZE 6  /* Not enough data in the input buffer to parse a block */
#define FT_INFLATE_EINV_CL_CODES_TREE 7  /* An error occurred while building the cl code's huffman tree */
#define FT_INFLATE_EINV_CL_CODES 8  /* A decoded CL code is invalid */

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

### On error
Sets ft_errno, sets `err` if not NULL and returns FALSE.
### ft_errno
- FT_EINVOP if there has been an error while decompressing. More information can be retrieved from `err`
### TODO
*/
bool ft_inflate_next_block(t_deflate_stream *stream, S32 *err);

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
	.save_state = {.type2 = {.block_type = 0,                                       \
							 .working_byte = 0,                                     \
							 .ll_codes = NULL,                                      \
							 .dist_codes = NULL}}})

#endif