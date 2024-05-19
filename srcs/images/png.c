/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   png.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 01:37:21 by reclaire          #+#    #+#             */
/*   Updated: 2024/05/16 03:48:35 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
TODO:

if indexed color, can't parse if PLTE comes after data

*/

#include "libft_int.h"

#include <stdio.h>
#include <stdlib.h>

static void reverse_endian(U32 *num)
{
	U32 cpy = *num;
	*num = (cpy & 0x000000ff) << 24u |
		   (cpy & 0x0000ff00) << 8u |
		   (cpy & 0x00ff0000) >> 8u |
		   (cpy & 0xff000000) >> 24u;
}

// png always starts with '137 80 78 71 13 10 26 10'
static bool check_png_sig(file f)
{
	const char png_sig[8] = {137, 80, 78, 71, 13, 10, 26, 10};
	char buff[8];
	if (
		ft_fread(f, buff, sizeof(buff)) != sizeof(buff) ||
		ft_memcmp(buff, png_sig, sizeof(png_sig)))
		return FALSE;
	return TRUE;
}

static U32 png_read_u32(U8 **buffer)
{
	U32 n = *(U32 *)(*buffer);
	*buffer += sizeof(U32);
	reverse_endian(&n);
	return n;
}

/*
trucs droles:

la taille est stocké sur un U32, mais le bit de signe n'est pas utilisé
(donc normalement limité sur S32_MAX), du coup il se passe quoi si je rentre une image
plus grande ?



*/

#define COL_TYPE_GRAYSCALE 0
#define COL_TYPE_RGB 2
#define COL_TYPE_PALETTE 3
#define COL_TYPE_GRAYSCALE_ALPHA 4
#define COL_TYPE_RGB_ALPHA 6

#define CHUNK_IHDR 1380206665
#define CHUNK_IEND 1145980233
#define CHUNK_PLTE 1163152464
#define CHUNK_IDAT 1413563465

#define CHUNK_tEXt 1951942004
#define CHUNK_zTXt 1951945850
#define CHUNK_gAMA 1095582055
#define CHUNK_iCCP 1346585449
#define CHUNK_bKGD 1145523042
#define CHUNK_pHYs 1935231088
#define CHUNK_tIME 1162692980

/*
Chunks that are not strictly necessary in order to meaningfully
display the contents of the file are known as "ancillary"
chunks.  A decoder encountering an unknown chunk in which the
ancillary bit is 1 can safely ignore the chunk and proceed to
display the image. The time chunk (tIME) is an example of an
ancillary chunk.

Chunks that are necessary for successful display of the file's
contents are called "critical" chunks. A decoder encountering
an unknown chunk in which the ancillary bit is 0 must indicate
to the user that the image contains information it cannot
safely interpret.  The image header chunk (IHDR) is an example
of a critical chunk.
*/
#define CHUNK_ANCILLARY(type_code) ((type_code >> 5) & 1)
/*
A public chunk is one that is part of the PNG specification or
is registered in the list of PNG special-purpose public chunk
types.  Applications can also define private (unregistered)
chunks for their own purposes.  The names of private chunks
must have a lowercase second letter, while public chunks will
always be assigned names with uppercase second letters.  Note
that decoders do not need to test the private-chunk property
bit, since it has no functional significance; it is simply an
administrative convenience to ensure that public and private
chunk names will not conflict.
*/
#define CHUNK_PRIVATE(type_code) ((type_code >> 13) & 1)
/*
The significance of the case of the third letter of the chunk
name is reserved for possible future expansion.  At the present
time all chunk names must have uppercase third letters.
(Decoders should not complain about a lowercase third letter,
however, as some future version of the PNG specification could
define a meaning for this bit.  It is sufficient to treat a
chunk with a lowercase third letter in the same way as any
other unknown chunk type.)
*/
#define CHUNK_RESERVED(type_code) ((type_code >> 21) & 1)
/*
If a chunk's safe-to-copy bit is 0, it indicates that the chunk
depends on the image data.  If the program has made any changes
to critical chunks, including addition, modification, deletion,
or reordering of critical chunks, then unrecognized unsafe
chunks must not be copied to the output PNG file.  (Of course,
if the program does recognize the chunk, it can choose to
output an appropriately modified version.)
*/
#define CHUNK_SAFE(type_code) ((type_code >> 29) & 1)

