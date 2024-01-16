/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tests.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 05:04:29 by reclaire          #+#    #+#             */
/*   Updated: 2023/10/11 03:47:43 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_TESTS_H
# define FT_TESTS_H

# ifndef FT_MEMCHECK
#  define FT_MEMCHECK
# endif
# ifndef FT_DEBUG
#  define FT_DEBUG
# endif
# include "libft.h"
# include <stdio.h>

# define RED "\e[0;91m"
# define GREEN "\e[0;92m"
# define RESET "\e[0m"

# define TEST(X) do {printf("%s:%d TESTING: %s: ", __FILE__, __LINE__, #X);fflush(stdout);if (X) {printf(GREEN"OK"RESET"\n");} else {printf(RED"KO"RESET"\n"); err=1;}} while(0);


S32 ft_test_array();
S32	ft_test_hashmap();
S32 ft_test_itoa();
S32 ft_test_ftoa();
S32	ft_test_vectors();
S32	ft_test_debug();

#endif