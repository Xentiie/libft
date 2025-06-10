/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adler.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 03:32:38 by reclaire          #+#    #+#             */
/*   Updated: 2025/06/04 03:20:27 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_int.h"

#define MOD_ADLER 65521

U64 ft_adler32(U8 *data, U64 len, U64 adler)
{
    U32 a, b;
    union {
        U64 full;
        struct {
            U32 low;
            U32 high;
        };
    } adler_u;

    adler_u.full = adler;
    if (adler)
    {
        b = adler_u.low;
        a = adler_u.high;
    }
    else
    {
        b = 0;
        a = 1;
    }

    for (U64 index = 0; index < len; index++)
    {
        a = (a + data[index]) % MOD_ADLER;
        b = (b + a) % MOD_ADLER;
    }

    adler_u.low = b;
    adler_u.high = a;
    return adler_u.full;
}

U32 ft_adler32_end(U64 adler)
{
    union {
        U64 full;
        struct {
            U32 low;
            U32 high;
        };
    } adler_u;

	adler_u.full = adler;

	return (adler_u.low << 16) | adler_u.high;
}
