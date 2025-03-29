/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_specifiers_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 17:33:00 by reclaire          #+#    #+#             */
/*   Updated: 2025/03/29 16:21:04 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/std.h"
#include "libft/io.h"

struct s_fmt_flag
{
	char c;
	U32 flag;
};

/*
Format specifier types, for printf like formatting, to use with `ft_parse_specifier`
`begin` is the start of the specifier, or `NULL` if no format specifier was found, in which case all the other members values are undefined
`length` is the length of the specifier
`flags` is the combined specifier, specifier flags and size flags of the found specifier
`width` is the requested width (padding), or `-1` if no width specified
`width_argpos` is the specified width argument index, or `-1` if no argument index specified. Takes priority over `width` if `width_argpos!= -1`
`prec` is the requested precision, or `-1` if no precision specified
`prec_argpos` is the specified precision argument index, or `-1` if no argument index specified. Takes priority over `prec` if `prec_argpos!= -1`
`argpos` is the specifier argument index
*/
struct s_fmt_spec
{
	/* NULL if none */
	string begin;
	U64 length;
	U32 flags;

	/* -1 if none */
	S32 width;
	/* -1 if none */
	S32 width_argpos;
	/* -1 if none */
	S32 prec;
	/* -1 if none */
	S32 prec_argpos;

	S32 argpos;
};

/* parses and returns the unsigned integer `X` in `X$`. returns `-1` if no argument position specifier is found */
static S32 parse_specifier_argpos(const_string *_fmt)
{
	const_string fmt;
	S32 n;

	n = 0;
	fmt = *_fmt;
	while (ft_isdigit(*fmt))
	{
		n = n * 10 + (*fmt - '0');
		fmt++;
	}

	/* make sure the $ dollar sign is present */
	if (*fmt == '$' && n > 0)
	{
		*_fmt = fmt + 1;
		return n - 1;
	}

	/* woops, wasn't an argument position specifier */
	return -1;
}

static U32 parse_specifier_multiple(const_string *_fmt, struct s_fmt_flag *specifier_flags)
{
	const_string fmt;
	S32 flags;
	U32 i;

	fmt = *_fmt;
	flags = 0;
	while (*fmt)
	{
		for (i = 0; specifier_flags[i].c != 0; i++)
		{
			if (specifier_flags[i].c == *fmt)
			{
				flags |= specifier_flags[i].flag;
				break;
			}
		}

		if (specifier_flags[i].c == 0)
			break;
		fmt++;
	}

	*_fmt = fmt;
	return flags;
}

static U32 parse_specifier_single(char fmt, struct s_fmt_flag *specifier, bool *valid)
{
	S32 flags;
	U32 i;

	flags = 0;
	for (i = 0; specifier[i].c != 0; i++)
	{
		if (specifier[i].c == fmt)
		{
			flags |= specifier[i].flag;
			break;
		}
	}
	*valid = specifier[i].c != 0;
	return flags;
}

static S32 parse_width(const_string *_fmt, S32 *arg_n, S32 *nextarg)
{
	const_string fmt;
	S32 n;

	fmt = *_fmt;
	n = 0;
	switch (*fmt)
	{
	case '*':
		fmt++;
		if (ft_isdigit(*fmt))
		{
			while (ft_isdigit(*fmt))
			{
				n = n * 10 + (*fmt - '0');
				fmt++;
			}
			if (*fmt == '$')
			{
				*_fmt = fmt + 1;
				*arg_n = n - 1;
				return -1;
			}
			else
			{
				*_fmt = (*_fmt) + 1;
				*arg_n = (*nextarg)++;
				return -1;
			}
		}
		else
		{
			*_fmt = (*_fmt) + 1;
			*arg_n = (*nextarg)++;
			return -1;
		}
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
		while (ft_isdigit(*fmt))
		{
			n = n * 10 + (*fmt - '0');
			fmt++;
		}
		*arg_n = -1;
		*_fmt = fmt;
		return n;
	default:
		*arg_n = -1;
		return -1;
	}
}

static S32 parse_prec(const_string *_fmt, S32 *arg_n, S32 *nextarg)
{
	const_string fmt;
	S32 n;

	if (**_fmt != '.')
	{
		*arg_n = -1;
		return -1;
	}
	(*_fmt)++;

	return parse_width(_fmt, arg_n, nextarg);
}

struct s_fmt_spec ft_parse_specifier(const_string fmt, S32 *nextarg, struct s_fmt_flag *specifiers, struct s_fmt_flag *specifier_flags, struct s_fmt_flag *size_flags)
{
	struct s_fmt_spec out;
	S32 pos_nextarg;
	S32 n2;
	S32 nextarg_save;
	bool valid;

