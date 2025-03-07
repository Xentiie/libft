/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sse.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 21:50:04 by reclaire          #+#    #+#             */
/*   Updated: 2025/03/06 02:48:46 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(FT_SSE_H)
#define FT_SSE_H

typedef float xmm __attribute__((vector_size(16), may_alias));
typedef float ymm __attribute__((vector_size(32), may_alias));

#endif
