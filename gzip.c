/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gzip.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 18:46:20 by reclaire          #+#    #+#             */
/*   Updated: 2024/06/13 17:01:41 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/std.h"
#include "libft/strings.h"
#include "libft/io.h"
#include "libft/getopt.h"
#include "libft/compression/gzip.h"
#include "libft/compression/deflate.h"

#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

S32 main(S32 argc, const_string *argv)
{
	string out_file = NULL;
	bool compress = TRUE;

	S32 c;
	while ((c = ft_getopt(argc, argv, "do:")) != -1)
	{
		switch (c)
		{
		case 'd':
			compress = FALSE;
			break;
		case 'o':
			out_file = (string)ft_optarg;
			break;
		case '?':
		default:
			return 1;
		}
	}

	if (ft_optind >= argc)
		ft_error(1, "no input files specified\n");

	const_string in_file = argv[ft_optind];
	if (!out_file)
	{
		if (compress)
			out_file = ft_strjoin(in_file, ".gz");
		else
		{
			out_file = ft_strdup(in_file);
			string d = (string)ft_strrchr(out_file, '.');
			if (!d || ft_strncmp(d, ".gz", 3))
				ft_error(1, "unknown suffix -- ignored\n");
			*d = '\0';
		}
	}

	if (access(out_file, F_OK) == 0)
	{
		ft_printf("file '%s' already exists, overwrite ? [Y/n]\n", out_file);
		char c = getc(stdin);
		if (c == 'n')
			return 0;
	}

	if (compress)
	{
		U8 buf[1024];
		file in = ft_fopen((string)in_file, "r");
		file out = ft_fopen((string)out_file, "w+");

		{
			if (in == (file)-1)
				ft_error_errno2(1, "couldn't open '%s'\n", in_file);
			if (out == (file)-1)
				ft_error_errno2(1, "couldn't open '%s'\n", out_file);
		}

		struct stat st;
		stat(in_file, &st);
		U64 in_size = st.st_size;
		U8 *data = malloc(sizeof(U8) * in_size);

		{
			t_gzip_header header = (t_gzip_header)
			{
				.is_text = FALSE,
				.header_crc16 = TRUE,
				.mtime = st.st_mtime,
				.extra_flags = FT_GZIP_XFLAG_NONE,
				.os = FT_GZIP_OS_UNIX,
				.extra_data_len = 0,
				.extra_data = NULL,
				.filename = (string)in_file,
				.comment = NULL
			};
			U64 header_len = ft_gzip_write_header(buf, sizeof(buf), &header);
			ft_fwrite(out, buf, header_len);
		}


		{
			U64 rd = 0;
			while (rd < in_size)
			{
				S64 r = ft_fread(in, data + rd, in_size - rd);
				if (r == 0)
					break;
				if (r < 0)
					ft_error_errno2(1, "couldn't read input file\n");
				rd += r;
			}
			ft_fclose(in);
		}

		U8 *data_out = malloc(sizeof(U8) * in_size);

		t_deflate_stream stream = ft_deflate_init_stream(data, in_size, data_out, in_size);
		if (!ft_deflate_next_block(&stream, in_size, TRUE, 1))
			ft_error_errno(1, "deflate error\n");
		ft_deflate_end(&stream);

		if (ft_errno != FT_OK)
			ft_error_errno(1, "\n");

		printf("Deflated %f%%\n", 100.0f - (stream.out_used / (F32)in_size));

		ft_fwrite(out, data_out, stream.out_used);

		{
			U64 footer_len = ft_gzip_write_footer(buf, 0xa7a1bb03, stream.in_used);
			ft_fwrite(out, buf, footer_len);
		}

		ft_fclose(out);
	}
	else
	{

		file in = ft_fopen((string)in_file, "r");
		file out = ft_fopen((string)out_file, "w+");

		{
			if (in == (file)-1)
				ft_error_errno2(1, "couldn't open '%s'\n", in_file);
			if (out == (file)-1)
				ft_error_errno2(1, "couldn't open '%s'\n", out_file);
		}

		struct stat st;
		stat(in_file, &st);
		U64 in_size = st.st_size;
		U8 *data = malloc(sizeof(U8) * in_size);

		{
			U64 rd = 0;
			while (rd < in_size)
			{
				S64 r = ft_fread(in, data + rd, in_size - rd);
				if (r == 0)
					break;
				if (r < 0)
					ft_error_errno2(1, "couldn't read input file\n");
				rd += r;
			}
			ft_fclose(in);
		}
		
		U64 header_size;
		{
			t_gzip_header header = {0};
			header_size = ft_gzip_read_header(data, in_size, &header, 0);
			if (ft_errno != FT_OK)
				ft_error_errno(1, "couldn't read gzip header\n");
			printf("%lu\n", header_size);
		}

		U8 buffer[32768];
		S32 err;
		t_deflate_stream stream = ft_deflate_init_stream(data + header_size, in_size - header_size, buffer, sizeof(buffer));
		if (!ft_inflate_next_block(&stream, &err) && err != FT_OK)
		{
			ft_dprintf(ft_stderr, "%s: couldn't inflate: %s\n", ft_argv[0], ft_inflate_strerror(err));
			exit(1);
		}

		ft_fwrite(out, buffer, stream.out_used);
		ft_fclose(out);
	}
}
