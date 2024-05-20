#include "error.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

int	socket_udp()
{
	int		udpfd;

	udpfd = socket(PF_INET, SOCK_DGRAM, 0);
	if (udpfd < 0)
		error_exit_strerr("socket");
	return (udpfd);
}

int	socket_icmp()
{
	int		icmpfd;

	icmpfd = socket(PF_INET, SOCK_RAW, IPPROTO_ICMP);
	if (icmpfd < 0)
	{
		icmpfd = socket(PF_INET, SOCK_DGRAM, IPPROTO_ICMP);
		if (icmpfd < 0) {
			error_exit_strerr("socket");
		}
	}
	return (icmpfd);
}