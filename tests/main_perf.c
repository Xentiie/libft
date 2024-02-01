/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 20:32:31 by reclaire          #+#    #+#             */
/*   Updated: 2024/01/24 20:32:31 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_tests.h"
#include <stdarg.h>
#include <stdlib.h>

#define PERF_ITER 100000

// create_behaviour_tests(&tests, t1, "name1", t2, "name2", ..., NULL)
void create_behaviour_tests(t_test_infos *infos, ...)
{
	va_list args;
	va_list args_save;
	va_start(args_save, infos);
	va_copy(args, args_save);

	infos->behaviour_test_count = 0;
	while (va_arg(args, behaviour_test) != NULL)
	{
		(void)va_arg(args, char *);
		infos->behaviour_test_count++;
	}

	infos->behaviour_tests = malloc(sizeof(behaviour_test) * infos->behaviour_test_count);
	infos->behaviour_tests_names = malloc(sizeof(char *) * infos->behaviour_test_count);

	va_copy(args, args_save);
	for (int i = 0; i < infos->behaviour_test_count; i++)
	{
		infos->behaviour_tests[i] = va_arg(args, behaviour_test);
		infos->behaviour_tests_names[i] = va_arg(args, char *);
	}
}

void create_perf_tests(t_test_infos *infos, ...)
{
	va_list args;
	va_list args_save;
	va_start(args_save, infos);
	va_copy(args, args_save);

	infos->perf_test_count = 0;
	while (va_arg(args, perf_test) != NULL)
	{
		(void)va_arg(args, char *);
		infos->perf_test_count++;
	}

	infos->perf_tests = malloc(sizeof(perf_test) * infos->perf_test_count);
	infos->perf_tests_names = malloc(sizeof(char *) * infos->perf_test_count);

	va_copy(args, args_save);
	for (int i = 0; i < infos->perf_test_count; i++)
	{
		infos->perf_tests[i] = va_arg(args, perf_test);
		infos->perf_tests_names[i] = va_arg(args, char *);
	}
}

uint64_t rdtsc()
{
	uint32_t lo, hi;
	asm volatile("rdtsc" : "=a"(lo), "=d"(hi));
	return ((uint64_t)hi << 32) | lo;
}

int main()
{
	t_test_infos tests = get_test_infos();

	if (tests.init)
	{
		printf("TESTS INIT\n");
		tests.init();
	}

	printf("FUNCTION PERFORMANCE TESTS\n");

	for (int i = 0; i < tests.perf_test_count; i++)
	{
		double average = 0;
		for (int j = 0; j < PERF_ITER; j++)
			average += tests.perf_tests[i]();
		average /= PERF_ITER;
		printf("    %s: %lf\n", tests.perf_tests_names[i], average);
	}
}
