#include "ft_traceroute.h"
#include "error.h"
#include "libft.h"
#include <sys/socket.h>

t_status	trace_recv(t_trace *trace)
{
	t_packet	packet = {0};
	ssize_t		ret;
	socklen_t	addr_len = sizeof(struct sockaddr);
	struct sockaddr src_addr;

	ft_memcpy(&src_addr, &trace->dst_addr, sizeof(struct sockaddr));
	ret = recvfrom(trace->icmpfd, &packet, sizeof(t_packet), MSG_DONTWAIT, &src_addr, &addr_len);
	if (ret < 0)
	{
		error_exit_strerr("recvfrom");
	}
	if (packet.icmphdr.type != ICMP_TIME_EXCEEDED && packet.icmphdr.code != ICMP_DEST_UNREACH)
		return (RETRY);

	if (packet.req_udphdr.dest != htons(trace->port))
		return (RETRY);

	if (packet.icmphdr.type == ICMP_DEST_UNREACH)
		return (STOP);
	if (packet.iphdr.saddr == trace->dst_addr.sin_addr.s_addr)
		return (STOP);

	return (CONTINUE);
}