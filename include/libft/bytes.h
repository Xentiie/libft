/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bytes.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 20:32:47 by reclaire          #+#    #+#             */
/*   Updated: 2024/11/26 16:52:26 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(FT_BYTES_H)
#define FT_BYTES_H

#include "libft/libft.h"

/* from rhash */
/* if x86 compatible cpu */
#if defined(i386) || defined(__i386__) || defined(__i486__) ||        \
	defined(__i586__) || defined(__i686__) || defined(__pentium__) || \
	defined(__pentiumpro__) || defined(__pentium4__) ||               \
	defined(__nocona__) || defined(prescott) || defined(__core2__) || \
	defined(__k6__) || defined(__k8__) || defined(__athlon__) ||      \
	defined(__amd64) || defined(__amd64__) ||                         \
	defined(__x86_64) || defined(__x86_64__) || defined(_M_IX86) ||   \
	defined(_M_AMD64) || defined(_M_IA64) || defined(_M_X64)
/* detect if x86-64 instruction set is supported */
#if defined(_LP64) || defined(__LP64__) || defined(__x86_64) || \
	defined(__x86_64__) || defined(_M_AMD64) || defined(_M_X64)
#define CPU_X64
#else
#define CPU_IA32
#endif
#endif

#define FT_BYTE_ORDER_LE 1234
#define FT_BYTE_ORDER_BE 4321

#if (defined(__BYTE_ORDER) && defined(__LITTLE_ENDIAN) && __BYTE_ORDER == __LITTLE_ENDIAN) || \
	(defined(__BYTE_ORDER__) && defined(__ORDER_LITTLE_ENDIAN__) && __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__)
#define FT_BYTE_ORDER FT_BYTE_ORDER_LE
#elif (defined(__BYTE_ORDER) && defined(__BIG_ENDIAN) && __BYTE_ORDER == __BIG_ENDIAN) || \
	(defined(__BYTE_ORDER__) && defined(__ORDER_BIG_ENDIAN__) && __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__)
#define FT_BYTE_ORDER FT_BYTE_ORDER_BE
#elif defined(_BYTE_ORDER)
#if defined(_LITTLE_ENDIAN) && (_BYTE_ORDER == _LITTLE_ENDIAN)
#define FT_BYTE_ORDER FT_BYTE_ORDER_LE
#elif defined(_BIG_ENDIAN) && (_BYTE_ORDER == _BIG_ENDIAN)
#define FT_BYTE_ORDER FT_BYTE_ORDER_BE
#endif
#elif defined(__sun) && defined(_LITTLE_ENDIAN)
#define FT_BYTE_ORDER FT_BYTE_ORDER_LE
#elif defined(__sun) && defined(_BIG_ENDIAN)
#define FT_BYTE_ORDER FT_BYTE_ORDER_BE
#endif

#if !defined(FT_BYTE_ORDER)
/* try detecting endianness by CPU */
#if defined(CPU_IA32) || defined(CPU_X64) || defined(__ia64) || defined(__ia64__) ||  \
	defined(__alpha__) || defined(_M_ALPHA) || defined(vax) || defined(MIPSEL) ||     \
	defined(_ARM_) || defined(__arm__) || defined(_M_ARM64) || defined(_M_ARM64EC) || \
	defined(__loongarch64)
#define FT_BYTE_ORDER FT_BYTE_ORDER_LE
#elif defined(__sparc) || defined(__sparc__) || defined(sparc) ||         \
	defined(_ARCH_PPC) || defined(_ARCH_PPC64) || defined(_POWER) ||      \
	defined(__POWERPC__) || defined(POWERPC) || defined(__powerpc) ||     \
	defined(__powerpc__) || defined(__powerpc64__) || defined(__ppc__) || \
	defined(__hpux) || defined(_MIPSEB) || defined(mc68000) ||            \
	defined(__s390__) || defined(__s390x__) || defined(sel) || defined(__hppa__)
#define FT_BYTE_ORDER FT_BYTE_ORDER_BE
#endif
#endif

#if !defined(FT_BYTE_ORDER)
#error "Can't detect CPU architechture"
#endif

#if FT_BYTE_ORDER == FT_BYTE_ORDER_BE
#define FT_IS_BIG_ENDIAN 1
#define FT_IS_LITTLE_ENDIAN 0
#else
#define FT_IS_BIG_ENDIAN 0
#define FT_IS_LITTLE_ENDIAN 1
#endif

