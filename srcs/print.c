#include "ft_traceroute.h"
#include "libft.h"
#include <stdio.h>
#include <unistd.h>

void	print_help()
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

void	print_header(t_trace *trace)
{
	printf("traceroute to %s (%s), %d hops max\n",
		trace->dst_hostname, trace->dst_ip, trace->num_max_hop);
}

void	print_index(int ttl, int hop)
{
	int		index;

# ifdef BONUS
	(void)hop;
	index = ttl;
# else
	(void)ttl;
	index = hop;
# endif
	ft_putchar_fd(' ', STDOUT_FILENO);
	if (index < 10)
		ft_putchar_fd(' ', STDOUT_FILENO);
	ft_putnbr_fd(index, STDOUT_FILENO);
	ft_putstr_fd("  ", STDOUT_FILENO);
}

void	print_star()
{
	ft_putstr_fd(" * ", STDOUT_FILENO);
}