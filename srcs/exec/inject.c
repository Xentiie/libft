/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inject.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 02:04:01 by reclaire          #+#    #+#             */
/*   Updated: 2024/11/09 23:02:02 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define __USE_GNU

#include "libft_int.h"
#include "libft/strings.h"
#include "exec_int.h"

#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>

void ft_execinject(struct s_exec_infos *einfos, char *lib)
{
	
	string preload = (string)ft_getenv2("LD_PRELOAD", (const_string *)einfos->env);
	if (preload == NULL)
		preload = ft_strdup(lib);
	else
	{
		//TODO ft_sprintf
		string tmp = preload;
		preload = ft_strjoin(preload, " ");
		free(tmp);

		tmp = preload;
		preload = ft_strjoin(preload, lib);
		free(tmp);
	}

	string tmp = preload;
	preload = ft_strjoin("LD_PRELOAD=", tmp);
	free(tmp);

	ft_exec_editenv2(einfos, preload, NULL);
}
