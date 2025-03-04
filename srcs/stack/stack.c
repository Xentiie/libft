/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 23:46:21 by reclaire          #+#    #+#             */
/*   Updated: 2025/03/05 00:18:38 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_int.h"

#include "libft/stack.h"

#include <stdlib.h>

/*
Macro au cas ou je décide de changer le (stack->cnt - 1)
/!\ Ca casse si stack->cnt == 0
*/
#define _stack_top(stack) (void *)(((U8 *)stack->data) + stack->elem_size * (stack->cnt - 1))

bool ft_stack_init(t_stack *stack, U64 elem_size, U64 init_size)
{
	stack->cnt = 0;
	stack->alloc = init_size;
	stack->elem_size = elem_size;
	if (UNLIKELY((stack->data = malloc(elem_size * stack->alloc)) == NULL))
		FT_RET_ERR(FALSE, FT_EOMEM);
	FT_RET_OK(TRUE);
}

void ft_stack_destroy(t_stack *stack)
{
	free(stack->data);
}

void *ft_stack_top(t_stack *stack)
{
	if (stack->cnt == 0)
		return NULL;
	return _stack_top(stack);
}

void *ft_stack_push(t_stack *stack)
{
	void *new;

	if (stack->cnt >= stack->alloc)
	{
		if (UNLIKELY((new = malloc(stack->elem_size * stack->alloc * _FT_GROWTH_FACTOR)) == NULL))
			FT_RET_ERR(NULL, FT_EOMEM);
		ft_memcpy(new, stack->data, stack->elem_size * stack->cnt);
		free(stack->data);
		stack->data = new;
		stack->alloc *= _FT_GROWTH_FACTOR;
	}
	stack->cnt++;
	FT_RET_OK(_stack_top(stack));
}

void *ft_stack_pop(t_stack *stack)
{
	void *out;

	if (stack->cnt == 0)
		return NULL;
	out = _stack_top(stack);
	stack->cnt--;
	return out;
}
