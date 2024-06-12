/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_gzip_deflate.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 20:54:22 by reclaire          #+#    #+#             */
/*   Updated: 2024/06/12 16:07:21 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// gcc -g -I../ -I../../ -L../../ -DTEST ./test_gzip_deflate.c -lft
#ifdef TEST

#include "libft_int.h"
#include <stdio.h>
#include <time.h>
#include <zlib.h>

#define _ASSERT(x, _f, _l, ...)                                            \
	do                                                                     \
	{                                                                      \
		if (!(x))                                                          \
		{                                                                  \
			printf(                                                        \
				"(" FT_BOLD "%s" FT_CRESET ":" FT_BOLD "%d" FT_CRESET ") " \
				"ASSERTION FAILED: %-20s " __VA_OPT__(": "),               \
				_f, _l, #x);                                               \
			__VA_OPT__(printf(__VA_ARGS__);)                               \
			printf("\n");                                                  \
		}                                                                  \
	} while (0)
#define ASSERT(x, ...) _ASSERT(x, __FILE__, __LINE__, __VA_ARGS__)

void test_gzip_header_write()
{
	t_gzip_header header;
	U64 out;

#define RUN_BUFFER_SPACE_TEST(_header_prep, _buffer_size, _output_size, _state, _errno)                                    \
	{                                                                                                                      \
		U8 buf[_buffer_size];                                                                                              \
		_header_prep;                                                                                                      \
		out = ft_gzip_write_header(buf, sizeof(buf), &header);                                                             \
		ASSERT(out == _output_size, "%5lu != %lu", out, (U64)(_output_size));                                              \
		ASSERT(ft_errno == _errno, "%7s(%d) != %s(%d)", ft_errnotostr(ft_errno), ft_errno, ft_errnotostr(_errno), _errno); \
		ASSERT(header.state == _state, "%5d != %d", header.state, _state);                                                 \
	}
#define HEADER_PREP_BZERO()                       \
	{                                             \
		ft_bzero(&header, sizeof(t_gzip_header)); \
	}
#define HEADER_PREP_RESET_STATE() \
	{                             \
		header.state = 0;         \
	}

	RUN_BUFFER_SPACE_TEST(HEADER_PREP_BZERO(), 2, 2, -1, FT_EOSPACE);
	RUN_BUFFER_SPACE_TEST(HEADER_PREP_BZERO(), 3, 3, -2, FT_EOSPACE);
	RUN_BUFFER_SPACE_TEST(HEADER_PREP_BZERO(), 4, 4, -3, FT_EOSPACE);
	RUN_BUFFER_SPACE_TEST(HEADER_PREP_BZERO(), 8, 8, -4, FT_EOSPACE);
	RUN_BUFFER_SPACE_TEST(HEADER_PREP_BZERO(), 9, 9, -5, FT_EOSPACE);

	RUN_BUFFER_SPACE_TEST(HEADER_PREP_BZERO(), 10, 10, 1, FT_OK); /* Without extra data / filename / comment */
	RUN_BUFFER_SPACE_TEST(HEADER_PREP_BZERO(), 100, 10, 1, FT_OK);

	{ /* With extra data */
		HEADER_PREP_BZERO();
		header.extra_data_len = 10;
		header.extra_data = "abcdefghij";
		RUN_BUFFER_SPACE_TEST(HEADER_PREP_RESET_STATE(), 9, 9, -5, FT_EOSPACE);
		RUN_BUFFER_SPACE_TEST(HEADER_PREP_RESET_STATE(), 10, 10, -6, FT_EOSPACE);
		RUN_BUFFER_SPACE_TEST(HEADER_PREP_RESET_STATE(), 12, 12, -7, FT_EOSPACE);
		RUN_BUFFER_SPACE_TEST(HEADER_PREP_RESET_STATE(), 15, 12, -7, FT_EOSPACE);
		RUN_BUFFER_SPACE_TEST(HEADER_PREP_RESET_STATE(), 21, 12, -7, FT_EOSPACE);
		RUN_BUFFER_SPACE_TEST(HEADER_PREP_RESET_STATE(), 22, 22, 1, FT_OK);
	}

	{ /* With filename */
		HEADER_PREP_BZERO();
		header.filename = "testtesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttest";
		RUN_BUFFER_SPACE_TEST(HEADER_PREP_RESET_STATE(), 12, 10, -8, FT_EOSPACE);
		RUN_BUFFER_SPACE_TEST(HEADER_PREP_RESET_STATE(), 15, 10, -8, FT_EOSPACE);
		RUN_BUFFER_SPACE_TEST(HEADER_PREP_RESET_STATE(), 21, 10, -8, FT_EOSPACE);
		RUN_BUFFER_SPACE_TEST(HEADER_PREP_RESET_STATE(), 95, 95, 1, FT_OK);
	}

	{ /* With comment */
		HEADER_PREP_BZERO();
		header.comment = "testtesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttest";
		RUN_BUFFER_SPACE_TEST(HEADER_PREP_RESET_STATE(), 12, 10, -9, FT_EOSPACE);
		RUN_BUFFER_SPACE_TEST(HEADER_PREP_RESET_STATE(), 15, 10, -9, FT_EOSPACE);
		RUN_BUFFER_SPACE_TEST(HEADER_PREP_RESET_STATE(), 21, 10, -9, FT_EOSPACE);
		RUN_BUFFER_SPACE_TEST(HEADER_PREP_RESET_STATE(), 95, 95, 1, FT_OK);
	}

	{ /* With extra data / filename / comment */
		HEADER_PREP_BZERO();
		header.extra_data_len = 10;
		header.extra_data = "abcdefghij";
		header.filename = "testtesttesttesttesttesttesttesttesttest";
		header.comment = "testtesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttest";

		RUN_BUFFER_SPACE_TEST(HEADER_PREP_RESET_STATE(), 10, 10, -6, FT_EOSPACE);
		RUN_BUFFER_SPACE_TEST(HEADER_PREP_RESET_STATE(), 22, 22, -8, FT_EOSPACE);
		RUN_BUFFER_SPACE_TEST(HEADER_PREP_RESET_STATE(), 63, 63, -9, FT_EOSPACE);
		RUN_BUFFER_SPACE_TEST(HEADER_PREP_RESET_STATE(), 147, 63, -9, FT_EOSPACE);
		RUN_BUFFER_SPACE_TEST(HEADER_PREP_RESET_STATE(), 148, 148, 1, FT_OK);
	}

	{ /* With extra data / filename / comment / crc16 */
		HEADER_PREP_BZERO();
		header.extra_data_len = 10;
		header.extra_data = "abcdefghij";
		header.filename = "testtesttesttesttesttesttesttesttesttest";
		header.comment = "testtesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttest";
		header.header_crc16 = TRUE;

		RUN_BUFFER_SPACE_TEST(HEADER_PREP_RESET_STATE(), 10, 10, -6, FT_EOSPACE);
		RUN_BUFFER_SPACE_TEST(HEADER_PREP_RESET_STATE(), 22, 22, -8, FT_EOSPACE);
		RUN_BUFFER_SPACE_TEST(HEADER_PREP_RESET_STATE(), 63, 63, -9, FT_EOSPACE);
		RUN_BUFFER_SPACE_TEST(HEADER_PREP_RESET_STATE(), 147, 63, -9, FT_EOSPACE);
		RUN_BUFFER_SPACE_TEST(HEADER_PREP_RESET_STATE(), 148, 148, -10, FT_EOSPACE);
		RUN_BUFFER_SPACE_TEST(HEADER_PREP_RESET_STATE(), 150, 150, 1, FT_OK);
	}

	/* check header integrity */
	U8 buf[150] = {0};
	HEADER_PREP_BZERO();
	header.extra_data_len = 3;
	header.extra_data = "abc";
	header.filename = "def";
	header.comment = "ghi";
	header.header_crc16 = TRUE;
	header.extra_flags = FT_GZIP_XFLAG_FAST;
	header.os = FT_GZIP_OS_ATARI_TOS;
	ft_gzip_write_header(buf, sizeof(buf), &header);

	U8 t[] = {
		0x1f, 0x8b, 0x8,
		(FT_GZIP_FLAG_HCRC | FT_GZIP_FLAG_EXTRA | FT_GZIP_FLAG_NAME | FT_GZIP_FLAG_COMMENT),
		0, 0, 0, 0,
		FT_GZIP_XFLAG_FAST,
		FT_GZIP_OS_ATARI_TOS,
		3, 0, 'a', 'b', 'c',
		'd', 'e', 'f', '\0',
		'g', 'h', 'i', '\0'};
	ASSERT(ft_memcmp(t, buf, sizeof(t)) == 0);
	U32 crc = ft_crc32(t, sizeof(t));
	ASSERT((U16)crc == *(U16 *)(buf + sizeof(t)));
}

