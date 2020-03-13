#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/udp.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <errno.h>
#include <unistd.h>
#include <net/if.h>

#include "proto.h"

int main(void)
{
	int sd;
	struct sockaddr_in laddr, raddr;
	socklen_t raddrlen;
	int cnt;
	struct ip_mreqn mrq;

	// man 7 socket  man 2 socket man 7 udp
	sd = socket(AF_INET, SOCK_DGRAM, 0);
	if (-1 == sd) {
		perror("socket()");
		exit(1);
	}

	// man 7 ip   man 2 bind   
	laddr.sin_family = AF_INET;
	laddr.sin_port = htons(SERVER_PORT); // man 3 htons
	laddr.sin_addr.s_addr = htonl(INADDR_ANY); // man 3 inet_aton
	if (bind(sd, (const struct sockaddr *)&laddr, sizeof(laddr)) == -1) {
		perror("bind()");
		close(sd);
		exit(1);
	}

	// 设置组地址
	inet_aton(MULTI_ADDR, &mrq.imr_multiaddr);
	inet_aton("0.0.0.0", &mrq.imr_address);
	mrq.imr_ifindex = if_nametoindex("ens33");
	if (setsockopt(sd, IPPROTO_IP, IP_MULTICAST_IF, &mrq, sizeof(mrq)) == -1) {
		perror("setsockopt()");
		close(sd);
		exit(1);
	}

	// 初始化接收端地址
	raddr.sin_family = AF_INET;
	inet_aton(MULTI_ADDR, &raddr.sin_addr);
	raddr.sin_port = htons(RCVPORT);

	while (1) {
		sendto(sd, "hello", 5, 0, (void *)&raddr, sizeof(raddr));
		sleep(1);
	}

	close(sd);

	exit(0);
}
