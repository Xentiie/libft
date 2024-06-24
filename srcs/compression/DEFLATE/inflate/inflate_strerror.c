/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inflate_strerror.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 21:17:10 by reclaire          #+#    #+#             */
/*   Updated: 2024/06/17 21:17:16 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inflate_int.h"

struct s_inflate_error_entry
{
	S32 err;
	string name;
	string desc;
};

#define ENT(X, desc) \
	{                \
		X, #X, desc  \
	}
#define ENTRIES_LEN ((S32)(sizeof(entries) / sizeof(struct s_inflate_error_entry) - 1))

static struct s_inflate_error_entry entries[] = {
	ENT(FT_OK, "No error"),
	ENT(FT_INFLATE_E_OUT_OMEM, "Not enough space in output buffer"),
	ENT(FT_INFLATE_E_IN_OMEM, "Not enough data in the input buffer to parse a block."),
	ENT(FT_INFLATE_EINV_BLOCK_SIZE, "Invalid (size/~size) in block type 0"),
	ENT(FT_INFLATE_EINV_LENGTH_CODE, "Invalid length code"),
	ENT(FT_INFLATE_EINV_DISTANCE, "Invalid distance. Not enough characters in buffer to process back-reference"),
	ENT(FT_INFLATE_EINV_BLOCK_TYPE, "Invalid block type."),
};

const_string ft_inflate_strerror(S32 err)
{
	if (err < 0)
		__FTRETURN_ERR((NULL), FT_ERANGE);
	if (err >= ENTRIES_LEN)
		__FTRETURN_ERR((NULL), FT_ENOENT);
	return entries[err].desc;
}

const_string ft_inflate_errortostr(S32 err)
{
	if (err < 0)
		__FTRETURN_ERR((NULL), FT_ERANGE);
	if (err >= ENTRIES_LEN)
		__FTRETURN_ERR((NULL), FT_ENOENT);
	return entries[err].name;
}

S32 ft_inflate_strtoerror(const_string name)
{
	if (name == NULL)
		__FTRETURN_ERR((-1), FT_EINVPTR);
	S32 i = 0;
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
