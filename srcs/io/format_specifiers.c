/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_specifiers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 17:33:00 by reclaire          #+#    #+#             */
/*   Updated: 2025/03/31 00:33:44 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/std.h"
#include "libft/io.h"
#include "libft/bits/format_specifiers.h"

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

static char parse_specifier(char fmt, struct s_fmt_flag *specifier, enum e_fmt_flag expected_type, U32 *flags)
{
	U32 i;

	for (i = 0; specifier[i].c != 0; i++)
	{
		if (specifier[i].type == expected_type)
		{
			if (specifier[i].c == fmt)
		{
			(*flags) |= specifier[i].flag;
			break;
		}
		else if (specifier[i].type == FMT_SIZE && specifier[i].c > 127 && specifier[i].c - 127 == fmt)
		{
			(*flags) |= (specifier[i].flag << 1);
			break;
		}
		}
	}
	return specifier[i].c;
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

char ft_parse_specifier(const_string fmt, S32 *nextarg, struct s_fmt_flag *specifiers, struct s_fmt_spec *out)
{
	S32 pos_nextarg;
	S32 n2;
	S32 nextarg_save;
	char ret;

	nextarg_save = (*nextarg);
	ret = 0;
	while (*fmt && ret == 0)
	{
		*nextarg = nextarg_save;

		while (*fmt && *fmt != '%')
			fmt++;
		if (*fmt == '\0' || *(fmt + 1) == '\0')
		{
			out->begin = NULL;
			return 0;
		}
		if (*(fmt + 1) == '%')
		{
			fmt += 2;
			continue;
		}
		ft_bzero(out, sizeof(struct s_fmt_spec));
		out->begin = (string)fmt;
		fmt++;

		out->argpos = parse_specifier_argpos(&fmt);
		while (parse_specifier(*fmt, specifiers, FMT_FLAG, &out->flags))
			fmt++;

		out->width = parse_width(&fmt, &out->width_argpos, nextarg);
		out->prec = parse_prec(&fmt, &out->prec_argpos, nextarg);

		if (out->argpos == -1)
			out->argpos = (*nextarg)++;

		while (parse_specifier(*fmt, specifiers, FMT_SIZE, &out->flags))
			fmt++;

		ret = parse_specifier(*fmt, specifiers, FMT_SPEC, &out->flags);
		fmt++;

		if (ret != 0)
			out->length = fmt - out->begin;
	}

	if (ret == 0)
		out->begin = NULL;
	return ret;
}

#if defined(TEST)
#include <stdio.h>

int main()
{
#define FL_ALT (1 << 0)
#define FL_ZEROPAD (1 << 1)
#define FL_SPACEPAD (1 << 2)
#define FL_LEFTJUST (1 << 3)
#define FL_SHOWSIGN (1 << 4)
#define FL_SPACESIGN (1 << 5)

#define FL_T_SHORT (1 << 7)
#define FL_T_LONG (1 << 8)
#define FL_T_LONGLONG (1 << 9)

#define FL_SPEC_UNSIGNED (1 << 10)

#define FL_SPEC_N (1 << 11)
#define FL_SPEC_STRING (2 << 11)
#define FL_SPEC_NUMBER (3 << 11)
#define FL_SPEC_FLOATING_POINT (4 << 11)
#define FL_SPEC_HEX (5 << 11)

	sizeof(struct s_fmt_flag);

	struct s_fmt_flag specifiers[] = {
		{ .type = FMT_FLAG, .c = '#', .flag = FL_ALT },
		{ .type = FMT_FLAG, .c = '0', .flag = FL_ZEROPAD },
		{ .type = FMT_FLAG, .c = ' ', .flag = FL_SPACEPAD },
		{ .type = FMT_FLAG, .c = '-', .flag = FL_LEFTJUST },
		{ .type = FMT_FLAG, .c = '+', .flag = FL_SHOWSIGN },
		{ .type = FMT_FLAG, .c = '\'', .flag = 0 },
		{ .type = FMT_FLAG, .c = 'I', .flag = 0 },

		{ .type = FMT_SIZE, .c = 'h', .flag = FL_T_SHORT },
		{ .type = FMT_SIZE, .c = 'l' + 127, .flag = FL_T_LONG },
		{ .type = FMT_SIZE, .c = 'j', .flag = FL_T_LONGLONG },
		{ .type = FMT_SIZE, .c = 'z', .flag = FL_T_LONGLONG },
		{ .type = FMT_SIZE, .c = 'Z', .flag = FL_T_LONGLONG },
		{ .type = FMT_SIZE, .c = 't', .flag = FL_T_LONGLONG },
		{ .type = FMT_SIZE, .c = 'L', .flag = FL_T_LONGLONG },
		{ .type = FMT_SIZE, .c = 'q', .flag = FL_T_LONGLONG },

		{ .type = FMT_SPEC, .c = 'n', .flag = FL_SPEC_N },
		{ .type = FMT_SPEC, .c = 'c', .flag = FL_SPEC_STRING },
		{ .type = FMT_SPEC, .c = 'D', .flag = FL_T_LONG | FL_SPEC_NUMBER },
		{ .type = FMT_SPEC, .c = 'd', .flag = FL_SPEC_NUMBER },
		{ .type = FMT_SPEC, .c = 'i', .flag = FL_SPEC_NUMBER },

		{.c = '#', .flag = FL_ALT, .type = FMT_FLAG},
		{.c = '0', .flag = FL_ZEROPAD, .type = FMT_FLAG},
		{.c = ' ', .flag = FL_SPACEPAD, .type = FMT_FLAG},
		{.c = '-', .flag = 0x80, .type = FMT_FLAG},
		{.c = '+', .flag = 0x100, .type = FMT_FLAG},

		{.c = 's', .flag = 0x1, .type = FMT_SPEC},
		{.c = 'd', .flag = 0x2, .type = FMT_SPEC},
		{.c = 'c', .flag = 0x4, .type = FMT_SPEC},
		{.c = 'u', .flag = 0x8, .type = FMT_SPEC},	
	
		{.c = 'h', .flag = 0x200, .type = FMT_SIZE},
		{.c = 'l' + 127, .flag = 0x400, .type = FMT_SIZE},
		{.c = 'j', .flag = 0x800, .type = FMT_SIZE},
		{.c = 'z', .flag = 0x800, .type = FMT_SIZE},
		{.c = 'Z', .flag = 0x800, .type = FMT_SIZE},
		{.c = 't', .flag = 0x800, .type = FMT_SIZE},
		{.c = 'L', .flag = 0x800, .type = FMT_SIZE},
		{.c = 'q', .flag = 0x800, .type = FMT_SIZE},
		{0},
	};

	struct s_fmt_spec out;

	if (ft_argc < 2)
		return 1;

	for (S32 i = 1; i < ft_argc; i++)
	{
		S32 nextarg = 0;
		string ptr = ft_argv[i];

		while (TRUE)
		{
			char c = ft_parse_specifier(ptr, &nextarg, specifiers, &out);
			if (out.begin == NULL)
			{
				ft_printf("done\n");
				break;
			}
			ft_printf("%.*s (l:%lu) (%#x)\n\t", out.length, out.begin, out.length, out.flags);

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
