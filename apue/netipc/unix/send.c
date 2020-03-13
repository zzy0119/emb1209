#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <string.h>

#include "proto.h"

int main(void)
{
	int sd;
	msg_t msg;
	struct sockaddr_un raddr;

	sd = socket(AF_UNIX, SOCK_DGRAM, 0);
	// if error

	// bind();

	raddr.sun_family = AF_UNIX;
	strncpy(raddr.sun_path, SUN_PATH, 108);
	msg.id = 1;
	strcpy(msg.name, "embedded");
	sendto(sd, &msg, sizeof(msg.id)+strlen(msg.name)+1, 0, \
		(struct sockaddr *)&raddr, sizeof(raddr.sun_family)+strlen(raddr.sun_path)+1);

	close(sd);
	
	exit(0);
}