	nextarg_save = (*nextarg);
	valid = FALSE;
	while (*fmt && !valid)
	{
		ft_bzero(&out, sizeof(struct s_fmt_spec));
		*nextarg = nextarg_save;

		while (*fmt && *fmt != '%')
			fmt++;
		if (*fmt == '\0' || *(fmt + 1) == '\0')
		{
			out.begin = NULL;
			return out;
		}
		if (*(fmt + 1) == '%')
		{
			fmt += 2;
			continue;
		}
		out.begin = (string)fmt;
		fmt++;

		out.argpos = parse_specifier_argpos(&fmt);
		if (specifier_flags)
			out.flags |= parse_specifier_multiple(&fmt, specifier_flags);

		out.width = parse_width(&fmt, &out.width_argpos, nextarg);
		out.prec = parse_prec(&fmt, &out.prec_argpos, nextarg);

		if (out.argpos == -1)
			out.argpos = (*nextarg)++;

		if (size_flags)
			out.flags |= parse_specifier_multiple(&fmt, size_flags);

		out.flags |= parse_specifier_single(*fmt, specifiers, &valid);
		fmt++;

		if (valid)
			out.length = fmt - out.begin;
	}

	if (!valid)
		out.begin = NULL;
	return out;
}

#if defined(TEST)
#include <stdio.h>

int main()
{
	struct s_fmt_flag specifiers[] = {
		{.c = 's', .flag = 0x1},
		{.c = 'd', .flag = 0x2},
		{.c = 'c', .flag = 0x4},
		{.c = 'u', .flag = 0x8},
		{0},
	};

	struct s_fmt_flag specifiers_flags[] = {
		{.c = '#', .flag = 0x10},
		{.c = ' ', .flag = 0x20},
		{.c = '0', .flag = 0x40},
		{.c = '-', .flag = 0x80},
		{.c = '+', .flag = 0x100},
		{0},
	};

	struct s_fmt_flag specifiers_sizes[] = {
		{.c = 'h', .flag = 0x200},
		{.c = 'l', .flag = 0x400},
		{.c = 'j', .flag = 0x800},
		{.c = 'z', .flag = 0x800},
		{.c = 'Z', .flag = 0x800},
		{.c = 't', .flag = 0x800},
		{.c = 'L', .flag = 0x800},
		{.c = 'q', .flag = 0x800},
	};

	struct s_fmt_spec out;

	if (ft_argc < 2)
		return 1;

	for (S32 i = 1; i < ft_argc; i++)
	{
		S32 nextarg = 0;
		string ptr = ft_argv[i];

		ft_printf("%1$-*1$.*1$d\n", 5);

		while (TRUE)
		{
			out = ft_parse_specifier(ptr, &nextarg, specifiers, specifiers_flags, NULL);
			if (out.begin == NULL)
			{
				ft_printf("done\n");
				break;
			}
			ft_printf("%.*s (l:%lu)\n\t", out.length, out.begin, out.length, nextarg);

			if (out.flags & 0x10)
				ft_printf("alternative-form ");
			if (out.flags & 0x20)
				ft_printf("space-padded ");
			if (out.flags & 0x40)
				ft_printf("zero-padded ");
			if (out.flags & 0x80)
				ft_printf("left-justified ");
			if (out.flags & 0x100)
				ft_printf("plus-signed ");

			if (out.flags & 0x800)
				ft_printf("long long precision ");
			else if (out.flags & 0x400)
				ft_printf("long precision ");
			else if (out.flags & 0x200)
				ft_printf("half precision ");

			switch (out.flags & 0xF)
			{
			case 0x1:
				ft_printf("str ");
				break;
			case 0x2:
				ft_printf("decimal ");
				break;
			case 0x4:
				ft_printf("char ");
				break;
			case 0x8:
				ft_printf("unsigned ");
				break;
			}

			ft_printf("in argument %d ", out.argpos);
			if (out.width >= 0)
				ft_printf("with %d max width ", out.width);
			if (out.width_argpos >= 0)
				ft_printf("with max width in argument %d ", out.width_argpos);

			if ((out.width >= 0 || out.width_argpos >= 0) && (out.prec >= 0 || out.prec_argpos >= 0))
				ft_printf("and ");
			else if (out.prec >= 0 || out.prec_argpos >= 0)
				ft_printf("with ");

			if (out.prec >= 0)
				ft_printf("%d precision ", out.prec);
			if (out.prec_argpos >= 0)
				ft_printf("precision in argument %d ", out.prec_argpos);
			ft_printf("\n\n");

			// return 0;
			ptr = out.begin + out.length;
		}
	}
}
#endif
