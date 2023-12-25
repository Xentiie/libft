/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freesplit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 04:31:30 by reclaire          #+#    #+#             */
/*   Updated: 2023/09/26 22:16:54 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#ifdef FT_STRINGS
void	ft_freesplit(string *split)
{
	U64	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}
#endif