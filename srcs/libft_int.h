/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_int.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 19:57:38 by reclaire          #+#    #+#             */
/*   Updated: 2024/02/20 15:38:23 by reclaire         ###   ########.fr       */
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


/*Private usage*/
# define __FTRETURN_OK(ret) do { ft_errno=FT_OK; return ret; } while (0)
# define __FTRETURN_ERR(ret, err) do { ft_errno = err ; return ret; } while (0)

#endif