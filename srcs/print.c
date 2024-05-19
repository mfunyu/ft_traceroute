# include "ft_traceroute.h"
# include <stdio.h>

void	print_header(t_trace *trace)
{
	printf("traceroute to %s (%s), %d hops max\n",
		trace->dst_hostname, trace->dst_ip, trace->num_max_hop);
}