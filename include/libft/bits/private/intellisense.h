/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intellisense.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 18:45:42 by reclaire          #+#    #+#             */
/*   Updated: 2025/04/14 20:01:31 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(_FT_PRIVATE_BITS)
#error "Don't include this manually"
#endif

#include "libft/bits/os_defines.h"
#if FT_IDE_INTELLISENSE

/* Intellisense thinks __attribute__((constructor)) takes no arguments */
#pragma diag_suppress 1094

#endif
