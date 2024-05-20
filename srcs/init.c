#include "ft_traceroute.h"
#include "parser.h"
#include "network.h"

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
	trace->port = trace->num_port;
	resolve_sockaddr_in_by_hostname(&trace->dst_addr, trace->dst_hostname);
	trace->dst_addr.sin_port = htons(trace->port);
	resolve_ip_str_by_sockaddr(trace->dst_ip, &trace->dst_addr);
	trace->udpfd = socket_udp();
	trace->icmpfd = socket_icmp();
}