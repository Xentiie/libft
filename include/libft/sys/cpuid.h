/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpuid.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 02:08:17 by reclaire          #+#    #+#             */
/*   Updated: 2025/06/02 16:40:38 by reclaire         ###   ########.fr       */
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
#define FT_CPUID_EXTENDED_FLAGS 7

/* Executes the `CPUID` instruction, with `reg` and `sub` as arguments, and outputs the result in `out` */
inline void ft_cpuid(U32 reg, U32 sub, U32 out[4])
{
	__asm__(
		"cpuid\n"
		: "=a"(out[0]), "=b"(out[1]), "=c"(out[2]), "=d"(out[3])
		: "a"(reg), "1"(0), "2"(sub));
}

/* Returns the max `reg` value possible for `CPUID` (`ft_cpuid(0, 0)[EAX]`) */
extern U32 ft_cpuid_get_max_infos();

/* Returns the max `reg` value possible for `CPUID` for extended infos (`ft_cpuid(0x80000000, 0)[EAX]`)*/
extern U32 ft_cpuid_get_max_extended_infos();

packed_enum e_cpuid_vendor
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

#define FT_CPUID_GET_STEPPING(cpuinfos) (((cpuinfos) >> 0) & 0xF)
#define FT_CPUID_GET_MODEL_ID(cpuinfos) (((cpuinfos) >> 4) & 0xF)
#define FT_CPUID_GET_FAMILY_ID(cpuinfos) (((cpuinfos) >> 8) & 0xF)
#define FT_CPUID_GET_PROC_TYPE(cpuinfos) (((cpuinfos) >> 12) & 0xF)
#define FT_CPUID_GET_EXT_MODEL_ID(cpuinfos) (((cpuinfos) >> 16) & 0xF)
#define FT_CPUID_GET_EXT_FAMILY_ID(cpuinfos) (((cpuinfos) >> 24) & 0xFF)
#define FT_CPUID_GET_BRAND_INDEX(cpuinfos) (((cpuinfos) >> 32) & 0xFF)
#define FT_CPUID_GET_CLFLUSH_SIZE(cpuinfos) (((cpuinfos) >> 40) & 0xFF)
#define FT_CPUID_GET_ADDRABLE_LOG_PROC_ID(cpuinfos) (((cpuinfos) >> 48) & 0xFF)
#define FT_CPUID_GET_LOCAL_APIC_ID(cpuinfos) (((cpuinfos) >> 56) & 0xFF)

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

// TODO:
/* Returns the identifier of the flag (highest bit set) specified in `flgs` */
// extern const_string ft_cpuid_strflg_short(U64 flgs);
/* Returns the description of the flag (highest bit set) specified in `flgs` */
// extern const_string ft_cpuid_strflg_descr(U64 flgs);

/* extended flags */
struct s_cpuid_flags
{
	union
	{
		struct
		{
			U32 fpu : 1;	/* Onboard x87 FPU */
			U32 vme : 1;	/* Virtual 8086 mode extensions (such as VIF, VIP, PVI) */
			U32 de : 1;		/* Debugging extensions (CR4 bit 3) */
			U32 pse : 1;	/* Page Size Extension (4 MB pages) */
			U32 tsc : 1;	/* Time Stamp Counter and RDTSC instruction */
			U32 msr : 1;	/* Model-specific registers and RDMSR/WRMSR instructions */
			U32 pae : 1;	/* Physical Address Extension */
			U32 mce : 1;	/* Machine Check Exception */
			U32 cx8 : 1;	/* CMPXCHG8B (compare-and-swap) instruction */
			U32 apic : 1;	/* Onboard Advanced Programmable Interrupt Controller */
			U32 __pad1 : 1; /* padding */
			U32 sep : 1;	/* SYSENTER and SYSEXIT fast system call instructions */
			U32 mtrr : 1;	/* Memory Type Range Registers */
			U32 pge : 1;	/* Page Global Enable bit in CR4 */
			U32 mca : 1;	/* Machine check architecture */
			U32 cmov : 1;	/* Conditional move: CMOV, FCMOV and FCOMI instructions[h] */
			U32 pat : 1;	/* Page Attribute Table */
			U32 pse36 : 1;	/* 36-bit page size extension */
			U32 psn : 1;	/* Processor Serial Number supported and enabled */
			U32 clfsh : 1;	/* CLFLUSH cache line flush instruction (SSE2) */
			U32 nx : 1;		/* No-execute (NX) bit (Itanium only, reserved on other CPUs) */
			U32 ds : 1;		/* Debug store: save trace of executed jumps */
			U32 acpi : 1;	/* Onboard thermal control MSRs for ACPI */
			U32 mmx : 1;	/* MMX instructions (64-bit SIMD) */
			U32 fxsr : 1;	/* FXSAVE, FXRSTOR instructions, CR4 bit 9 */
			U32 sse : 1;	/* Streaming SIMD Extensions (SSE) instructions (aka "Katmai New Instructions"; 128-bit SIMD) */
			U32 sse2 : 1;	/* SSE2 instructions */
			U32 ss : 1;		/* CPU cache implements self-snoop */
			U32 htt : 1;	/* Max APIC IDs reserved field is Valid */
			U32 tm : 1;		/* Thermal monitor automatically limits temperature */
			U32 ia64 : 1;	/* IA64 processor emulating x86 */
			U32 pbe : 1;	/* Pending Break Enable (PBE# pin) wakeup capability */

