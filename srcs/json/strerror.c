/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strerror.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 02:08:32 by reclaire          #+#    #+#             */
/*   Updated: 2025/01/07 02:10:19 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "json_private.h"

#include "libft/strings.h"

static const_string errors_str[] = {
	"JSON_ERR_SYS",
	"JSON_ERR_BAD_CHARACTER",
	"JSON_ERR_DUPLICATE_MEMBER",
	"JSON_ERR_BAD_STRING",
	"JSON_ERR_MISSING_COMMA",
};

const_string ft_json_strerror(enum e_json_error err)
{
	if (err < 0 || err >= (sizeof(errors_str) / sizeof(errors_str[0])))
		return NULL;

	if (err == JSON_ERR_SYS)
		return ft_strerror2();

	return errors_str[err];
}
