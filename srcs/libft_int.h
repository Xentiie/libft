/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_int.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 19:57:38 by reclaire          #+#    #+#             */
/*   Updated: 2024/05/19 23:16:13 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_INT_H
# define LIBFT_INT_H

# include <stdlib.h>

# include "../headers/_libft.h"
# include "../headers/ansi.h"
# include "../headers/debug.h"
# include "../headers/io.h"
# include "../headers/limits.h"
# include "../headers/lists.h"
# include "../headers/macros.h"
# include "../headers/maths.h"
# include "../headers/std.h"
# include "../headers/strings.h"
# include "../headers/time.h"
# include "../headers/types.h"
# include "../headers/getopt.h"
# include "../headers/exec.h"
# include "../headers/path.h"
# include "../headers/crypt.h"
# include "../headers/images.h"
# include "../headers/compression.h"
# include "../headers/btree.h"
# include "../headers/debug.h"

/*Private usage*/
# define __FTRETURN_OK(ret) do { ft_errno=FT_OK; return ret; } while (0)

# ifdef DEBUG
#  define __FTRETURN_ERR(ret, err) do { ft_errno = err ; ft_debug_break(); return ret; } while (0)
# else
#  define __FTRETURN_ERR(ret, err) do { ft_errno = err ; return ret; } while (0)
# endif

# ifndef LIBFT_AVOID_ALLOCA
#  ifdef FT_OS_WIN
#   include <malloc.h>
#  else
#   include <alloca.h>
#  endif
#  define a_malloc(...) alloca(__VA_ARGS__)
#  define a_free(...)
# endif

#endif