			U32 ss3 : 1;		  /* SSE3 (Prescott New Instructions - PNI) */
			U32 pclmulqdq : 1;	  /* PCLMULQDQ (carry-less multiply) instruction */
			U32 dtes64 : 1;		  /* 64-bit debug store (edx bit 21) */
			U32 monitor : 1;	  /* MONITOR and MWAIT instructions (PNI) */
			U32 ds_cpl : 1;		  /* CPL qualified debug store */
			U32 vmx : 1;		  /* Virtual Machine eXtensions */
			U32 smx : 1;		  /* Safer Mode Extensions (LaGrande) (GETSEC instruction) */
			U32 est : 1;		  /* Enhanced SpeedStep */
			U32 tm2 : 1;		  /* Thermal Monitor 2 */
			U32 ssse3 : 1;		  /* Supplemental SSE3 instructions */
			U32 cnxt_id : 1;	  /* L1 Context ID */
			U32 sdbg : 1;		  /* Silicon Debug interface */
			U32 fma : 1;		  /* Fused multiply-add (FMA3) */
			U32 cx16 : 1;		  /* CMPXCHG16B instruction */
			U32 xtpr : 1;		  /* Can disable sending task priority messages */
			U32 pdcm : 1;		  /* Perfmon & debug capability */
			U32 __pad2 : 1;		  /* padding */
			U32 pcid : 1;		  /* Process context identifiers (CR4 bit 17) */
			U32 dca : 1;		  /* Direct cache access for DMA writes */
			U32 sse4_1 : 1;		  /* SSE4.1 instructions */
			U32 sse4_2 : 1;		  /* SSE4.2 instructions */
			U32 x2apic : 1;		  /* x2APIC (enhanced APIC) */
			U32 movbe : 1;		  /* MOVBE instruction (big-endian) */
			U32 popcnt : 1;		  /* POPCNT instruction */
			U32 tsc_deadline : 1; /* APIC implements one-shot operation using a TSC deadline value */
			U32 aes_ni : 1;		  /* AES instruction set */
			U32 xsave : 1;		  /* Extensible processor state save/restore: XSAVE, XRSTOR, XSETBV, XGETBV instructions */
			U32 osxsave : 1;	  /* XSAVE enabled by OS */
			U32 avx : 1;		  /* Advanced Vector Extensions (256-bit SIMD) */
			U32 f16c : 1;		  /* Floating-point conversion instructions to/from FP16 format */
			U32 rdrnd : 1;		  /* RDRAND (on-chip random number generator) feature */
			U32 hypervisor : 1;	  /* Hypervisor present (always zero on physical CPUs) */
		};

		struct
		{
			U32 flags_edx;
			U32 flags_ecx;
		};

		U32 flags[2];
	};

	union
	{
		struct
		{
			U32 __pad0 : 32; /* padding */

