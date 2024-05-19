#include "ft_traceroute.h"
#include "parser.h"
#include "error.h"
#include "libft.h"
#include <netinet/in.h>
#include <errno.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stddef.h>
#include <sys/socket.h>

int	init_socket()
{
	int		udpfd;

	udpfd = socket(PF_INET, SOCK_DGRAM, 0);
	if (udpfd < 0)
		error_exit_strerr("socket");
	return (udpfd);
}

void	set_ip_str_by_sockaddr(char *ip, struct sockaddr const *addr)
{
	struct sockaddr_in const	*addr_in;
	char const					*ret;

	addr_in = (struct sockaddr_in const *)addr;
	ret = inet_ntop(AF_INET, &addr_in->sin_addr, ip, INET_ADDRSTRLEN);
	if (!ret)
		error_exit_strerr("inet_ntop error");
}

void	set_sockaddr_by_hostname(struct sockaddr *addr, char const *hostname)
{
	struct addrinfo	hints = {
		.ai_family = AF_INET,
		.ai_socktype = SOCK_RAW,
		.ai_protocol = IPPROTO_ICMP
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

void	init(t_trace *trace, t_args *args)
{
	trace->dst_hostname = args->params[0];

# ifndef BONUS
	trace->num_first_hop = NUM_FIRST_HOP;
	trace->num_max_hop = NUM_MAX_HOP;
	trace->num_port = NUM_PORT;
	trace->num_tries = NUM_TRIES;
	trace->num_wait = NUM_WAIT;
# else
	if (args->flags[FHOP] != -1)
		trace->num_first_hop = args->flags[FHOP];
	if (args->flags[MHOP] != -1)
		trace->num_max_hop = args->flags[MHOP];
	if (args->flags[PORT] != -1)
		trace->num_port = args->flags[PORT];
	if (args->flags[TRIES] != -1)
		trace->num_tries = args->flags[TRIES];
	if (args->flags[WAIT] != -1)
		trace->num_wait = args->flags[WAIT];
# endif
	trace->ttl = trace->num_first_hop;
	set_sockaddr_by_hostname(&trace->dst_addr, trace->dst_hostname);
	set_ip_str_by_sockaddr(trace->dst_ip, &trace->dst_addr);
	trace->udpfd = init_socket();
}