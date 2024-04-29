# ft_traceroute
Recoding the traceroute command to deepen the knowledge of the network (TCP/IP) by following the paths that an IP packet will take between two machines.

#### $> man traceroute
> traceroute  tracks  the  route  packets taken from an IP network on their way to a given
       host. It utilizes the IP protocol's time to live (TTL) field and attempts to  elicit  an
       ICMP TIME_EXCEEDED response from each gateway along the path to the host.


## Basic implementation

- Sending UDP in loop while increasing TTL
- Send `max_hops` packets for each TTL size
- If a packet is not acknowledged within the expected interval, `*` is displayed

- The destination port number will be incremented by each probe


## Feachers

- parameters
  - takes IPv4 (address/hostname) as a program parameter
- options
  - `--help`
- hostname resolution
  - manage the FQDN without running the DNS resolution in the jump display

### bonus

  | option | details |
  | :- | :- |
  | --help | Print help info and exit. |
  | -q, --queries | Sets the number of probe packets per hop. (default: 3) |
  | -m, --max-hops | Specifies the maximum number of hops (max time-to-live value) traceroute will probe. (default: 30) |
  | -p, --port | Specifies the destination port base traceroute will use (default: 33434) |
  | -f, --first | Start from the first_ttl hop (instead from 1) | Start from the first_ttl hop (instead from 1) |