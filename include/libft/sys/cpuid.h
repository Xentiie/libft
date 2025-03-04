/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpuid.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 02:08:17 by reclaire          #+#    #+#             */
/*   Updated: 2025/02/19 18:31:38 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(FT_CPUID_H)
#define FT_CPUID_H

#include "libft/libft.h"

#define FT_CPUID_LEAF_HIGHEST_LEAF_AND_VENDOR_ID 0
#define FT_CPUID_PROC_INFO_AND_FLAGS 1
#define FT_CPUID_CACHE_INFO_AND_TLB_INFO 2
#define FT_CPUID_PROC_SERIAL 3
#define FT_CPUID_CACHE_HIERARCHY_AND_TOPOLOGY 4

/* Executes the `CPUID` instruction, with `reg` and `sub` as arguments, and outputs the result in `out` */
extern void ft_cpuid(U32 reg, U32 sub, U32 out[4]);

/* Returns the max `reg` value possible for `CPUID` (`ft_cpuid(0, 0)[EAX]`) */
extern U32 ft_cpuid_get_max_infos();

/* Returns the max `reg` value possible for `CPUID` for extended infos (`ft_cpuid(0x80000000, 0)[EAX]`)*/
extern U32 ft_cpuid_get_max_extended_infos();

enum __attribute__((packed)) e_cpuid_vendor
{
	FT_CPUID_VENDOR_UNKNOWN,
	FT_CPUID_VENDOR_INTEL,
	FT_CPUID_VENDOR_AMD,
	FT_CPUID_VENDOR_CYRIX,
	FT_CPUID_VENDOR_VIA,
	FT_CPUID_VENDOR_UMC,
	FT_CPUID_VENDOR_NEXGEN,
	FT_CPUID_VENDOR_RISE,
	FT_CPUID_VENDOR_TRANSMETA,
	FT_CPUID_VENDOR_SIS,
	FT_CPUID_VENDOR_NSC,
	FT_CPUID_VENDOR_VORTEX,
	FT_CPUID_VENDOR_RDC,
	FT_CPUID_VENDOR_HYGON,
	FT_CPUID_VENDOR_ZHAOXIN,
	__FT_CPUID_VENDOR_MAX,
};

/* Returns the vendor id, and fills in `true_name` the string returned by `CPUID`, if non-NULL (`ft_cpuid(0, 0)[EAX]`)*/
extern enum e_cpuid_vendor ft_cpuid_get_vendor(char true_name[13]);

/*
Returns the string associated with `vendor_id`
### On error
Sets ft_errno, and returns NULL.
### ft_errno
- FT_ENOENT if no string is associated with `vendor_id`
*/
const_string ft_cpuid_strvendor(enum e_cpuid_vendor vendor_id);

#define FT_CPUID_GET_STEPPING(cpuinfos)             (((cpuinfos) >> 0) & 0xF)
#define FT_CPUID_GET_MODEL_ID(cpuinfos)             (((cpuinfos) >> 4) & 0xF)
#define FT_CPUID_GET_FAMILY_ID(cpuinfos)            (((cpuinfos) >> 8) & 0xF)
#define FT_CPUID_GET_PROC_TYPE(cpuinfos)            (((cpuinfos) >> 12) & 0xF)
#define FT_CPUID_GET_EXT_MODEL_ID(cpuinfos)         (((cpuinfos) >> 16) & 0xF)
#define FT_CPUID_GET_EXT_FAMILY_ID(cpuinfos)        (((cpuinfos) >> 24) & 0xFF)
#define FT_CPUID_GET_BRAND_INDEX(cpuinfos)          (((cpuinfos) >> 32) & 0xFF)
#define FT_CPUID_GET_CLFLUSH_SIZE(cpuinfos)         (((cpuinfos) >> 40) & 0xFF)
#define FT_CPUID_GET_ADDRABLE_LOG_PROC_ID(cpuinfos) (((cpuinfos) >> 48) & 0xFF)
#define FT_CPUID_GET_LOCAL_APIC_ID(cpuinfos)        (((cpuinfos) >> 56) & 0xFF)

