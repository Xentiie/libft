/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_behaviour.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 20:32:31 by reclaire          #+#    #+#             */
/*   Updated: 2024/02/12 15:46:35 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_tests.h"
#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define PERF_ITER 100000

int pipefd[2];
int stdout_save;

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

void start_stdout_redirect()
{
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		exit(1);
	}
	if ((stdout_save = dup(ft_stdout)) < 0)
	{
		perror("dup");
		exit(1);
	}
	if (dup2(pipefd[1], ft_stdout) < 0)
	{
		perror("dup2");
		exit(1);
	}
	close(pipefd[1]);
}

char *read_stdout_redirect()
{
	fflush(stdout);
	char *out = ft_strdup("");
	char buf[4096];
	U64 br = 0;

	while ((br = ft_fread(pipefd[0], buf, sizeof(char) * 4095)) > 0)
	{
		
	}
	if (br == -1)
	{
		
	}
}

void end_stdout_redirect()
{
	close(pipefd[0]);
	if (dup2(stdout_save, 1) < 0)
	{
		perror("dup2");
		exit(1);
	}
    close(stdout_save);
}

int main()
{
	t_test_infos tests = get_test_infos();

	if (tests.init)
	{
		printf("TESTS INIT\n");
		tests.init();
	}

	printf("FUNCTION BEHAVIOUR TESTS\n");
	for (int i = 0; i < tests.behaviour_test_count; i++)
	{
		if (tests.behaviour_tests[i]())
			printf("    -> %s: PASSED\n", tests.behaviour_tests_names[i]);
		else
		{
			printf("    -> %s: FAILED", tests.behaviour_tests_names[i]);
			if (ft_errno != FT_OK)
				printf(" (ft_errno: %d)\n", ft_errno);
			else
				printf("\n");
		}
	}
	free(tests.behaviour_tests);
	free(tests.behaviour_tests_names);
	free(tests.perf_tests);
	free(tests.perf_tests_names);
}
