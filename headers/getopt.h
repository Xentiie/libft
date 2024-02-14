/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getopt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 01:30:07 by reclaire          #+#    #+#             */
/*   Updated: 2024/02/11 23:16:50 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_GETOPT_H
# define LIBFT_GETOPT_H

# include "_libft.h"

extern int			ft_optopt;
extern int			ft_optind;
extern const_string	ft_optarg;

int ft_getopt(int argc, char const **argv, char const *optstr);

#endif