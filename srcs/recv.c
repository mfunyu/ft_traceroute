#include "ft_traceroute.h"
#include "error.h"
#include "libft.h"
#include <stdbool.h>
#include <sys/socket.h>

void	_recv(t_trace *trace, t_packet *packet)
{
	ssize_t			ret;
	socklen_t		addr_len = sizeof(struct sockaddr);
	struct sockaddr src_addr;

	ft_memcpy(&src_addr, &trace->dst_addr, sizeof(struct sockaddr));
	ret = recvfrom(trace->icmpfd, packet, sizeof(t_packet), MSG_DONTWAIT, &src_addr, &addr_len);
	if (ret < 0)
	{
		error_exit_strerr("recvfrom");
	}
}

bool	_is_valid_packet(t_packet *packet, int port)
{
	if (packet->icmphdr.type != ICMP_TIME_EXCEEDED
		&& packet->icmphdr.type != ICMP_DEST_UNREACH)
		return (false);

	if (packet->req_udphdr.dest != htons(port))
		return (false);
	return (true);
}

int	trace_recv(t_trace *trace)
{
	t_packet	packet = {0};

	_recv(trace, &packet);
	if (!_is_valid_packet(&packet, trace->port))
		return (-1);

	if (packet.icmphdr.type == ICMP_DEST_UNREACH ||
		packet.iphdr.saddr == trace->dst_addr.sin_addr.s_addr)
	{
		trace->is_terminated = true;
	}

	return (0);
}