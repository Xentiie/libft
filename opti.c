#include "srcs/libft_int.h"
#include <stdio.h>


static bool write_block_header(t_bitstream *stream, bool last, U8 block_type)
{
	if (UNLIKELY(stream->bit_offset > 5 && stream->byte_offset + 1 > stream->buffer_max_len))
		return FALSE;

	U16 n = last | (block_type << 1);
	U16 *addr = (U16*)(stream->buffer + stream->byte_offset);
	*addr |= (n << stream->bit_offset);

	printf("%d %u %#x -> %#x\n", n, stream->bit_offset, (n << stream->bit_offset), *addr);

	if (stream->bit_offset > 5)
	{
		stream->bit_offset %= 8;
		stream->byte_offset++;
		stream->buffer[stream->byte_offset] = 0;
	}
	else
		stream->bit_offset += 3;
	return TRUE;
}


int test1()
{
	U8 buffer[100000];

	t_bitstream stream = FT_BITSTREAM_INIT(buffer, sizeof(buffer));

	t_clock cl;
	clk_init(&cl);
	clk_start(&cl);

	for (U64 i = 0; i < 3000000; i++)
	{
		S32 r = ft_rand();
		bool last = r & 1;
		bool block_type = r & 0x6;
		if (!write_block_header(&stream, last, block_type))
			stream.byte_offset = 0;
	}

	clk_stop(&cl);
	string fmt = clk_fmt_elapsed_str(&cl);
	printf("write_block_header: %s\n", fmt);
}

int test2()
{
	U8 buffer[100000];

	t_bitstream stream = FT_BITSTREAM_INIT(buffer, sizeof(buffer));

	t_clock cl;
	clk_init(&cl);
	clk_start(&cl);

	for (U64 i = 0; i < 3000000; i++)
	{
		S32 r = ft_rand();
		bool last = r & 1;
		bool block_type = (r & 0x6) >> 1;
		ft_bstrm_write_bit(&stream, last);
		ft_bstrm_write_bit(&stream, block_type);
		ft_bstrm_write_bit(&stream, block_type >> 1);
		if (ft_errno == FT_ERANGE)
			stream.byte_offset = 0;
	}

	clk_stop(&cl);
	string fmt = clk_fmt_elapsed_str(&cl);
	printf("ft_bstrm_write_bit: %s\n", fmt);
}

void validate()
{
	U8 buffer[50];
	ft_bzero(buffer, sizeof(buffer));

	t_bitstream stream1 = FT_BITSTREAM_INIT(buffer, sizeof(buffer));
	t_bitstream stream2 = FT_BITSTREAM_INIT(buffer + 25, sizeof(buffer));

	for (int i = 0; i < 10; i++)
	{
		S32 r = ft_rand();
		bool last = r & 1;
		bool block_type = (r & 0x6) >> 1;
		ft_bstrm_write_bit(&stream1, last);
		ft_bstrm_write_bit(&stream1, block_type);
		ft_bstrm_write_bit(&stream1, block_type >> 1);

		write_block_header(&stream2, last, block_type);

		//if (buffer[i] != buffer[i + 25])
		//	printf("(%d, %u/%u)Invalid: %#x %#x\n", i, last, block_type, buffer[0], buffer[1]);
	}
	if (ft_memcmp(buffer, buffer + 25, 10))
	{
		printf("Invalid :(\n");
		
		printf("%d%d%d\n", buffer[0] & 1, buffer[0] & 2, buffer[0] & 4);
		printf("%d%d%d\n", buffer[25] & 1, buffer[25] & 2, buffer[25] & 4);

		printf("%d%d%d\n", buffer[0] & 8, buffer[0] & 16, buffer[0] & 32);
		printf("%d%d%d\n", buffer[25] & 8, buffer[25] & 16, buffer[25] & 32);

		printf("%d%d%d\n", buffer[0] & 64, buffer[0] & 128, buffer[1] & 1);
		printf("%d%d%d\n", buffer[25] & 64, buffer[25] & 128, buffer[26] & 1);
	}
}

int main()
{
	//test1();
	//test2();

6; 0; 0x6; 0x6;
7; 3; 0x38; 0x3e;
4; 6; 0x100; 0x13e;
5; 6; 0x140; 0x140;
	validate();

	unsigned int i = 8;
	printf("\n%u\n", i / 8);

}