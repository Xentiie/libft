/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_debug.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 19:57:43 by reclaire          #+#    #+#             */
/*   Updated: 2023/09/27 22:47:14 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//TMP
#ifndef WIN32



#include "libft.h"
#ifdef FT_DEBUG
#  include <stdio.h>
#  include <signal.h>
# ifdef WIN32
#  include <debugapi.h>
#  define SIGTRAP STATUS_BREAKPOINT
# else
#  include <sys/ptrace.h>
#  include <valgrind/valgrind.h>
#endif

//TODO: check si tout marche sous windows

static S8	__is_debugger = -1;

S8	ft_is_debugger()
{
	if (__is_debugger == -1)
	{
# ifdef WIN32
		if (IsDebuggerPresent())
			__is_debugger = FT_DEBUG_GDB;
		else
			__is_debugger = FT_DEBUG_NONE;
# else
		if (RUNNING_ON_VALGRIND)
			__is_debugger = FT_DEBUG_VALGRIND;
    	else if (ptrace(PTRACE_TRACEME, 0, 1, 0) == -1)
			__is_debugger = FT_DEBUG_GDB;
    	else 
			__is_debugger = FT_DEBUG_NONE;
# endif
	}
	return __is_debugger;
}

void	ft_debug_break()
{
	if (ft_is_debugger() == FT_DEBUG_GDB)
		raise(SIGTRAP);
}

#endif




#endif /* #ifndef WIN32 */