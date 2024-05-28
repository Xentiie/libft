/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compression.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 00:28:17 by reclaire          #+#    #+#             */
/*   Updated: 2024/05/23 23:11:36 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_COMPRESSION_H
# define LIBFT_COMPRESSION_H

# include "_libft.h"
# include "libft/bitstreams.h"

typedef struct s_huffman_node
{
	U8 byte;
	U32 huffman_coding;
	U32 nbits;
	U64 n;
	struct s_huffman_node *right;
	struct s_huffman_node *left;
}   t_huffman_node;

//NEEDS CALL FREE ON nodes
t_huffman_node *ft_create_huffman_tree(U8 *data, U64 len, t_huffman_node ***leafs_out, U64 *out_nodes_count);
void ft_print_huffman_tree(t_huffman_node *tree);
void ft_print_huffman_node(t_huffman_node *node, bool nl);

//RETURNS NULL and FT_ENOENT IF NOT FOUND
t_huffman_node *ft_get_huffman_node(U8 byte, t_huffman_node **nodes, U64 count);
void ft_free_huffman_tree(t_huffman_node *leafs);


void ft_lzss_compress(U8 *data, U64 len, t_bitstream *stream, U64 window_max_size, U64 lookahead_size);
U64 ft_lzss_decompress(t_bitstream *stream, U8 *out, U64 len);

void ft_make_gzip(U8 *data, U64 len, string out_file);

void ft_deflate(U8 *data, U64 size, t_bitstream *out_stream);
void ft_inflate(U8 *data, U64 size, U64 *output, U64 output_len);

#endif