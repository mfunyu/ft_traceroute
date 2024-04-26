#include "parser.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

void	parse_args(t_args *args, int ac, char **av)
{
	int		idx;

	idx = 0;
	args->params = av;
	for (int i = 1; i < ac; i++)
	{
		if (av[i][0] == '-' && av[i][1])
		{
			if (ft_strncmp(av[i], "--help", 7) == 0)
			{
				args->flags[HELP] = true;
				break ;
			}
			else
			{
				fprintf(stderr, "Bad option `%s' (arg %d)\n", av[i], i);
				exit(EXIT_FAILURE);
			}
		}
		else
			args->params[idx++] = av[i];
	}
	args->params[idx] = NULL;
}