			U32 fsgsbase : 1;		 /* Access to base of %fs and %gs */
			U32 ia32_tsc_adjust : 1; /* IA32_TSC_ADJUST MSR */
			U32 sgx : 1;			 /* Software Guard Extensions */
			U32 bmi1 : 1;			 /* Bit Manipulation Instruction Set 1 */
			U32 hle : 1;			 /* TSX Hardware Lock Elision */
			U32 avx2 : 1;			 /* Advanced Vector Extensions 2 */
			U32 fdp_excptn_only : 1; /* x87 FPU data pointer register updated on exceptions only  */
			U32 smep : 1;			 /* Supervisor Mode Execution Prevention */
			U32 bmi2 : 1;			 /* Bit Manipulation Instruction Set 2 */
			U32 erms : 1;			 /* Enhanced REP MOVSB/STOSB */
			U32 invpcid : 1;		 /* INVPCID instruction */
			U32 rtm : 1;			 /* TSX Restricted Transactional Memory */
			U32 rdtm_pqm : 1;		 /* Intel Resource Director (RDT) Monitoring or AMD Platform QOS Monitoring  */
			U32 __pad3 : 1;			 /* padding */
			U32 mpx : 1;			 /* Intel MPX (Memory Protection Extensions)  */
			U32 rdta_pqe : 1;		 /* Intel Resource Director (RDT) Allocation or AMD Platform QOS Enforcement */
			U32 avx512_f : 1;		 /* AVX-512 Foundation */
			U32 avx512_dq : 1;		 /* AVX-512 Doubleword and Quadword Instructions */
			U32 rdseed : 1;			 /* RDSEED instruction */
			U32 adx : 1;			 /* Intel ADX (Multi-Precision Add-Carry Instruction Extensions) */
			U32 smap : 1;			 /* Supervisor Mode Access Prevention */
			U32 avx512_ifma : 1;	 /* AVX-512 Integer Fused Multiply-Add Instructions  */
			U32 pcommit : 1;		 /* (PCOMMIT instruction, deprecated) */
			U32 clflushopt : 1;		 /* CLFLUSHOPT instruction  */
			U32 clwb : 1;			 /* CLWB (Cache line writeback) instruction  */
			U32 pt : 1;				 /* Intel Processor Trace  */
			U32 avx512_pf : 1;		 /* AVX-512 Prefetch Instructions  */
			U32 avx512_er : 1;		 /* AVX-512 Exponential and Reciprocal Instructions */
			U32 avx512_cd : 1;		 /* AVX-512 Conflict Detection Instructions */
			U32 sha : 1;			 /* SHA-1 and SHA-256 extensions */
			U32 avx512_bw : 1;		 /* AVX-512 Byte and Word Instructions */
			U32 avx512_vl : 1;		 /* AVX-512 Vector Length Extensions */

			U32 prefetchwt1 : 1;	  /* PREFETCHWT1 instruction */
			U32 avx512_vbmi : 1;	  /* AVX-512 Vector Bit Manipulation Instructions */
			U32 umip : 1;			  /* User-mode Instruction Prevention */
			U32 pku : 1;			  /* Memory Protection Keys for User-mode pages */
			U32 ospke : 1;			  /* PKU enabled by OS */
			U32 waitpkg : 1;		  /* Timed pause and user-level monitor/wait instructions (TPAUSE, UMONITOR, UMWAIT) */
			U32 avx512_vbmi2 : 1;	  /* AVX-512 Vector Bit Manipulation Instructions 2  */
			U32 cet_ss_shstk : 1;	  /* Control flow enforcement (CET): shadow stack (SHSTK alternative name)  */
			U32 gfni : 1;			  /* Galois Field instructions  */
			U32 vaes : 1;			  /* Vector AES instruction set (VEX-256/EVEX)  */
			U32 vpclmulqdq : 1;		  /* CLMUL instruction set (VEX-256/EVEX)  */
			U32 avx512_vnni : 1;	  /* AVX-512 Vector Neural Network Instructions  */
			U32 avx512_bitalg : 1;	  /* AVX-512 BITALG instructions  */
			U32 tme_en : 1;			  /* Total Memory Encryption MSRs available  */
			U32 avx512_vpopcntdq : 1; /* AVX-512 Vector Population Count Double and Quad-word  */
			U32 fzm : 1;			  /* ? */
			U32 la57 : 1;			  /* 5-level paging (57 address bits)  */
			U32 mawau : 5;			  /* The value of userspace MPX Address-Width Adjust used by the BNDLDX and BNDSTX Intel MPX instructions in 64-bit mode  */
			U32 rdpid : 1;			  /* RDPID (Read Processor ID) instruction and IA32_TSC_AUX MSR  */
			U32 kl : 1;				  /* AES Key Locker  */
			U32 bus_lock_detect : 1;  /* Bus lock debug exceptions   */
			U32 cldemote : 1;		  /* CLDEMOTE (Cache line demote) instruction  */
			U32 mprr : 1;			  /* ? */
			U32 movdiri : 1;		  /* MOVDIRI instruction  */
			U32 movdir64b : 1;		  /* MOVDIR64B (64-byte direct store) instruction  */
			U32 enqcmd : 1;			  /* Enqueue Stores and EMQCMD/EMQCMDS instructions  */
			U32 sgx_lc : 1;			  /* SGX Launch Configuration  */
			U32 pks : 1;			  /* Protection keys for supervisor-mode pages  */

