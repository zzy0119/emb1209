#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#include "proto.h"

int main(void)
{
	int sd;
	struct sockaddr_un laddr;
	msg_t msg;
	int cnt;

	sd = socket(AF_UNIX, SOCK_DGRAM, 0);
	if (sd < 0) {
		perror("socket()");
		exit(1);
	}

	laddr.sun_family = AF_UNIX;
	strncpy(laddr.sun_path, SUN_PATH, 108);
	if (bind(sd, (struct sockaddr *)&laddr, sizeof(laddr.sun_family)+strlen(laddr.sun_path)+1) == -1) {
		perror("bind()");
		goto ERROR;
	}
	  
	cnt = recvfrom(sd, &msg, sizeof(msg), 0, NULL, NULL);
	if (cnt < 0) {
		perror("recvfrom()");
		goto ERROR;
	}
	// printf("cnt:%d\n", cnt);
	printf("%d %s\n", msg.id, msg.name);

	close(sd);

	exit(0);
ERROR:
	close(sd);
	exit(1);
}

