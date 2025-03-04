/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_private.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 08:44:37 by reclaire          #+#    #+#             */
/*   Updated: 2024/12/29 16:00:01 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(FT_FILE_PRIVATE_H)
#define FT_FILE_PRIVATE_H

#define _GNU_SOURCE
#define _FT_FILE_DEF
#include "libft_int.h"
#include "libft/io.h"

#include <pthread.h>

#if defined(FT_OS_WIN)
#include <windows.h>
#endif

bool __parse_mode(const_string mode, bool *readable, bool *writeable, bool *append, bool *binary_mode);

#endif
