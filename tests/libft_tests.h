/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_tests.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 20:34:20 by reclaire          #+#    #+#             */
/*   Updated: 2024/02/12 01:03:33 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_TESTS_H
# define LIBFT_TESTS_H

# ifdef FT_NO_ALL
#  undef FT_NO_ALL
# endif

# define FT_NO_MEMCHECK

# include "libft/ansi.h"
# include "libft/debug.h"
# include "libft/getopt.h"
# include "libft/strings.h"
# include "libft/std.h"
# include "libft/lists.h"
# include "libft/io.h"
# include "libft/limits.h"
# include "libft/macros.h"
# include "libft/time.h"
# include "libft/maths.h"

# include <stdio.h>
# include <stdint.h>
# include <time.h>
# include <stdlib.h>

typedef void (*init_test)();
typedef bool (*behaviour_test)();
typedef U64 (*perf_test)();
typedef void (*cleanup_test)();

typedef struct s_test_infos
{
	init_test		init;

	int				behaviour_test_count;
	behaviour_test	*behaviour_tests;
	char			**behaviour_tests_names;

	int				perf_test_count;
	perf_test		*perf_tests;
	char			**perf_tests_names;
}	t_test_infos;

t_test_infos get_test_infos();

uint64_t rdtsc();

//create_behaviour_tests(&tests, t1, "name1", t2, "name2", ...)
void create_behaviour_tests(t_test_infos *infos, ...);
void create_perf_tests(t_test_infos *infos, ...);
#define CHECK(x) ({ if (!(x)) return FALSE; })
#define TIMER_INIT() uint64_t __start, __end
#define TIMER_START() __start = rdtsc()
#define TIMER_END() __end = rdtsc()
#define TIMER_RESULT() __end - __start

#endif