#define FT_CPUID_GET_TRUE_MODEL_ID(cpuinfos) ((FT_CPUID_GET_FAMILY_ID(cpuinfos) == 0x6 || FT_CPUID_GET_FAMILY_ID(cpuinfos) == 0xF) ? ((FT_CPUID_GET_EXT_MODEL_ID(cpuinfos) << 4) | FT_CPUID_GET_MODEL_ID(cpuinfos)) : FT_CPUID_GET_MODEL_ID(cpuinfos))
#define FT_CPUID_GET_TRUE_FAMILY_ID(cpuinfos) ((FT_CPUID_GET_FAMILY_ID(cpuinfos) == 0xF) ? (FT_CPUID_GET_EXT_FAMILY_ID(cpuinfos) + FT_CPUID_GET_FAMILY_ID(cpuinfos)) : FT_CPUID_GET_FAMILY_ID(cpuinfos))

/*
Fills `cpuinfos` by the CPU version infos returned by `CPUID` (`ft_cpuid(1, 0)[EAX]`).
### On error
Sets ft_errno, and returns FALSE.
### ft_errno
- FT_ENOENT if version infos are not available
*/
extern bool ft_cpuid_get_cpuinfos(U32 maxinfos, U64 *cpuinfos);

/* Returns the identifier of the flag (highest bit set) specified in `flgs` */
extern const_string ft_cpuid_strflg_short(U64 flgs);

/* Returns the description of the flag (highest bit set) specified in `flgs` */
extern const_string ft_cpuid_strflg_descr(U64 flgs);

