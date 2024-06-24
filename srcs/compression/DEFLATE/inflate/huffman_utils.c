/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   huffman_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 21:07:33 by reclaire          #+#    #+#             */
/*   Updated: 2024/06/17 21:09:12 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../deflate_int.h"

t_huffman_node *huffman_add_node(t_huffman_node *root, U16 code, U16 code_len, S32 symbol)
{
	if (code_len == 0)
	{
		if (root != NULL)
			return NULL;
		root = malloc(sizeof(t_huffman_node));
		if (UNLIKELY(root == NULL))
			__FTRETURN_ERR(NULL, FT_EOMEM);
		root->left = NULL;
		root->right = NULL;
		root->symbol = symbol;
		root->nbits = code_len;
		root->huffman_coding = code;
		return root;
	}
	else
	{
		U8 bit = (code >> (code_len - 1)) & 0x1;
		if (root == NULL)
		{
			root = malloc(sizeof(t_huffman_node));
			if (root == NULL)
				__FTRETURN_ERR(NULL, FT_EOMEM);
			ft_bzero(root, sizeof(t_huffman_node));
			root->symbol = -1;
		}
		if (bit == 0)
		{
			root->left = huffman_add_node(root->left, code, code_len - 1, symbol);
			if (UNLIKELY(root->left == NULL))
				__FTRETURN_ERR(NULL, FT_EOMEM);
		}
		else
		{
			root->right = huffman_add_node(root->right, code, code_len - 1, symbol);
			if (UNLIKELY(root->right == NULL))
				__FTRETURN_ERR(NULL, FT_EOMEM);
		}
		return root;
	}
}

t_huffman_node *mk_huffman(U16 *data, U64 len)
{
	t_huffman_node *root = NULL;
	for (U64 i = 0; i < len; i++)
	{
		U16 num_bits = data[i * 2];
		U16 code_bits = data[i * 2 + 1];
		if (num_bits == 0)
			continue;

		root = huffman_add_node(root, code_bits, num_bits, (S32)i);
		if (UNLIKELY(root == NULL))
			break;
	}
	return root;
}

void free_huffman(t_huffman_node *root)
{
	if (!root)
		return;
	free_huffman(root->left);
	free_huffman(root->right);
	free(root);
}
