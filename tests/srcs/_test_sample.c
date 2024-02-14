/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _test_sample.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 19:30:56 by reclaire          #+#    #+#             */
/*   Updated: 2024/02/14 19:37:43 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_tests.h"

void test_init()
{

}

/* behaviour tests */
bool test_behaviour1()
{
	CHECK(1 != 2);

	if (1 == 1)
		return TRUE;
	else
		return FALSE;
}

bool test_behaviour2()
{
	CHECK(1 != 2);

	if (1 == 1)
		return TRUE;
	else
		return FALSE;
}


/* performance tests  WILL BE RUN MULTIPLE TIMES */
U64 test_performance1()
{
	TIMER_INIT();
	
	int a = 10;
	int b = 1000;
	
	TIMER_START();
	while (a < b)
		a++;
	TIMER_END();

	return TIMER_RESULT();
}

U64 test_performance2()
{
	TIMER_INIT();
	
	int a = 1000;
	int b = 10;
	
	TIMER_START();
	while (a > b)
		a--;
	TIMER_END();

	return TIMER_RESULT();
}


t_test_infos get_test_infos()
{
	t_test_infos infos;

	infos.init = test_init;
	
	create_behaviour_tests(&infos,
		test_behaviour1, "behaviour test 1",
		test_behaviour2, "behaviour test 2",
	NULL);

	create_perf_tests(&infos,
		test_performance1, "performance test 1",
		test_performance2, "performance test 2",
	NULL);

	return infos;
}

