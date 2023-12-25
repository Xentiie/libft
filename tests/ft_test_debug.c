/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_test_debug.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 04:26:46 by reclaire          #+#    #+#             */
/*   Updated: 2023/10/11 03:48:10 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_tests.h"

S32	ft_test_debug()
{
	void *ptr = malloc(1000);
	ft_check_leaks();
	(free)(ptr);

	ptr = malloc(1000);
	free(ptr);

	free(ptr);

	return 0;
	
}
