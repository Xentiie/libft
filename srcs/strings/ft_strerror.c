/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strerror.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 14:52:06 by reclaire          #+#    #+#             */
/*   Updated: 2025/04/15 02:42:06 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_int.h"

#include "libft/bits/errors_str.h"
#include "libft/strings.h"

#if FT_OS_LINUX
#include <errno.h>
#include <string.h>
#elif FT_OS_WINDOWS
#include <windows.h>
#include <winerror.h>
#endif

FT_DEFINE_ERROR_ENTRIES(entries,
						[FT_OK] = { "FT_OK", "No error" },
						[FT_EOMEM] = { "FT_EOMEM", "Out of memory" },
						[FT_EINVPTR] = { "FT_EINVPTR", "Invalid pointer" },
						[FT_EINVVAL] = { "FT_EINVVAL", "Invalid value" },
						[FT_EINVOP] = { "FT_EINVOP", "Invalid operation" },
						[FT_ESYSCALL] = { "FT_ESYSCALL", "System call failed" },
						[FT_ENOENT] = { "FT_ENOENT", "No entries found" },
						[FT_ERANGE] = { "FT_ERANGE", "Out of range" },
						[FT_ENOINIT] = { "FT_ENOINIT", "Libft value not initialized" },
						[FT_EOSPACE] = { "FT_EOSPACE", "Out of space" });

const_string ft_strerror(S32 err)
{
	FT_DEFINE_STRERROR(entries);
}

const_string ft_strerrorname(S32 err)
{
	FT_DEFINE_STRERRORNAME(entries);
}

const_string ft_strerror_os()
{
#if FT_OS_POSIX
	return strerror(errno);
#elif FT_OS_WINDOWS
	threadlocal static char buf[200] = {0};
	U64 len;
	S32 err;

	if ((err = GetLastError()) != 0)
	{
		len = FormatMessageA(
			FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL,
			err,
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			(LPSTR)&buf,
			sizeof(buf) - 1,
			NULL);

		for (S64 i = len - 1; i >= 0; i--)
		{
			if (buf[i] == '\n')
			{
				buf[i] = '\0';
				break;
			}
		}
		return buf;
	}
	else
		return entries[FT_OK].desc; /* No error */
#endif
}

const_string ft_strerror2()
{
	S32 err;

	err = ft_errno;
	if ((err == FT_OK && errno != 0) || err == FT_ESYSCALL)
		return ft_strerror_os();
	else
		return entries[err].desc;
}
