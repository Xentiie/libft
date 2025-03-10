/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:15:22 by reclaire          #+#    #+#             */
/*   Updated: 2025/03/11 00:35:43 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _GNU_SOURCE

#include "libft_int.h"

#include "libft/images.h"

#include <stdlib.h>

bool ft_init_image(t_image *img, t_iv2 size)
{
	img->size = size;
	if (UNLIKELY(posix_memalign((void **)&img->data, 32, sizeof(t_color) * (size.x * size.y)) != 0))
		FT_RET_ERR(FALSE, FT_EOMEM);
	img->pixels = (t_color *)img->data;

	FT_RET_OK(TRUE);
}

void ft_destroy_image(t_image *img) { free(img->data); }

extern t_iv4 ft_image_rect(t_image *img);
