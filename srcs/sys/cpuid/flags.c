/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 01:35:11 by reclaire          #+#    #+#             */
/*   Updated: 2025/03/05 17:49:27 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cpuid_private.h"

#if !defined(array_len)
#define array_len(x) (sizeof(x) / sizeof((x)[0]))
#endif

bool ft_cpuid_get_flags(U32 maxinfos, struct s_cpuid_flags *flags)
{
	U32 out[4];
	U32 max_ecx;
	U32 i;
	U32 *ptr;

	ft_bzero(flags, sizeof(struct s_cpuid_flags));
	if (FT_CPUID_PROC_INFO_AND_FLAGS >= maxinfos)
		FT_RET_ERR(FALSE, FT_ENOENT);

	ft_cpuid(FT_CPUID_PROC_INFO_AND_FLAGS, 0, out);
	flags->flags_ecx = out[_ECX];
	flags->flags_edx = out[_EDX];

	if (maxinfos < FT_CPUID_EXTENDED_FLAGS)
		FT_RET_OK(TRUE); /* no extended flags */

	ft_cpuid(FT_CPUID_EXTENDED_FLAGS, 0, out);
	max_ecx = out[_EAX]; /* 'Returns the maximum ECX value for EAX=7 in EAX' */
	max_ecx = (max_ecx <= array_len(flags->extended_flags)) ? max_ecx : array_len(flags->extended_flags);

	ptr = flags->extended_flags;
	i = 0;
	while (i <= max_ecx)
	{
		ft_cpuid(FT_CPUID_EXTENDED_FLAGS, i, out);
		ft_memcpy(ptr, out, sizeof(out));
		ptr += array_len(out);
		i++;
	}
	FT_RET_OK(TRUE);
}

struct s_cpuid_flags *ft_cpuid_get_cached_flags()
{
	static U32 maxinfos;
	static struct s_cpuid_flags flags;
	static bool cached = FALSE;

	if (cached)
		return &flags;
	
	maxinfos = ft_cpuid_get_max_infos();
	ft_cpuid_get_flags(maxinfos, &flags);
	cached = TRUE;

	return &flags;
}

#define CPUID_FLAGS_SHORT \
	"fpu",                \
		"vme",            \
		"de",             \
		"pse",            \
		"tsc",            \
		"msr",            \
		"pae",            \
		"mce",            \
		"cx8",            \
		"apic",           \
		"reserved",       \
		"sep",            \
		"mtrr",           \
		"pge",            \
		"mca",            \
		"cmov",           \
		"pat",            \
		"pse36",          \
		"psn",            \
		"clfsh",          \
		"nx",             \
		"ds",             \
		"acpi",           \
		"mmx",            \
		"fxsr",           \
		"sse",            \
		"sse2",           \
		"ss",             \
		"htt",            \
		"tm",             \
		"ia64",           \
		"pbe",            \
		"sse3",           \
		"pclmulqdq",      \
		"dtes64",         \
		"monitor",        \
		"ds_cpl",         \
		"vmx",            \
		"smx",            \
		"est",            \
		"tm2",            \
		"ssse3",          \
		"cnxt_id",        \
		"sdbg",           \
		"fma",            \
		"cx16",           \
		"xtpr",           \
		"pdcm",           \
		"reserved",       \
		"pcid",           \
		"dca",            \
		"sse4_1",         \
		"sse4_2",         \
		"x2apic",         \
		"movbe",          \
		"popcnt",         \
		"tsc_deadline",   \
		"aes",            \
		"xsave",          \
		"osxsave",        \
		"avx",            \
		"f16c",           \
		"rdrand",         \
		"hypervisor"

#define CPUID_FLAGS_DESCR                                             \
	"Onboard x87 FPU",                                                \
		"Virtual 8086 mode extensions (VIF, VIP, PVI)",               \
		"Debugging extensions (CR4 bit 3)",                           \
		"Page Size Extension (4MB pages)",                            \
		"Time Stamp Counter",                                         \
		"Model-specific registers",                                   \
		"Physical Address Extension",                                 \
		"Machine Check Exception",                                    \
		"CMPXCHG8B instruction",                                      \
		"APIC on-chip",                                               \
		"Reserved",                                                   \
		"SYSENTER and SYSEXIT instructions",                          \
		"Memory Type Range Registers",                                \
		"Page Global Enable",                                         \
		"Machine Check Architecture",                                 \
		"Conditional Move Instructions (CMOV)",                       \
		"Page Attribute Table",                                       \
		"36-bit Page Size Extension",                                 \
		"Processor Serial Number",                                    \
		"CLFLUSH instruction",                                        \
		"No-execute (NX) bit (Itanium only, reserved on other CPUs)", \
		"Debug Store (save trace of executed jumps)",                 \
		"Thermal monitor and clock modulation",                       \
		"MMX technology",                                             \
		"FXSAVE, FXRSTOR instructions, CR4 bit 9",                    \
		"SSE instructions",                                           \
		"SSE2 instructions",                                          \
		"Self Snoop",                                                 \
		"Hyper-threading",                                            \
		"Thermal monitor",                                            \
		"IA64 processor emulating x86",                               \
		"Pending Break Enable",                                       \
		"SSE3 (Prescott New Instructions - PNI)",                     \
		"PCLMULQDQ instruction",                                      \
		"64-bit Debug Store",                                         \
		"MONITOR and MWAIT instructions",                             \
		"CPL-qualified Debug Store",                                  \
		"Virtual Machine Extensions (VMX)",                           \
		"Safer Mode Extensions (SMX)",                                \
		"Enhanced SpeedStep Technology",                              \
		"Thermal Monitor 2",                                          \
		"Supplemental SSE3 instructions",                             \
		"L1 Context ID",                                              \
		"Silicon Debug Interface",                                    \
		"Fused Multiply-Add (FMA3)",                                  \
		"CMPXCHG16B instruction",                                     \
		"xTPR Disable",                                               \
		"Perfmon and Debug Capability",                               \
		"Reserved",                                                   \
		"Process Context Identifiers (PCID)",                         \
		"Direct Cache Access",                                        \
		"SSE4.1 instructions",                                        \
		"SSE4.2 instructions",                                        \
		"x2APIC support",                                             \
		"MOVBE instruction",                                          \
		"POPCNT instruction",                                         \
		"Time Stamp Counter deadline",                                \
		"AES instruction set",                                        \
		"XSAVE, XRESTOR, XSETBV, XGETBV",                             \
		"OS-enabled XSAVE",                                           \
		"AVX instruction set",                                        \
		"16-bit Floating Point conversion instructions (F16C)",       \
		"RDRAND instruction",                                         \
		"Hypervisor presence"

const_string ft_cpuid_strflg_short(U64 flgs)
{
	static const_string data[] = {CPUID_FLAGS_SHORT};
	return data[63 - __builtin_clzll(flgs)];
}

const_string ft_cpuid_strflg_descr(U64 flgs)
{
	static const_string data[] = {CPUID_FLAGS_DESCR};
	return data[63 - __builtin_clzll(flgs)];
}
