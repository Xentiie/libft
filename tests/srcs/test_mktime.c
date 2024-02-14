/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_mktime.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 19:30:56 by reclaire          #+#    #+#             */
/*   Updated: 2024/02/14 19:39:52 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_tests.h"
#include <time.h>

void test_init()
{

}

/* behaviour tests */
bool test_behaviour1()
{
	time_t t = time(NULL);

	struct tm *orig = gmtime(&t);
	t_tm ft = ft_mktime(t);

	CHECK(orig->tm_sec == ft.second);
	CHECK(orig->tm_min == ft.minute);
	CHECK(orig->tm_hour == ft.hour);
	CHECK(orig->tm_wday == ft.week_day);
	CHECK(orig->tm_mday == ft.month_day);
	CHECK(orig->tm_yday == ft.year_day);
	CHECK(orig->tm_mon == ft.month);
	CHECK(orig->tm_year == ft.year);

	return TRUE;
}

/* performance tests  WILL BE RUN MULTIPLE TIMES */
U64 test_performance1()
{
	TIMER_INIT();
	
	time_t t = time(NULL);
	
	TIMER_START();
	t_tm ft = ft_mktime(t);
	TIMER_END();

	return TIMER_RESULT();
}

t_test_infos get_test_infos()
{
	t_test_infos infos;

	infos.init = test_init;
	
	create_behaviour_tests(&infos,
		test_behaviour1, "behaviour test 1",
	NULL);

	create_perf_tests(&infos,
		test_performance1, "performance test 1",
	NULL);

	return infos;
}

