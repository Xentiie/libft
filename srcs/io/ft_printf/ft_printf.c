/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 16:43:53 by reclaire          #+#    #+#             */
/*   Updated: 2025/01/27 22:21:02 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_int.h"
#include "libft/limits.h"

#include <stdlib.h>

#if defined(TEST)
#include <stdio.h>
#endif

static S64 write_interface_fd(const_string str, U64 len, void *data)
{
	return ft_write(*((filedesc *)data), (string)str, len);
}

static S64 write_interface_file(const_string str, U64 len, void *data)
{
	return ft_fwrite(data, (string)str, len);
}

S64 ft_iprintf(f_printf_write_interface write_interface, void *data, const_string fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	U64 out = ft_viprintf(fmt, args, write_interface, data);
	va_end(args);
	return out;
}

S64 ft_printf(const_string fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	U64 out = ft_vfprintf(ft_fstdout, fmt, args);
	va_end(args);
	return out;
}

S64 ft_fprintf(t_file *file, const_string fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	U64 out = ft_vfprintf(file, fmt, args);
	va_end(args);
	return out;
}

S64 ft_dprintf(filedesc fd, const_string fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	U64 out = ft_vdprintf(fd, fmt, args);
	va_end(args);
	return out;
}

S64 ft_vprintf(const_string fmt, va_list args)
{
	return ft_vfprintf(ft_fstdout, fmt, args);
}

S64 ft_vfprintf(t_file *file, const_string fmt, va_list args)
{
	U64 ret;

	ft_ffilelock(file);
	ret = ft_viprintf(fmt, args, write_interface_file, file);
	ft_ffileunlock(file);
	return ret;
}

S64 ft_vdprintf(filedesc fd, const_string fmt, va_list args)
{
	return __ftprintf_internal(fmt, args, write_interface_fd, &fd);
}

struct s_wr_i_str_data
{
	U64 n;
	string str;
};

static S64 write_interface_str(const_string str, U64 len, void *data)
{
	struct s_wr_i_str_data *_data = (struct s_wr_i_str_data *)data;

	U64 i = 0;

	if (_data->n <= 0 || _data->n - 1 > (len))
		ft_errno = FT_EOSPACE;

	while (i < len && i < _data->n)
	{
		_data->str[i] = str[i];
		i++;
	}
	_data->str += i;
	_data->n -= i;
	return i;
}

static S64 write_interface_void(const_string str, U64 len, void *data)
{
	(void)str;
	(void)data;
	return len;
}

S64 ft_sprintf(string str, const_string fmt, ...)
{
	va_list args;

	va_start(args, fmt);
	U64 out = ft_vsprintf(str, fmt, args);
	va_end(args);
	return out;
}

S64 ft_snprintf(string str, U64 n, const_string fmt, ...)
{
	va_list args;

	va_start(args, fmt);
	U64 out = ft_vsnprintf(str, n, fmt, args);
	va_end(args);
	return out;
}

string ft_saprintf(const_string fmt, ...)
{
	va_list args;
	string ret;

	va_start(args, fmt);
	ret = ft_vsaprintf(fmt, args);
	va_end(args);
	return ret;
}

string ft_sanprintf(U64 n, const_string fmt, ...)
{
	va_list args;
	string ret;

	va_start(args, fmt);
	ret = ft_vsanprintf(n, fmt, args);
	va_end(args);
	return ret;
}

S64 ft_vsprintf(string str, const_string fmt, va_list args)
{
	return ft_vsnprintf(str, U64_MAX, fmt, args);
}

S64 ft_vsnprintf(string str, U64 n, const_string fmt, va_list args)
{
	struct s_wr_i_str_data data = {n, str};
	U64 out = __ftprintf_internal(fmt, args, write_interface_str, &data);
	if (data.n == 0 && n != 0)
		*(data.str - 1) = '\0';
	else
		out += write_interface_str("", 1, &data);
	return out;
}

string ft_vsaprintf(const_string fmt, va_list args)
{
	return ft_vsanprintf(U64_MAX, fmt, args);
}

string ft_vsanprintf(U64 n, const_string fmt, va_list args)
{
	U64 ret;
	string str;
	va_list dup;

	va_copy(dup, args);
	ret = ft_viprintf(fmt, dup, write_interface_void, NULL) + 1;
	va_end(dup);
	if (ret > n)
		ret = n;
	if (UNLIKELY((str = malloc(sizeof(U8) * ret)) == NULL))
		FT_RET_ERR(NULL, FT_EOMEM);
	ft_vsnprintf(str, ret, fmt, args);

	return str;
}

#if defined(TEST)

// gcc -g  -DFT_OS_LINUX -DTEST  -I../../ -L../../  *.c  -lft -lm
int main()
{
#define TEST_STR(fmt, ...) { ft_printf(fmt, __VA_ARGS__); printf("  "); printf(fmt, __VA_ARGS__); printf("\n"); }
	TEST_STR("|%5c|", 'a');
	TEST_STR("|%05c|", 'a');
	TEST_STR("|% 5c|", 'a');
	TEST_STR("|%-5c|", 'a');
	TEST_STR("|%- 5c|", 'a');
	TEST_STR("|%-05c|", 'a');
}

#endif
