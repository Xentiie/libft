/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_return.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 20:06:27 by reclaire          #+#    #+#             */
/*   Updated: 2025/04/15 01:46:13 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(FT_BITS_FT_RETURN_H)
#define FT_BITS_FT_RETURN_H

/* Resets `ft_errno` and returns `ret` */
# define FT_RET_OK(ret) do { ft_errno=FT_OK; return ret; } while (0)

# if defined(DEBUG)
#  include "libft/debug.h"
/* Sets `ft_errno` to `err` and returns `ret` */
#  define FT_RET_ERR(ret, err) do { ft_errno = err ; ft_debug_break(); return ret; } while (0)
# else
/* Sets `ft_errno` to `err` and returns `ret` */
#  define FT_RET_ERR(ret, err) do { ft_errno = err ; return ret; } while (0)
# endif

#endif