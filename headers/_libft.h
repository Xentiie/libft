/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _libft.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 19:56:09 by reclaire          #+#    #+#             */
/*   Updated: 2024/02/12 21:08:27 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _LIBFT_H
# define _LIBFT_H

# if !defined(FT_WIN32) && !defined(FT_OSX) && !defined(FT_LINUX)
#  warning No platform seem to be specified, errors WILL occur.
# endif

# include "types.h"

extern	int				ft_argc;
extern	const_string	*ft_argv;
extern	const_string	*ft_env;
# define FT_INIT_ARGV(argc, argv, env) ft_argc=argc;ft_argv=argv;ft_env=env;

/*Error code returned by some ft functions*/
extern	t_error_code		ft_errno;
# define FT_OK				0	/*No error*/
# define FT_EOMEM			1	/*Out of memory*/
# define FT_EINVPTR			2	/*Invalid pointer*/
# define FT_EINVVAL			3	/*Invalid value*/
# define FT_ESYSCALL		4	/*System call failed*/
# define FT_ENOENT			5	/*No entries found*/
# define FT_ERANGE			6	/*Out of range*/
# define FT_ENOINIT			7	/*Libft value not initialized*/

# define FUNCTION_HOT __attribute__((hot))
# define FUNCTION_COLD __attribute__((cold))


#endif