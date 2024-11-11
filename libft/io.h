/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 20:01:40 by reclaire          #+#    #+#             */
/*   Updated: 2024/11/10 00:27:10 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(LIBFT_IO_H)
#define LIBFT_IO_H

#include "_libft.h"
#include <sys/types.h>
#include <stdarg.h>

extern filedesc ft_stdout;
extern filedesc ft_stdin;
extern filedesc ft_stderr;
extern t_file *ft_fstdout;
extern t_file *ft_fstdin;
extern t_file *ft_fstderr;

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
extern t_file *ft_fcreate(filedesc fd);

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
extern S64 ft_read(filedesc fd, char *buffer, U64 size);
extern S64 ft_fread(t_file *file, char *buffer, U64 size);

/*
Writes 'size' bytes from 'buffer' into file 'fd'.
### On error
Sets ft_errno and returns -1.
### ft_errno
- FT_ESYSCALL if a syscall fails
*/
extern S64 ft_write(filedesc fd, char *buffer, U64 size);
extern S64 ft_fwrite(t_file *file, char *buffer, U64 size);

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
- FT_EOMEM if there was a failure allocating memory for internal data
*/
extern bool ft_ffilelock(t_file *file);

/*
Tries to lock the file.
Returns 0 for failure, >0 for success
### On error
Returns -1
### ft_errno
- FT_EOMEM if there was a failure allocating memory for internal data
*/
extern S32 ft_ftryfilelock(t_file *file);

/*
Unlocks the file
### On error
Returns FALSE
### ft_errno
- FT_EOMEM if there was a failure allocating memory for internal data
*/
extern bool ft_ffileunlock(t_file *file);

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

extern S64 ft_vprintf(const_string fmt, va_list args);
extern S64 ft_vfprintf(t_file *file, const_string fmt, va_list args);
extern S64 ft_vdprintf(filedesc fd, const_string fmt, va_list args);
extern S64 ft_vsprintf(string str, const_string fmt, va_list args);
extern S64 ft_vsnprintf(string str, U64 n, const_string fmt, va_list args);

/*
Checks the type of a file.
'b': block device
'c': character device
'd': directory
'p': FIFO/pipe
'l': symlink
's': socket
'?': unkown
*/
extern char ft_ftype(U32 md);

/*
Parses the mode of a file (returned by stat) into buf. Buf should have 10 or more spaces allocated.
*/
extern void ft_fmode(U32 md, char *buf);

#endif