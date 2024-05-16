#include "parser.h"
#include "error.h"
#include "ft_traceroute.h"
#include <stdlib.h>
#include <stdio.h>

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

int	ft_traceroute(t_args *args)
{
	(void)args;
	return (0);
}

int	main(int ac, char **av)
{
	t_args			args = {0};
	t_traceroute	traceroute = {0};

	_handle_args(&args, ac, av);
	init(&traceroute, &args);
	ft_traceroute(&args);
	return (0);
}
