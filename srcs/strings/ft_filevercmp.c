/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_filevercmp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 13:08:45 by reclaire          #+#    #+#             */
/*   Updated: 2025/01/10 14:33:43 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_int.h"

#include "libft/strings.h"
#include "libft/limits.h"

/* http://www.debian.org/doc/debian-policy/ch-controlfields.html#s-f-Version */

static const_string match_suffix(const_string *str)
{
	const_string match;
	bool read_alpha;

	match = NULL;
	read_alpha = FALSE;
	while (**str)
	{
		if (read_alpha)
		{
			read_alpha = FALSE;
			if (!ft_isalpha(**str) && **str != '~')
				match = NULL;
		}
		else if (**str == '.')
		{
			read_alpha = TRUE;
			if (!match)
				match = *str;
		}
		else if (!ft_isalnum(**str) && **str != '~')
			match = NULL;
		(*str)++;
	}
	return match;
}

/* verrevcmp helper function */
static inline S32 order(U8 c)
{
	if (ft_isdigit(c))
		return 0;
	else if (ft_isalpha(c))
		return c;
	else if (c == '~')
		return -1;
	else
		return (S32)c + U8_MAX + 1;
}

static S32 verrevcmp(const_string s1, U64 len1, const_string s2, U64 len2)
{
	S32 first_diff;
	S32 s1_c;
	S32 s2_c;
	U64 i;
	U64 j;

	i = 0;
	j = 0;
	while (i < len1 || j < len2)
	{
		first_diff = 0;
		while ((i < len1 && !ft_isdigit(s1[i])) || (j < len2 && !ft_isdigit(s2[j])))
		{
			s1_c = (i == len1) ? 0 : order(s1[i]);
			s2_c = (j == len2) ? 0 : order(s2[j]);
			if (s1_c != s2_c)
				return s1_c - s2_c;
			i++;
			j++;
		}
		while (s1[i] == '0')
			i++;
		while (s2[j] == '0')
			j++;
		while (ft_isdigit(s1[i]) && ft_isdigit(s2[j]))
		{
			if (!first_diff)
				first_diff = s1[i] - s2[j];
			i++;
			j++;
		}
		if (ft_isdigit(s1[i]))
			return 1;
		if (ft_isdigit(s2[j]))
			return -1;
		if (first_diff)
			return first_diff;
	}
	return 0;
}

S32 ft_filevercmp(const_string s1, const_string s2)
{
	const_string s1_pos;
	const_string s2_pos;
	const_string s1_suffix;
	const_string s2_suffix;
	U64 s1_len;
	U64 s2_len;
	S32 result;
	S32 simple_cmp;

	/* easy comparison to see if strings are identical */
	if ((simple_cmp = ft_strcmp(s1, s2)) == 0)
		return 0;

	/* special cases: "", "." and ".." */
	if (!*s1)
		return -1;
	if (!*s2)
		return 1;
	if (*(s1) == '.' && *(s1 + 1) == '\0')
		return -1;
	if (*(s2) == '.' && *(s2 + 1) == '\0')
		return 1;
	if (*(s1) == '.' && *(s1 + 1) == '.' && *(s1 + 2) == '\0')
		return -1;
	if (*(s2) == '.' && *(s2 + 1) == '.' && *(s2 + 2) == '\0')
		return 1;

	/* special handle for other hidden files */
	if (*s1 == '.' && *s2 != '.')
		return -1;
	if (*s1 != '.' && *s2 == '.')
		return 1;
	if (*s1 == '.' && *s2 == '.')
	{
		s1++;
		s2++;
	}

	/* "cut" file suffixes */
	s1_pos = s1;
	s2_pos = s2;
	s1_suffix = match_suffix(&s1_pos);
	s2_suffix = match_suffix(&s2_pos);
	s1_len = (s1_suffix ? s1_suffix : s1_pos) - s1;
	s2_len = (s2_suffix ? s2_suffix : s2_pos) - s2;

	/* restore file suffixes if strings are identical after "cut" */
	if ((s1_suffix || s2_suffix) && (s1_len == s2_len) && !ft_strncmp(s1, s2, s1_len))
	{
		s1_len = s1_pos - s1;
		s2_len = s2_pos - s2;
	}

	if ((result = verrevcmp(s1, s1_len, s2, s2_len)) == 0)
		return simple_cmp;
	else
		return result;
}
