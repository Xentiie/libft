/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpuinfos.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 02:10:42 by reclaire          #+#    #+#             */
/*   Updated: 2025/02/19 04:07:52 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cpuid_private.h"

bool ft_cpuid_get_cpuinfos(U32 maxinfos, U64 *cpuinfos)
{
	U32 out[4];

	if (FT_CPUID_PROC_INFO_AND_FLAGS >= maxinfos)
		FT_RET_ERR(FALSE, FT_ENOENT);

	ft_cpuid(FT_CPUID_PROC_INFO_AND_FLAGS, 0, out);
	*cpuinfos = (out[_EAX] | (((U64)out[_EBX]) << 32));
	FT_RET_OK(TRUE);
}
