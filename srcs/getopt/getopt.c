/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getopt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 14:44:13 by reclaire          #+#    #+#             */
/*   Updated: 2025/04/15 02:29:11 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_int.h"

#include "libft/getopt.h"
#include "libft/strings.h"
#include "libft/io.h"

#include "libft/bits/alloca.h"

#if defined(TEST)
#include <getopt.h>
#endif

_FT_GLOBAL_VAR_DEF(S32, ft_optopt, 0);
_FT_GLOBAL_VAR_DEF(S32, ft_optind, 0);
_FT_GLOBAL_VAR_DEF(S32, ft_opterr, 1);
_FT_GLOBAL_VAR_DEF(S32, ft_optchr, '?');
_FT_GLOBAL_VAR_DEF(const_string, ft_optarg, NULL);

static _FT_GLOBAL_VAR_DEF(const_string, nextchar, NULL);
static _FT_GLOBAL_VAR_DEF(S32, first_nonopt, -1);

#define nextchar _FT_GLOBAL_VAR(nextchar)
#define first_nonopt _FT_GLOBAL_VAR(first_nonopt)

static bool pushback_arg(S32 start, S32 end, const_string *argv, int argc)
{
	S32 len;
	const_string *tmp;

	if ((len = end - start) < 1)
		return TRUE;

	if (UNLIKELY((tmp = ft_alloca(sizeof(const_string) * len)) == NULL))
		return FALSE;

	ft_memcpy(tmp, &argv[start], sizeof(const_string) * (len));
	ft_memcpy(&argv[start], &argv[start + len], sizeof(const_string) * (argc - len - start));
	ft_memcpy(&argv[argc - len], tmp, sizeof(const_string) * (len));

	first_nonopt -= len;
	ft_afree(tmp);
	return TRUE;
}

inline static bool is_opt(const_string str)
{
	return str[0] == '-' && str[1] != '\0';
}

inline static bool is_stop(const_string str)
{
	return str[0] == '-' && str[1] == '-' && str[2] == '\0';
}

S32 ft_getopt_long(S32 argc, const_string *argv, const_string optstr, const t_long_opt *longopts, S32 *longopts_index)
{
	if (longopts == NULL && optstr == NULL)
		FT_RET_ERR(-3, FT_EINVPTR);
	if (first_nonopt == -1)
		first_nonopt = argc - 1;

	/* Pas d'arg qui se fait parser -> on trouve la prochaine option */
	if (nextchar == NULL || *nextchar == '\0')
	{
		/* On passe a la prochaine option. ft_optind est init a 0, donc on skip toujours le premier arg (ft_argv[0]) */
		ft_optind++;
		if (ft_optind >= argc || ft_optind > first_nonopt)
			goto finish;

		/* Skip tout les non-options */
		S32 cnt = 0;
		while (ft_optind + cnt <= first_nonopt && !is_opt(argv[ft_optind + cnt]))
			cnt++;
		if (UNLIKELY(!pushback_arg(ft_optind, ft_optind + cnt, argv, argc)))
			FT_RET_ERR(-3, FT_EOMEM);

		/* Si '--' trouvé, on arrete de parser les options */
		if (is_stop(argv[ft_optind]))
		{
			if (UNLIKELY(!pushback_arg(ft_optind + 1, first_nonopt + 1, argv, argc)))
				FT_RET_ERR(-3, FT_EOMEM);
			FT_RET_OK(-2);
		}

		if (ft_optind >= argc || ft_optind > first_nonopt)
			goto finish;
		nextchar = argv[ft_optind] + 1; /* Skip '-' */
	}

	/*
	On arrive ici uniquement si on a trouvé une option

	On skip automatiquement le premier '-', donc pour
	./a.out a b -CD e, nextchar == "CD\0"
	./a.out a b --longopt d, nextchar == "-longopt\0"
	*/

	S32 ret;
	/* Vu qu'on skip le premier '-', on peut check si il y en a un 2eme avec is_opt */
	if (longopts && (is_opt(nextchar) || optstr == NULL))
	{
		if (*nextchar == '-')
			nextchar++; /* Skip 2eme '-' */

		const_string name_end = nextchar;
		while (*name_end && *name_end != '=')
			name_end++;

		S32 ind = 0;
		bool ambiguous = FALSE;
		bool exact = FALSE;
		S32 found_ind = 0;
		const t_long_opt *found = NULL;
		while (longopts[ind].name)
		{
			if (ft_strncmp(longopts[ind].name, nextchar, name_end - nextchar) == 0)
			{
				if ((U64)(name_end - nextchar) == ft_strlen(longopts[ind].name))
				{
					found = &longopts[ind];
					exact = TRUE;
					found_ind = ind;
					break;
				}
				else if (found == NULL)
				{
					found = &longopts[ind];
					found_ind = ind;
				}
				else
					ambiguous = TRUE;
			}
			ind++;
		}

		if (ambiguous && !exact)
		{
			if (ft_opterr)
				ft_fprintf(ft_fstderr, "%s: option `%s' is ambiguous\n", argv[0], argv[ft_optind]);
			ret = 0;
			goto failure_long;
		}

		if (found == NULL)
		{
			if (ft_opterr)
				ft_fprintf(ft_fstderr, "%s: unrecognized option '%s'\n", argv[0], argv[ft_optind]);
			ret = 0;
			goto failure_long;
		}

		if (found->has_argument == no_argument)
		{
			if (*name_end == '=')
			{
				if (ft_opterr)
					ft_fprintf(ft_fstderr, "%s: option '%s' doesn't allow an argument\n", argv[0], argv[ft_optind]);
				ret = found->flag_value;
				goto failure_long;
			}
		}
		else
		{
			if (*name_end == '=')
				ft_optarg = name_end + 1;
			else if (ft_optind < first_nonopt && found->has_argument != optional_argument)
			{
				ft_optarg = argv[ft_optind + 1];
				ft_optind++;
			}
			else if (found->has_argument == required_argument)
			{
				if (ft_opterr)
					ft_fprintf(ft_fstderr, "%s: option '%s' requires an argument\n", argv[0], argv[ft_optind]);
				ret = found->flag_value;
				nextchar += ft_strlen(nextchar);
				ft_optind++;
				ft_optopt = ret;
				FT_RET_OK(ft_optchr);
			}
		}

		nextchar += ft_strlen(nextchar);
		if (longopts_index)
			*longopts_index = found_ind;
		if (found->flag_ptr)
		{
			*found->flag_ptr = found->flag_value;
			FT_RET_OK(0);
		}
		FT_RET_OK(found->flag_value);

	failure_long:
		nextchar += ft_strlen(nextchar);
		ft_optind++;
		ft_optopt = ret;
		FT_RET_OK(ft_optchr);
	}
	else
	{
		const_string optstr_loc = ft_strchr(optstr, *nextchar);
		if (!optstr_loc)
		{
			// Not opt
			if (ft_opterr)
				ft_fprintf(ft_fstderr, "%s: invalid option -- '%c'\n", argv[0], *nextchar);
			ret = *nextchar;
			goto failure;
		}
		else
		{
			ret = *nextchar;
			// Check if opt has an argument
			if (*(optstr_loc + 1) == ':')
			{
				// Check if argument is in same arg
				if (*(nextchar + 1) != '\0')
				{
					ft_optarg = nextchar + 1;
					nextchar += ft_strlen(nextchar) - 1;
				}
				// Check if there is an argument next
				else if (ft_optind < first_nonopt)
				{
					ft_optind++;
					if (ft_optind >= argc || ft_optind > first_nonopt)
						goto finish;
					ft_optarg = argv[ft_optind];
					nextchar += ft_strlen(nextchar) - 1;
				}
				// Nothing found :(
				else
				{
					if (ft_opterr)
						ft_fprintf(ft_fstderr, "%s: option requires an argument -- '%c'\n", argv[0], ret);
					nextchar++;
					ft_optopt = ret;
					FT_RET_OK(ft_optchr);
				}
			}
			else
				ft_optarg = NULL;
			goto success;
		}
	}

