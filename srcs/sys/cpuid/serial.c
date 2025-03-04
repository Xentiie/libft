/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serial.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 04:09:36 by reclaire          #+#    #+#             */
/*   Updated: 2025/02/18 04:19:39 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cpuid_private.h"

bool ft_cpuid_get_proc_serial(U32 maxinfos, enum e_cpuid_vendor vendor_id, U64 *serial)
{
	//TOOD: test
	U32 out[4];

	if (vendor_id != FT_CPUID_VENDOR_INTEL && vendor_id != FT_CPUID_VENDOR_TRANSMETA)
	{
		*serial = 0;
		FT_RET_ERR(FALSE, FT_EINVOP);
	}

	if (FT_CPUID_PROC_SERIAL >= maxinfos)
		FT_RET_ERR(FALSE, FT_ENOENT);
	ft_cpuid(FT_CPUID_PROC_SERIAL, 0, out);

	if (vendor_id == FT_CPUID_VENDOR_INTEL)
		*serial = (((U64)(out[_EBX])) << 32) | (out[_ECX]);
	else
		*serial = (((U64)(out[_EBX])) << 32) | (out[_EAX]);

	FT_RET_OK(TRUE);
}
