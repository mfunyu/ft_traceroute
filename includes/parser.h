#ifndef PARSER_H
# define PARSER_H

# include <stdbool.h>

typedef enum e_flags
{
	NONE = 0,
	HELP,
	TOTAL
}			t_flags;

typedef struct s_args
{
	int		flags[TOTAL];
	char	**params;
}			t_args;

void	parse_args(t_args *args, int ac, char **av);

#endif /* PARSER_H */