void test_gzip_header_read()
{
	U8 t[] = {
		0x1f, 0x8b, 0x8,
		(FT_GZIP_FLAG_HCRC | FT_GZIP_FLAG_EXTRA | FT_GZIP_FLAG_NAME | FT_GZIP_FLAG_COMMENT),
		0, 0, 0, 0,
		FT_GZIP_XFLAG_FAST,
		FT_GZIP_OS_ATARI_TOS,
		3, 0, 'a', 'b', 'c',
		'd', 'e', 'f', '\0',
		'g', 'h', 'i', '\0'};

	t_gzip_header header = {0};
	ft_gzip_read_header(t, sizeof(t), &header, 0);

	ASSERT(header.header_crc16 == TRUE);
	ASSERT(header.extra_flags == FT_GZIP_XFLAG_FAST);
	ASSERT(header.os == FT_GZIP_OS_ATARI_TOS);
	ASSERT(header.extra_data_len == 3);
	ASSERT(header.extra_data != NULL);
	ASSERT(header.filename != NULL);
	ASSERT(header.comment != NULL);

	ASSERT(ft_memcmp(header.extra_data, "abc", 3) == 0);
	ASSERT(ft_memcmp(header.filename, "def", 4) == 0);
	ASSERT(ft_memcmp(header.comment, "ghi", 4) == 0);

	free(header.extra_data);
	free(header.filename);
	free(header.comment);

	// TODO: tests du buffer (en soit c'est le meme truc que pour le write, mais on sait jamais)
}