/* FLAGS TO USE WITH `ft_cpuid_get_flags` */
#define FT_CPUID_FLG_FPU (1UL << 0)					/* Onboard x87 FPU */
#define FT_CPUID_FLG_VME (1UL << 1)					/* Virtual 8086 mode extensions (such as VIF, VIP, PVI) */
#define FT_CPUID_FLG_DE (1UL << 2)					/* Debugging extensions (CR4 bit 3) */
#define FT_CPUID_FLG_PSE (1UL << 3)					/* Page Size Extension (4 MB pages) */
#define FT_CPUID_FLG_TSC (1UL << 4)					/* Time Stamp Counter and RDTSC instruction */
#define FT_CPUID_FLG_MSR (1UL << 5)					/* Model-specific registers and RDMSR/WRMSR instructions */
#define FT_CPUID_FLG_PAE (1UL << 6)					/* Physical Address Extension */
#define FT_CPUID_FLG_MCE (1UL << 7)					/* Machine Check Exception */
#define FT_CPUID_FLG_CX8 (1UL << 8)					/* CMPXCHG8B (compare-and-swap) instruction */
#define FT_CPUID_FLG_APIC (1UL << 9)				/* Onboard Advanced Programmable Interrupt Controller */
#define FT_CPUID_FLG_SEP (1UL << 11)				/* SYSENTER and SYSEXIT fast system call instructions */
#define FT_CPUID_FLG_MTRR (1UL << 12)				/* Memory Type Range Registers */
#define FT_CPUID_FLG_PGE (1UL << 13)				/* Page Global Enable bit in CR4 */
#define FT_CPUID_FLG_MCA (1UL << 14)				/* Machine check architecture */
#define FT_CPUID_FLG_CMOV (1UL << 15)				/* Conditional move: CMOV, FCMOV and FCOMI instructions[h] */
#define FT_CPUID_FLG_PAT (1UL << 16)				/* Page Attribute Table */
#define FT_CPUID_FLG_PSE36 (1UL << 17)				/* 36-bit page size extension */
#define FT_CPUID_FLG_PSN (1UL << 18)				/* Processor Serial Number supported and enabled */
#define FT_CPUID_FLG_CLFSH (1UL << 19)				/* CLFLUSH cache line flush instruction (SSE2) */
#define FT_CPUID_FLG_NX (1UL << 20)					/* No-execute (NX) bit (Itanium only, reserved on other CPUs) */
#define FT_CPUID_FLG_DS (1UL << 21)					/* Debug store: save trace of executed jumps */
#define FT_CPUID_FLG_ACPI (1UL << 22)				/* Onboard thermal control MSRs for ACPI */
#define FT_CPUID_FLG_MMX (1UL << 23)				/* MMX instructions (64-bit SIMD) */
#define FT_CPUID_FLG_FXSR (1UL << 24)				/* FXSAVE, FXRSTOR instructions, CR4 bit 9 */
#define FT_CPUID_FLG_SSE (1UL << 25)				/* Streaming SIMD Extensions (SSE) instructions (aka "Katmai New Instructions"; 128-bit SIMD) */
#define FT_CPUID_FLG_SSE2 (1UL << 26)				/* SSE2 instructions */
#define FT_CPUID_FLG_SS (1UL << 27)					/* CPU cache implements self-snoop */
#define FT_CPUID_FLG_HTT (1UL << 28)				/* Max APIC IDs reserved field is Valid */
#define FT_CPUID_FLG_TM (1UL << 29)					/* Thermal monitor automatically limits temperature */
#define FT_CPUID_FLG_IA64 (1UL << 30)				/* IA64 processor emulating x86 */
#define FT_CPUID_FLG_PBE (1UL << 31)				/* Pending Break Enable (PBE# pin) wakeup capability */
#define FT_CPUID_FLG_SS3 (1UL << (32 + 0))			/* SSE3 (Prescott New Instructions - PNI) */
#define FT_CPUID_FLG_PCLMULQDQ (1UL << (32 + 1))	/* PCLMULQDQ (carry-less multiply) instruction */
#define FT_CPUID_FLG_DTES64 (1UL << (32 + 2))		/* 64-bit debug store (edx bit 21) */
#define FT_CPUID_FLG_MONITOR (1UL << (32 + 3))		/* MONITOR and MWAIT instructions (PNI) */
#define FT_CPUID_FLG_DSCPL (1UL << (32 + 4))		/* CPL qualified debug store */
#define FT_CPUID_FLG_VMX (1UL << (32 + 5))			/* Virtual Machine eXtensions */
#define FT_CPUID_FLG_SMX (1UL << (32 + 6))			/* Safer Mode Extensions (LaGrande) (GETSEC instruction) */
#define FT_CPUID_FLG_EST (1UL << (32 + 7))			/* Enhanced SpeedStep */
#define FT_CPUID_FLG_TM2 (1UL << (32 + 8))			/* Thermal Monitor 2 */
#define FT_CPUID_FLG_SSSE3 (1UL << (32 + 9))		/* Supplemental SSE3 instructions */
#define FT_CPUID_FLG_CNXTID (1UL << (32 + 10))		/* L1 Context ID */
#define FT_CPUID_FLG_SDBG (1UL << (32 + 11))		/* Silicon Debug interface */
#define FT_CPUID_FLG_FMA (1UL << (32 + 12))			/* Fused multiply-add (FMA3) */
#define FT_CPUID_FLG_CX16 (1UL << (32 + 13))		/* CMPXCHG16B instruction */
#define FT_CPUID_FLG_XTPR (1UL << (32 + 14))		/* Can disable sending task priority messages */
#define FT_CPUID_FLG_PDCM (1UL << (32 + 15))		/* Perfmon & debug capability */
#define FT_CPUID_FLG_PCID (1UL << (32 + 17))		/* Process context identifiers (CR4 bit 17) */
#define FT_CPUID_FLG_DCA (1UL << (32 + 18))			/* Direct cache access for DMA writes */
#define FT_CPUID_FLG_SEE41 (1UL << (32 + 19))		/* SSE4.1 instructions */
#define FT_CPUID_FLG_SSE42 (1UL << (32 + 20))		/* SSE4.2 instructions */
#define FT_CPUID_FLG_X2APIC (1UL << (32 + 21))		/* x2APIC (enhanced APIC) */
#define FT_CPUID_FLG_MOVBE (1UL << (32 + 22))		/* MOVBE instruction (big-endian) */
#define FT_CPUID_FLG_POPCNT (1UL << (32 + 23))		/* POPCNT instruction */
#define FT_CPUID_FLG_TSCDEADLINE (1UL << (32 + 24)) /* APIC implements one-shot operation using a TSC deadline value */
#define FT_CPUID_FLG_AESNI (1UL << (32 + 25))		/* AES instruction set */
#define FT_CPUID_FLG_XSAVE (1UL << (32 + 26))		/* Extensible processor state save/restore: XSAVE, XRSTOR, XSETBV, XGETBV instructions */
#define FT_CPUID_FLG_OSXSAVE (1UL << (32 + 27))		/* XSAVE enabled by OS */
#define FT_CPUID_FLG_AVX (1UL << (32 + 28))			/* Advanced Vector Extensions (256-bit SIMD) */
#define FT_CPUID_FLG_F16C (1UL << (32 + 29))		/* Floating-point conversion instructions to/from FP16 format */
#define FT_CPUID_FLG_RDRND (1UL << (32 + 30))		/* RDRAND (on-chip random number generator) feature */
#define FT_CPUID_FLG_HYPERVISOR (1UL << (32 + 31))	/* Hypervisor present (always zero on physical CPUs) */