			U32 sgx_tem : 1;				/* ? */
			U32 sgx_keys : 1;				/* Attestation Services for Intel SGX  */
			U32 avx512_4vnniw : 1;			/* AVX-512 4-register Neural Network Instructions  */
			U32 avx512_4fmaps : 1;			/* AVX-512 4-register Multiply Accumulation Single precision  */
			U32 fsrm : 1;					/* Fast Short REP MOVSB  */
			U32 uintr : 1;					/* User Inter-processor Interrupts  */
			U32 __pad6 : 2;					/* padding */
			U32 avx512_vp2intersect : 1;	/* AVX-512 vector intersection instructions on 32/64-bit integers  */
			U32 srbds_ctrl : 1;				/* Special Register Buffer Data Sampling Mitigations  */
			U32 md_clear : 1;				/* VERW instruction clears CPU buffers  */
			U32 rtm_always_abort : 1;		/* All TSX transactions are aborted  */
			U32 __pad7 : 1;					/* padding */
			U32 rtm_force_abort : 1;		/* TSX_FORCE_ABORT (MSR 0x10f) is available  */
			U32 serialize : 1;				/* SERIALIZE instruction  */
			U32 hybrid : 1;					/* Mixture of CPU types in processor topology (e.g. Alder Lake)  */
			U32 tsxldtrk : 1;				/* TSX load address tracking suspend/resume instructions (TSUSLDTRK and TRESLDTRK)  */
			U32 __pad8 : 1;					/* padding */
			U32 pconfig : 1;				/* Platform configuration (Memory Encryption Technologies Instructions)  */
			U32 lbr : 1;					/* Architectural Last Branch Records  */
			U32 cet_ibt : 1;				/* Control flow enforcement (CET): indirect branch tracking  */
			U32 __pad9 : 1;					/* padding */
			U32 amx_bf16 : 1;				/* AMX tile computation on bfloat16 numbers  */
			U32 avx512_fp16 : 1;			/* AVX-512 half-precision floating-point arithmetic instructions[104]  */
			U32 amx_tile : 1;				/* AMX tile load/store instructions  */
			U32 amx_int8 : 1;				/* AMX tile computation on 8-bit integers  */
			U32 ibrs_spec_ctrl : 1;			/* Speculation Control, part of Indirect Branch Control (IBC): Indirect Branch Restricted Speculation (IBRS) and Indirect Branch Prediction Barrier (IBPB) */
			U32 stibp : 1;					/* Single Thread Indirect Branch Predictor, part of IBC */
			U32 l1d_flush : 1;				/* IA32_FLUSH_CMD */
			U32 ia32_arch_capabilities : 1; /* IA32_ARCH_CAPABILITIES MSR (lists speculative side channel mitigations)  */
			U32 ia32_core_capabilities : 1; /* IA32_CORE_CAPABILITIES MSR (lists model-specific core capabilities)  */
			U32 ssbd : 1;					/* Speculative Store Bypass Disable,[105] as mitigation for Speculative Store Bypass (IA32_SPEC_CTRL)  */

