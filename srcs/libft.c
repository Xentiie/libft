/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 04:01:02 by reclaire          #+#    #+#             */
/*   Updated: 2024/02/12 21:07:06 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_int.h"

#if defined(FT_WIN32)
# include <windows.h>
#endif

int				ft_argc = -1;
const_string	*ft_argv = NULL;
const_string	*ft_env = NULL;

t_error_code	ft_errno;

file			ft_stdout;
file			ft_stdin;
file			ft_stderr;

__attribute__((constructor))
void __init_libft()
{
#if defined(FT_WIN32)
	ft_stdin = GetStdHandle(STD_INPUT_HANDLE);
	ft_stdout = GetStdHandle(STD_OUTPUT_HANDLE);
	ft_stderr = GetStdHandle(STD_ERROR_HANDLE);
#elif defined(FT_LINUX) || defined(FT_OSX)
	ft_stdin = (file)0;
	ft_stdout = (file)1;
	ft_stderr = (file)2;
#endif

}
