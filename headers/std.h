/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   std.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 19:49:34 by reclaire          #+#    #+#             */
/*   Updated: 2024/02/14 02:47:55 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_STD_H
# define LIBFT_STD_H

# include "_libft.h"

/*
Search for the environnement variable associated with 'name' in 'ft_env'
### On error
Sets ft_errno and returns NULL.
### ft_errno
- FT_EINVPTR if 'name' is NULL
- FT_ENOINIT if FT_INIT_ARGV has not been called
- FT_ENOENT if no environnement variables associated with 'name' has been found
*/
extern const_string	ft_getenv(const_string name);

/*
Search for the environnement variable associated with 'name' in 'env'
### On error
Sets ft_errno and returns NULL.
### ft_errno
- FT_EINVPTR if 'name' or 'env' is NULL
- FT_ENOENT if no environnement variables associated with 'name' has been found
*/
extern const_string	ft_getenv2(const_string name, const_string *env);

/*
Writes n zeroed bytes to the string s.
*/
extern void		ft_bzero(void *s, U64 n);

/*
Locates the first occurrence of c in string s.
*/
extern void		*ft_memchr(void const *s, U8 c, U64 n);

/*
Compares byte string s1 against byte string s2.
*/
extern S32		ft_memcmp(void const *s1, void const *s2, U64 n);

/*
Copies n bytes from memory area src to memory area dst.
The two strings may not overlap. If they do use ft_memmove instead.
### On error
Sets ft_errno and returns dst.
### ft_errno
- FT_EINVPTR if dst or src is NULL
*/
extern void		*ft_memcpy(void *dst, void const *src, U64 n);

/*
Duplicates n bytes of src.
Caller owns returned value
### On error
Sets ft_errno and returns NULL.
### ft_errno
- FT_EOMEM if out of memory
*/
extern void		*ft_memdup(void const *src, U64 n);

/*
Copies len bytes from string src to string dst. The two strings may overlap;
the copy is always done in a non-destructive manner.
*/
extern void		*ft_memmove(void *dst, void const *src, U64 len);

/*
Writes len bytes of value c.
*/
extern void		*ft_memset(void *b, U8 c, U64 len);

/*
Stupid hash function, may or may not work
*/
extern U32		ft_hash_buffer(const void *buff, U64 size);

/*
Converts a string to an int.
*/
extern S32		ft_atoi(const_string str, U64 *out);

/*
Converts a string to a float.
*/
extern F32		ft_atof(const_string str, U64 *len);

/*
Converts a hex string to a unsigned int.
*/
extern U32		ft_atoix(const_string str, U64 *len);

/*
Converts an int to a string.
Caller owns returned value
### On error
Sets ft_errno and returns NULL.
### ft_errno
- FT_EOMEM if out of memory
*/
extern string	ft_itoa(S32 n);

/*
Converts an unsigned int to a string.
Caller owns returned value
### On error
Sets ft_errno and returns NULL.
### ft_errno
- FT_EOMEM if out of memory
*/
extern string	ft_uitoa(U64 n);

/*
Converts a float to a string.
Caller owns returned value
### On error
Sets ft_errno and returns NULL.
### ft_errno
- FT_EOMEM if out of memory
*/
extern string	ft_ftoa(F32 n);

/*
Check if character is digit or alpha.
*/
extern bool 	ft_isalnum(U8 c);

/*
Check if character is alpha.
*/
extern bool 	ft_isalpha(U8 c);

/*
Check if character is ascii.
*/
extern bool 	ft_isascii(U8 c);

/*
Check if character is digit.
*/
extern bool 	ft_isdigit(U8 c);

/*
Check if character is printable.
*/
extern bool 	ft_isprint(U8 c);

/*
Check if character is whitespace. (' ', '\t', '\r', '\n', '\v', '\f')
*/
extern bool		ft_iswhitespace(U8 c);

/*
Check if character is lower-case
*/
extern bool		ft_islower(U8 c);

/*
Check if character is upper-case
*/
extern bool		ft_isupper(U8 c);

/*
Check if null-terminated string str is digit or alpha-numerical.
*/
extern bool 	ft_str_isalnum(string str);

/*
Check if null-terminated string str is alpha.
*/
extern bool 	ft_str_isalpha(string str);

/*
Check if null-terminated string str is ascii.
*/
extern bool 	ft_str_isascii(string str);

/*
Check if null-terminated string str is digit-only.
*/
extern bool 	ft_str_isdigit(string str);

/*
Check if null-terminated string str is printable.
*/
extern bool 	ft_str_isprint(string str);

/*
Check if null-terminated string str is whitespace. (' ', '\\t', '\\r', '\\n', '\\v', '\\f')
*/
extern bool 	ft_str_iswhitespace(string str);

/*
### On error
Sets ft_errno and returns NULL.
### ft_errno
- FT_EOMEM if out of memory
Creates an array of int from min to max.
*/
extern S32		*ft_range(S32 min, S32 max);

/*
Creates an array of int from min to max and returns the size of the array.
### On error
Sets ft_errno, sets the pointer pointed by 'range' to NULL and returns -1.
### ft_errno
- FT_EOMEM if out of memory
*/
extern S32		ft_nrange(S32 **range, S32 min, S32 max);

/*
Sorts the array 'a' inplace, using 'key' function.
'elem_size': the size of 1 element in the array
'array_len': the length of the array
*/
extern void		ft_sort(void *a, U64 elem_size, U64 array_len, S32 (*key)(void *, void *));


#endif