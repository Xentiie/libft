/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ht.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 23:05:17 by reclaire          #+#    #+#             */
/*   Updated: 2024/05/22 02:37:14 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_HT_H
# define LIBFT_HT_H

typedef struct s_hash_bucket
{
	U8 *data;
	U64 data_alloc;
	U64 count;
}	t_hash_bucket;

typedef struct s_ht
{
	t_hash_bucket *buckets;
	U64 buckets_alloc;
	U64 buckets_count;

	U64 elem_size;
	U64 (*hash)(void *data);

}	t_ht;

t_ht *ft_new_hash_table(U64 elem_size, U64 init_size, U64 (*hash)(void *elem));
void ft_hash_free(t_ht *table);

void *ft_hash_get(t_ht *table, void *elem);
t_hash_bucket *ft_hash_get_bucket(t_ht *table, void *elem);

void ft_hash_insert(t_ht *table, void *elem);
void ft_hash_remove(t_ht *table, void *elem);

#endif