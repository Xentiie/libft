/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 15:38:35 by reclaire          #+#    #+#             */
/*   Updated: 2023/12/25 00:12:23 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_tests.h"

int main(int argc, char **argv)
{
	ft_argc = argc;
	ft_argv = (const_string)argv;
	ft_memcheck_init((const_string*)argv, FALSE);

	t_error_code err = FT_OK;
	t_array array = ft_array_new(sizeof(int));
	if (err != FT_OK) {printf("Error: %s\n", FT_ERROR_LOOKUP(err));}
	for (int i = 0; i < 10; i++)
	{
		ft_array_append(array, &i);
		if (err != FT_OK) {printf("Error: %s\n", FT_ERROR_LOOKUP(err));}
	}
	
	ft_array_free(array);
	ft_check_leaks();

	//if (
	//	//ft_test_array() || (!printf("\n")) ||
	//	//ft_test_itoa() || (!printf("\n")) ||
	//	//ft_test_ftoa() || (!printf("\n")) ||
	//	ft_test_hashmap() || (!printf("\n")) ||
	//	//ft_test_vectors() || (!printf("\n")) ||
	//	//ft_test_debug() || (!printf("\n")) ||
	//0)
	//	return 1;
}
