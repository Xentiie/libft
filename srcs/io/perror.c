/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perror.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 12:08:26 by reclaire          #+#    #+#             */
/*   Updated: 2025/04/03 12:09:12 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/io.h"
#include "libft/strings.h"

void ft_perror(const_string str)
{
	ft_fprintf(ft_fstderr, "%s: %s: %s\n", ft_argv[0], str, ft_strerror2());
}
