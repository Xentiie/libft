/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   addler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 15:23:59 by reclaire          #+#    #+#             */
/*   Updated: 2025/06/04 03:13:44 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(FT_ADDLER_H)
#define FT_ADDLER_H

# include "../libft.h"

extern U64 ft_adler32(U8 *data, U64 len, U64 adler);
extern U32 ft_adler32_end(U64 adler);

#endif