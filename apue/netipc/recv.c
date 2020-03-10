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

#include "proto.h"

int main(void)
{
	int sd;
	struct sockaddr_in laddr, raddr;
	msg_t rcvbuf;
	socklen_t raddrlen;
	int cnt;

	// man 7 socket  man 2 socket man 7 udp
	sd = socket(AF_INET, SOCK_DGRAM, 0);
	if (-1 == sd) {
		perror("socket()");
		exit(1);
	}

	// man 7 ip   man 2 bind   
	laddr.sin_family = AF_INET;
	laddr.sin_port = htons(RCVPORT); // man 3 htons
	inet_aton(RCV_IP, &laddr.sin_addr); // man 3 inet_aton
	if (bind(sd, (const struct sockaddr *)&laddr, sizeof(laddr)) == -1) {
		perror("bind()");
		close(sd);
		exit(1);
	}

	raddrlen = sizeof(raddr);
	while (1) {
		cnt = recvfrom(sd, &rcvbuf, sizeof(rcvbuf), 0, (void *)&raddr, &raddrlen);
		if (cnt == -1) {
			if (errno == EINTR)
				continue;
			perror("recvfrom()");
			close(sd);
			exit(1);
		}
		printf("[ip:%s, port:%d]\n", inet_ntoa(raddr.sin_addr), ntohs(raddr.sin_port));
		printf("%d %s\n", rcvbuf.id, rcvbuf.name);
	}

	close(sd);

	exit(0);
}
