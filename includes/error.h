#ifndef ERROR_H
# define ERROR_H

void	error_exit_usage(const char *msg);
void	error_exit_strerr(const char *msg);
void	error_exit_parse(const char *msg, const char *parameter);
void	error_exit(const char *msg);
void	error_exit_gai(const char *msg, int ret);

#endif /* ERROR_H */