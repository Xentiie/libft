/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_private.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 08:44:37 by reclaire          #+#    #+#             */
/*   Updated: 2025/04/14 20:23:35 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(FT_FILE_PRIVATE_H)
#define FT_FILE_PRIVATE_H

#define _GNU_SOURCE
#include "libft_int.h"
#include "libft/io.h"
#include "libft/bits/filestream.h"

#include <pthread.h>

#if FT_OS_WINDOWS
#include <windows.h>
#endif

bool __parse_mode(const_string mode, bool *readable, bool *writeable, bool *append, bool *binary_mode);

#endif
