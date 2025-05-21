/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 15:39:47 by reclaire          #+#    #+#             */
/*   Updated: 2025/05/19 17:46:07 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/std.h"
#include "libft/io.h"
#include "libft/strings.h"
#include "libft/getopt.h"

#include "libft/bits/variants/ft_strlen.h"

enum e_test
{
	TEST_FT_STRLEN,
};

struct s_test
{
	string name;
	enum e_test test;
};

t_long_opt longopts[] = {
	{"all", no_argument, NULL, 'a'},
	{"test", required_argument, NULL, 't'},
	{0},
};

struct s_test all_tests[] = {
	{"ft_strlen", TEST_FT_STRLEN},
};

S32 main()
{
	const char _str[] = "abcdefghijklmnopqrstuvw";
	string str = ft_strdup(_str);

	ft_printf("true %lu\n", sizeof(_str) - 1);
	ft_printf("strlen: %lu\n", __ft_strlen_base(str));
	ft_printf("strlen64: %lu\n", __ft_strlen_64(str));

	ft_printf("%#lx\n", str);
	ft_printf("%#lx\n", (U64)str & 0xF);
	ft_printf("%#lx\n", ((U64)str & 0xF) & -0x10);
}
