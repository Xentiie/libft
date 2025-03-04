/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_sha.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 18:34:06 by reclaire          #+#    #+#             */
/*   Updated: 2024/11/19 18:37:11 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_tests.h"
#include "libft/crypt/sha.h"

bool test_sha1_base()
{
	U8 buf[8192] = {[0 ... 8191] = 'a'};

	struct s_sha1_state state;
	U8 digest[20];

	ft_sha1_init(&state);
	ft_sha1_update(&state, buf, sizeof(buf));
	ft_sha1_final(&state, digest);

	
}

t_test_infos get_test_infos()
{
	t_test_infos infos;

	infos.init = NULL;
		create_behaviour_tests(&infos,
		(t_behaviour_test){ "sha1", test_sha1 },
	NULL);

	create_perf_tests(&infos,
	NULL);

	return infos;
}
