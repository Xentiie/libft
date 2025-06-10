/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 01:49:04 by reclaire          #+#    #+#             */
/*   Updated: 2025/06/08 02:13:17 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_int.h"

#include "libft/io.h"

#include <stdlib.h>

#if FT_OS_WINDOWS
#include <windows.h>
#define __thread
#endif

_FT_GLOBAL_VAR_DEF(S32, ft_argc, -1);
_FT_GLOBAL_VAR_DEF(string *, ft_argv, NULL);
_FT_GLOBAL_VAR_DEF(string *, ft_env, NULL);
_FT_GLOBAL_VAR_DEF_THREADLOCAL(S32, ft_errno, FT_OK);

_FT_GLOBAL_VAR_DEF(filedesc, ft_stdin);
_FT_GLOBAL_VAR_DEF(filedesc, ft_stdout);
_FT_GLOBAL_VAR_DEF(filedesc, ft_stderr);

_FT_GLOBAL_VAR_DEF(t_file *, ft_fstdin);
_FT_GLOBAL_VAR_DEF(t_file *, ft_fstdout);
_FT_GLOBAL_VAR_DEF(t_file *, ft_fstderr);

_FT_GLOBAL_VAR_DEF_THREADLOCAL(f_ft_allocator, ftalloc, malloc)
_FT_GLOBAL_VAR_DEF_THREADLOCAL(f_ft_free, ftfree, free)

__attribute__((constructor(101))) static void __init_libft(S32 argc, string *argv, string *env)
{
#if FT_OS_WINDOWS
	(void)argc;
	(void)argv;
	(void)env;

	ft_argc = __argc;
	ft_argv = __argv;
	ft_env = environ;
#elif FT_OS_LINUX
	ft_argc = argc;
	ft_argv = argv;
	ft_env = env;
#endif

#if FT_OS_WINDOWS
	ft_stdin = GetStdHandle(STD_INPUT_HANDLE);
	ft_stdout = GetStdHandle(STD_OUTPUT_HANDLE);
	ft_stderr = GetStdHandle(STD_ERROR_HANDLE);
#elif FT_OS_POSIX
	ft_stdin = (filedesc)0;
	ft_stdout = (filedesc)1;
	ft_stderr = (filedesc)2;
#endif

	if (UNLIKELY((ft_fstdin = ft_fcreate(ft_stdin, "r")) == NULL) ||
		UNLIKELY((ft_fstdout = ft_fcreate(ft_stdout, "w")) == NULL) ||
		UNLIKELY((ft_fstderr = ft_fcreate(ft_stderr, "w")) == NULL))
		exit(42);
}

void lock_ht_cleanup(); /* lock.c:37 */
__attribute__((destructor(65535))) void __destroy_libft()
{
	ft_fdestroy(ft_fstdin);
	ft_fdestroy(ft_fstdout);
	ft_fdestroy(ft_fstderr);
	lock_ht_cleanup();
}
