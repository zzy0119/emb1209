#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>
#include <string.h>

#include "proto.h"

int main(int argc, char *argv[])
{
	int msgid;
	key_t key;
	int created = 1;
	struct msg_st msg;

	if (argc < 3)
		exit(1);

	key = ftok(PATHNAME, PRO_ID);
	if (-1 == key) {
		perror("ftok()");
		exit(1);
	}

	msgid = msgget(key, IPC_CREAT | IPC_EXCL | 0600);
	if (-1 == msgid) {
		if (errno == EEXIST) {
			msgid = msgget(key, 0);
			created = 0;
		} else {
			perror("msgget()");
			exit(1);
		}
	}

	// 发消息
	msg.mtype = atoi(argv[1]);
	strncpy(msg.msg, argv[2], MSGSIZE);
	msgsnd(msgid, &msg, strlen(argv[2])+1, 0);
	
	if (created) {
		msgctl(msgid, IPC_RMID, NULL);
	}

	exit(0);
}
