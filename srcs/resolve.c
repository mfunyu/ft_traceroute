#include "error.h"
#include "libft.h"
#include <netinet/in.h>
#include <stddef.h>
#include <errno.h>
#include <netdb.h>
#include <arpa/inet.h>

void	resolve_sockaddr_in_by_hostname(struct sockaddr_in *addr, char const *hostname)
{
	struct addrinfo	hints = {
		.ai_family = AF_INET,
		.ai_socktype = SOCK_DGRAM,
	};
	struct addrinfo	*result;
	int				ret;

	ret = getaddrinfo(hostname, NULL, &hints, &result);
	if (ret)
	{
		if (ret == EAI_NONAME)
			error_exit("unknown host");
		error_exit_gai("getaddrinfo error", ret);
	}
	ft_memcpy(addr, result->ai_addr, sizeof(struct sockaddr));
	freeaddrinfo(result);
}

void	resolve_ip_str_by_sockaddr(char *ip, struct sockaddr_in const *addr_in)
{
	char const	*ret;

	ret = inet_ntop(AF_INET, &addr_in->sin_addr, ip, INET_ADDRSTRLEN);
	if (!ret)
		error_exit_strerr("inet_ntop error");
}

void	resolve_ip_str_by_in_addr(char *ip, in_addr_t saddr)
{
	char const	*ret;

	ret = inet_ntop(AF_INET, &saddr, ip, INET_ADDRSTRLEN);
	if (!ret)
		error_exit_strerr("inet_ntop error");
}