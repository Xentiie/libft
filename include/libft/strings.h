/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 19:42:00 by reclaire          #+#    #+#             */
/*   Updated: 2025/04/15 02:42:18 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(LIBFT_STRINGS_H)
#define LIBFT_STRINGS_H

#include "libft/libft.h"

/*
TODO
*/
void ft_str_tolower(string str);

/*
TODO
*/
void ft_str_toupper(string str);

/*
Returns a copy of 'str' left-padded 'n' times with char 'c'
### On error
Sets ft_errno and returns NULL.
### ft_errno
- FT_EINVPTR if 'str' is NULL
- FT_EOMEM if out of memory
*/
string ft_lpad(string str, char c, U64 n);

/*
Returns a copy of 'str' right-padded 'n' times with char 'c'
### On error
Sets ft_errno and returns NULL.
### ft_errno
- FT_EINVPTR if 'str' is NULL
- FT_EOMEM if out of memory
*/
string ft_rpad(string str, char c, U64 n);

/*
Returns the description of the error number 'err'
### On error
Sets ft_errno and returns NULL.
### ft_errno
- FT_ERANGE if 'err' is < 0
- FT_ENOENT if no error associated with 'err' was found
*/
const_string ft_strerror(S32 err);

/*
Returns the description of the error number 'ft_errno'.
If `ft_errno == FT_ESYSCALL`, returns `ft_strerror_os(errno)`
### On error
Sets ft_errno and returns NULL.
### ft_errno
- FT_ERANGE if 'err' is < 0
- FT_ENOENT if no error associated with 'ft_errno' was found
*/
const_string ft_strerror2();

/*
Returns the name of the error number 'err'
### On error
Sets ft_errno and returns NULL.
### ft_errno
- FT_ERANGE if 'err' is < 0
- FT_ENOENT if no error associated with 'err' was found
*/
const_string ft_strerrorname(S32 err);

const_string ft_strerror_os();

/*
Append src behind dest. Dest must have enough space, including \0
*/
extern string ft_strcat(string dest, const_string src);

/*
Appends string src to the end of dst.
It will append at most dstsize - strlen(dst) - 1 characters.
It will then NUL-terminate the new string
*/
extern U64 ft_strlcat(string dest, const_string src, U64 size);

/*
Concatenate s1 and s2.
Caller gets ownership of returned string.
### On error
Sets ft_errno and returns NULL.
### ft_errno
- FT_EOMEM if out of memory
*/
extern string ft_strjoin(const_string s1, const_string s2);

/*
Copies up to dstsize - 1 characters from the string src to dst,
NUL-terminating the result if dstsize is not 0.
*/
extern U64 ft_strlcpy(string dest, const_string src, U64 size);

/*
Copies 'src' into 'dest'.
*/
extern U64 ft_strcpy(string dest, const_string src);

/*
Duplicates the string str into a new char array.
Caller gets ownership of returned string.
### On error
Sets ft_errno and returns NULL.
### ft_errno
- FT_EINVPTR if 'str' is NULL
- FT_EOMEM if out of memory
*/
extern string ft_strdup(const_string str);

/*
Duplicates the string 'str' into a new char array, and sets 'len' if non-null to the length of the string.
Caller gets ownership of returned string.
### On error
Sets ft_errno, sets 'len' to 0 if non-null and returns NULL.
### ft_errno
- FT_EINVPTR if 'str' is NULL
- FT_EOMEM if out of memory
*/
extern string ft_strdup_l(const_string str, U64 *len);

/*
Duplicates the string str into a new char array (no more that n characters).
Caller gets ownership of returned string.
### On error
Sets ft_errno and returns NULL.
### ft_errno
- FT_EINVPTR if 'str' is NULL
- FT_EOMEM if out of memory
*/
extern string ft_strndup(const_string str, U64 n);

/*
Duplicates the string 'str' into a new char array (no more that n characters), and sets 'len' if non-null to the length of the string.
Caller gets ownership of returned string.
### On error
Sets ft_errno, sets 'len' to 0 if non-null and returns NULL.
### ft_errno
- FT_EINVPTR if 'str' is NULL
- FT_EOMEM if out of memory
*/
extern string ft_strndup_l(const_string str, U64 n, U64 *len);

/*
Returns a new string from s, starting at index start with size len.
Caller gets ownership of returned string.
### On error
Sets ft_errno and returns NULL.
### ft_errno
- FT_EOMEM if out of memory
*/
extern string ft_substr(const_string s, U64 start, U64 len);

/*
Locates the first occurrence of c in the string pointed to by s.
The terminating null character taken into account.
*/
extern const_string ft_strchr(const_string str, U8 c);

/*
Locates the first occurrence of c in the string pointed to by s, searching at most len characters.
The terminating null character taken into account.
*/
extern const_string ft_strnchr(const_string str, U8 c, U64 len);

/*
Locates the last occurrence of c in string s
*/
extern const_string ft_strrchr(const_string str, U8 c);

/*
Locates the first occurrence of the null-terminated string needle in the
string haystack, where not more than len characters are searched.
If to_find is an empty string, str is returned; if to_find occurs
nowhere in str, NULL is returned; otherwise a pointer to the first
character of the first occurrence of to_find is returned.
*/
extern const_string ft_strnstr(const_string haystack, const_string needle, U64 len);

/* Returns the length of string */
extern U64 ft_strlen(const_string str);

/* Returns the length of string, no more than maxlen */
extern U64 ft_strnlen(const_string str, U64 maxlen);

/*
Returns the index of the first occurrence of c in str, -1 if not found.
*/
extern S64 ft_strgetindex(const_string str, U8 c);

/*
Compares string s1 against string s2. Returns s1 - s2
*/
extern S32 ft_strcmp(const_string s1, const_string s2);

/*
Compares string s1 against string s2. Compares no more than n characters. Returns s1 - s2
*/
extern S32 ft_strncmp(const_string s1, const_string s2, U64 n);

/*
Compares filenames s1 against s2. Uses debian's versionning rules to determine highest file version
*/
extern S32 ft_filevercmp(const_string s1, const_string s2);

/*
Converts a lower-case letter to the corresponding upper-case letter.
*/
extern U8 ft_tolower(U8 c);

/*
Converts a upper-case letter to the corresponding lower-case letter.
*/
extern U8 ft_toupper(U8 c);

/*
Creates a copy of s1 wihout the characters in set at end and start of string.
### On error
Sets ft_errno and returns NULL.
### ft_errno
- FT_EOMEM if out of memory
*/
extern string ft_strtrim(const_string s1, const_string set);

/*
Applies function f to each characters in string str, and returns
a new string of all the results of f.
Caller gets ownership of returned string.
*/
extern string ft_strmapi(const_string str, U8 (*f)(U64 index, U8));

/*
Applies function f to each characters in string s.
*/
extern void ft_striteri(string str, void (*f)(U64 index, string str));

#endif