finish:
	ft_optind = first_nonopt + 1;
	FT_RET_OK(-1);

failure:
	nextchar++;
	ft_optopt = ret;
	FT_RET_OK(ft_optchr);

success:
	nextchar++;
	FT_RET_OK(ret);
}

S32 ft_getopt_long_only(S32 argc, const_string *argv, const t_long_opt *longopts, S32 *longopts_index)
{
	return ft_getopt_long(argc, argv, NULL, longopts, longopts_index);
}

S32 ft_getopt(S32 argc, const_string *argv, const_string optstr)
{
	return ft_getopt_long(argc, argv, optstr, NULL, NULL);
}

#if defined(TEST)

// cd srcs/getopt
// gcc -L../.. -I../ getopt.c -lft -DTEST
// make -C ../../ && gcc -L../.. -I../ getopt.c -lft -DTEST -g -lm

#define std_optind optind
#define std_opterr opterr
#define std_optarg optarg
#define std_optopt optopt

#define LOGDIFF(fmt, ...) printf("(ft_optind:%d std_optind:%d) DIFF: " fmt, ft_optind, std_optind __VA_OPT__(, __VA_ARGS__))

S32 ft_strcmp_t(const_string s1, const_string s2)
{
	if (s1 == NULL || s2 == NULL)
	{
		if (s1 != NULL || s2 != NULL)
			return 1;
		else
			return 0;
	}
	return ft_strcmp(s1, s2);
}

