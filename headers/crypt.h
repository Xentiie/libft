/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crypt.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:46:23 by reclaire          #+#    #+#             */
/*   Updated: 2024/05/16 17:56:19 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_CRYPT_H
# define LIBFT_CRYPT_H

# include "_libft.h"

U32 ft_crc32(U8 *data, U64 len);
U32 ft_crc32_u(U8 *data, U64 len, U32 crc);

#endif