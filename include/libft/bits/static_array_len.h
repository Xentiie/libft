/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   static_array_len.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 20:44:24 by reclaire          #+#    #+#             */
/*   Updated: 2025/04/15 01:47:23 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(FT_BITS_STATIC_ARRAY_LEN_H)
#define FT_BITS_STATIC_ARRAY_LEN_H

#define statarray_len(x) (sizeof(x) / sizeof((x[0])))

#endif
