FROM debian:11

RUN apt-get -y update \
	&& apt-get -y install inetutils-traceroute \
	&& apt-get -y install tcpdump tshark make gcc libc6 iproute2

WORKDIR /workdir

CMD [ "tail", "-f", "/dev/null" ]
