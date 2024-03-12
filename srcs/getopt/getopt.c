/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getopt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 14:44:13 by reclaire          #+#    #+#             */
/*   Updated: 2024/02/18 01:22:52 by reclaire         ###   ########.fr       */
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
