/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 00:01:59 by reclaire          #+#    #+#             */
/*   Updated: 2023/09/27 21:10:20 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#ifdef FT_STD
# include <math.h>

# define AFTERPOINT 5

static void	reverse(string str, U64 len)
{
	U64	i;
	U64	j;
	U8	temp;

	i = 0;
	j = len - 1;
	while (i < j)
	{
		temp = str[i];
		str[i] = str[j];
		str[j] = temp;
		i++;
		j--;
	}
}

static S32	int_to_str(S32 x, string str, S32 d, bool is_neg)
{
	S32	i;

	i = is_neg;
	if (x == 0)
	{
		str[i] = '0';
		return (1);
	}
	while (x)
	{
		str[i++] = (x % 10) + '0';
		if (i >= (AFTERPOINT * 2 + 2))
		{
			str[i - 1] = '\0';
			return (-1);
		}
		x = x / 10;
	}

	while (i < d && i < (AFTERPOINT * 2 + 2) - 1)
		str[i++] = '0';
	reverse(str, i);
	str[i] = '\0';
	return (i);
}

string ft_ftoa(float n)
{
	S32		ipart;
	F32		fpart;
	S32		i;
	string	out;

	bool	neg = FALSE;

	out = malloc(sizeof(char) * (AFTERPOINT * 2 + 3));
	if (out == NULL)
		__FTRETURN_ERR(NULL, FT_EOMEM);

	ft_bzero(out, sizeof(char) * (AFTERPOINT * 2 + 3));
	if (n < 0) { neg = TRUE; n *= -1; }

	ipart = (S32)n;
	fpart = n - (float)ipart;

	i = int_to_str(ipart, out, 0, neg);
	if (neg)
		out[0] = '-';
	if (i > 0 && i < (AFTERPOINT * 2 + 1) - 1)
	{
		out[i] = '.';
		fpart = fpart * pow(10, AFTERPOINT);
		int_to_str((int)fpart, out + i + 1, AFTERPOINT, neg);
	}
	__FTRETURN_OK(out);
}
#endif