/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_specifiers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 17:33:00 by reclaire          #+#    #+#             */
/*   Updated: 2025/03/31 15:52:10 by reclaire         ###   ########.fr       */
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
				if ((*flags) & specifier[i].flag)
				{
					(*flags) &= ~(specifier[i].flag);
					(*flags) |= (specifier[i].flag << 1);
				}
				else
					(*flags) |= specifier[i].flag;
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

bool ft_parse_specifier(const_string fmt, S32 *nextarg, struct s_fmt_flag *specifiers, struct s_fmt_spec *out)
{
	S32 pos_nextarg;
	S32 n2;
	S32 nextarg_save;

	nextarg_save = (*nextarg);
	out->spec = 0;
	while (*fmt && out->spec == 0)
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

		out->spec = parse_specifier(*fmt, specifiers, FMT_SPEC, &out->flags);
		out->length = fmt - out->begin + 1;
		fmt++;
	}

	if (out->spec == 0)
	{
		*nextarg = nextarg_save;
		return FALSE;
	}
	else
		return TRUE;
}

U64 ft_write_specifier(string buf, U64 buflen, struct s_fmt_flag *specifiers_lst, struct s_fmt_spec *specifier)
{
	U64 cnt;

	cnt = ft_snprintf(buf, buflen, "%%%d$", specifier->argpos + 1) - 1;
	if (cnt >= buflen)
		return cnt;

	for (struct s_fmt_flag *s = specifiers_lst; s->c != 0; s++)
	{
		if (s->type == FMT_FLAG && (s->flag & specifier->flags))
		{
			buf[cnt++] = s->c;
			if (cnt >= buflen)
				return cnt;
		}
	}

	if (specifier->width > -1)
	{
		cnt += ft_snprintf(&buf[cnt], buflen - cnt, "%d", specifier->width) - 1;
		if (cnt >= buflen)
			return cnt;
	}
	else if (specifier->width_argpos > -1)
	{
		cnt += ft_snprintf(&buf[cnt], buflen - cnt, "*%d$", specifier->width_argpos + 1) - 1;
		if (cnt >= buflen)
			return cnt;
	}

	if (specifier->prec > -1)
	{
		cnt += ft_snprintf(&buf[cnt], buflen - cnt, ".%d", specifier->width) - 1;
		if (cnt >= buflen)
			return cnt;
	}
	else if (specifier->prec_argpos > -1)
	{
		cnt += ft_snprintf(&buf[cnt], buflen - cnt, ".*%d$", specifier->prec_argpos + 1) - 1;
		if (cnt >= buflen)
			return cnt;
	}

	for (struct s_fmt_flag *s = specifiers_lst; s->c != 0; s++)
	{
		if (s->type == FMT_SIZE)
		{
			if (s->c > 127)
			{
				if (s->flag & specifier->flags)
				{
					buf[cnt++] = (s->c - 127);
					if (cnt >= buflen)
						return cnt;
				}
				else if ((s->flag << 1) & specifier->flags)
				{
					buf[cnt++] = (s->c - 127);
					if (cnt >= buflen)
						return cnt;
					buf[cnt++] = (s->c - 127);
					if (cnt >= buflen)
						return cnt;
				}
				break;
			}
			else if (s->flag & specifier->flags)
			{
				buf[cnt++] = s->c;
				if (cnt >= buflen)
					return cnt;
				break;
			}
		}
	}

	buf[cnt++] = specifier->spec;
	return cnt;
}

#if defined(TEST)
#include "libft/bits/printf_format_specifiers.h"

#include <stdio.h>

int main()
{
	sizeof(struct s_fmt_flag);

	struct s_fmt_flag *specifiers = ft_printf_format_specifiers();
	struct s_fmt_spec out;

	if (ft_argc < 2)
		return 1;

	for (S32 i = 1; i < ft_argc; i++)
	{
		S32 nextarg = 0;
		string ptr = ft_argv[i];

		while (ft_parse_specifier(ptr, &nextarg, specifiers, &out))
		{
			ft_printf("%.*s (l:%lu) (%#x)\n\t", out.length, out.begin, out.length, out.flags);

			if (out.flags & FL_ALT)
				ft_printf("alternative-form ");
			if (out.flags & FL_SPACEPAD)
				ft_printf("space-padded ");
			if (out.flags & FL_ZEROPAD)
				ft_printf("zero-padded ");
			if (out.flags & FL_LEFTJUST)
				ft_printf("left-justified ");
			if (out.flags & FL_SHOWSIGN)
				ft_printf("show-sign ");

			if (out.flags & FL_T_LONGLONG)
				ft_printf("long long precision ");
			else if (out.flags & FL_T_LONG)
				ft_printf("long precision ");
			else if (out.flags & FL_T_SHORT)
				ft_printf("half precision ");

			if (out.flags & FL_SPEC_HEX_U)
				ft_printf("uppercase-hexadecimal ");
			else if (out.flags & FL_SPEC_HEX)
				ft_printf("hexadecimal ");
			if (out.flags & FL_SPEC_UNSIGNED)
				ft_printf("unsigned ");
			if (out.flags & FL_SPEC_NUMBER)
				ft_printf("integer ");
			if (out.flags & FL_SPEC_FLOATING_POINT)
				ft_printf("floating point ");

			ft_printf("%c ", out.spec);

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
			ft_printf("\n\t");

			U8 buf[256];
			buf[ft_write_specifier(buf, sizeof(buf), specifiers, &out)] = '\0';
			ft_printf("%s\n", buf);

			ft_printf("\n");
			ptr = out.begin + out.length;
		}
	}
}
#endif
