/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 01:29:45 by reclaire          #+#    #+#             */
/*   Updated: 2025/05/19 17:40:34 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(FT_BITS_ASM_UTILS_H)
#define FT_BITS_ASM_UTILS_H

/*
Inline asm constraints table:

/-----------------+-------------------------------------------------------------------------------\
| Constraint      | Meaning                                                                       |
+-----------------+-------------------------------------------------------------------------------+
| `"r"`           | Use any general-purpose register                                              |
| `"m"`           | Use a memory location                                                         |
| `"i"`           | An immediate integer constant (must be known at compile time)                 |
| `"g"`           | "General": either memory or register                                          |
| `"0"`, `"1"`... | Tells compiler that this operand is the same as output operand `0`, `1`, etc. |
| `"a"`           | Use the `eax` register                                                        |
| `"b"`           | Use the `ebx` register                                                        |
| `"c"`           | Use the `ecx` register                                                        |
| `"d"`           | Use the `edx` register                                                        |
\-----------------+-------------------------------------------------------------------------------/

Constraints order:
output -> inputs -> clobbers
Exemple:
	`asm("..." : "=a"(output_var) : "a"(input_var1), "r"(input_var2) : "xmm0")`
	The output is expected to be in the `ax` register at the end of the inline asm.
	The content of `input_var1` will be put into the `ax` register right before the inline asm.
	The content of `input_var2` will be put in any register right before the inline asm, and can be referenced using `%x` (`%0`, `%1`...).
	The register `xmm0` is marked as 'used' somewhere in the inline asm, it's content will be stored and restored before and after the inline asm,
	if necessary.
*/

/* Formats an inline asm output operand.
 * `constraint` is the constraint used.
 * `cvar` is the output C variable.
 * Exemples:
 *  `asm_output(a, myvar)` => `"=a"(myvar)`
 *  `asm_output(m, myvar)` => `"=m"(myvar)` */
#define asm_output(constraint, cvar) "="#constraint(cvar)

/* Formats an inline asm input operand.
 * `constraint` is the constraint used.
 * `cvar` is the input C variable.
 * Exemples:
 *  `asm_input(a, myvar)` => `"a"(myvar)`
 *  `asm_input(m, myvar)` => `"m"(myvar)` */
#define asm_input(constraint, cvar) #constraint(cvar)

/* Formats an inline asm input/output operand.
 * `constraint` is the constraint used.
 * `cvar` is the input C variable.
 * Exemples:
 *  `asm_input(a, myvar)` => `"a"(myvar)`
 *  `asm_input(m, myvar)` => `"m"(myvar)` */
#define asm_input_output(constraint, cvar) "+"#constraint(cvar)

/* Formats an inline asm clobber register.
 * `reg` is the register used.
 * Exemples:
 *  `asm_clobber(xmm1)` => `"xmm1"` */
#define asm_clobber(reg) #reg

#endif
