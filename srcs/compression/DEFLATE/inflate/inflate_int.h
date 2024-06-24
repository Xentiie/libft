/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inflate_int.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 21:08:50 by reclaire          #+#    #+#             */
/*   Updated: 2024/06/18 12:03:07 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_INFLATE_INT
#define FT_INFLATE_INT

#include "../deflate_int.h"

#define FT_INFLATE_DEBUG
#ifdef FT_INFLATE_DEBUG
#include <stdio.h>
#define IFDEBUG(...) \
	{                \
		__VA_ARGS__; \
	}
#else
#define IFDEBUG(...)
#endif

#ifdef DEBUG
#define __FTINFLATEERR2(ret, _ft_errno) \
	do                                  \
	{                                   \
		if (err)                        \
			*err = FT_OK;               \
		ft_errno = _ft_errno;           \
		ft_debug_break();               \
		return ret;                     \
	} while (0)
#else
#define __FTINFLATEERR2(ret, _ft_errno) \
	do                                  \
	{                                   \
		if (err)                        \
			*err = FT_OK;               \
		ft_errno = _ft_errno;           \
		return ret;                     \
	} while (0)
#endif

#define __FTINFLATEERR(_inflate_err)                                                \
	do                                                                              \
	{                                                                               \
		if (err)                                                                    \
			*err = _inflate_err;                                                    \
		if (_inflate_err != FT_EOMEM)                                               \
			ft_memset(&stream->save_state, 0, sizeof(t_deflate_stream_save_state)); \
		__FTRETURN_ERR(FALSE, FT_EINVOP);                                           \
	} while (0)

#define CHK_IN_SIZE(val) (UNLIKELY(stream->in_used >= stream->in_size) || stream->in_size - stream->in_used < val)
#define CHK_OUT_SIZE(val) (UNLIKELY(stream->out_used >= stream->out_size) || stream->out_size - stream->out_used < val)

t_huffman_node *huffman_add_node(t_huffman_node *root, U16 code, U16 code_len, S32 symbol);
t_huffman_node *mk_huffman(U16 *data, U64 len);
void free_huffman(t_huffman_node *root);

bool inflate_block_type0(t_deflate_stream *stream, S32 *err);
bool inflate_block_type1(t_deflate_stream *stream, S32 *err, bool load_save);
bool inflate_block_type2(t_deflate_stream *stream, S32 *err);

#endif