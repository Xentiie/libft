/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forbidden_chars.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 05:57:04 by reclaire          #+#    #+#             */
/*   Updated: 2024/12/31 15:58:12 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(FORBIDDEN_CHARS_H)
#define FORBIDDEN_CHARS_H

#include "libft/types.h"

static const char forbidden_chars_linux[] = {
	'/',
};

static const char forbidden_chars_windows[] = {
	'/',
	'\\',
	':',
	'*',
	'?',
	'"',
	'<',
	'>',
	'|',
};

static inline const_string get_forbidden_chars(S32 target)
{
	switch (target)
	{
	case FT_TARGET_LINUX:
		return forbidden_chars_linux;
	case FT_TARGET_WIN:
		return forbidden_chars_windows;
	default:
		return NULL;
	}
}

#endif