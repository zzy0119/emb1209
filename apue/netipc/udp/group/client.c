#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <errno.h>
#include <net/if.h>

#include "proto.h"

int main(int argc, char *argv[])
{
	int sd;
	struct sockaddr_in  laddr;
	struct ip_mreqn mrq;
	char buf[MSGSIZE] = {};
	int len;

	sd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sd == -1) {
		perror("socket()");
		exit(1);
	}

	laddr.sin_family = AF_INET;
	laddr.sin_port = htons(RCVPORT);
	laddr.sin_addr.s_addr = INADDR_ANY;
	if (bind(sd, (struct sockaddr *)&laddr, sizeof(laddr)) == -1) {
		perror("bind()");
		close(sd);
		exit(1);
	}

	// 加入组
	inet_aton(MULTI_ADDR, &mrq.imr_multiaddr);
	inet_aton("0.0.0.0", &mrq.imr_address);
	mrq.imr_ifindex = if_nametoindex("ens33");
	if (setsockopt(sd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mrq, sizeof(mrq)) == -1) {
		perror("setsockopt()");
		close(sd);
		exit(1);
	}

	while (1) {
		len = recvfrom(sd, buf, MSGSIZE, 0, NULL, NULL);
		if (len == -1) {
			if (errno == EINTR)
				continue;
			perror("recvfrom()");
			close(sd);
			exit(1);
		}
		write(1, buf, len);
	}

	close(sd);

	exit(0);
}


