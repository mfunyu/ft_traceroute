#include "ft_traceroute.h"
#include "error.h"
#include "libft.h"
#include "utils_time.h"
#include "network.h"
#include <stdbool.h>

static void	_recv(t_trace *trace, t_packet *packet)
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

static bool	_is_valid_packet(t_packet *packet, int port)
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
	t_packet		packet = {0};
	struct timeval	tv_recv;

	_recv(trace, &packet);
	tv_recv = get_current_time();
	if (!_is_valid_packet(&packet, trace->port))
		return (-1);

	trace->triptime = diff_time(trace->tv_send, tv_recv);

	trace->type = packet.icmphdr.type;
	trace->code = packet.icmphdr.code;
	trace->src_ip.s_addr = packet.iphdr.saddr;

	if (trace->type == ICMP_DEST_UNREACH ||
		trace->src_ip.s_addr == trace->dst_addr.sin_addr.s_addr)
	{
		trace->is_terminated = true;
	}

	return (0);
}