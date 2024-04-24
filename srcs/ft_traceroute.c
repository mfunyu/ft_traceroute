#include "parser.h"
#include <stdlib.h>
#include <stdio.h>

void	print_help(void)
{
	printf("Usage:\n  ./ft_traceroute [OPTION...] host ...\n");
	printf("Options:");
	printf("\n\
  --help                      Read this help and exit\n\n");
	printf("Arguments:\n\
+     host          The host to traceroute to\n");
}

static void	_handle_args(t_args *args, int ac, char **av)
{
	if (ac <= 1)
	{
		print_help();
		exit(EXIT_SUCCESS);
	}
	parse_args(args, ac, av);
	if (args->flags[HELP])
	{
		print_help();
		exit(EXIT_SUCCESS);
	}
	if (!args->params[0])
		error_exit_usage("Specify \"host\" missing argument.");
}

int	main(int ac, char **av)
{
	t_args	args = {0};

	_handle_args(&args, ac, av);
	return (0);
}