			U32 sha512 : 1;						 /* SHA-512 extensions */
			U32 sm3 : 1;						 /* SM3 hash extensions */
			U32 sm4 : 1;						 /* SM4 cipher extensions */
			U32 rao_int : 1;					 /* Remote Atomic Operations on integers: AADD, AAND, AOR, AXOR instructions  */
			U32 avx_vnni : 1;					 /* AVX Vector Neural Network Instructions (VNNI) (VEX encoded)  */
			U32 avx512_bf16 : 1;				 /* AVX-512 instructions for bfloat16 numbers  */
			U32 lass : 1;						 /* Linear Address Space Separation (CR4 bit 27)  */
			U32 cmpccxadd : 1;					 /* CMPccXADD instructions  */
			U32 archperf_monext : 1;			 /* Architectural Performance Monitoring Extended Leaf (EAX=23h)  */
			U32 dedup : 1;						 /* ? */
			U32 fzrm : 1;						 /* Fast zero-length REP MOVSB  */
			U32 fsrs : 1;						 /* Fast short REP STOSB  */
			U32 rsrcs : 1;						 /* Fast short REP CMPSB and REP SCASB  */
			U32 __pad10 : 4;					 /* padding */
			U32 fred : 1;						 /* Flexible Return and Event Delivery[109]  */
			U32 lkgs : 1;						 /* LKGS Instruction[109]  */
			U32 wrmsrns : 1;					 /* WRMSRNS instruction (non-serializing write to MSRs)  */
			U32 nmi_src : 1;					 /* NMI source reporting[109]  */
			U32 amx_fp16 : 1;					 /* AMX instructions for FP16 numbers  */
			U32 hreset : 1;						 /* HRESET instruction, IA32_HRESET_ENABLE (17DAh) MSR, and Processor History Reset Leaf (EAX=20h)  */
			U32 avx_ifma : 1;					 /* AVX IFMA instructions  */
			U32 __pad11 : 2;					 /* padding */
			U32 lam : 1;						 /* Linear Address Masking  */
			U32 msrlist : 1;					 /* RDMSRLIST and WRMSRLIST instructions, and the IA32_BARRIER (02Fh) MSR  */
			U32 __pad12 : 2;					 /* padding */
			U32 invd_disable_post_bios_done : 1; /* If 1, supports INVD instruction execution prevention after BIOS Done.  */
			U32 movrs : 1;						 /* MOVRS and PREFETCHRST2 instructions supported (memory read/prefetch with read-shared hint)  */

			U32 intel_ppin : 1;			  /* Intel PPIN (Protected Processor Inventory Number): IA32_PPIN_CTL (04Eh) and IA32_PPIN (04Fh) MSRs.  */
			U32 pbndkb : 1;				  /* Total Storage Encryption: PBNDKB instruction and TSE_CAPABILITY (9F1h) MSR.  */
			U32 __pad13 : 1;			  /* padding */
			U32 cpuid_maxval_lim_rmv : 1; /* If 1, then bit 22 of IA32_MISC_ENABLE cannot be set to 1 to limit the value returned by CPUID.(EAX=0):EAX[7:0].  */
			U32 __pad14_1 : 28;			  /* padding */

			U32 __pad14_2 : 2;			/* padding */
			U32 legacy_reduced_isa : 1; /* (X86S,[107] cancelled[108])  */
			U32 __pad15 : 1;			/* padding */
			U32 sipi64 : 1;				/* 64-bit SIPI (Startup InterProcessor Interrupt) (part of cancelled X86S)  */
			U32 msr_imm : 1;			/*  Immediate forms of the RDMSR and WRMSRNS instructions  */
			U32 __pad16_1 : 26;			/* padding */

