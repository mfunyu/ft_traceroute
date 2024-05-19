#ifndef FT_TRACEROUTE_H
# define FT_TRACEROUTE_H

# include <sys/socket.h>
# include <arpa/inet.h>

# define NUM_FIRST_HOP	1
# define NUM_MAX_HOP	64
# define NUM_PORT		33434
# define NUM_TRIES		3
# define NUM_WAIT		3

typedef struct	s_trace {
	int				udpfd;
	char			*dst_hostname;
	struct sockaddr	dst_addr;
	char			dst_ip[INET_ADDRSTRLEN];
	int				ttl;

	int		num_first_hop;
	int		num_max_hop;
	int		num_port;
	int		num_tries;
	int		num_wait;
}				t_trace;

typedef struct s_args	t_args;

void	init(t_trace *trace, t_args *args);

void	print_header(t_trace *trace);

#endif /* FT_TRACEROUTE_H */