/*
Fills `flags` with the flags returned by `CPUID` (`ft_cpuid(1, 0)[ECX/EDX]`)
### On error
Sets ft_errno, and returns FALSE.
### ft_errno
- FT_ENOENT if no flags informations are not available
*/
extern bool ft_cpuid_get_flags(U32 maxinfos, U64 *flags);

enum __attribute__((packed)) e_cpuid_cache_type
{
	FT_CPUID_CACHE_INSTRUCTION,
	FT_CPUID_CACHE_DATA,
	FT_CPUID_CACHE_UNIFIED,
};

struct s_cpuid_cache
{
	enum e_cpuid_cache_type type;
	U8 level; /* cache level */
	U64 size;
	U64 line_size;	   /* cache line size */
	U64 associativity; /* if `associativity == U8_MAX`, fully-associative */
};

struct s_cpuid_tlb
{
	bool is_data;	  /* TRUE if LTB is data TLB, FALSE if instruction TLB */
	U64 entries_cnt;  /* TLB entries */
	U64 page_size;	  /* TLB page-size */
	U64 associativity; /* if `associativity == U8_MAX`, fully-associative */
};

struct s_cpuid_ctlb_infos
{
	U32 raw[4];

	U8 cache_cnt;
	struct s_cpuid_cache *caches;

	U8 tlb_cnt;
	struct s_cpuid_tlb *tlbs;

	bool no_l3_cache;
	U8 prefetchnta_preferred_stride_64;
	U8 prefetchnta_preferred_stride_128;
};

/*
Fills `infos` with cache and TLB informations returned by `CPUID` (`ft_cpuid(2, 0)[ECX/EDX]`)
*/
extern bool ft_cpuid_get_cache_tlb_info(U32 maxinfos, U64 cpuinfos, struct s_cpuid_ctlb_infos *infos);

/*
Fills `serial` with the processor's serial returned by `CPUID` (`ft_cpuid(1, 0)[ECX/EDX]`)
### On error
Sets ft_errno, and returns FALSE.
### ft_errno
- FT_EINVOP if `vendor_id` is not `FT_CPUID_VENDOR_INTEL` or `FT_CPUID_VENDOR_TRANSMETA`
- FT_ENOENT if no flags informations are not available
*/
extern bool ft_cpuid_get_proc_serial(U32 maxinfos, enum e_cpuid_vendor vendor_id, U64 *serial);

struct s_cpuid_monitor_mwait_infos
{
	U16 min_monitor_line_size;
	U16 max_monitor_line_size;

	bool extensions_enumerations;
	bool mwait_treat_interrupts_as_break_events;
	bool mwait_monitorless;

	U8 sub_states_cnt[8];
};

/* Fills `info` with MONITOR/MWAIT feature information */
extern bool ft_cpuid_get_monitor_mwait_infos(U32 maxinfos, struct s_cpuid_monitor_mwait_infos *infos);

#endif
