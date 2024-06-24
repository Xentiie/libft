/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inflate_quick.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 17:16:38 by reclaire          #+#    #+#             */
/*   Updated: 2024/06/17 01:36:12 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_int.h"

U8 *ft_inflate_quick(U8 *data, U64 data_len, t_deflate_stream *out_stream, S32 *err)
{
	if (err)
		*err = FT_OK;

	U64 buffer_alloc = sizeof(U8) * 65536;
	U8 *buffer = malloc(buffer_alloc);
	if (UNLIKELY(buffer == NULL))
		__FTRETURN_ERR(NULL, FT_EOMEM);
	ft_bzero(buffer, buffer_alloc);

	*out_stream = ft_deflate_init_stream(data, data_len, buffer, buffer_alloc);
	S32 _err;

	while (TRUE)
	{
		printf("%lu\n", out_stream->in_used);
		if (!ft_inflate(out_stream, &_err))
		{
			if (_err == FT_OK) // Done
				break;
			else
			{
				if (_err == FT_INFLATE_E_OUT_OMEM)
				{
					//printf("Realloc: %lu->%lu (%lu/%lu)\n", buffer_alloc, buffer_alloc * 2, out_stream->in_used, out_stream->out_used);
					//Le soucis c'est que quand on retourne dans ft_inflate apres ca, le block est reset
					U8 *buffer_new = malloc(sizeof(U8) * (buffer_alloc * 2));
					if (UNLIKELY(buffer_new == NULL))
					{
						//free(buffer);
						__FTRETURN_ERR(NULL, FT_EOMEM);
					}

					ft_memcpy(buffer_new, buffer, out_stream->out_used);

					//free(buffer);

					buffer_alloc *= 2;
					buffer = buffer_new;

					out_stream->out = buffer;
					out_stream->out_size = buffer_alloc;
				}
				else
				{
					if (err)
						*err = _err;
					//free(buffer);
					__FTRETURN_ERR(NULL, ft_errno);
				}
			}
		}
	}

	U8 *out = malloc(sizeof(U8) * out_stream->out_used);
	if (UNLIKELY(out == NULL))
	{
		//free(buffer);
		__FTRETURN_ERR(NULL, FT_EOMEM);
	}
	ft_memcpy(out, buffer, out_stream->out_used);

	if (out_stream->bit_offset != 0)
		out_stream->in_used++;

	//free(buffer);
	__FTRETURN_OK(out);
}
