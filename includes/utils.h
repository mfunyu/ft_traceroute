#ifndef UTILS_H
# define UTILS_H

/* utils_time.c */
struct timeval	get_current_time();
struct timeval	get_timeout_time(struct timeval interval, struct timeval last);
struct timeval	sub_time(struct timeval tv1, struct timeval tv2);
double			diff_time(struct timeval tv1, struct timeval tv2);

#endif /* UTILS_H */