#define CHUNK 16384
S32 zlib_decompress(U8 *source, U64 source_len, U8 *dest, U64 *dest_len)
{
	S32 ret;
	z_stream strm;
	U8 out[CHUNK];
	U8 in[CHUNK];
	U64 total_out = 0;

	// Initialize the z_stream structure
	strm.zalloc = Z_NULL;
	strm.zfree = Z_NULL;
	strm.opaque = Z_NULL;
	strm.avail_in = 0;
	strm.next_in = Z_NULL;

	// The negative value of windowBits tells zlib to treat the input data as raw deflate data
	ret = inflateInit2(&strm, -MAX_WBITS);
	if (ret != Z_OK)
	{
		printf("Zlib error: inflateInit2\n");
		return ret;
	}

	strm.avail_in = source_len;
	strm.next_in = (U8 *)source;

	// Decompress until the input is exhausted or the output buffer is full
	do
	{
		strm.avail_out = CHUNK;
		strm.next_out = out;

		ret = inflate(&strm, Z_NO_FLUSH);
		if (ret == Z_STREAM_ERROR)
		{
			printf("Zlib error: inflate\n");
			inflateEnd(&strm);
			return ret;
		}

		switch (ret)
		{
		case Z_NEED_DICT:
			ret = Z_DATA_ERROR;
		case Z_DATA_ERROR:
		case Z_MEM_ERROR:
			printf("Zlib error: switch %d\n", ret);
			inflateEnd(&strm);
			return ret;
		default:
			break;
		}

		U64 have = CHUNK - strm.avail_out;
		if (total_out + have > *dest_len)
		{
			printf("Zlib error: z_buf_error\n");
			inflateEnd(&strm);
			return Z_BUF_ERROR;
		}
		ft_memcpy(dest + total_out, out, have);
		total_out += have;
	} while (strm.avail_out == 0);

	// Clean up
	inflateEnd(&strm);

	// Set the decompressed length
	*dest_len = total_out;

	return ret == Z_STREAM_END ? Z_OK : Z_DATA_ERROR;
}

void deflate_write_to_file(t_deflate_stream *stream)
{
	t_gzip_header header = {0};
	header.os = FT_GZIP_OS_UNIX;
	header.state = 0;
	U8 header_buf[20];
	U64 header_len = ft_gzip_write_header(header_buf, 20, &header);
	
	file fd = ft_fopen("./compressed.gz", "w+");
	ft_fwrite(fd, header_buf, header_len);
	ft_fwrite(fd, stream->out, stream->out_used);

	ft_gzip_write_footer(header_buf, stream->crc32, stream->in_used);
	ft_fwrite(fd, header_buf, 8);
	ft_fclose(fd);
}

