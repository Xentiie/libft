/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xsave.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 03:22:32 by reclaire          #+#    #+#             */
/*   Updated: 2025/03/10 03:20:02 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(FT_XSAVE_H)
#define FT_XSAVE_H

#include "libft/std.h"

#define FT_XGETBV_FLAGS 0

bool ft_xgetbv(U32 ecx, U64 *out);

struct s_xcr0_flags
{
	union
	{
		struct
		{
			U64 x87 : 1; // 'Must be 1'
			U64 sse : 1;
			U64 avx : 1;
			U64 bndreg : 1;
			U64 bndcsr : 1;
			U64 opmask : 1;
			U64 zmm_hi256 : 1;
			U64 hi16_zmm : 1;
			U64 pt : 1;
			U64 pkru : 1;
			U64 pasid : 1;
			U64 cet_u : 1;
			U64 cet_s : 1;
			U64 hdc : 1;
			U64 uintr : 1;
			U64 lbr : 1;
			U64 hwp : 1;
			U64 xtilecfg : 1;
			U64 xtiledata : 1;
			U64 apx : 1;
			U64 __pad : 44;
		};
		U64 flags;
	};
};

#endif