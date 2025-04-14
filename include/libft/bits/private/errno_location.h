/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errno_location.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:26:48 by reclaire          #+#    #+#             */
/*   Updated: 2025/04/14 20:13:15 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(FT_BITS_ERRNO_LOCATION_H)
#define FT_BITS_ERRNO_LOCATION_H

#include "libft/bits/private/no_globals.h"
#include "libft/types.h"

#if _FT_NO_GLOBALS
#define _FT_ERRNO_LOCATION 1
#endif

#if _FT_ERRNO_LOCATION
S32 *__ft_errno_location();
#define ft_errno (*__ft_errno_location())
#else
extern __thread S32 ft_errno;
#endif

#endif
