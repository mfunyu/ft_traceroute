#include "parser.h"
#include "error.h"
#include "ft_traceroute.h"
#include <stdlib.h>
#include <stdio.h>
#include <sys/select.h>
#include <sys/time.h>

void	print_help(void)
{
	printf("Usage: ./ft_traceroute [OPTION...] HOST\n\
Print the route packets trace to network host.\n\n");
# ifdef BONUS
	printf("\
  -f, --first-hop=NUM        set initial hop distance, i.e., time-to-live\n\
  -m, --max-hop=NUM          set maximal hop count (default: 64)\n\
  -p, --port=PORT            use destination PORT port (default: 33434)\n\
  -q, --tries=NUM            send NUM probe packets per hop (default: 3)\n\
  -w, --wait=NUM             wait NUM seconds for response (default: 3)\n");
# endif
	printf("\
  -?, --help                 give this help list\n\n");
	printf("Mandatory or optional arguments to long options are also mandatory or optional\n\
for any corresponding short options.\n\n");
	printf("Report bugs to: <https://github.com/mfunyu/ft_traceroute/issues>\n");
}

static void	_handle_args(t_args *args, int ac, char **av)
{
	if (ac <= 1)
		error_exit_usage("missing host operand");
	parse_args(args, ac, av);
	if (args->flags[HELP])
	{
		print_help();
		exit(EXIT_SUCCESS);
	}
	if (!args->params[0])
		error_exit_usage("missing host operand");
}

int	select_loop(t_trace *trace)
{
	fd_set	readfds;
	int		ready;
	int		ret;
	int		maxfd;

	maxfd = trace->icmpfd + 1;
	FD_ZERO(&readfds);
	FD_SET(trace->icmpfd, &readfds);
	trace->timeout.tv_sec = trace->num_wait;
	trace->timeout.tv_usec = 0;
	ready = select(maxfd, &readfds, NULL, NULL, &trace->timeout);
	if (ready < 0)
		error_exit_strerr("select");
	if (ready != 0) {
		ret = trace_recv(trace);
		if (ret == -1)
			return (ret);
	}
	return (ready);
}

void	run_try(t_trace *trace)
{
	int		ready;
	bool	ip_printed = false;

	for (int i = 0; i < trace->num_tries; i++)
	{
		trace_send(trace);
		ready = -1;
		while (ready < 0) {
			ready = select_loop(trace);
		}
		if (ready == 0) {
			printf(" * ");
			fflush(stdout);
		} else {
			if (!ip_printed) {
				printf(" %s ", trace->src_ip);
				ip_printed = true;
			}
			printf(" %.3fms ", trace->triptime);
		}
	}
	printf("\n");
}

void	set_ttl(int udpfd, int ttl)
{
	int	ret;

	ret = setsockopt(udpfd, IPPROTO_IP, IP_TTL, &ttl, sizeof(int));
	if (ret < 0)
		error_exit_strerr("setsockopt");
}

void	ft_traceroute(t_trace *trace)
{
	print_header(trace);
	for (int hop = 1; trace->ttl <= trace->num_max_hop; hop++)
	{
		trace->dst_addr.sin_port = htons(trace->port);
		printf(" %2d  ", hop);
		set_ttl(trace->udpfd, trace->ttl);
		run_try(trace);
		if (trace->is_terminated)
			break;
		trace->ttl++;
		trace->port++;
	}
}

int	main(int ac, char **av)
{
	t_args	args = {0};
	t_trace	trace = {0};

	_handle_args(&args, ac, av);
	init(&trace, &args);
	ft_traceroute(&trace);
	return (0);
}
