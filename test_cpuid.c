/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_cpuid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 16:25:48 by reclaire          #+#    #+#             */
/*   Updated: 2025/03/05 16:28:14 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/sys/cpuid.h"
#include "libft/strings.h"
#include "libft/io.h"

S32 main()
{
	U32 maxinfo;
	struct s_cpuid_flags flags;
	
	maxinfo = ft_cpuid_get_max_infos();
	if (!ft_cpuid_get_flags(maxinfo, &flags))
	{
		ft_fprintf(ft_fstderr, "%s: ft_cpuid_get_flags: %s\n", ft_argv[0], ft_strerror2());
		return 1;
	}

	

}
