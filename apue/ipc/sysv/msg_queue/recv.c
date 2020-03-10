#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>

#include "proto.h"

int main(void)
{
	int mgid;
	key_t key;
	struct msg_st buf;
	int created = 1;

	key = ftok(PATHNAME, PRO_ID);
	if (-1 == key) {
		perror("ftok()");
		exit(1);
	}
	mgid = msgget(key, IPC_CREAT | IPC_EXCL | 0666);
	if (mgid == -1) {
		if (errno != EEXIST) {
			perror("msgget()");
			exit(1);
		} else {
			// 已存在　获取
			mgid = msgget(key, 0);
			created = 0;
		}
	}

	// 数据交换

	if (msgrcv(mgid, &buf, MSGSIZE, 5, 0) == -1) {
		perror("msgrcv()");
		goto ERROR;
	}

	printf("%ld %s\n", buf.mtype, buf.msg);

	if (created) {
		msgctl(mgid, IPC_RMID, NULL);
	}

	exit(0);
ERROR:
	if (created) {
		msgctl(mgid, IPC_RMID, NULL);
	}
	exit(1);
}

