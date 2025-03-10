/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_debug.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 19:57:43 by reclaire          #+#    #+#             */
/*   Updated: 2025/03/08 04:02:40 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_int.h"

#include "libft/debug.h"
#include "libft/io.h"
#include "libft/macros.h"

#include <signal.h>

#if defined(FT_OS_WIN)
#include <debugapi.h>
#define SIGTRAP STATUS_BREAKPOINT

S8 ft_is_debugger()
{
	if (__is_debugger == -1)
	{
		if (IsDebuggerPresent())
			__is_debugger = FT_DEBUG_TRUE;
		else
			__is_debugger = FT_DEBUG_FALSE;
	}
	return __is_debugger;
}
#else
#include <sys/ptrace.h>
#include <valgrind/valgrind.h>

#undef RUNNING_ON_VALGRIND
#define RUNNING_ON_VALGRIND FALSE

S8 ft_is_debugger()
{
	static S8 __is_debugger = -1;
	if (__is_debugger == -1)
	{
		if (RUNNING_ON_VALGRIND)
			__is_debugger = FT_DEBUG_VALGRIND;
		else if (ptrace(PTRACE_TRACEME, 0, 1, 0) == -1)
			__is_debugger = FT_DEBUG_TRUE;
		else
			__is_debugger = FT_DEBUG_FALSE;
	}
	return __is_debugger;
}

#endif /* FT_OS_WIN */

void ft_debug_break()
{
	if (ft_is_debugger() == FT_DEBUG_TRUE)
		raise(SIGTRAP);
}
