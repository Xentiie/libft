/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 20:13:26 by reclaire          #+#    #+#             */
/*   Updated: 2024/11/10 22:43:22 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #define _WIN32_WINNT
#include "libft_int.h"

#define _GNU_SOURCE
#if defined(FT_OS_WIN)
#include <winsock2.h>
#include <ws2tcpip.h>
#else
#include <sys/socket.h>
typedef filedesc SOCKET;
#endif

#if defined(FT_OS_WIN)
static bool WSA_init = FALSE; // TODO: thread safety
static S32 __init_WSA()
{
	if (!WSA_init)
	{
		WSADATA wsaData;
		S32 out = WSAStartup(MAKEWORD(2, 2), &wsaData);
		if (out == 0)
			WSA_init = TRUE;
		return out;
	}
	else
		return 0;
}
#else
static S32 __init_WSA()
{
	return 0;
}
#endif

#if defined(FT_OS_WIN)
S32 ft_resolve_hostname(void *addr_out, string host, string port)
{
	__init_WSA();

	S32 ret;
	struct addrinfo *addrinfo = NULL,
					hints;

	ft_memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	if ((ret = getaddrinfo(host, port, &hints, &addrinfo)) != 0)
	{
		// TODO: set errno
		return -1;
	}

	*(struct addrinfo *)addr_out = *addrinfo;
	freeaddrinfo(addrinfo);
	return 0;
}
#endif

#if defined(FT_OS_WIN)
filedesc ft_socket(S32 domain, S32 type, S32 protocol)
{
	filedesc sock;

	__init_WSA();

	if (UNLIKELY((sock = (filedesc)socket(domain, type, protocol)) == (filedesc)INVALID_SOCKET))
		__FTRETURN_ERR((filedesc)-1, FT_ESYSCALL);
	__FTRETURN_OK(sock);
}
#else
filedesc ft_socket(S32 domain, S32 type, S32 protocol)
{
	filedesc sock;
	
	sock = (filedesc)socket(domain, type, protocol);
	if (UNLIKELY((sock = (filedesc)socket(domain, type, protocol)) == (filedesc)-1))
		__FTRETURN_ERR((filedesc)-1, FT_ESYSCALL);
	__FTRETURN_OK(sock);
}
#endif

#if defined(FT_OS_WIN)
bool ft_connect(filedesc socket, const void *addr, U64 addr_len)
{
	__init_WSA();
	return connect((SOCKET)socket, addr, addr_len) != 0; // -1 on linux
}
#endif

// TODO: peut etre qu'on veut check les retours ici pour set ft_errno a FT_ESYSCALL si ca fail
S64 ft_send(filedesc socket, const U8 *buf, U64 size, S32 flags)
{
	__init_WSA();
	return send((SOCKET)socket, (const char *)buf, size, flags);
}

S64 ft_recv(filedesc socket, const U8 *buf, U64 size, S32 flags)
{
	__init_WSA();
	return recv((SOCKET)socket, (char *)buf, size, flags);
}
