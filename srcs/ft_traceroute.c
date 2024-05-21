#include "ft_traceroute.h"
#include "parser.h"
#include "error.h"
#include "network.h"
#include <stdlib.h>
#include <stdio.h>
#include <sys/select.h>
#include <sys/time.h>

static const char	_unreach_sign[NR_ICMP_UNREACH + 2] = "NHPPFS**U**TTXXX";

static int	_select_loop(t_trace *trace)
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

static void	_run_try(t_trace *trace)
{
	int			ready;
	in_addr_t	prev_addr = 0;

	for (int i = 0; i < trace->num_tries; i++)
	{
		trace_send(trace);
		ready = -1;
		while (ready < 0) {
			ready = _select_loop(trace);
		}
		if (ready == 0) {
			printf(" * ");
			fflush(stdout);
		} else {
			if (i == 0 || prev_addr != trace->src_ip.s_addr) {
				printf(" %s ", inet_ntoa(trace->src_ip));
				prev_addr = trace->src_ip.s_addr;
			}
			printf(" %.3fms ", trace->triptime);
			if (trace->type == ICMP_DEST_UNREACH
				&& trace->code != ICMP_PORT_UNREACH) {
				printf("!%c ", _unreach_sign[trace->code & 0x0f]);
			}
		}
	}
	printf("\n");
}

static void	_ft_traceroute(t_trace *trace)
{
	print_header(trace);
	for (int hop = 1; trace->ttl <= trace->num_max_hop; hop++)
	{
		trace->dst_addr.sin_port = htons(trace->port);
		printf(" %2d  ", hop);
		socket_set_ttl(trace->udpfd, trace->ttl);
		_run_try(trace);
		if (trace->is_terminated)
			break;
		trace->ttl++;
		trace->port++;
	}
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

int	main(int ac, char **av)
{
	t_args	args = {0};
	t_trace	trace = {0};

	_handle_args(&args, ac, av);
	init(&trace, &args);
	_ft_traceroute(&trace);
	return (0);
}