#define IS_ALIGNED_32(p) (0 == (3 & (U64)(p)))
#define IS_ALIGNED_64(p) (0 == (7 & (U64)(p)))

static inline U16 ft_bswap16(U16 x)
{
#if FT_HAS_BUILTIN(__builtin_bswap16)
	return __builtin_bswap16(x);
#else
	return ((U16)((((x) >> 8) & 0xff) |
				  (((x) & 0xff) << 8)))
#endif
}

static inline U32 ft_bswap32(U32 x)
{
#if FT_HAS_BUILTIN(__builtin_bswap32)
	return __builtin_bswap32(x);
#else
	return ((U32)((((x) & 0xff000000u) >> 24) |
				  (((x) & 0x00ff0000u) >> 8) |
				  (((x) & 0x0000ff00u) << 8) |
				  (((x) & 0x000000ffu) << 24)))
#endif
}

static inline U64 ft_bswap64(U64 x)
{
#if FT_HAS_BUILTIN(__builtin_bswap64)
	return __builtin_bswap64(x);
#else
	return ((U64)((((x) & 0xff00000000000000ull) >> 56) |
				  (((x) & 0x00ff000000000000ull) >> 40) |
				  (((x) & 0x0000ff0000000000ull) >> 24) |
				  (((x) & 0x000000ff00000000ull) >> 8) |
				  (((x) & 0x00000000ff000000ull) << 8) | (((x) & 0x0000000000ff0000ull) << 24) |
				  (((x) & 0x000000000000ff00ull) << 40) | (((x) & 0x00000000000000ffull) << 56)))
#endif
}

static inline U32 ft_ctz(U32 x)
{
#if FT_HAS_BUILTIN(__builtin_ctz)
	return __builtin_ctz(x);
#else
	static U32 bit_pos[32] = {
		0, 1, 28, 2, 29, 14, 24, 3, 30, 22, 20, 15, 25, 17, 4, 8,
		31, 27, 13, 23, 21, 19, 16, 7, 26, 12, 18, 6, 11, 5, 10, 9};

	/* The De Bruijn bit-scan was devised in 1997, according to Donald Knuth
	 * by Martin Lauter. The constant 0x077CB531UL is a De Bruijn sequence,
	 * which produces a unique pattern of bits into the high 5 bits for each
	 * possible bit position that it is multiplied against.
	 * See http://graphics.stanford.edu/~seander/bithacks.html
	 * and http://chessprogramming.wikispaces.com/BitScan */
	return (U32)bit_pos[((U32)((x & -x) * 0x077CB531U)) >> 27];
#endif
}

static inline U32 ft_popcount(U32 x)
{
#if FT_HAS_BUILTIN(__builtin_popcount)
	return __builtin_popcount(x);
#else
	x -= (x >> 1) & 0x55555555;
	x = ((x >> 2) & 0x33333333) + (x & 0x33333333);
	x = ((x >> 4) + x) & 0x0f0f0f0f;
	return (x * 0x01010101) >> 24;
#endif
}

/* Forcement on va rien swap sur 8 bits, c'est juste la prcque ca sert dans des macros des fois */
#define ft_betoh8(x) (x)
#define ft_letoh8(x) (x)
#define ft_htobe8(x) (x)
#define ft_htole8(x) (x)
#if FT_IS_BIG_ENDIAN
#define ft_betoh16(x) (x)
#define ft_betoh32(x) (x)
#define ft_betoh64(x) (x)
#define ft_letoh16(x) ft_bswap16(x)
#define ft_letoh32(x) ft_bswap32(x)
#define ft_letoh64(x) ft_bswap64(x)

#define ft_htobe16(x) (x)
#define ft_htobe32(x) (x)
#define ft_htobe64(x) (x)
#define ft_htole16(x) ft_bswap16(x)
#define ft_htole32(x) ft_bswap32(x)
#define ft_htole64(x) ft_bswap64(x)
#else
#define ft_betoh16(x) ft_bswap16(x)
#define ft_betoh32(x) ft_bswap32(x)
#define ft_betoh64(x) ft_bswap64(x)
#define ft_letoh16(x) (x)
#define ft_letoh32(x) (x)
#define ft_letoh64(x) (x)

#define ft_htobe16(x) ft_bswap16(x)
#define ft_htobe32(x) ft_bswap32(x)
#define ft_htobe64(x) ft_bswap64(x)
#define ft_htole16(x) (x)
#define ft_htole32(x) (x)
#define ft_htole64(x) (x)
#endif

#endif
