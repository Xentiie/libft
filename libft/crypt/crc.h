/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crc.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 15:23:59 by reclaire          #+#    #+#             */
/*   Updated: 2024/11/19 04:06:20 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(FT_CRC_H)
#define FT_CRC_H

#include "../libft.h"

/* Computes CRC32 from `data` */
extern U32 ft_crc32(U8 *data, U64 len);
/* Updates a CRC32 from `data` */
extern U32 ft_crc32_u(U8 *data, U64 len, U32 crc);

#endif