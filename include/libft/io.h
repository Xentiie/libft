/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 20:01:40 by reclaire          #+#    #+#             */
/*   Updated: 2025/05/21 20:16:17 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(LIBFT_IO_H)
#define LIBFT_IO_H

#include "libft/bits/globals.h"

#include "libft/libft.h"

#include <sys/types.h>
/* we only need the definition of va_list type */
#define __need_va_list
#include <stdarg.h>

#define FT_IO_UNBUFFERED 0
#define FT_IO_LINE_BUFFERED 1
#define FT_IO_FULL_BUFFERED 2

_FT_GLOBAL_VAR_DEC(U64, _ft_bufsiz);

_FT_GLOBAL_VAR_DEC(filedesc, ft_stdin);
_FT_GLOBAL_VAR_DEC(filedesc, ft_stdout);
_FT_GLOBAL_VAR_DEC(filedesc, ft_stderr);

_FT_GLOBAL_VAR_DEC(t_file *, ft_fstdin);
_FT_GLOBAL_VAR_DEC(t_file *, ft_fstdout);
_FT_GLOBAL_VAR_DEC(t_file *, ft_fstderr);

#define _ft_bufsiz _FT_GLOBAL_VAR(_ft_bufsiz)
#define ft_stdin _FT_GLOBAL_VAR(ft_stdin)
#define ft_stdout _FT_GLOBAL_VAR(ft_stdout)
#define ft_stderr _FT_GLOBAL_VAR(ft_stderr)
#define ft_fstdin _FT_GLOBAL_VAR(ft_fstdin)
#define ft_fstdout _FT_GLOBAL_VAR(ft_fstdout)
#define ft_fstderr _FT_GLOBAL_VAR(ft_fstderr)

/*
Opens a file. The string 'mode' can be one of the following:
	r: open for reading
	w: open for writing
	a: open for appending
	[r/w/a]+: read/write
Modes [w/a] will create the file if it doesn't exists
### On error
Sets ft_errno and returns -1.
### ft_errno
- FT_EINVPTR if 'path' or 'mode' is NULL
- FT_EINVVAL if 'mode' is invalid
- FT_ESYSCALL if a syscall fails
*/
extern filedesc ft_open(const_string path, const_string mode);
extern t_file *ft_fopen(const_string path, const_string mode);

/*
Creates a new t_file from a filedesc `fd`.
*/
extern t_file *ft_fcreate(filedesc fd, const_string mode);

/*
Closes the file descriptor 'fd'
### On error
Sets ft_errno and returns -1.
### ft_errno
- FT_EINVVAL if 'fd' is invalid
- FT_ESYSCALL if a syscall fails
### TODO
Linux error check
*/
extern void ft_close(filedesc fd);
extern void ft_fclose(t_file *file);
extern void ft_fdestroy(t_file *file);

/*
Reads 'size' bytes from file 'fd' into 'buffer'.
### On error
Sets ft_errno and returns -1.
### ft_errno
- FT_ESYSCALL if a syscall fails
*/
extern S64 ft_read(filedesc fd, void *buffer, U64 size);
extern S64 ft_fread(t_file *file, void *buffer, U64 size);
extern S64 ft_fread_unlocked(t_file *file, void *buffer, U64 size);

/*
Writes 'size' bytes from 'buffer' into file 'fd'.
### On error
Sets ft_errno and returns -1.
### ft_errno
- FT_ESYSCALL if a syscall fails
*/
extern S64 ft_write(filedesc fd, void *buffer, U64 size);
extern S64 ft_fwrite(t_file *file, void *buffer, U64 size);
extern S64 ft_fwrite_unlocked(t_file *file, void *buffer, U64 size);

/*
Flushes the internal buffer
### On error
See ft_write
*/
extern void ft_fflush(t_file *file);

/*
Locks the file
### On error
Returns FALSE
### ft_errno
- FT_EOMEM if out of memory
*/
extern bool ft_ffilelock(t_file *file);

