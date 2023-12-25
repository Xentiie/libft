/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_test_itoa.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 03:47:09 by reclaire          #+#    #+#             */
/*   Updated: 2023/08/18 04:10:43 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_tests.h"

S32 ft_test_itoa()
{
	int err = 0;
	
	string tmp = ft_itoa(31);
	TEST(tmp);
	TEST(tmp[0] == '3' && tmp[1] == '1');
	free(tmp);

	tmp = ft_itoa(11111);
	TEST(tmp);
	TEST(tmp[0] == '1' && tmp[1] == '1' && tmp[2] == '1' && tmp[3] == '1' && tmp[4] == '1');
	free(tmp);

	tmp = ft_itoa(111112);
	TEST(tmp);
	TEST(tmp[0] == '1' && tmp[1] == '1' && tmp[2] == '1' && tmp[3] == '1' && tmp[4] == '1' && tmp[5] == '2');
	free(tmp);

	ft_check_leaks();
	return err;
}
