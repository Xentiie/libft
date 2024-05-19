/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compression.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 00:28:17 by reclaire          #+#    #+#             */
/*   Updated: 2024/05/19 16:34:58 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_COMPRESSION_H
# define LIBFT_COMPRESSION_H

# include "_libft.h"

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
t_huffman_node *ft_create_huffman_tree(U8 *data, U64 len, t_huffman_node ***nodes, U64 *out_nodes_count);
void ft_print_huffman_tree(t_huffman_node *tree);
void ft_print_huffman_node(t_huffman_node *node, bool nl);

//RETURNS NULL and FT_ENOENT IF NOT FOUND
t_huffman_node *ft_get_huffman_node(U8 byte, t_huffman_node **nodes, U64 count);
void ft_free_huffman_tree(t_huffman_node *tree);


U8 *ft_lzss(U8 *data, U64 len, U64 window_size, U64 lookahead);

#endif