int test_getopt_manual(int argc, char **argv)
{
	char **argv_cpy = ft_memdup(argv, sizeof(const_string) * argc);
	const_string optstr = "ab:cd:";

	int c;
	while ((c = getopt(argc, argv_cpy, optstr)) != -1)
		printf("STD: out:%d(%c) optopt:%d(%c) optind:%d optarg:%s opterr:%d\n", c, c, std_optopt, std_optopt, std_optind, std_optarg, std_opterr);
	printf("ARGV STD:\n");
	for (int i = 0; i < argc; i++)
		printf("%d: %s\n", i, argv_cpy[i]);
	printf("NONOPT STD:\n");
	for (int i = std_optind; i < argc; i++)
		printf("%d: %s\n", i, argv_cpy[i]);
	printf("\n");

	printf("ARGV FT:\n");
	while ((c = ft_getopt(argc, (const_string *)argv, optstr)) != -1)
		printf("FT: out:%d(%c) optopt:%d(%c) optind:%d optarg:%s opterr:%d\n", c, c, ft_optopt, ft_optopt, ft_optind, ft_optarg, ft_opterr);
	for (int i = 0; i < argc; i++)
		printf("%d: %s\n", i, argv[i]);
	printf("NONOPT FT:\n");
	for (int i = ft_optind; i < argc; i++)
		printf("%d: %s\n", i, argv[i]);
	printf("\n");
}

int test_getopt_auto(int argc, char **argv)
{
	const_string *ft_argv = ft_memdup(argv, sizeof(const_string) * argc);
	const_string *std_argv = (const_string *)argv;

	const_string optstr = "abcd:";
	S32 ft_out, std_out;

	while ((ft_out = ft_getopt(argc, ft_argv, optstr)) != -1 && (std_out = getopt(argc, (char *const *)std_argv, optstr)) != -1)
	{
		if (ft_out != std_out)
			LOGDIFF("ft_out:%d(%c) std_out:%d(%c)\n", ft_out, ft_out, std_out, std_out);
		// if (ft_optind != std_optind)
		//	LOGDIFF("ft_optind:%d std_optind:%d\n", ft_optind, std_optind);
		if (ft_strcmp_t(ft_optarg, std_optarg) != 0)
			LOGDIFF("ft_optarg:|%s| std_optarg:|%s|\n", ft_optarg, std_optarg);
		if (ft_opterr != std_opterr)
			LOGDIFF("ft_opterr:%d(%c) std_opterr:%d(%c)\n", ft_opterr, ft_opterr, std_opterr, std_opterr);
		if (ft_optopt != std_optopt)
			LOGDIFF("ft_optopt:%d(%c) std_optopt:%d(%c)\n", ft_optopt, ft_optopt, std_optopt, std_optopt);
	}
	// if (ft_out != -1 || std_out != -1)
	//	printf("???: %d %d\n", ft_out, std_out);
	// if (ft_optind != std_optind)
	//	LOGDIFF("ft_optind:%d std_optind:%d\n", ft_optind, std_optind);

	for (int i = 0; i < argc; i++)
	{
		if (ft_strcmp_t(ft_argv[i], std_argv[i]) != 0)
		{
			printf("ARGV DIFF:\n   ft         std\n");
			for (i = 0; i < argc; i++)
				printf("%-10s|%10s\n", ft_argv[i], std_argv[i]);
			break;
		}
	}
	free(ft_argv);
}

int test_getopt_long_manual(int argc, char **argv)
{
	char **argv_cpy = ft_memdup(argv, sizeof(const_string) * argc);
	const_string optstr = "ab:cd:";

	int flag = 0;
	int longopt_index = 0;

	struct option std_longopts[] = {
		{"aaa", no_argument, NULL, 'a'},
		{"bbb", required_argument, NULL, 'b'},
		{"ccc", no_argument, NULL, 'c'},
		{"ddd", required_argument, NULL, 'd'},

		{"flag", no_argument, &flag, 1},
		{"optional", optional_argument, NULL, 'o'},
		{NULL, 0, NULL, 0}};

	t_long_opt *ft_longopts = (t_long_opt *)std_longopts;

	int c;
	while ((c = getopt_long(argc, argv_cpy, optstr, std_longopts, &longopt_index)) != -1)
		printf("STD: out:%d(%c) optopt:%d(%c) optind:%d optarg:%s opterr:%d | flag:%d longopt_index:%d\n", c, c, std_optopt, std_optopt, std_optind, std_optarg, std_opterr, flag, longopt_index);
	printf("ARGV STD:\n");
	for (int i = 0; i < argc; i++)
		printf("%d: %s\n", i, argv_cpy[i]);
	printf("NONOPT STD:\n");
	for (int i = std_optind; i < argc; i++)
		printf("%d: %s\n", i, argv_cpy[i]);
	printf("\n");

	flag = 0;
	printf("ARGV FT:\n");
	while ((c = ft_getopt_long(argc, (const_string *)argv, optstr, ft_longopts, &longopt_index)) != -1)
		printf("FT: out:%d(%c) optopt:%d(%c) optind:%d optarg:%s opterr:%d | flag:%d longopt_index:%d\n", c, c, ft_optopt, ft_optopt, ft_optind, ft_optarg, ft_opterr, flag, longopt_index);
	for (int i = 0; i < argc; i++)
		printf("%d: %s\n", i, argv[i]);
	printf("NONOPT FT:\n");
	for (int i = ft_optind; i < argc; i++)
		printf("%d: %s\n", i, argv[i]);
	printf("\n");
}

int main(int argc, char **argv)
{
	// test_getopt_manual(argc, argv);
	// test_getopt_auto(argc, argv);

	test_getopt_long_manual(argc, argv);
}

#endif
