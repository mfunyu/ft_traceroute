#include "parser.h"
#include <stdlib.h>
#include <stdio.h>

void	help(void)
{
	printf("Usage:\n  ./ft_traceroute host\n");
	printf("Options:");
	printf("\n\
  --help                      Read this help and exit\n\n");
	printf("Arguments:\n\
+     host          The host to traceroute to\n");
	exit(EXIT_SUCCESS);
}

void	error_exit(const char *msg)
{
	fprintf(stderr, "%s\n", msg);
	exit(EXIT_FAILURE);
}

static void	_handle_args(t_args *args, int ac, char **av)
{
	if (ac <= 1)
	{
		help();
	}
	parse_args(args, ac, av);
	if (args->flags[HELP])
	{
		help();
	}
	if (!args->params[0])
		error_exit("Specify \"host\" missing argument.");
}

int	main(int ac, char **av)
{
	t_args	args = {0};

	_handle_args(&args, ac, av);
	return (0);
}
