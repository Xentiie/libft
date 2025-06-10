/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpuid.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 02:05:23 by reclaire          #+#    #+#             */
/*   Updated: 2025/06/08 02:14:34 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cpuid_private.h"

extern void ft_cpuid(U32 reg, U32 sub, U32 out[4]);

U32 ft_cpuid_get_max_infos()
{
	U32 out[4];

	ft_cpuid(FT_CPUID_LEAF_HIGHEST_LEAF_AND_VENDOR_ID, 0, out);
	return out[_EAX];
}

U32 ft_cpuid_get_max_extended_infos()
{
	U32 reg;
	U32 sub;
	U32 out[4];

	reg = 0x80000000;
	sub = 0;
	ft_cpuid(reg, sub, out);

	return out[_EAX];
}

#if 0
struct s_cpuid_dump
{
	U32 reg;
	U32 sub;
	union
	{
		struct
		{
			U32 eax;
			U32 ebx;
			U32 ecx;
			U32 edx;
		};
		U32 data[4];
	};
};

struct s_cpuid_dump *ft_cpuid_dump(U64 *cnt)
{
	struct s_cpuid_dump *dump;
	struct s_cpuid_dump *dump_new;
	U32 reg;
	U32 sub;
	U32 max;
	U32 out[4];
	U64 dump_cnt;
	U64 dump_alloc;

	reg = 0;
	sub = 0;
	ft_cpuid(reg, sub, out);
	max = out[_EAX];

	dump_alloc = max;
	if (UNLIKELY((dump = ftalloc(sizeof(struct s_cpuid_dump) * dump_alloc)) == NULL))
		FT_RET_ERR(NULL, FT_EOMEM);

	while (reg <= max)
	{
		if (reg >= dump_alloc)
		{
			if (UNLIKELY((dump_new = ftalloc(sizeof(struct s_cpuid_dump) * dump_alloc * 2)) == NULL))
			{
				free(dump);
				FT_RET_ERR(NULL, FT_EOMEM);
			}
			ft_memcpy(dump_new, dump, sizeof(struct s_cpuid_dump) * dump_alloc);
			free(dump);
			dump = dump_new;
			dump_alloc *= 2;
		}

		if (reg == 4) /* cache */
		{
			
		}

		ft_cpuid(reg, sub, dump->data);
	}
}
#endif