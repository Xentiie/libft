/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getopt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 01:30:07 by reclaire          #+#    #+#             */
/*   Updated: 2025/04/15 01:50:51 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(LIBFT_GETOPT_H)
#define LIBFT_GETOPT_H

#include "libft/libft.h"

_FT_GLOBAL_VAR_DEC(S32, ft_optopt)
_FT_GLOBAL_VAR_DEC(S32, ft_optind)
_FT_GLOBAL_VAR_DEC(S32, ft_opterr)
_FT_GLOBAL_VAR_DEC(S32, ft_optchr)
_FT_GLOBAL_VAR_DEC(const_string, ft_optarg)

#define ft_optopt _FT_GLOBAL_VAR(ft_optopt)
#define ft_optind _FT_GLOBAL_VAR(ft_optind)
#define ft_opterr _FT_GLOBAL_VAR(ft_opterr)
#define ft_optchr _FT_GLOBAL_VAR(ft_optchr)
#define ft_optarg _FT_GLOBAL_VAR(ft_optarg)

#if !defined(no_argument)
#define no_argument 0
#endif

#if !defined(required_argument)
#define required_argument 1
#endif

#if !defined(optional_argument)
#define optional_argument 2
#endif

typedef struct s_long_opt
{
	string name;
	S32 has_argument; /* can be either `no_argument` (0), `required_argument` (1), or `optional_argument` (2) */
	S32 *flag_ptr;
	S32 flag_value;
} t_long_opt;

/*
Parses option like GNU getopt.
Returns the char associated with the short opt found, or the `flag_value` value in the long opt found,
or if `flag_ptr` is not NULL, returns 0 and sets `flag_value` in the address pointer by `flag_ptr`
Returns a value <0 when done:
-1 if done
-2 if done because of '--'
-3 if an error has occured
### On error
Sets ft_errno and returns -2. `ft_optchr` should not be set to -2
### ft_errno
- FT_EOMEM if out of memory
*/
S32 ft_getopt(S32 argc, const_string *argv, const_string optstr);
S32 ft_getopt_long(S32 argc, const_string *argv, const_string optstr, const t_long_opt *longopts, S32 *longopts_index);
S32 ft_getopt_long_only(S32 argc, const_string *argv, const t_long_opt *longopts, S32 *longopts_index);

#endif