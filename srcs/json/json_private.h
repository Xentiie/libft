/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   json_private.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 01:44:04 by reclaire          #+#    #+#             */
/*   Updated: 2025/01/07 02:48:50 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(LIBFT_JSON_PRIVATE_H)
#define LIBFT_JSON_PRIVATE_H

#include "libft_int.h"

#include "libft/json.h"

struct s_json_ht
{
	struct s_json_member **buckets;
	U64 buckets_len;
};

struct s_json_ht *__ftjson_init_ht();
struct s_json_member **__ftjson_lookup_ht(struct s_json_ht *ht, const_string key);
bool __ftjson_insert_ht(struct s_json_member **node, const_string key, struct s_json_object *obj);
void __ftjson_cleanup_ht(struct s_json_ht *ht);

#endif
