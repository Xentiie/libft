/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   png.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 01:37:21 by reclaire          #+#    #+#             */
/*   Updated: 2024/06/17 13:23:15 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
TODO:

if indexed color, can't parse if PLTE comes after data

*/

#include "libft_int.h"

#include <stdio.h>
#include <stdlib.h>

#include <zlib.h>

// Error handling macro
#define CHECK_ERR(err, msg) { \
    if (err != Z_OK) { \
        fprintf(stderr, "%s error: %d\n", msg, err); \
        return -1; \
    } \
}

// Function to decompress data
int decompress_data(const unsigned char *source, size_t source_len, unsigned char **dest, size_t *dest_len) {
    int ret;
    z_stream strm;
    unsigned char outbuffer[32768]; // Output buffer for decompression
    size_t total_out = 0;

    // Allocate initial output buffer
    *dest = NULL;
    *dest_len = 0;

    // Initialize the zlib stream structure
    memset(&strm, 0, sizeof(strm));
    strm.next_in = (unsigned char *)source;
    strm.avail_in = source_len;

    // Initialize the inflate operation
    ret = inflateInit(&strm);
    CHECK_ERR(ret, "inflateInit");

    // Decompress until deflate stream ends or end of buffer
    do {
        strm.next_out = outbuffer;
        strm.avail_out = sizeof(outbuffer);

        ret = inflate(&strm, 0);
        if (ret != Z_OK && ret != Z_STREAM_END && ret != Z_BUF_ERROR) {
            inflateEnd(&strm);
            return -1; // Decompression error
        }

        // Allocate or expand the output buffer
        size_t out_size = sizeof(outbuffer) - strm.avail_out;
        unsigned char *temp = realloc(*dest, total_out + out_size);
        if (!temp) {
            inflateEnd(&strm);
            free(*dest);
            *dest = NULL;
            return -1; // Memory allocation error
        }
        *dest = temp;

        // Copy the decompressed data to the output buffer
        memcpy(*dest + total_out, outbuffer, out_size);
        total_out += out_size;
    } while (ret != Z_STREAM_END);

    // Set the total length of decompressed data
    *dest_len = total_out;

    // Clean up and return
    inflateEnd(&strm);
    return 0;
}

#define reverse16(n) __builtin_bswap16(n)
#define reverse32(n) __builtin_bswap32(n)
#define reverse64(n) __builtin_bswap64(n)

// png always starts with '137 80 78 71 13 10 26 10'
static bool check_png_sig(file f)
{
	const U8 png_sig[8] = {137, 80, 78, 71, 13, 10, 26, 10};
	U8 buff[8];
	if (
		ft_fread(f, (char *)buff, sizeof(buff)) != sizeof(buff) ||
		ft_memcmp(buff, png_sig, sizeof(png_sig)))
		return FALSE;
	return TRUE;
}

static U32 png_read_u32(U8 **buffer)
{
	U32 n = reverse32(*(U32 *)(*buffer));
	*buffer += sizeof(U32);
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
	if (UNLIKELY(!(x)))                                                                       \
	{                                                                                         \
		if (UNLIKELY(verbose))                                                                \
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

	string txt; // buffer for text and ztxt chunks
	S32 err; // err variable for inflate
	t_deflate_stream stream; // stream for inflate

	U8 *data; // buffer

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
	chunk_length = reverse32(chunk_length);
	ASSERT(ft_fread(f, (char *)&chunk_type_code, sizeof(U32)) == sizeof(U32), "Couldn't read chunk #%d type code", chunk_n);
	if (UNLIKELY(chunk_n == 1))
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
		while ((bytes_read = ft_fread(f, (char *)(buffer + total_read), chunk_length - total_read)) > 0)
			total_read += bytes_read;
		ASSERT(total_read == chunk_length, "Error reading chunk #%d", chunk_n);

		ASSERT(ft_fread(f, (char *)&crc, sizeof(U32)) == sizeof(U32), "Couldn't read chunk #%d CRC", chunk_n);
		crc = reverse32(crc);
		U32 current_crc = ft_crc32(crc_buffer, chunk_length + 4);
		ASSERT(current_crc == crc, "Invalid CRC on chunk #%d (is:%#x should be:%#x)", chunk_n, current_crc, crc);
	}

	printf("Chunk: %.4s\n", &chunk_type_code);

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
		if (!img->data)
			__FTRETURN_ERR(NULL, FT_EOMEM);
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

		buffer += 2; //zlib header

		err = 0;
		ft_memset(&stream, 0, sizeof(t_deflate_stream));
		t_deflate_stream stream = ft_deflate_init_stream(buffer, chunk_length, img->data, sizeof(U8) * img->width * img->height * img->bit_depth);
		ASSERT(ft_inflate(&stream, &err) == TRUE, "Inflate error: %s\n", ft_inflate_strerror(err));

		free(data);
		goto next_chunk;

	case CHUNK_tEXt:;

		// TODO: peut etre quand meme verif la taille du keyword (entre 1 et 79 bytes)
		txt = malloc(sizeof(char) * (chunk_length + 1));
		ft_memcpy(txt, buffer, chunk_length);
		txt[chunk_length] = '\0';
		ft_lstadd_front(&img->text_data, ft_lstnew(txt));
		goto next_chunk;

	case CHUNK_zTXt:;
		U8 *buffer_sv = buffer;
		U64 keyword_length = ft_strlen((string)buffer);
		buffer += keyword_length + 1;
		ASSERT(*buffer == 0, "Unknown compression method");
		buffer++;
		buffer += 2; //Zlib header

		U64 compressed_size = chunk_length - (buffer - buffer_sv) - 4;

		err = 0;
		ft_memset(&stream, 0, sizeof(t_deflate_stream));
		data = ft_inflate_quick(buffer, compressed_size, &stream, &err);
		ASSERT(data != NULL, "zTXt chunk: couldn't decompress: %s", ft_inflate_strerror(err));

		txt = malloc(sizeof(char) * (keyword_length + 1 + stream.out_used + 1));
		ft_memcpy(txt, buffer_sv, keyword_length);
		txt[keyword_length] = '\0';
		ft_memcpy(txt + keyword_length + 1, data, stream.out_used);
		txt[keyword_length + 1 + stream.out_used] = '\0';

		free(data);

		ft_lstadd_front(&img->text_data, ft_lstnew(txt));

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
