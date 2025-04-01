/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xgetbv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 03:05:23 by reclaire          #+#    #+#             */
/*   Updated: 2025/04/01 04:08:14 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_int.h"

#include "libft/sys/xsave.h"
#include "libft/sys/cpuid.h"
#include "libft/std.h"

bool ft_xgetbv(U32 ecx, U64 *out)
{
	U32 cpuid_out[4];
	struct s_cpuid_flags *flags;
	U32 maxinfos;

	flags = ft_cpuid_get_cached_flags();
	if (!flags->osxsave || !flags->xsave ||
		ft_cpuid_get_max_infos() < 0x0D)
		FT_RET_ERR(FALSE, FT_EINVOP);

	if (ecx == 1)
	{
		maxinfos = ft_cpuid_get_max_infos();
		if (maxinfos < 0x0D)
			FT_RET_ERR(0, FT_ENOENT);
		ft_cpuid(0x0D, 1, cpuid_out);
		if ((cpuid_out[0] & 0x4) == 0)
			FT_RET_ERR(FALSE, FT_EINVVAL);
	}
	else if (ecx != 0)
		FT_RET_ERR(FALSE, FT_EINVVAL);

	asm(
		"xgetbv\n"
		"shl rdx, 32\n"
		"or  rdx, rax\n"
		"mov QWORD PTR [%0], rdx\n" : : "r"(out),
										"c"(ecx) : "rdx", "rax");

	FT_RET_OK(TRUE);
}