void test_deflate()
{
	time_t t = time(NULL);
	U8 data[65536];
	for (U64 i = 0; i < sizeof(data); i++)
		data[i] = ft_frand(t + i) * 255;

	U8 out[80000] = {0};
	t_deflate_stream stream = ft_deflate_init_stream(data, sizeof(data), out, 80000);
	if (!ft_deflate_next_block(&stream, 4096, 1, DEFLATE_BLOCK_TYPE_1) || !ft_deflate_end(&stream))
	{
		printf("Deflate error: %s\n", ft_strerror(ft_errno));
		return;
	}

	printf("Deflated from %lu to %lu (%f%%)\n", sizeof(data), stream.out_used, 100.0f - (stream.out_used * 100.0f / sizeof(data)));

	{
		S32 ret;
		U8 decompressed[65536];
		U64 decompressed_len = sizeof(decompressed);
		if ((ret = zlib_decompress(stream.out, stream.out_used, decompressed, &decompressed_len) != Z_OK) || ft_memcmp(decompressed, data, decompressed_len) != 0)
		{
			deflate_write_to_file(&stream);
			printf("Zlib error: %d\n", ret);
			return;
		}
	}
}

void test_deflate_file()
{
	time_t t = time(NULL);
	U8 data[65536];
	U64 data_size;
	{
		file fd = ft_fopen("./test_gzip_deflate.c", "r");
		if (ft_errno != FT_OK)
		{
			printf("Error opening file\n");
			return;
		}
		U64 rd = 0;
		while (rd < sizeof(data))
		{
			U64 out = ft_fread(fd, data + rd, sizeof(data) - rd);
			if (ft_errno != FT_OK)
			{
				printf("Error reading file\n");
				return;
			}
			if (out == 0)
				break;
			rd += out;
		}
		data_size = rd;
	}

	U8 out[80000] = {0};
	t_deflate_stream stream = ft_deflate_init_stream(data, data_size, out, 80000);
	if (!ft_deflate_next_block(&stream, 79000, 1, DEFLATE_BLOCK_TYPE_1) || !ft_deflate_end(&stream))
	{
		printf("Deflate error: %s\n", ft_strerror(ft_errno));
		return;
	}

	printf("Deflated from %lu to %lu (%f%%)\n", data_size, stream.out_used, 100.0f - (stream.out_used * 100.0f / data_size));
	if (ft_argc > 1 && ft_argv[1][0] == '-' && ft_argv[1][1] == 'o')
		deflate_write_to_file(&stream);

	{
		S32 ret;
		U8 decompressed[65536];
		U64 decompressed_len = sizeof(decompressed);
		if ((ret = zlib_decompress(stream.out, stream.out_used, decompressed, &decompressed_len) != Z_OK) || ft_memcmp(decompressed, data, decompressed_len) != 0)
		{
			deflate_write_to_file(&stream);
			printf("Zlib error: %d\n", ret);
			return;
		}
	}
}


void test_inflate()
{
	U64 data_size;
	S32 err = FT_OK;
	U8 *data, *data_sv;
	U8 buffer[32768] = {0};

	{
		file fd = ft_fopen("./test2.gz", "r");
		if (ft_errno != FT_OK)
			ft_error(1, "couldn't read ./test.gzip: %s\n", ft_strerror2(ft_errno));
		data = ft_readfile(fd, &data_size);
		data_sv = data;
		ft_fclose(fd);
	}

	{
		t_gzip_header header;
		U64 header_size = ft_gzip_read_header(data, data_size, &header, 0);
		data += header_size;
		data_size -= header_size;

		printf("==GZIP HEADER==\n");
		printf("	flag: is text: %s\n", header.is_text ? "TRUE" : "FALSE");
		printf("	flag: has hcrc16: %s\n", header.header_crc16 ? "TRUE" : "FALSE");
		printf("	flag: has extra data: %s\n", header.extra_data ? "TRUE" : "FALSE");
		printf("	modification time: %u\n", header.mtime);
		printf("	extra flags: %u\n", header.extra_flags);
		printf("	os: %u\n", header.os);
		if (header.extra_data)
			printf("	extra data len: %u\n", header.extra_data_len);
		if (header.filename)
			printf("	filename: %s\n", header.filename);
		if (header.comment)
			printf("	comment: %s\n", header.comment);
		printf("===============\n");
		free(header.extra_data);
		free(header.filename);
		free(header.comment);
	}

	t_deflate_stream stream = ft_deflate_init_stream(data, data_size, buffer, sizeof(buffer));
	ft_inflate_next_block(&stream, &err);
	if (err != FT_OK)
		ft_error(1, "couldn't inflate: %s\n", ft_inflate_strerror(err));

	printf("\n\n%lu\n", stream.out_used);
	printf("Result:\n%s\n", stream.out);
	printf("%d\n", stream.out[4]);
	printf("%d\n", stream.out[5]);
	printf("%d\n", stream.out[6]);

	free(data_sv);
}


int main()
{
	//test_gzip_header_write();
	//test_gzip_header_read();

	//test_deflate();
	//test_deflate_file();

	test_inflate();
}

#endif