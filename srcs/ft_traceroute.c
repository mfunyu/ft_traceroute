#include "parser.h"

int	main(int ac, char **av)
{
	t_args	args = {0};

	parse_args(&args, ac, av);
	return (0);
}
