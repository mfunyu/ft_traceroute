#ifndef UTILS_TIME_H
# define UTILS_TIME_H

struct timeval	get_current_time();
struct timeval	sub_time(struct timeval tv1, struct timeval tv2);
double			diff_time(struct timeval tv1, struct timeval tv2);

#endif /* UTILS_TIME_H */