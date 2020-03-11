#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

#include "proto.h"

int main(int argc, char *argv[])
{
	int sd;
	struct sockaddr_in raddr;
	msg_t buf;

	if (argc < 2)
		exit(0);

	sd = socket(AF_INET, SOCK_STREAM, 0);
	if (sd < 0) {
		perror("socket()");
		exit(1);
	}

	// bind();

	raddr.sin_family = AF_INET;
	raddr.sin_port = htons(RCV_PORT);
	inet_aton(RCV_IP, &raddr.sin_addr);
	if (connect(sd, (const struct sockaddr *)&raddr, sizeof(raddr)) == -1) {
		perror("connect()");
		close(sd);
		exit(1);
	}


	strncpy(buf.msg, argv[1], MSGSIZE);
	send(sd, &buf, strlen(argv[1])+1, 0); // write();

	exit(0);
}

