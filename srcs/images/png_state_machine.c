/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   png_state_machine.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 02:52:09 by reclaire          #+#    #+#             */
/*   Updated: 2025/02/13 02:52:19 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/compression/deflate.h"
#include "libft/compression/gzip.h"
#include "libft/crypt/crc.h"
#include "libft/images.h"
#include "libft/io.h"
#include "libft/maths.h"
#include "libft/strings.h"
#include "libft_int.h"

#include <stdio.h>
#include <stdlib.h>


