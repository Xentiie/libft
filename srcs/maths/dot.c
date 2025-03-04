/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dot.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 22:45:45 by reclaire          #+#    #+#             */
/*   Updated: 2025/02/05 23:54:24 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/maths.h"
#include "libft_int.h"

inline F64 ft_dot2(t_v2 a, t_v2 b) { return (a.x * b.x + a.y * b.y); }

inline F64 ft_dot3(t_v3 a, t_v3 b)
{
#if 0
	// TODO: assumes t_v3 components to be double precision floating-point numbers
	__asm__(

		/*
		`vmovupd` pourrait nous permettre de charger nos t_v3 dans des registres, mais il agis sur
		4*64 bits. Cependant ici on a seulement 3*64 bits. Si on vmovupd sur une mauvaise addresse,
		ca crash. Donc on utilise `vmaskmovpd`, qui agit avec un mask en 2eme operand, et donc evite
		un crash.
		*/

		//TODO: Une fois de plus, j'ai le problème de charger une constante dans un registre ymm :/
		// ce coup ci je tente de charger depuis une addresse mémoire
		".section .rodata\n"
		"loading_mask: .long "
		"vmaskmovpd ymm0, [rax]\n" // Load 'a' into
		"vmaskmovpd ymm1, [rbx]\n"

		: "=a"(result)
		: "a"(&a), "b"(&b)
		: "ymm0", "ymm1");
#endif

	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

inline F64 ft_dot3_4(t_v4 a, t_v4 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}
