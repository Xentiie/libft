/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vendor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 02:07:00 by reclaire          #+#    #+#             */
/*   Updated: 2025/02/18 02:12:59 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cpuid_private.h"

#include "libft/strings.h"

enum e_cpuid_vendor ft_cpuid_get_vendor(char true_name[13])
{
	U32 reg;
	U32 sub;
	U32 out[4];

	reg = 0;
	sub = 0;
	ft_cpuid(reg, sub, out);

	out[0] = out[2];
	out[1] = out[1];
	out[2] = out[3];
	out[3] = out[0];

	if (true_name)
	{
		ft_memcpy(true_name, out + 1, 12);
		true_name[12] = '\0';
	}

	if (!ft_strncmp((const_string)(out + 1), "GenuineIntel", 12))
		return FT_CPUID_VENDOR_INTEL;
	else if (!ft_strncmp((const_string)(out + 1), "AuthenticAMD", 12))
		return FT_CPUID_VENDOR_AMD;
	else if (!ft_strncmp((const_string)(out + 1), "CyrixInstead", 12))
		return FT_CPUID_VENDOR_CYRIX;
	else if (!ft_strncmp((const_string)(out + 1), "CentaurHauls", 12))
		return FT_CPUID_VENDOR_VIA;
	else if (!ft_strncmp((const_string)(out + 1), "UMC UMC UMC ", 12))
		return FT_CPUID_VENDOR_UMC;
	else if (!ft_strncmp((const_string)(out + 1), "NexGenDriven", 12))
		return FT_CPUID_VENDOR_NEXGEN;
	else if (!ft_strncmp((const_string)(out + 1), "RiseRiseRise", 12))
		return FT_CPUID_VENDOR_RISE;
	else if (!ft_strncmp((const_string)(out + 1), "GenuineTMx86", 12))
		return FT_CPUID_VENDOR_TRANSMETA;
	else if (!ft_strncmp((const_string)(out + 1), "SiS SiS SiS ", 12))
		return FT_CPUID_VENDOR_SIS;
	else if (!ft_strncmp((const_string)(out + 1), "Geode by NSC", 12))
		return FT_CPUID_VENDOR_NSC;
	else if (!ft_strncmp((const_string)(out + 1), "Vortex86 SoC", 12))
		return FT_CPUID_VENDOR_VORTEX;
	else if (!ft_strncmp((const_string)(out + 1), "Genuine  RDC", 12))
		return FT_CPUID_VENDOR_RDC;
	else if (!ft_strncmp((const_string)(out + 1), "HygonGenuine", 12))
		return FT_CPUID_VENDOR_HYGON;
	else if (!ft_strncmp((const_string)(out + 1), "  Shanghai  ", 12))
		return FT_CPUID_VENDOR_ZHAOXIN;

	return out[_EAX];
}


const_string ft_cpuid_strvendor(enum e_cpuid_vendor vendor_id)
{
	static const_string vendor_id_str[] = {
#define mk_vendor_id_str(X) [X] = #X
		mk_vendor_id_str(FT_CPUID_VENDOR_UNKNOWN),
		mk_vendor_id_str(FT_CPUID_VENDOR_INTEL),
		mk_vendor_id_str(FT_CPUID_VENDOR_AMD),
		mk_vendor_id_str(FT_CPUID_VENDOR_CYRIX),
		mk_vendor_id_str(FT_CPUID_VENDOR_VIA),
		mk_vendor_id_str(FT_CPUID_VENDOR_UMC),
		mk_vendor_id_str(FT_CPUID_VENDOR_NEXGEN),
		mk_vendor_id_str(FT_CPUID_VENDOR_RISE),
		mk_vendor_id_str(FT_CPUID_VENDOR_TRANSMETA),
		mk_vendor_id_str(FT_CPUID_VENDOR_SIS),
		mk_vendor_id_str(FT_CPUID_VENDOR_NSC),
		mk_vendor_id_str(FT_CPUID_VENDOR_VORTEX),
		mk_vendor_id_str(FT_CPUID_VENDOR_RDC),
		mk_vendor_id_str(FT_CPUID_VENDOR_HYGON),
		mk_vendor_id_str(FT_CPUID_VENDOR_ZHAOXIN),
#undef mk_vendor_id_str
	};

	if (vendor_id < 0 || vendor_id >= __FT_CPUID_VENDOR_MAX)
		FT_RET_ERR(NULL, FT_ENOENT);
	FT_RET_OK(vendor_id_str[vendor_id]);
}
