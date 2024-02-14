/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strerror.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 14:52:06 by reclaire          #+#    #+#             */
/*   Updated: 2024/02/12 21:09:20 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_int.h"

struct s_error_entry
{
	t_error_code	err;
	string			name;
	string			desc;
};

# define ENT(X, desc) { X, #X, desc },
# define ENTRIES_LEN (sizeof(entries)/sizeof(struct s_error_entry) - 1)

static struct s_error_entry entries[] = {
	ENT(FT_OK, "No error")
	ENT(FT_EOMEM, "Out of memory")
	ENT(FT_EINVPTR, "Invalid pointer")
	ENT(FT_ESYSCALL, "System call failed")
	ENT(FT_ENOENT, "No entries found")
	ENT(FT_ERANGE, "Out of range")
	ENT(FT_ENOINIT, "Libft value not initialized")
};


const_string	ft_strerror(t_error_code err)
{
	if (err < 0)
		__FTRETURN_ERR((NULL), FT_ERANGE);
	if (err >= ENTRIES_LEN)
		__FTRETURN_ERR((NULL), FT_ENOENT);
	return entries[err].desc;
}

const_string	ft_errnotostr(t_error_code err)
{
	if (err < 0)
		__FTRETURN_ERR((NULL), FT_ERANGE);
	if (err >= ENTRIES_LEN)
		__FTRETURN_ERR((NULL), FT_ENOENT);
	return entries[err].name;
}

t_error_code ft_strtoerrno(const_string name)
{
	if (name == NULL)
		__FTRETURN_ERR((-1), FT_EINVPTR);
	t_error_code i = 0;
	while (i < ENTRIES_LEN)
	{
		if (!ft_strcmp(name, entries[i].name))
			break;
		i++;
	}
	if (i == ENTRIES_LEN)
		__FTRETURN_ERR((-1), FT_ENOENT);
	__FTRETURN_OK(i);
}
