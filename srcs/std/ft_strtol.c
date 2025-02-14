/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtol.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 19:16:28 by reclaire          #+#    #+#             */
/*   Updated: 2025/01/07 19:56:51 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_int.h"
#include "libft/maths.h"
#include "libft/strings.h"
#include "libft/limits.h"

#include "libft/io.h"

static const_string base10 = "0123456789";

#define INIT_BASE()                     \
	do                                  \
	{ /* init base */                   \
		if (base == NULL)               \
		{                               \
			base = base10;              \
			base_len = 10;              \
		}                               \
		else                            \
			base_len = ft_strlen(base); \
	} while (0)

#define PARSE_SIGN(type)      \
	do                        \
	{ /* parse sign */        \
		neg = FALSE;          \
		if (*str == '+')      \
			str++;            \
		else if (*str == '-') \
		{                     \
			str++;            \
			neg = TRUE;       \
		}                     \
	} while (0)

S8 ft_strtoS8(const_string str, U64 *len, const_string base)
{
	U64 base_len;
	S16 i;
	S16 num_len;
	bool neg;

	S8 n;
	S8 ret;

	if (str == NULL)
		FT_RET_ERR(0, FT_EINVPTR);

	INIT_BASE();
	PARSE_SIGN(S8);

#if 0
	{ /* simple first overflow check */
		i = 0;
		while (ft_isdigit(str[i]))
			i++;
		if (i > S8_MAX_MAG)
			/* would overflow */
			FT_RET_ERR(S8_MIN, FT_EINVOP);
	}
#endif

	ret = 0;
	i = 0;
	if (neg)
	{
		while (ft_isdigit(str[i]))
		{
			n = str[i] - '0';
			if (ret > (S8_MIN / 10) || ret > (S8_MIN + n))
				/* would overflow */
				FT_RET_ERR(S8_MIN, FT_EINVOP);

			ft_printf("N:%d\n", n);
			ft_printf("ret:%d > (S8_MIN / 10)(%d) = %s\n", ret, (S8_MIN / 10), ret > (S8_MIN / 10) ? "TRUE" : "FALSE");
			ft_printf("ret:%d > (S8_MIN + n)(%d) = %s\n", ret, (S8_MIN + n), ret > (S8_MIN + n) ? "TRUE" : "FALSE");

			ret = (ret * 10) - (str[i] - '0');
			i++;
		}
	}
	else
	{
		while (ft_isdigit(str[i]))
		{
			n = str[i] - '0';

			ft_printf("N:%d\n", n);
			ft_printf("ret:%d > (S8_MAX / 10)(%d) = %s\n", ret, (S8_MAX / 10), ret > (S8_MAX / 10) ? "TRUE" : "FALSE");
			ft_printf("ret:(%d*10=%d) > (S8_MAX - n)(%d-%d=%d) = %s\n\n", ret, ret*10, S8_MAX, n, S8_MAX - n, (ret * 10) > (S8_MAX - n) ? "TRUE" : "FALSE");

			if (ret > (S8_MAX / 10) || (ret * 10) > (S8_MAX - n))
				/* would overflow */
				FT_RET_ERR(S8_MAX, FT_EINVOP);


			ret = (ret * 10) + (str[i] - '0');
			i++;
		}
	}

	FT_RET_OK(ret);
}

int main()
{
	S8 out = ft_strtoS8(ft_argv[1], NULL, NULL);
	ft_printf("Out:%d\nft_errno:%d:%s\n", out, ft_errno, ft_strerror(ft_errno));
}

U8 ft_strtoU8(const_string str, U64 *len, const_string base)
{
}

S32 ft_strtoS32(const_string str, U64 *len, const_string base)
{
}

U32 ft_strtoU32(const_string str, U64 *len, const_string base)
{
}

S64 ft_strtoS64(const_string str, U64 *len, const_string base)
{
}

U64 ft_strtoU64(const_string str, U64 *len, const_string base)
{
}

F32 ft_strtoF32(const_string str, U64 *len, const_string base)
{
}

F64 ft_strtoF64(const_string str, U64 *len, const_string base)
{
}
