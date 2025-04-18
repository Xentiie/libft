/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errno.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 20:41:37 by reclaire          #+#    #+#             */
/*   Updated: 2025/04/15 01:46:07 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(FT_BITS_FT_ERRNO_H)
#define FT_BITS_FT_ERRNO_H

#include "libft/bits/globals.h"

#include "libft/types.h"

#define FT_OK 0		  /* No error */
#define FT_EOMEM 1	  /* Out of memory */
#define FT_EINVPTR 2  /* Invalid pointer */
#define FT_EINVVAL 3  /* Invalid value */
#define FT_EINVOP 4	  /* Invalid operation */
#define FT_ESYSCALL 5 /* System call failed */
#define FT_ENOENT 6	  /* No entries found */
#define FT_ERANGE 7	  /* Out of range */
#define FT_ENOINIT 8  /* Libft value not initialized */
#define FT_EOSPACE 9  /* Out of space */

_FT_GLOBAL_VAR_DEC(S32, ft_errno);

#define ft_errno _FT_GLOBAL_VAR(ft_errno)

#endif
