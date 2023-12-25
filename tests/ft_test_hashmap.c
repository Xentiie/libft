/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_test_hashmap.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 05:17:12 by reclaire          #+#    #+#             */
/*   Updated: 2023/10/11 03:45:17 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_tests.h"

int ft_test_hashmap()
{
	int err = 0;


	t_hash_map	map = ft_hash_init(NULL, sizeof(S32), sizeof(F32));
	t_array		arr;
	TEST(ft_array_init(&arr, sizeof(F32)) == FT_OK);
	TEST(map);

	S32 k1 = 0;
	F32 v1 = 0.1f;
	t_array_code _err;
	TEST(ft_hash_put(map, &k1, ft_array_append(arr, &v1, &_err)) == FT_OK && _err == FT_OK);
	
	F32 *ret;
	TEST(ft_hash_get(map, &k1, (t_hash_any*)&ret) == FT_OK);
	TEST(*ret == v1);


	t_hash_map map2 = ft_hash_init(NULL, sizeof(S32), sizeof(F32));
	for (S32 i = 0; i < 2047; i++)
	{
		S32 k = i;
		F32 v = i / 2.0f;
		TEST(ft_hash_put(map2, &k, ft_array_append(arr, &v, &_err)) == FT_OK && _err == FT_OK);
	}

	for (S32 i = 0; i < 2047; i++)
	{
		S32 k = i;
		F32 *ret;
		TEST(ft_hash_get(map2, &k, (t_hash_any*)&ret) == FT_OK);
		TEST(*ret == i / 2.0f);
	}




	TEST(ft_hash_free(map) == FT_OK);
	TEST(ft_hash_free(map2) == FT_OK);
	ft_array_free(arr);





	int in;
	int *out;
	t_array		test_arr;
	t_hash_map	test_vec = ft_hash_init(NULL, sizeof(t_iv3), sizeof(int));
	ft_array_init(&test_arr, sizeof(S32));

#define HASH_TEST(...) in = __COUNTER__;\
	ft_hash_put(test_vec, &(t_iv3){__VA_ARGS__}, ft_array_append(test_arr, &in, NULL));\
	ft_hash_get(test_vec, &(t_iv3){__VA_ARGS__}, (t_hash_any)&out);\

	HASH_TEST(0, 0, 0);
	HASH_TEST(1, 1, 0);
	HASH_TEST(2, 2, 0);
	HASH_TEST(3, 3, 0);
	out = NULL;
	ft_hash_get(test_vec, &(t_iv3){2, 0, 1}, (t_hash_any)&out);
	TEST(out == NULL);

	TEST(ft_hash_free(test_vec) == FT_OK);
	ft_array_free(test_arr);

	ft_check_leaks();
	return err;
}