t_png_img *ft_load_png(file f, bool verbose)
{
	// A valid PNG image must contain an IHDR chunk, one or more IDAT chunks, and an IEND chunk.

#define ASSERT(x, ...)                                                                        \
	if (UNLICKELY(!(x)))                                                                      \
	{                                                                                         \
		if (UNLICKELY(verbose))                                                               \
		{                                                                                     \
			if (ft_errno != FT_OK)                                                            \
				ft_dprintf(ft_stderr, "(ft_errno: %d:%s) ", ft_errno, ft_strerror(ft_errno)); \
			ft_dprintf(ft_stderr, "png error: ");                                             \
			ft_dprintf(ft_stderr, __VA_ARGS__);                                               \
			ft_dprintf(ft_stderr, "\n");                                                      \
		}                                                                                     \
		goto png_error;                                                                       \
	}

	U8 *__buffer = NULL;
	U8 *buffer = NULL;
	U8 *crc_buffer;
	U64 buffer_alloc = 0;

	U32 chunk_length;
	U32 chunk_type_code;
	U32 crc;
	t_png_img *img = NULL;

	U8 *palette = NULL;
	U64 palette_size = 0;

	ASSERT(check_png_sig(f), "Bad PNG signature");

	S32 chunk_n = 0;
next_chunk:
	chunk_n++;
	buffer = __buffer;

	// Chunk length/type
	ASSERT(ft_fread(f, (char *)&chunk_length, sizeof(U32)) == sizeof(U32), "Couldn't read chunk #%d length", chunk_n);
	reverse_endian(&chunk_length);
	ASSERT(ft_fread(f, (char *)&chunk_type_code, sizeof(U32)) == sizeof(U32), "Couldn't read chunk #%d type code", chunk_n);
	if (UNLICKELY(chunk_n == 1))
		ASSERT(chunk_type_code == CHUNK_IHDR, "First chunk isn't IDHR");

	// Grow buffer
	chunk_length += 4; // Need to take chunk_type_code for CRC, so buffer needs to require enough space to hold everything
	if (chunk_length > buffer_alloc)
	{
		free(__buffer);
		if (!(__buffer = malloc(sizeof(U8) * chunk_length)))
			goto png_error;
		buffer = __buffer;
		buffer_alloc = chunk_length;
	}
	chunk_length -= 4;
	crc_buffer = buffer;
	buffer += 4;
	*(U32 *)crc_buffer = chunk_type_code;

	// Read whole chunk and validate CRC
	{
		U64 bytes_read = 0, total_read = 0;
		while ((bytes_read = ft_fread(f, buffer + total_read, chunk_length - total_read)) > 0)
			total_read += bytes_read;
		ASSERT(total_read == chunk_length, "Error reading chunk #%d", chunk_n);

		ASSERT(ft_fread(f, (char *)&crc, sizeof(U32)) == sizeof(U32), "Couldn't read chunk #%d CRC", chunk_n);
		reverse_endian(&crc);
		U32 current_crc = ft_crc32(crc_buffer, chunk_length + 4);
		ASSERT(current_crc == crc, "Invalid CRC on chunk #%d (is:%#x should be:%#x)", chunk_n, current_crc, crc);
	}

	// Analyse chunk
	switch (chunk_type_code)
	{
	case CHUNK_IHDR:
		ASSERT(chunk_n == 1, "IDHR chunk found where it shouldn't be");

		ASSERT((img = malloc(sizeof(t_png_img))) != NULL, "Memory allocation error");

		img->width = png_read_u32(&buffer);
		img->height = png_read_u32(&buffer);
		img->bit_depth = *buffer++;
		img->color_type = *buffer++;
		img->compression_method = *buffer++;
		img->filter_method = *buffer++;
		img->interlace_method = *buffer++;
		img->sample_depth = img->color_type == COL_TYPE_PALETTE ? 8 : img->bit_depth;

		// Values check
		{
			ASSERT(img->bit_depth == 1 || img->bit_depth == 2 || img->bit_depth == 4 || img->bit_depth == 8 || img->bit_depth == 16, "Bad bit depth");
			ASSERT(img->color_type == 0 || img->color_type == 2 || img->color_type == 3 || img->color_type == 4 || img->color_type == 6, "Bad color type");
			ASSERT(
				(img->color_type == COL_TYPE_RGB && (img->bit_depth == 8 || img->bit_depth == 16)) ||
					(img->color_type == COL_TYPE_PALETTE && (img->bit_depth == 1 || img->bit_depth == 2 || img->bit_depth == 4 || img->bit_depth == 8)) ||
					(img->color_type == COL_TYPE_GRAYSCALE_ALPHA && (img->bit_depth == 8 || img->bit_depth == 16)) ||
					(img->color_type == COL_TYPE_RGB_ALPHA && (img->bit_depth == 8 || img->bit_depth == 16)),
				"Invalid color type/bit depth combination");

			ASSERT(img->compression_method == 0, "Unrecognized compression method");
			ASSERT(img->filter_method == 0, "Unrecognized filter method");
			ASSERT(img->interlace_method == 0 || img->interlace_method == 1, "Unrecognized interlace method");
		}

		img->data = malloc(sizeof(U8) * img->width * img->height * img->bit_depth);
		img->text_data = NULL;

		goto next_chunk;

	case CHUNK_PLTE:
		ASSERT(palette == NULL, "Multiple PLTE chunk found");
		ASSERT(chunk_length % 3 == 0, "Bad PLTE chunk length");
		ASSERT(img->color_type != COL_TYPE_GRAYSCALE && img->color_type != COL_TYPE_GRAYSCALE_ALPHA, "PLTE chunk shouldn't be here");

		palette_size = chunk_length / 3;
		ASSERT(palette_size <= pow(2, img->bit_depth), "Too much color in palette");

		ASSERT(((palette = malloc(sizeof(U8) * chunk_length)) != NULL), "Memory allocation error");
		ft_memcpy(palette, buffer, sizeof(U8) * chunk_length);
		goto next_chunk;

	case CHUNK_IDAT:
		if (img->color_type == COL_TYPE_PALETTE)
			ASSERT(palette != NULL, "PLTE chunk not found / PLTE chunk appears after IDAT chunk");
		
		goto next_chunk;

	case CHUNK_tEXt:
		//TODO: peut etre quand meme verif la taille du keyword (entre 1 et 79 bytes)
		string txt = malloc(sizeof(char) * (chunk_length + 1));
		ft_memcpy(txt, buffer, chunk_length);
		txt[chunk_length] = '\0';
		ft_lstadd_front(&img->text_data, ft_lstnew(txt));
		goto next_chunk;

	case CHUNK_zTXt:
		U8 *buffer_sv = buffer;
		buffer += ft_strlen(buffer) + 1;

		U64 compressed_size = chunk_length - (buffer - buffer_sv);
		

		goto next_chunk;

	case CHUNK_IEND:
		break;
	default:
		if (verbose)
			printf("Unknown chunk found: %.4s (code: %u) (%u bytes)\n", (string)&chunk_type_code, chunk_type_code, chunk_length);
		goto next_chunk;
	}

	free(__buffer);
	free(palette);
	return img;

png_error:
	free(__buffer);
	free(palette);
	free(img->data);
	ft_lstclear(&img->text_data, free);
	free(img);
	return NULL;
}

void ft_free_png_img(t_png_img *img)
{
	free(img->data);
	ft_lstclear(&img->text_data, free);
	free(img);
}
