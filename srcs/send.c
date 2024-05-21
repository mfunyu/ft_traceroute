#include "ft_traceroute.h"
#include "error.h"
#include "utils_time.h"

void	trace_send(t_trace *trace)
{
	char	msg[TRACE_DATALEN] = "SUPERMAN";
	ssize_t	ret;

	ret = sendto(trace->udpfd, msg, TRACE_DATALEN, 0, (struct sockaddr *)&trace->dst_addr, sizeof(struct sockaddr));
	if (ret < 0)
		error_exit_strerr("sendto");

	trace->tv_send = get_current_time();
}