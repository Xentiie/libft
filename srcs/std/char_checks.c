/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_checks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 20:44:18 by reclaire          #+#    #+#             */
/*   Updated: 2024/02/12 16:19:01 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_int.h"

inline bool ft_islower(U8 c)
{
	if (c >= 97 && c <= 122)
		return TRUE;
	return FALSE;
}

inline bool ft_isupper(U8 c)
{
	if (c >= 64 && c <= 90)
		return TRUE;
	return FALSE;
}

inline bool	ft_isascii(U8 c)
{
	if (c <= 127)
		return (TRUE);
	return (FALSE);
}

inline bool	ft_isalpha(U8 c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (TRUE);
	return (FALSE);
}

inline bool	ft_isdigit(U8 c)
{
	if (c >= '0' && c <= '9')
		return (TRUE);
	return (FALSE);
}

inline bool	ft_isalnum(U8 c)
{
	if ((c >= '0' && c <= '9') || ft_isalpha(c))
		return (TRUE);
	return (FALSE);
}

inline bool	ft_isprint(U8 c)
{
	if (c >= 32 && c <= 126)
		return (TRUE);
	return (FALSE);
}

inline bool	ft_iswhitespace(U8 c)
{
	if (c == ' ' || c == '\t' || c == '\r' || c == '\n' || c == '\v' || c == '\f')
		return (TRUE);
	return (FALSE);
}
