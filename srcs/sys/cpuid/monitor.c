/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 02:04:20 by reclaire          #+#    #+#             */
/*   Updated: 2025/02/18 02:35:39 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cpuid_private.h"

bool ft_cpuid_get_monitor_mwait_infos(U32 maxinfos, struct s_cpuid_monitor_mwait_infos *infos)
{
	U32 reg;
	U32 sub;
	U32 out[4];

	reg = 1;
	sub = 0;
	if (reg >= maxinfos)
		FT_RET_ERR(FALSE, FT_ENOENT);

	ft_cpuid(reg, sub, out);
	infos->min_monitor_line_size = out[_EAX] & 0xFFFF;
	infos->max_monitor_line_size = out[_EBX] & 0xFFFF;

	infos->extensions_enumerations = out[_ECX] & (1 << 0);
	infos->mwait_treat_interrupts_as_break_events = out[_ECX] & (1 << 1);
	infos->mwait_monitorless = out[_ECX] & (1 << 3);

	for (U8 i = 0; i < 8; i++)
		infos->sub_states_cnt[i] = (out[_EDX] >> (i * 4)) & 0xF;

	FT_RET_OK(TRUE);
}