			U32 __pad16_2 : 4;			   /* padding */
			U32 avx_vnni_int8 : 1;		   /* AVX VNNI INT8 instructions  */
			U32 avx_ne_convert : 1;		   /* AVX no-exception FP conversion instructions (bfloat16↔FP32 and FP16→FP32)  */
			U32 __pad17 : 2;			   /* padding */
			U32 amx_complex : 1;		   /* AMX support for "complex" tiles (TCMMIMFP16PS and TCMMRLFP16PS)  */
			U32 __pad18 : 1;			   /* padding */
			U32 avx_vnni_int16 : 1;		   /* AVX VNNI INT16 instructions  */
			U32 __pad19 : 2;			   /* padding */
			U32 utmr : 1;				   /* User-timer events: IA32_UINTR_TIMER (1B00h) MSR  */
			U32 prefetchi : 1;			   /* Instruction-cache prefetch instructions (PREFETCHIT0 and PREFETCHIT1)  */
			U32 user_msr : 1;			   /* User-mode MSR access instructions (URDMSR and UWRMSR)  */
			U32 __pad20 : 1;			   /* padding */
			U32 uiret_uif_from_rflags : 1; /* If 1, the UIRET (User Interrupt Return) instruction will set UIF (User Interrupt Flag) to the value of bit 1 of the RFLAGS image popped off the stack.  */
			U32 cet_sss : 1;			   /* If 1, then Control-Flow Enforcement (CET) Supervisor Shadow Stacks (SSS) are guaranteed not to become prematurely busy as long as shadow stack switching does not cause page faults on the stack being switched to.[110][111]  */
			U32 avx10 : 1;				   /* AVX10 Converged Vector ISA (see also leaf 24h)[112]  */
			U32 __pad21 : 1;			   /* padding */
			U32 apx_f : 1;				   /* Advanced Performance Extensions, Foundation (adds REX2 and extended EVEX prefix encodings to support 32 GPRs, as well as some new instructions)[113]  */
			U32 __pad22 : 1;			   /* padding */
			U32 mwait : 1;				   /* MWAIT instruction[b]  */
			U32 __pad23 : 8;			   /* padding */

			U32 __pad24 : 32; /* padding */

			U32 __pad25 : 32; /* padding */

			U32 __pad26 : 32; /* padding */

			U32 psfd : 1;			 /* Fast Store Forwarding Predictor[114] disable supported. (SPEC_CTRL (MSR 48h) bit 7)  */
			U32 ipred_ctrl : 1;		 /* IPRED_DIS controls[115] supported. (SPEC_CTRL bits 3 and 4) IPRED_DIS prevents instructions at an indirect branch target from speculatively executing until the branch target address is resolved.  */
			U32 rrsba_ctrl : 1;		 /* RRSBA behavior[116][115] disable supported. (SPEC_CTRL bits 5 and 6)  */
			U32 ddpd_u : 1;			 /* Data Dependent Prefetcher[117] disable supported. (SPEC_CTRL bit 8)  */
			U32 bhi_ctrl : 1;		 /* BHI_DIS_S behavior[115] enable supported. (SPEC_CTRL bit 10) BHI_DIS_S prevents predicted targets of indirect branches executed in ring0/1/2 from being selected based on branch history from branches executed in ring 3.  */
			U32 mcdt_no : 1;		 /* If set, the processor does not exhibit MXCSR configuration dependent timing.  */
			U32 uc_lock_disable : 1; /* UC-lock disable feature supported.  */
			U32 monitor_mitg_no : 1; /* If set, indicates that the MONITOR/UMONITOR instructions are not affected by performance/power issues caused by the instructions exceeding the capacity of an internal monitor tracking table.[118]  */
			U32 __pad27 : 24;		 /* padding */
		};

		struct
		{
			U32 extended_flags_ecx_1_eax;
			U32 extended_flags_ecx_1_ebx;
			U32 extended_flags_ecx_1_ecx;
			U32 extended_flags_ecx_1_edx;

			U32 extended_flags_ecx_2_eax;
			U32 extended_flags_ecx_2_ebx;
			U32 extended_flags_ecx_2_ecx;
			U32 extended_flags_ecx_2_edx;

			U32 extended_flags_ecx_3_eax;
			U32 extended_flags_ecx_3_ebx;
			U32 extended_flags_ecx_3_ecx;
			U32 extended_flags_ecx_3_edx;
		};

		U32 extended_flags[12];
	};
};

/*
Fills `flags` with the flags returned by `CPUID` (`ft_cpuid(1, 0)[ECX/EDX]`)
### On error
Sets ft_errno, and returns FALSE.
### ft_errno
- FT_ENOENT if no flags informations are not available
*/
extern bool ft_cpuid_get_flags(U32 maxinfos, struct s_cpuid_flags *flags);
extern struct s_cpuid_flags *ft_cpuid_get_cached_flags();

packed_enum e_cpuid_cache_type
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
	bool is_data;	   /* TRUE if LTB is data TLB, FALSE if instruction TLB */
	U64 entries_cnt;   /* TLB entries */
	U64 page_size;	   /* TLB page-size */
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
