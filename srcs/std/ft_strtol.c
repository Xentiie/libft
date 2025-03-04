/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtol.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 19:16:28 by reclaire          #+#    #+#             */
/*   Updated: 2025/02/14 03:03:52 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_int.h"

#include "libft/strings.h"
#include "libft/limits.h"

#define ft_strtoX_impl_unsigned(X)                                           \
	X ft_strto##X(const_string str, U64 *len, const_string base)             \
	{                                                                        \
		S64 ind;                                                             \
		U64 base_len;                                                        \
		X out;                                                               \
		U64 i;                                                               \
                                                                             \
		if (*str == '-')                                                     \
			FT_RET_ERR(0, FT_ERANGE);                                        \
		if (*str == '+')                                                     \
			str++;                                                           \
                                                                             \
		if (base == NULL)                                                    \
			base = "0123456789";                                             \
		base_len = ft_strlen(base);                                          \
                                                                             \
		out = 0;                                                             \
		i = 0;                                                               \
		while ((ind = ft_strgetindex(base, str[i])) != -1 && str[i] != '\0') \
		{                                                                    \
			if (out > (X##_MAX / (X)base_len))                               \
				FT_RET_ERR(X##_MAX, FT_ERANGE);                              \
			out *= base_len;                                                 \
                                                                             \
			if (out > (X##_MAX - ind))                                       \
				FT_RET_ERR(X##_MAX, FT_ERANGE);                              \
			out += ind;                                                      \
			i++;                                                             \
		}                                                                    \
                                                                             \
		if (len)                                                             \
			*len = i;                                                        \
                                                                             \
		FT_RET_OK(out);                                                      \
	}

#define ft_strtoX_impl_signed(X)                                                 \
	X ft_strto##X(const_string str, U64 *len, const_string base)                 \
	{                                                                            \
		S64 ind;                                                                 \
		U64 base_len;                                                            \
		X out;                                                                   \
		U64 i;                                                                   \
                                                                                 \
		if (base == NULL)                                                        \
			base = "0123456789";                                                 \
		base_len = ft_strlen(base);                                              \
                                                                                 \
		out = 0;                                                                 \
		i = 0;                                                                   \
		if (*str == '-')                                                         \
		{                                                                        \
			i++;                                                                 \
			while ((ind = ft_strgetindex(base, str[i])) != -1 && str[i] != '\0') \
			{                                                                    \
				if (out < (X##_MIN / (X)base_len))                               \
					FT_RET_ERR(X##_MIN, FT_ERANGE);                              \
				out *= base_len;                                                 \
                                                                                 \
				if (out < (X##_MIN + ind))                                       \
					FT_RET_ERR(X##_MIN, FT_ERANGE);                              \
				out -= ind;                                                      \
				i++;                                                             \
			}                                                                    \
		}                                                                        \
		else                                                                     \
		{                                                                        \
			if (*str == '+')                                                     \
				str++;                                                           \
			while ((ind = ft_strgetindex(base, str[i])) != -1 && str[i] != '\0') \
			{                                                                    \
				if (out > (X##_MAX / (X)base_len))                               \
					FT_RET_ERR(X##_MAX, FT_ERANGE);                              \
				out *= base_len;                                                 \
                                                                                 \
				if (out > (X##_MAX - ind))                                       \
					FT_RET_ERR(X##_MAX, FT_ERANGE);                              \
				out += ind;                                                      \
				i++;                                                             \
			}                                                                    \
		}                                                                        \
                                                                                 \
		if (len)                                                                 \
			*len = i;                                                            \
                                                                                 \
		FT_RET_OK(out);                                                          \
	}

ft_strtoX_impl_unsigned(U8);
ft_strtoX_impl_unsigned(U16);
ft_strtoX_impl_unsigned(U32);
ft_strtoX_impl_unsigned(U64);
ft_strtoX_impl_signed(S8);
ft_strtoX_impl_signed(S16);
ft_strtoX_impl_signed(S32);
ft_strtoX_impl_signed(S64);
