#ifndef NETWORK_H
# define NETWORK_H

void	resolve_ip_str_by_sockaddr_in(char *ip, struct sockaddr_in const *addr_in);
void	resolve_sockaddr_in_by_hostname(struct sockaddr_in *addr, char const *hostname);
void	resolve_ip_str_by_in_addr(char *ip, in_addr_t saddr);

int		socket_udp();
int		socket_icmp();
void	socket_set_ttl(int udpfd, int ttl);

#endif /* NETWORK_H */