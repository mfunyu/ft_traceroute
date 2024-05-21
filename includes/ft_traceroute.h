#ifndef FT_TRACEROUTE_H
# define FT_TRACEROUTE_H

# include <sys/socket.h>
# include <arpa/inet.h>
# include <netinet/udp.h>
# include <netinet/ip_icmp.h>
# include <sys/time.h>
# include <stdbool.h>

# define MAX_IPLEN	60
# define MAX_ICMPLEN	76
# define MAX_DATALEN	65535 - MAX_IPLEN - MAX_ICMPLEN

# define TRACE_DATALEN	9

# define NUM_FIRST_HOP	1
# define NUM_MAX_HOP	64
# define NUM_PORT		33434
# define NUM_TRIES		3
# define NUM_WAIT		3

/*
** struct udphdr {
**     u_int16_t source;  // port source
**     u_int16_t dest;    // port de destination
**     u_int16_t len;     // longueur du datagramme
**     u_int16_t check;   // somme de contrôle
** };
*/

typedef struct	s_trace {
	int					udpfd;
	int					icmpfd;
	char				*dst_hostname;
	struct sockaddr_in	dst_addr;
	char				dst_ip[INET_ADDRSTRLEN];
	int					ttl;
	struct timeval 		timeout;
	int					port;

	struct timeval	tv_send;
	double			triptime;
	struct in_addr	src_ip;
	int				type;
	int				code;
	bool			is_terminated;

	int		num_first_hop;
	int		num_max_hop;
	int		num_port;
	int		num_tries;
	int		num_wait;
}				t_trace;

typedef struct	s_packet
{
	struct iphdr	iphdr;
	struct icmphdr	icmphdr;
	union
	{
		char			data[MAX_DATALEN];
		struct
		{
			struct iphdr	iphdr;
			struct udphdr	udphdr;
		} error;
	} un;
# define req_iphdr	un.error.iphdr
# define req_udphdr	un.error.udphdr
# define icmpdata	un.data
}				t_packet;

typedef struct s_args	t_args;

void	init(t_trace *trace, t_args *args);

void	print_help();
void	print_header(t_trace *trace);

void	trace_send(t_trace *trace);
int		trace_recv(t_trace *trace);

#endif /* FT_TRACEROUTE_H */