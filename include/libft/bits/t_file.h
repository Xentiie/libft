/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_file.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 03:05:44 by reclaire          #+#    #+#             */
/*   Updated: 2025/03/10 03:07:03 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(FT_BITS_T_FILE_H)
#define FT_BITS_T_FILE_H

#include "libft/types.h"

typedef struct s_file
{
	U8 buffering_mode;
	U8 *buff;
	U64 buff_size;
	U64 buff_cnt;
	filedesc fd;
	bool binary_mode;
	bool readable;
	bool writeable;
} t_file;

/* cleanup lock in lock ht, called from ft_fclose */
bool __ft_flockcleanup(t_file *fp);

#endif
