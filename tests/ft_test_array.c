/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_test_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 02:56:33 by reclaire          #+#    #+#             */
/*   Updated: 2023/10/11 03:48:43 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_tests.h"

# define ARRAY_SIZE 1024
# define ARRAY_TYPE S32

typedef struct s_test
{
	char a;
	S32 b;
	float c;
}	t_test;

S32	do_tests_on(t_array arr)
{
	S32 err = 0;
	TEST(ft_array_count(arr) == ARRAY_SIZE);
	for (S32 i = 0; i < ARRAY_SIZE; i++)
	{
		S32 *ptr = ft_array_get(arr, i);
		TEST(ptr && *ptr == i*10);
	}
	return err;
}

S32 ft_test_array()
{
	S32 err = 0;

	t_clock init;
	t_clock fill;
	t_clock get;
	t_clock free;
	clk_init(&init);
	clk_init(&fill);
	clk_init(&get);
	clk_init(&free);

	clk_start(&init);
	t_array arr1;
	TEST(ft_array_init(&arr1, sizeof(ARRAY_TYPE)) == FT_OK);
	clk_stop(&init);
	
	clk_start(&fill);
	for (S32 i = 0; i < ARRAY_SIZE; i++)
	{
		t_array_code err;
		TEST((*(int *)ft_array_append(arr1, &(S32){i*10}, &err) == i*10 && err == FT_OK));
	}
	clk_stop(&fill);

	clk_start(&get);
	do_tests_on(arr1);
	clk_stop(&get);

	clk_start(&free);
	ft_array_free(arr1);
	clk_stop(&free);


	printf(
"""init:%s\n\
fill:%s\n\
get:%s\n\
free:%s\n\
""",
		clk_fmt_elapsed_ns(&init),
		clk_fmt_elapsed_ns(&fill),
		clk_fmt_elapsed_ns(&get),
		clk_fmt_elapsed_ns(&free)
	);

	ft_check_leaks();

	return err;
}