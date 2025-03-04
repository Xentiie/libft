/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cache.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 03:49:03 by reclaire          #+#    #+#             */
/*   Updated: 2025/02/19 20:07:35 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cpuid_private.h"

#include "libft/limits.h"

#include <stdlib.h>

union _u_cpuid_cache_tlb
{
	struct s_cpuid_cache c;
	struct s_cpuid_tlb t;
};

static S16 table_lookup(U8 v, union _u_cpuid_cache_tlb *o);

bool ft_cpuid_get_cache_tlb_info(U32 maxinfos, U64 cpuinfos, struct s_cpuid_ctlb_infos *infos)
{
	U32 out[4];
	U8 *bytes;
	U8 tlb_alloc;
	U8 cache_alloc;
	void *newptr;
	union _u_cpuid_cache_tlb v;

	ft_bzero(infos, sizeof(struct s_cpuid_ctlb_infos));
	return FALSE;
/* grows `infos->caches` if needed, returns the address to the next free space and increases `infos->cache_cnt` */
#define get_next_cache_ptr() ({                                                                  \
	if (infos->cache_cnt >= cache_alloc)                                                         \
	{                                                                                            \
		if (cache_alloc == 0)                                                                    \
			cache_alloc = 1;                                                                     \
		if (UNLIKELY((newptr = malloc(sizeof(struct s_cpuid_cache) * cache_alloc * 2)) == NULL)) \
			FT_RET_ERR(FALSE, FT_EOMEM);                                                         \
		ft_memcpy(newptr, infos->caches, sizeof(struct s_cpuid_cache) * infos->cache_cnt);       \
		free(infos->caches);                                                                     \
		infos->caches = newptr;                                                                  \
		cache_alloc *= 2;                                                                        \
	}                                                                                            \
	&infos->caches[infos->cache_cnt++];                                                          \
})

/* grows `infos->tlbs` if needed, returns the address to the next free space and increases `infos->tlb_cnt` */
#define get_next_tlb_ptr() ({                                                                \
	if (infos->tlb_cnt >= tlb_alloc)                                                         \
	{                                                                                        \
		if (tlb_alloc == 0)                                                                  \
			tlb_alloc = 1;                                                                   \
		if (UNLIKELY((newptr = malloc(sizeof(struct s_cpuid_tlb) * tlb_alloc * 2)) == NULL)) \
			FT_RET_ERR(FALSE, FT_EOMEM);                                                     \
		ft_memcpy(newptr, infos->tlbs, sizeof(struct s_cpuid_tlb) * infos->tlb_cnt);         \
		free(infos->tlbs);                                                                   \
		infos->tlbs = newptr;                                                                \
		tlb_alloc *= 2;                                                                      \
	}                                                                                        \
	&infos->tlbs[infos->tlb_cnt++];                                                          \
})

	if (FT_CPUID_CACHE_INFO_AND_TLB_INFO >= maxinfos)
		FT_RET_ERR(FALSE, FT_ENOENT);
	ft_cpuid(FT_CPUID_CACHE_INFO_AND_TLB_INFO, 0, out);
	infos->raw[0] = out[0];
	infos->raw[1] = out[1];
	infos->raw[2] = out[2];
	infos->raw[3] = out[3];

	if ((out[_EAX] & 0xFF) != 0x1)
		FT_RET_ERR(FALSE, FT_EINVOP);

	cache_alloc = 0;
	infos->cache_cnt = 0;
	infos->caches = NULL;

	tlb_alloc = 0;
	infos->tlb_cnt = 0;
	infos->tlbs = NULL;

	infos->no_l3_cache = FALSE;
	infos->prefetchnta_preferred_stride_64 = 0;
	infos->prefetchnta_preferred_stride_128 = 0;

	bytes = (U8 *)(out);
	for (U8 i = 1; i < 8; i++)
	{
		switch (table_lookup(bytes[i], &v))
		{
		case 0:
		default:
			printf("unknown: %#x\n", bytes[i]);
			break;

		case -1: /* tlb */
			*get_next_tlb_ptr() = v.t;
			break;

		case -2: /* cache */
			*get_next_cache_ptr() = v.c;
			break;

		case 0x40:
			infos->no_l3_cache = TRUE;
			break;

		case 0x49:
			if (FT_CPUID_GET_FAMILY_ID(cpuinfos) == 0x0F && FT_CPUID_GET_MODEL_ID(cpuinfos) == 6)
				*get_next_cache_ptr() = (struct s_cpuid_cache){.level = 1, .type = FT_CPUID_CACHE_UNIFIED, .size = 4194304, .line_size = 64, .associativity = 16};
			break;
		}
	}

	FT_RET_OK(TRUE);
}


