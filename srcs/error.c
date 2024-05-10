
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>

void	error_exit_usage(const char *msg)
{
	if (msg)
		fprintf(stderr, "ft_traceroute: %s\n", msg);
	fprintf(stderr, "Try './ft_traceroute --help' for more information.\n");
	exit(EXIT_FAILURE);
}

void	error_exit_strerr(const char *msg)
{
	fprintf(stderr, "ft_traceroute: %s", msg);
	if (errno)
		fprintf(stderr, " - %s", strerror(errno));
	fprintf(stderr, "\n");
	exit(EXIT_FAILURE);
}

void	error_exit_parse(const char *msg, const char *parameter)
{
	fprintf(stderr, "ft_traceroute: %s `%s'\n", msg, parameter);
	exit(EXIT_FAILURE);
}

void	error_exit(const char *msg)
{
	fprintf(stderr, "ft_traceroute: %s\n", msg);
	exit(EXIT_FAILURE);
}

void	error_exit_gai(const char *msg, int ret)
{
	fprintf(stderr, "ft_traceroute: %s - %s\n", msg, gai_strerror(ret));
	exit(EXIT_FAILURE);
}
