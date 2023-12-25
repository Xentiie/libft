/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 00:18:05 by reclaire          #+#    #+#             */
/*   Updated: 2023/09/26 21:51:52 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#ifdef FT_STD
# include <math.h>
# include <string.h>
typedef union u_bits_to_float
{
	U32		bits;
	F32		f;
}	t_bits_to_float;

F32	ft_atof(const_string str, U64 *len)
{
	const_string save = str;
	S8 neg;
	if (*str == '+')
	{neg = 0; str++;}
	if (*str == '-')
	{neg = 1; str++;}

	F32 v = 0.0f;
	S32 numDigits = 0;
	while (*str >= '0' && *str <= '9')
	{
		v = v * 10.0f + (F32)(*str++ - '0');
		numDigits++;
	}
	if (*str++ == '.')
	{
		F32 scale = 1.0f;
		while (*str >= '0' && *str <= '9')
		{
			scale *= 0.1f;
			v += scale * (F32)(*str++ - '0');
			numDigits++;
		}
	}
	if (!numDigits)
	{
		*len = 0;
		return 0;
	}

    if (*str == '#')
    {
        if (strncmp(str, "#INF", 4))
        {
			*len = str-save;
            return (t_bits_to_float){.bits=((neg) ? 0xFF800000 : 0x7F800000)}.f;
        }
        if (strncmp(str, "#SNAN", 5))
        {
			*len = str-save;
            return (t_bits_to_float){.bits=((neg) ? 0xFF800001 : 0x7F800001)}.f;
        }
        if (strncmp(str, "#QNAN", 5))
        {
			*len = str-save;
            return (t_bits_to_float){.bits=((neg) ? 0xFFC00001 : 0x7FC00001)}.f;
        }
        if (strncmp(str, "#IND", 4))
        {
			*len = str-save;
            return (t_bits_to_float){.bits=((neg) ? 0xFFC00000 : 0x7FC00000)}.f;
        }
    }

	U64 e = 0;
	if (((*str == 'e') || *str == 'E'))
	{
		str++;
		int _;
		if ( (_  = ft_atoi(str, &e)))
		{
			str += _;
			if (e)
				v *= pow(10.0f, (F32)e);
		}
	}
	*len = str - save;
	return (neg) ? -v : v;
}
#endif