//TODO: fix plus 'unknown string'
/* Auto-generated by build-aux/cpuid/parse_cache_tlb_table.py. Depends on "cpuid_private.h" */
static S16 table_lookup(U8 v, union _u_cpuid_cache_tlb *o)
{
	switch (v)
	{
	case 0x01:
		o->t = (struct s_cpuid_tlb){.is_data = FALSE, .entries_cnt = 32, .page_size = 4096, .associativity = 4};
		return -1;
	case 0x02:
		o->t = (struct s_cpuid_tlb){.is_data = FALSE, .entries_cnt = 2, .page_size = 4194304, .associativity = U8_MAX};
		return -1;
	case 0x03:
		o->t = (struct s_cpuid_tlb){.is_data = TRUE, .entries_cnt = 64, .page_size = 4096, .associativity = 4};
		return -1;
	case 0x04:
		o->t = (struct s_cpuid_tlb){.is_data = TRUE, .entries_cnt = 8, .page_size = 4194304, .associativity = 4};
		return -1;
	case 0x05:
		o->t = (struct s_cpuid_tlb){.is_data = TRUE, .entries_cnt = 32, .page_size = 4194304, .associativity = 4};
		return -1;
	case 0x06:
		o->c = (struct s_cpuid_cache){.level = 1, .type = FT_CPUID_CACHE_INSTRUCTION, .size = 8192, .line_size = 32, .associativity = 4};
		return -2;
	case 0x08:
		o->c = (struct s_cpuid_cache){.level = 1, .type = FT_CPUID_CACHE_INSTRUCTION, .size = 16384, .line_size = 32, .associativity = 4};
		return -2;
	case 0x09:
		o->c = (struct s_cpuid_cache){.level = 1, .type = FT_CPUID_CACHE_INSTRUCTION, .size = 32768, .line_size = 64, .associativity = 4};
		return -2;
	case 0x0A:
		o->c = (struct s_cpuid_cache){.level = 1, .type = FT_CPUID_CACHE_DATA, .size = 8192, .line_size = 32, .associativity = 2};
		return -2;
	case 0x0B:
		o->t = (struct s_cpuid_tlb){.is_data = FALSE, .entries_cnt = 4, .page_size = 4194304, .associativity = U8_MAX};
		return -1;
	case 0x0C:
		o->c = (struct s_cpuid_cache){.level = 1, .type = FT_CPUID_CACHE_DATA, .size = 16384, .line_size = 32, .associativity = 4};
		return -2;
	case 0x0D:
		o->c = (struct s_cpuid_cache){.level = 1, .type = FT_CPUID_CACHE_DATA, .size = 16384, .line_size = 64, .associativity = 4};
		return -2;
	case 0x0E:
		o->c = (struct s_cpuid_cache){.level = 1, .type = FT_CPUID_CACHE_DATA, .size = 24576, .line_size = 64, .associativity = 6};
		return -2;
	case 0x10:
		o->c = (struct s_cpuid_cache){.level = 1, .type = FT_CPUID_CACHE_DATA, .size = 16384, .line_size = 32, .associativity = 4};
		return -2;
	case 0x15:
		o->c = (struct s_cpuid_cache){.level = 1, .type = FT_CPUID_CACHE_INSTRUCTION, .size = 16384, .line_size = 32, .associativity = 4};
		return -2;
	case 0x1A:
		o->c = (struct s_cpuid_cache){.level = 2, .type = FT_CPUID_CACHE_UNIFIED, .size = 98304, .line_size = 64, .associativity = 6};
		return -2;
	case 0x1D:
		o->c = (struct s_cpuid_cache){.level = 2, .type = FT_CPUID_CACHE_UNIFIED, .size = 131072, .line_size = 64, .associativity = 2};
		return -2;
	case 0x21:
		o->c = (struct s_cpuid_cache){.level = 2, .type = FT_CPUID_CACHE_UNIFIED, .size = 262144, .line_size = 64, .associativity = 8};
		return -2;
	case 0x22:
		o->c = (struct s_cpuid_cache){.level = 3, .type = FT_CPUID_CACHE_UNIFIED, .size = 524288, .line_size = 64, .associativity = 4};
		return -2;
	case 0x23:
		o->c = (struct s_cpuid_cache){.level = 3, .type = FT_CPUID_CACHE_UNIFIED, .size = 1048576, .line_size = 64, .associativity = 8};
		return -2;
	case 0x24:
		o->c = (struct s_cpuid_cache){.level = 2, .type = FT_CPUID_CACHE_UNIFIED, .size = 1048576, .line_size = 64, .associativity = 16};
		return -2;
	case 0x25:
		o->c = (struct s_cpuid_cache){.level = 3, .type = FT_CPUID_CACHE_UNIFIED, .size = 2097152, .line_size = 64, .associativity = 8};
		return -2;
	case 0x26:
		/* unknown string: */
		/* '(128-byteprefetch)[e]' */
		/* '(128-byteprefetch)[e]' */
		return v;
	case 0x27:
		/* unknown string: */
		/* '(128-byteprefetch)[e]' */
		/* '(128-byteprefetch)[e]' */
		return v;
	case 0x28:
		/* unknown string: */
		/* '(128-byteprefetch)[e]' */
		/* '(128-byteprefetch)[e]' */
		return v;
	case 0x29:
		o->c = (struct s_cpuid_cache){.level = 3, .type = FT_CPUID_CACHE_UNIFIED, .size = 4194304, .line_size = 64, .associativity = 8};
		return -2;
	case 0x2C:
		o->c = (struct s_cpuid_cache){.level = 1, .type = FT_CPUID_CACHE_DATA, .size = 32768, .line_size = 64, .associativity = 8};
		return -2;
	case 0x30:
		o->c = (struct s_cpuid_cache){.level = 1, .type = FT_CPUID_CACHE_INSTRUCTION, .size = 32768, .line_size = 64, .associativity = 8};
		return -2;
	case 0x39:
		o->c = (struct s_cpuid_cache){.level = 2, .type = FT_CPUID_CACHE_UNIFIED, .size = 131072, .line_size = 64, .associativity = 4};
		return -2;
	case 0x3A:
		o->c = (struct s_cpuid_cache){.level = 2, .type = FT_CPUID_CACHE_UNIFIED, .size = 196608, .line_size = 64, .associativity = 6};
		return -2;
	case 0x3B:
		o->c = (struct s_cpuid_cache){.level = 2, .type = FT_CPUID_CACHE_UNIFIED, .size = 131072, .line_size = 64, .associativity = 2};
		return -2;
	case 0x3C:
		o->c = (struct s_cpuid_cache){.level = 2, .type = FT_CPUID_CACHE_UNIFIED, .size = 262144, .line_size = 64, .associativity = 4};
		return -2;
	case 0x3D:
		o->c = (struct s_cpuid_cache){.level = 2, .type = FT_CPUID_CACHE_UNIFIED, .size = 393216, .line_size = 64, .associativity = 6};
		return -2;
	case 0x3E:
		o->c = (struct s_cpuid_cache){.level = 2, .type = FT_CPUID_CACHE_UNIFIED, .size = 524288, .line_size = 64, .associativity = 4};
		return -2;
	case 0x3F:
		o->c = (struct s_cpuid_cache){.level = 2, .type = FT_CPUID_CACHE_UNIFIED, .size = 262144, .line_size = 64, .associativity = 2};
		return -2;
	case 0x40:
		/* unknown string: */
		/* 'noL3cachepresent' */
		/* 'no L3 cachepresent' */
		return v;
	case 0x41:
		o->c = (struct s_cpuid_cache){.level = 2, .type = FT_CPUID_CACHE_UNIFIED, .size = 131072, .line_size = 32, .associativity = 4};
		return -2;
	case 0x42:
		o->c = (struct s_cpuid_cache){.level = 2, .type = FT_CPUID_CACHE_UNIFIED, .size = 262144, .line_size = 32, .associativity = 4};
		return -2;
	case 0x43:
		o->c = (struct s_cpuid_cache){.level = 2, .type = FT_CPUID_CACHE_UNIFIED, .size = 524288, .line_size = 32, .associativity = 4};
		return -2;
	case 0x44:
		o->c = (struct s_cpuid_cache){.level = 2, .type = FT_CPUID_CACHE_UNIFIED, .size = 1048576, .line_size = 32, .associativity = 4};
		return -2;
	case 0x45:
		o->c = (struct s_cpuid_cache){.level = 2, .type = FT_CPUID_CACHE_UNIFIED, .size = 2097152, .line_size = 32, .associativity = 4};
		return -2;
	case 0x46:
		o->c = (struct s_cpuid_cache){.level = 3, .type = FT_CPUID_CACHE_UNIFIED, .size = 4194304, .line_size = 64, .associativity = 4};
		return -2;
	case 0x47:
		o->c = (struct s_cpuid_cache){.level = 3, .type = FT_CPUID_CACHE_UNIFIED, .size = 8388608, .line_size = 64, .associativity = 8};
		return -2;
	case 0x48:
		o->c = (struct s_cpuid_cache){.level = 2, .type = FT_CPUID_CACHE_UNIFIED, .size = 3145728, .line_size = 64, .associativity = 12};
		return -2;
	case 0x49:
		/* unknown string: */
		/* 'L2C/L3C:[i]4M,16A,64L' */
		/* 'L2C/L3C:[i]4M, 16A, 64L' */
		return v;
	case 0x4A:
		o->c = (struct s_cpuid_cache){.level = 3, .type = FT_CPUID_CACHE_UNIFIED, .size = 6291456, .line_size = 64, .associativity = 12};
		return -2;
	case 0x4B:
		o->c = (struct s_cpuid_cache){.level = 3, .type = FT_CPUID_CACHE_UNIFIED, .size = 8388608, .line_size = 64, .associativity = 16};
		return -2;
	case 0x4C:
		o->c = (struct s_cpuid_cache){.level = 3, .type = FT_CPUID_CACHE_UNIFIED, .size = 12582912, .line_size = 64, .associativity = 12};
		return -2;
	case 0x4D:
		o->c = (struct s_cpuid_cache){.level = 3, .type = FT_CPUID_CACHE_UNIFIED, .size = 16777216, .line_size = 64, .associativity = 16};
		return -2;
	case 0x4E:
		o->c = (struct s_cpuid_cache){.level = 2, .type = FT_CPUID_CACHE_UNIFIED, .size = 6291456, .line_size = 64, .associativity = 24};
		return -2;
	case 0x4F:
		/* unknown string: */
		/* 'ITLB:32E,4Kp[j]' */
		/* 'ITLB: 32E,4Kp[j]' */
		return v;
	case 0x50:
		/* unknown string: */
		/* 'ITLB:64E,FA,4K/2M/4Mp' */
		/* 'ITLB: 64E,FA,4K/2M/4Mp' */
		return v;
	case 0x51:
		/* unknown string: */
		/* 'ITLB:128E,FA,4K/2M/4Mp' */
		/* 'ITLB: 128E,FA,4K/2M/4Mp' */
		return v;
	case 0x52:
		/* unknown string: */
		/* 'ITLB:256E,FA,4K/2M/4Mp' */
		/* 'ITLB: 256E,FA,4K/2M/4Mp' */
		return v;
	case 0x55:
		/* unknown string: */
		/* 'ITLB:7E,2M/4Mp,FA' */
		/* 'ITLB: 7E,2M/4Mp, FA' */
		return v;
	case 0x56:
		o->t = (struct s_cpuid_tlb){.is_data = TRUE, .entries_cnt = 16, .page_size = 4194304, .associativity = 4};
		return -1;
	case 0x57:
		o->t = (struct s_cpuid_tlb){.is_data = TRUE, .entries_cnt = 16, .page_size = 4096, .associativity = 4};
		return -1;
	case 0x59:
		o->t = (struct s_cpuid_tlb){.is_data = TRUE, .entries_cnt = 16, .page_size = 4096, .associativity = U8_MAX};
		return -1;
	case 0x5A:
		/* unknown string: */
		/* 'DTLB:32E,2M/4Mp,4A' */
		/* 'DTLB: 32E,2M/4Mp, 4A' */
		return v;
	case 0x5B:
		/* unknown string: */
		/* 'DTLB:64E4K/4Mp,FA' */
		/* 'DTLB: 64E4K/4Mp, FA' */
		return v;
	case 0x5C:
		/* unknown string: */
		/* 'DTLB:128E,4K/4Mp,FA' */
		/* 'DTLB: 128E,4K/4Mp, FA' */
		return v;
	case 0x5D:
		/* unknown string: */
		/* 'DTLB:256E,4K/4Mp,FA' */
		/* 'DTLB: 256E,4K/4Mp, FA' */
		return v;
	case 0x60:
		o->c = (struct s_cpuid_cache){.level = 1, .type = FT_CPUID_CACHE_DATA, .size = 16384, .line_size = 64, .associativity = 8};
		return -2;
	case 0x61:
		o->t = (struct s_cpuid_tlb){.is_data = FALSE, .entries_cnt = 48, .page_size = 4096, .associativity = U8_MAX};
		return -1;
	case 0x63:
		/* unknown string: */
		/* 'TwoDTLBs:32E,2M/4Mp,4A+4E,1Gp,FA' */
		/* 'Two DTLBs:32E, 2M/4Mp, 4A+ 4E, 1Gp, FA' */
		return v;
	case 0x64:
		o->t = (struct s_cpuid_tlb){.is_data = TRUE, .entries_cnt = 512, .page_size = 4096, .associativity = 4};
		return -1;
	case 0x66:
		o->c = (struct s_cpuid_cache){.level = 1, .type = FT_CPUID_CACHE_DATA, .size = 8192, .line_size = 64, .associativity = 4};
		return -2;
	case 0x67:
		o->c = (struct s_cpuid_cache){.level = 1, .type = FT_CPUID_CACHE_DATA, .size = 16384, .line_size = 64, .associativity = 4};
		return -2;
	case 0x68:
		o->c = (struct s_cpuid_cache){.level = 1, .type = FT_CPUID_CACHE_DATA, .size = 32768, .line_size = 64, .associativity = 4};
		return -2;
	case 0x6A:
		o->t = (struct s_cpuid_tlb){.is_data = TRUE, .entries_cnt = 64, .page_size = 4096, .associativity = 8};
		return -1;
	case 0x6B:
		o->t = (struct s_cpuid_tlb){.is_data = TRUE, .entries_cnt = 256, .page_size = 4096, .associativity = 8};
		return -1;
	case 0x6C:
		/* unknown string: */
		/* 'DTLB:128E,2M/4Mp,8A' */
		/* 'DTLB: 128E,2M/4Mp, 8A' */
		return v;
	case 0x6D:
		/* unknown string: */
		/* 'DTLB:16E,1Gp,FA' */
		/* 'DTLB: 16E,1Gp, FA' */
		return v;
	case 0x70:
		/* unknown string: */
		/* 'Tracecache,12K-μop,8A[k]' */
		/* 'Trace cache,12K-μop, 8A[k]' */
		return v;
	case 0x71:
		/* unknown string: */
		/* 'Tracecache,16K-μop,8A' */
		/* 'Trace cache,16K-μop, 8A' */
		return v;
	case 0x72:
		/* unknown string: */
		/* 'Tracecache,32K-μop,8A' */
		/* 'Trace cache,32K-μop, 8A' */
		return v;
	case 0x73:
		/* unknown string: */
		/* 'Tracecache,64K-μop,8A[f]' */
		/* 'Trace cache,64K-μop, 8A[f]' */
		return v;
	case 0x74:
		/* unknown string: */
		/* '[h]' */
		/* '[h]' */
		return v;
	case 0x76:
		/* unknown string: */
		/* 'ITLB:8E,2M/4Mp,FA[l]' */
		/* 'ITLB: 8E,2M/4Mp, FA[l]' */
		return v;
	case 0x77:
		o->c = (struct s_cpuid_cache){.level = 1, .type = FT_CPUID_CACHE_INSTRUCTION, .size = 16384, .line_size = 64, .associativity = 4};
		return -2;
	case 0x78:
		o->c = (struct s_cpuid_cache){.level = 2, .type = FT_CPUID_CACHE_UNIFIED, .size = 1048576, .line_size = 64, .associativity = 4};
		return -2;
	case 0x79:
		o->c = (struct s_cpuid_cache){.level = 2, .type = FT_CPUID_CACHE_UNIFIED, .size = 131072, .line_size = 64, .associativity = 8};
		return -2;
	case 0x7A:
		o->c = (struct s_cpuid_cache){.level = 2, .type = FT_CPUID_CACHE_UNIFIED, .size = 262144, .line_size = 64, .associativity = 8};
		return -2;
	case 0x7B:
		o->c = (struct s_cpuid_cache){.level = 2, .type = FT_CPUID_CACHE_UNIFIED, .size = 524288, .line_size = 64, .associativity = 8};
		return -2;
	case 0x7C:
		o->c = (struct s_cpuid_cache){.level = 2, .type = FT_CPUID_CACHE_UNIFIED, .size = 1048576, .line_size = 64, .associativity = 8};
		return -2;
	case 0x7D:
		o->c = (struct s_cpuid_cache){.level = 2, .type = FT_CPUID_CACHE_UNIFIED, .size = 2097152, .line_size = 64, .associativity = 8};
		return -2;
	case 0x7E:
		o->c = (struct s_cpuid_cache){.level = 2, .type = FT_CPUID_CACHE_UNIFIED, .size = 262144, .line_size = 128, .associativity = 8};
		return -2;
	case 0x7F:
		o->c = (struct s_cpuid_cache){.level = 2, .type = FT_CPUID_CACHE_UNIFIED, .size = 524288, .line_size = 64, .associativity = 2};
		return -2;
	case 0x80:
		o->c = (struct s_cpuid_cache){.level = 2, .type = FT_CPUID_CACHE_UNIFIED, .size = 524288, .line_size = 64, .associativity = 8};
		return -2;
	case 0x81:
		o->c = (struct s_cpuid_cache){.level = 2, .type = FT_CPUID_CACHE_UNIFIED, .size = 131072, .line_size = 32, .associativity = 8};
		return -2;
	case 0x82:
		o->c = (struct s_cpuid_cache){.level = 2, .type = FT_CPUID_CACHE_UNIFIED, .size = 262144, .line_size = 32, .associativity = 8};
		return -2;
	case 0x83:
		o->c = (struct s_cpuid_cache){.level = 2, .type = FT_CPUID_CACHE_UNIFIED, .size = 524288, .line_size = 32, .associativity = 8};
		return -2;
	case 0x84:
		o->c = (struct s_cpuid_cache){.level = 2, .type = FT_CPUID_CACHE_UNIFIED, .size = 1048576, .line_size = 32, .associativity = 8};
		return -2;
	case 0x85:
		o->c = (struct s_cpuid_cache){.level = 2, .type = FT_CPUID_CACHE_UNIFIED, .size = 2097152, .line_size = 32, .associativity = 8};
		return -2;
	case 0x86:
		o->c = (struct s_cpuid_cache){.level = 2, .type = FT_CPUID_CACHE_UNIFIED, .size = 524288, .line_size = 64, .associativity = 4};
		return -2;
	case 0x87:
		o->c = (struct s_cpuid_cache){.level = 2, .type = FT_CPUID_CACHE_UNIFIED, .size = 1048576, .line_size = 64, .associativity = 8};
		return -2;
	case 0x88:
		o->c = (struct s_cpuid_cache){.level = 3, .type = FT_CPUID_CACHE_UNIFIED, .size = 2097152, .line_size = 64, .associativity = 4};
		return -2;
	case 0x89:
		o->c = (struct s_cpuid_cache){.level = 3, .type = FT_CPUID_CACHE_UNIFIED, .size = 4194304, .line_size = 64, .associativity = 4};
		return -2;
	case 0x8A:
		o->c = (struct s_cpuid_cache){.level = 3, .type = FT_CPUID_CACHE_UNIFIED, .size = 8388608, .line_size = 64, .associativity = 4};
		return -2;
	case 0x8D:
		o->c = (struct s_cpuid_cache){.level = 3, .type = FT_CPUID_CACHE_UNIFIED, .size = 3145728, .line_size = 128, .associativity = 12};
		return -2;
	case 0x90:
		/* unknown string: */
		/* '(ITLB:64E,FA,4K-256Mp)[c]' */
		/* '(ITLB: 64E,FA,4K-256Mp)[c]' */
		return v;
	case 0x96:
		/* unknown string: */
		/* '(DTLB:32E,FA,4K-256Mp)[c]' */
		/* '(DTLB: 32E,FA,4K-256Mp)[c]' */
		return v;
	case 0x9B:
		/* unknown string: */
		/* '(DTLB:96E,FA,4K-256Mp)[c]' */
		/* '(DTLB: 96E,FA,4K-256Mp)[c]' */
		return v;
	case 0xA0:
		o->t = (struct s_cpuid_tlb){.is_data = TRUE, .entries_cnt = 32, .page_size = 4096, .associativity = U8_MAX};
		return -1;
	case 0xB0:
		o->t = (struct s_cpuid_tlb){.is_data = FALSE, .entries_cnt = 128, .page_size = 4096, .associativity = 4};
		return -1;
	case 0xB1:
		/* unknown string: */
		/* 'ITLB:8E,2M/4Mp,4A[o]' */
		/* 'ITLB: 8E,2M/4Mp, 4A[o]' */
		return v;
	case 0xB2:
		o->t = (struct s_cpuid_tlb){.is_data = FALSE, .entries_cnt = 64, .page_size = 4096, .associativity = 4};
		return -1;
	case 0xB3:
		o->t = (struct s_cpuid_tlb){.is_data = TRUE, .entries_cnt = 128, .page_size = 4096, .associativity = 4};
		return -1;
	case 0xB4:
		o->t = (struct s_cpuid_tlb){.is_data = TRUE, .entries_cnt = 256, .page_size = 4096, .associativity = 4};
		return -1;
	case 0xB5:
		o->t = (struct s_cpuid_tlb){.is_data = FALSE, .entries_cnt = 64, .page_size = 4096, .associativity = 8};
		return -1;
	case 0xB6:
		o->t = (struct s_cpuid_tlb){.is_data = FALSE, .entries_cnt = 128, .page_size = 4096, .associativity = 8};
		return -1;
	case 0xBA:
		o->t = (struct s_cpuid_tlb){.is_data = TRUE, .entries_cnt = 64, .page_size = 4096, .associativity = 4};
		return -1;
	case 0xC0:
		/* unknown string: */
		/* 'DTLB:8E,4K/4Mp,4A' */
		/* 'DTLB: 8E,4K/4Mp, 4A' */
		return v;
	case 0xC1:
		/* unknown string: */
		/* 'L2TLB:1024E,4K/2Mp,8A' */
		/* 'L2TLB: 1024E,4K/2Mp, 8A' */
		return v;
	case 0xC2:
		/* unknown string: */
		/* 'DTLB:16E,2M/4Mp,4A[83]' */
		/* 'DTLB: 16E,2M/4Mp, 4A[83]' */
		return v;
	case 0xC3:
		/* unknown string: */
		/* 'TwoL2STLBs:1536E,4K/2Mp,6A[p]+16E,1Gp,4A' */
		/* 'Two L2 STLBs:1536E, 4K/2Mp, 6A[p]+ 16E, 1Gp, 4A' */
		return v;
	case 0xC4:
		/* unknown string: */
		/* 'DTLB:32E,2M/4Mp,4A' */
		/* 'DTLB: 32E,2M/4Mp, 4A' */
		return v;
	case 0xCA:
		/* unknown string: */
		/* 'L2TLB:512E,4Kp,4A' */
		/* 'L2TLB: 512E,4Kp, 4A' */
		return v;
	case 0xD0:
		o->c = (struct s_cpuid_cache){.level = 3, .type = FT_CPUID_CACHE_UNIFIED, .size = 524288, .line_size = 64, .associativity = 4};
		return -2;
	case 0xD1:
		o->c = (struct s_cpuid_cache){.level = 3, .type = FT_CPUID_CACHE_UNIFIED, .size = 1048576, .line_size = 64, .associativity = 4};
		return -2;
	case 0xD2:
		o->c = (struct s_cpuid_cache){.level = 3, .type = FT_CPUID_CACHE_UNIFIED, .size = 2097152, .line_size = 64, .associativity = 4};
		return -2;
	case 0xD6:
		o->c = (struct s_cpuid_cache){.level = 3, .type = FT_CPUID_CACHE_UNIFIED, .size = 1048576, .line_size = 64, .associativity = 8};
		return -2;
	case 0xD7:
		o->c = (struct s_cpuid_cache){.level = 3, .type = FT_CPUID_CACHE_UNIFIED, .size = 2097152, .line_size = 64, .associativity = 8};
		return -2;
	case 0xD8:
		o->c = (struct s_cpuid_cache){.level = 3, .type = FT_CPUID_CACHE_UNIFIED, .size = 4194304, .line_size = 64, .associativity = 8};
		return -2;
	case 0xDC:
		/* unknown string: */
		/* 'L3C:1.5M,12A,64L' */
		/* 'L3C: 1.5M,12A, 64L' */
		return v;
	case 0xDD:
		o->c = (struct s_cpuid_cache){.level = 3, .type = FT_CPUID_CACHE_UNIFIED, .size = 3145728, .line_size = 64, .associativity = 12};
		return -2;
	case 0xDE:
		o->c = (struct s_cpuid_cache){.level = 3, .type = FT_CPUID_CACHE_UNIFIED, .size = 6291456, .line_size = 64, .associativity = 12};
		return -2;
	case 0xE2:
		o->c = (struct s_cpuid_cache){.level = 3, .type = FT_CPUID_CACHE_UNIFIED, .size = 2097152, .line_size = 64, .associativity = 16};
		return -2;
	case 0xE3:
		o->c = (struct s_cpuid_cache){.level = 3, .type = FT_CPUID_CACHE_UNIFIED, .size = 4194304, .line_size = 64, .associativity = 16};
		return -2;
	case 0xE4:
		o->c = (struct s_cpuid_cache){.level = 3, .type = FT_CPUID_CACHE_UNIFIED, .size = 8388608, .line_size = 64, .associativity = 16};
		return -2;
	case 0xEA:
		o->c = (struct s_cpuid_cache){.level = 3, .type = FT_CPUID_CACHE_UNIFIED, .size = 12582912, .line_size = 64, .associativity = 24};
		return -2;
	case 0xEB:
		o->c = (struct s_cpuid_cache){.level = 3, .type = FT_CPUID_CACHE_UNIFIED, .size = 18874368, .line_size = 64, .associativity = 24};
		return -2;
	case 0xEC:
		o->c = (struct s_cpuid_cache){.level = 3, .type = FT_CPUID_CACHE_UNIFIED, .size = 25165824, .line_size = 64, .associativity = 24};
		return -2;
	case 0xF0:
		/* unknown string: */
		/* '64-byteprefetch[q]' */
		/* '64-byteprefetch[q]' */
		return v;
	case 0xF1:
		/* unknown string: */
		/* '128-byteprefetch[q]' */
		/* '128-byteprefetch[q]' */
		return v;
	case 0xFE:
		/* unknown string: */
		/* 'Leaf2hasnoTLBinfo,useleaf18h' */
		/* 'Leaf 2 hasno TLB info,use leaf 18h' */
		return v;
	case 0xFF:
		/* unknown string: */
		/* 'Leaf2hasnocacheinfo,useleaf4' */
		/* 'Leaf 2 hasno cache info,use leaf 4' */
		return v;
	default:
		return 0;
	}
}
