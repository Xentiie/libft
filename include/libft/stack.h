/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 23:46:34 by reclaire          #+#    #+#             */
/*   Updated: 2025/04/24 21:58:33 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(FT_STACK_H)
#define FT_STACK_H

#include "libft/libft.h"

typedef struct s_stack
{
	U64 elem_size;
	U32 alloc;
	U32 cnt;
	U8 *data;
} t_stack;

/*
Initializes the specified stack
### On error
Sets ft_errno and returns FALSE.
### ft_errno
- FT_EOMEM if out of memory
*/
extern bool ft_stack_init(t_stack *stack, U64 elem_size, U64 init_size);

/* Destroys the specified stack */
extern void ft_stack_destroy(t_stack *stack);

/* Returns the element at the top of the stack, or NULL if stack is empty */
extern void *ft_stack_top(t_stack *stack);

/*
Allocates space for a new stack element, and returns a pointer to said element.
#### /!\ The pointer validity is only guaranteed until a subsequent call to `ft_stack_push`. Use `ft_stack_push2` if a reference to returned element is required
### On error
Sets ft_errno and returns NULL.
### ft_errno
See `ft_stack_push`
*/
extern void *ft_stack_push(t_stack *stack);

/*
Allocates space for a new stack element, and the offset of said element in the stack.
### On error
Sets ft_errno and returns NULL.
### ft_errno
- FT_EOMEM if out of memory
*/
extern U64 ft_stack_push2(t_stack *stack);

/*
`type *ft_stack_get(t_stack *stack, U64 ofs)`
Returns an element at a specific offset. The returned element is cast to `type *`
*/
#define ft_stack_get(stack, ofs, type) ((type *)((stack)->data + (ofs)))

/*
Pops and returns the element at the top of the stack
#### /!\ The pointer validity is only guaranteed until a subsequent call to `ft_stack_push`.
*/
extern void *ft_stack_pop(t_stack *stack);

/*
Pops and returns the offset in the stack of the element at the top of the stack
#### /!\ The offset validity is only guaranteed until a subsequent call to `ft_stack_push`.
*/
extern U64 ft_stack_pop2(t_stack *stack);

#endif
