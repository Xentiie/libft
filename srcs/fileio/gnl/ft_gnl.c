/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gnl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 20:17:38 by reclaire          #+#    #+#             */
/*   Updated: 2024/01/22 20:17:38 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#ifdef FT_FILEIO

typedef struct s_save
{
	file	fd;
	string	save;
}	t_save;

# if defined(FT_WIN32)


string	ft_gnl(file fd)
{
	
}

# elif defined(FT_LINUX) || defined(FT_OSX)



#endif


#endif