/*
Tries to lock the file.
Returns 0 for failure, >0 for success
### On error
Returns -1
### ft_errno
- FT_EOMEM if out of memory
*/
extern S32 ft_ftryfilelock(t_file *file);

/*
Unlocks the file
### On error
Returns FALSE
### ft_errno
- FT_EOMEM if out of memory
*/
extern bool ft_ffileunlock(t_file *file);

/*
Changes the internal buffer.

If `buf` is non NULL, sets the t_file `f` buffer to `buf`, with size `size`.

If the file is not buffered, always return TRUE without doing anything
### On error
Returns FALSE
### ft_errno
- FT_EINVVAL if `buf` is non NULL and `size` is 0
- FT_EOMEM if out of memory
*/
extern bool ft_fsetbuf(t_file *f, U8 *buf, U64 size, S16 bufmode);

/*
Reads the whole file.
Returns a malloc'ed buffer containing the whole file,
and puts the buffer size in `out_size`
### On error
Sets ft_errno and returns NULL.
### ft_errno
- FT_ESYSCALL if a syscall fails
- FT_EOMEM if out of memory
*/
extern U8 *ft_readfile(filedesc fd, U64 *out_size);

/*
Reads the whole file.
Returns a malloc'ed buffer containing the whole file,
and puts the buffer size in `out_size`
### On error
Sets ft_errno and returns NULL.
### ft_errno
- FT_ESYSCALL if a syscall fails
- FT_EOMEM if out of memory
*/
extern U8 *ft_freadfile(t_file *file, U64 *out_size);



/*
printf !
*/
extern S64 ft_printf(const_string fmt, ...) __attribute__((format(printf, 1, 2)));
extern S64 ft_fprintf(t_file *file, const_string fmt, ...) __attribute__((format(printf, 2, 3)));
extern S64 ft_dprintf(filedesc fd, const_string fmt, ...) __attribute__((format(printf, 2, 3)));
extern S64 ft_sprintf(string str, const_string fmt, ...) __attribute__((format(printf, 2, 3)));
extern S64 ft_snprintf(string str, U64 n, const_string fmt, ...) __attribute__((format(printf, 3, 4)));
extern string ft_saprintf(const_string fmt, ...) __attribute__((format(printf, 1, 2)));
extern string ft_sanprintf(U64 n, const_string fmt, ...) __attribute__((format(printf, 2, 3)));

extern S64 ft_vprintf(const_string fmt, va_list args) __attribute__((format(printf, 1, 0)));
extern S64 ft_vfprintf(t_file *file, const_string fmt, va_list args) __attribute__((format(printf, 2, 0)));
extern S64 ft_vdprintf(filedesc fd, const_string fmt, va_list args) __attribute__((format(printf, 2, 0)));
extern S64 ft_vsprintf(string str, const_string fmt, va_list args) __attribute__((format(printf, 2, 0)));
extern S64 ft_vsnprintf(string str, U64 n, const_string fmt, va_list args) __attribute__((format(printf, 3, 0)));
extern string ft_vsaprintf(const_string fmt, va_list args) __attribute__((format(printf, 1, 0)));
extern string ft_vsanprintf(U64 n, const_string fmt, va_list args) __attribute__((format(printf, 2, 0)));
#if defined(_FT_IPRINTF)
typedef S64 (*f_printf_write_interface)(const_string str, U64 str_len, void *data);
extern S64 ft_iprintf(f_printf_write_interface write_interface, void *data, const_string fmt, ...) __attribute__((format(printf, 3, 4)));
extern S64 ft_viprintf(const_string fmt, va_list args, f_printf_write_interface write_interface, void *data) __attribute__((format(printf, 1, 0)));
#endif

void ft_perror(const_string str);

/*
Checks the type of a file from a bitfield `md` (returned by `stat`)
'b': block device
'c': character device
'd': directory
'p': FIFO/pipe
'l': symlink
's': socket
'?': unkown
*/
extern U8 ft_fchk_type(U32 md);

/*
Parses the mode of a file (returned by stat) into buf.
*/
extern void ft_fchk_mode(U32 md, char buf[11]);

#endif