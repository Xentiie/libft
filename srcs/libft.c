/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 04:01:02 by reclaire          #+#    #+#             */
/*   Updated: 2024/01/15 04:01:02 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_error_code		ft_errno;
const_string		ft_error_lookup_table[] = { //TODO
	"SUCCESS",
	"FT_ERROR",
	"FT_OMEM",
	"FT_BAD_FD",
	"FT_MAP_FULL",
	"FT_MAP_MISSING",
};