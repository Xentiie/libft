/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getopt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 14:44:13 by reclaire          #+#    #+#             */
/*   Updated: 2024/02/14 19:42:19 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_int.h"

int 			ft_optopt;
int				ft_optind = 1;
const_string	ft_optarg;

const_string	nextchar = NULL;
int				last_nonopt = -1;

int ft_getopt(int argc, char const **argv, char const *optstr)
{
	/* nothing left to parse */
	if (ft_optind == argc)
	{
		if (last_nonopt != -1)
			ft_optind = last_nonopt;
		else
			ft_optind = argc;
		return -1;
	}

	/* arrived at the end of current arg -> step */
	if (nextchar && *nextchar == '\0')
	{
		ft_optind++;
		nextchar = NULL;
		return ft_getopt(argc, argv, optstr);
	}

	/* non-option -> update last_nonopt -> step */
	if (argv[ft_optind][0] != '-' || argv[ft_optind][1] == '\0')
	{
		if (last_nonopt == -1)
			last_nonopt = ft_optind;
		ft_optind++;
		return ft_getopt(argc, argv, optstr);
	}

	/* non-option previously stepped, update argv to have all non-option at the end */
	if (last_nonopt != -1)
	{
		char const *arg_save = argv[ft_optind];
		for (int i = ft_optind - 1; i >= last_nonopt; i--)
			argv[i + 1] = argv[i];
		argv[last_nonopt] = arg_save;
		ft_optind = last_nonopt;
		last_nonopt = -1;
	}

	/* get current opt */
	char ret;
	if (nextchar == NULL)
	{
		ret = argv[ft_optind][1];
		nextchar = &(argv[ft_optind][2]);
	}
	else
	{
		ret = *nextchar;
		nextchar++;
	}

	/* check if current opt is valid */
	unsigned long i = 0;
	while (optstr[i] && optstr[i] != ret)
		i++;

	/* invalid */
	if (optstr[i] != ret)
	{
		ft_optopt = ret;
		return '?';
	}

	/* check if current opt requires arg */
	if (optstr[i + 1] == ':')
	{
		if (*nextchar == '\0')
		{
			ft_optind++;
			/* nothing that could be arg for opt, invalid */
			if (ft_optind == argc)
			{
				ft_optopt = ret;
				return '?';
			}

			ft_optopt = ret;
			ft_optarg = argv[ft_optind];
			//ft_optind++;
			return ret;
		}
		else
		{
			ft_optopt = ret;
			ft_optarg = nextchar;
			ft_optind++;
			nextchar = NULL;
			return ret;
		}
	}

	ft_optopt = ret;
	return ret;
}

#ifdef TEST
#ifdef FT
# define GETOPT ft_getopt
# define OPTARG ft_optarg
# define OPTOPT ft_optopt
# define OPTIND ft_optind
#else
# define GETOPT getopt
# define OPTARG optarg
# define OPTOPT optopt
# define OPTIND optind
#endif

#define xstr(s) str(s)
#define str(s) #s

int main(int argc, char **argv)
{
	int opt;

	printf("Using: %s\n", xstr(GETOPT));

	while ((opt = ft_getopt(argc, argv, "abc:")) != -1)
	{
		switch (opt)
		{
		case 'a':
			printf("Option 'a' was specified.\n");
			break;
		case 'b':
			printf("Option 'b' was specified.\n");
			break;
		case 'c':
			printf("Option 'c' was specified with argument '%s'.\n", ft_optarg);
			break;
		case '?':
			// Unrecognized option or missing argument
			if (ft_optopt == 'c')
			{
				fprintf(stderr, "Option '-%c' requires an argument.\n", ft_optopt);
			}
			else
			{
				fprintf(stderr, "Unknown option '-%c'.\n", ft_optopt);
			}
			break;
		default:
			fprintf(stderr, "Usage: %s [-a] [-b] [-c value]\n", argv[0]);
			return 1;
		}
	}

	// Process remaining non-option arguments
	for (int i = ft_optind; i < argc; i++)
	{
		printf("Non-option argument: %s\n", argv[i]);
	}

	return 0;
}
#endif