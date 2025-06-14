/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_specifiers.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 11:40:50 by reclaire          #+#    #+#             */
/*   Updated: 2025/06/02 16:40:33 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(FT_BITS_FORMAT_SPECIFIERS_H)
#define FT_BITS_FORMAT_SPECIFIERS_H

#include "libft/libft.h"

packed_enum e_fmt_flag
{
	FMT_FLAG,
	FMT_SIZE,
	FMT_SPEC,
};

struct s_fmt_flag
{
	U8 c;
	enum e_fmt_flag type;
	U16 flag;
};

struct s_fmt_spec
{
	string begin;
	U64 length;
	U32 flags;

	S32 width;
	S32 width_argpos;
	S32 prec;
	S32 prec_argpos;

	S32 argpos;
	char spec;
};

/*
Searches the string `fmt` for format specifiers starting with '%'.
`nextarg`, `specifiers` and `out` must be valid pointers.

Format specifiers are compared against the `specifiers` array. The array must be terminate by an element where `specifiers->c == 0`.
Exemple:
```
struct s_fmt_flag specifiers[] = {
	{ .c = '#', .flag = 0x1, .type = FMT_FLAG },
	{ .c = 'd', .flag = 0x2, .type = FMT_SPEC },
	...
	{ .c = 0 } // (or {0})
};
```

The member `type` of `struct s_fmt_flag` specifies the valid location of the character in a specifier:
```
    %      FMT_FLAG     W      .          P      FMT_SIZE    FMT_SPEC

    |         |         |      |          |         |           |
    |         |         |      |          |         |           |
  begin   1 or more   width  begin        |     see notes     1 only
specifier                 precision   precision
```

Returns TRUE if a valid format specifier was found, FALSE otherwise
Additionnal infos are returned in `out`:
- `out->begin`: pointer to the beginning of the format specifier (i.e. pointer to  '%')
- `out->length`: length of the format specifier (include '%')
- `out->flags`: bitwise-or'ed combined flags
- `out->width`: width field of the specifier (`-1` if none specified, or if the width is specified in an argument)
- `out->width_argpos`: argument position of the width field (`-1` if none specified)
- `out->prec`: precision field of the specifier (`-1` if none specified, or if the precision is specified in an argument)
- `out->prec_argpos`: argument position of the precision field (`-1` if none specified)
- `out->argpos`: argument position for this format specifier
- `out->spec`: the final character in the format specifier

Notes:
If no valid specifiers are found, the value pointer to by `nextarg` stay unchanged, while the values in `out` are undefined. 
Even if no valid specifiers are found, values pointed to by `nextarg` and `out` can change.

FMT_SIZE: to allow multiple flags to combine (exemple: %lld, with double 'l'), if the member 'c' of a `struct s_fmt_flag` with
`type == FMT_SIZE` is greater than 127, then it's actual character will be `c - 127`, and 2 consecutive size specifier for that
character will be allowed. In that case, the bit flag set will be `flag << 1`.
*/
bool ft_parse_specifier(const_string fmt, S32 *nextarg, struct s_fmt_flag *specifiers, struct s_fmt_spec *out);

/*
Formats a parsed specifier back to a format string into buf, no more characters that buflen, using the infos in specifiers_lst. Returns
the number of characters written.
*/
U8 ft_write_specifier(string buf, U64 buflen, struct s_fmt_flag *specifiers_lst, struct s_fmt_spec *specifier);

#endif
