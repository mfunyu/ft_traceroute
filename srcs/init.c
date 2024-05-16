#include "ft_traceroute.h"
#include "parser.h"

void	init(t_traceroute *traceroute, t_args *args)
{
	traceroute->dst_hostname = args->params[0];

# ifndef BONUS
	traceroute->num_first_hop = NUM_FIRST_HOP;
	traceroute->num_max_hop = NUM_MAX_HOP;
	traceroute->num_port = NUM_PORT;
	traceroute->num_tries = NUM_TRIES;
	traceroute->num_wait = NUM_WAIT;
# else
	if (args->flags[FHOP] != -1)
		traceroute->num_first_hop = args->flags[FHOP];
	if (args->flags[MHOP] != -1)
		traceroute->num_max_hop = args->flags[MHOP];
	if (args->flags[PORT] != -1)
		traceroute->num_port = args->flags[PORT];
	if (args->flags[TRIES] != -1)
		traceroute->num_tries = args->flags[TRIES];
	if (args->flags[WAIT] != -1)
		traceroute->num_wait = args->flags[WAIT];
# endif
}