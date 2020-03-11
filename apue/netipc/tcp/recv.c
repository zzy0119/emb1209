#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "proto.h"

#define BUFSIZE	1024

int main(void)
{
	int sd, newsd;
	struct sockaddr_in laddr;
	msg_t rcvbuf;
	int cnt;

	sd = socket(AF_INET, SOCK_STREAM, 0);
	if (sd == -1) {
		perror("socket()");
		exit(1);
	}

	laddr.sin_family = AF_INET;
	laddr.sin_port = htons(RCV_PORT);
	inet_aton(RCV_IP, &laddr.sin_addr);
	if (bind(sd, (struct sockaddr *)&laddr, sizeof(laddr)) == -1) {
		perror("bind()");
		close(sd);
		exit(1);
	}

	if (listen(sd, 20) == -1) {
		perror("listen()");
		close(sd);
		exit(1);
	}

	while (1) {
#if 1
		newsd = accept(sd, NULL, NULL);
		if (newsd == -1) {
			perror("accept()");
			close(sd);
			exit(1);
		}
		cnt = read(newsd, &rcvbuf, MSGSIZE); // recv();
		write(1, rcvbuf.msg, cnt);
		close(newsd);
#endif
	}

	close(sd);

	exit(0);
}
