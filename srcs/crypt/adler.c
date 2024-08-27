/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adler.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 03:32:38 by reclaire          #+#    #+#             */
/*   Updated: 2024/07/02 03:38:21 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_int.h"

#define MOD_ADLER 65521

U64 ft_adler32(U8 *data, U64 len, U64 adler)
{
	U32 a, b;
	
	if (adler)
	{
		b = *(U32*)&adler;
    	a = *((U32*)(&adler) + 1);
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

	*(U32*)&adler = b;
    *((U32*)(&adler) + 1) = a;
	return adler;
}

U32 ft_adler32_end(U64 adler)
{
	return ((*(U32*)adler) << 16) | *(U32*)(adler + 1);
}

