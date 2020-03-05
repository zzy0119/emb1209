#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/select.h>

#define BUFSIZE	1024
#define TTY1	"/dev/tty9"
#define TTY2	"/dev/tty10"

/*
	ADT
 */
enum {
	STATE_R,
	STATE_W,
	STATE_E,
	STATE_T
};

typedef struct fsm {
	int rfd;
	int wfd;
	char buf[BUFSIZE];
	char *errmsg;
	int rcnt;
	int stat;
	int pos;
}fsm_t;

static int fsm_drive(fsm_t *fsm)
{
	int ret;

	switch (fsm->stat) {
		case STATE_R:
			fsm->rcnt = read(fsm->rfd, fsm->buf, BUFSIZE);
			if (fsm->rcnt == 0) {
				fsm->stat = STATE_T;
			} else if (fsm->rcnt < 0) {
				if (errno != EAGAIN) {
					fsm->errmsg = "read()";
					fsm->stat = STATE_E;
				}
			} else {
				fsm->pos = 0;
				fsm->stat = STATE_W;
			}
			break;
		case STATE_W:
			ret = write(fsm->wfd, fsm->buf+fsm->pos, fsm->rcnt);
			if (ret < 0) {
				if (errno != EAGAIN) {
					fsm->errmsg = "write()";
					fsm->stat = STATE_E;
				}
			} else {
				if (ret < fsm->rcnt) {
					fsm->pos += ret;	
					fsm->rcnt -= ret;
				} else {
					fsm->stat = STATE_R;
				}
			}
			break;
		case STATE_E:
			perror(fsm->errmsg);
			fsm->stat = STATE_R;
			break;
		case STATE_T:
			printf("bye-bye");
			break;
		default:
			abort();
			break;
	}
	return 0;
}

static int fsm_create(int fd1, int fd2)
{
	fsm_t fsm12, fsm21;
	int fd1_state, fd2_state;
	fd_set rset, wset;
	
	// 非阻塞
	fd1_state = fcntl(fd1, F_GETFL);
	fcntl(fd1, F_SETFL, fd1_state | O_NONBLOCK);

	fd2_state = fcntl(fd2, F_GETFL);
	fcntl(fd2, F_SETFL, fd2_state | O_NONBLOCK);

	fsm12.rfd = fd1;
	fsm12.wfd = fd2;
	fsm12.stat = STATE_R;
	memset(fsm12.buf, '\0', BUFSIZE);
	fsm12.pos = 0;
	fsm12.rcnt = 0;
	fsm12.errmsg = NULL;

	fsm21.rfd = fd2;
	fsm21.wfd = fd1;
	fsm21.stat = STATE_R;
	memset(fsm21.buf, '\0', BUFSIZE);
	fsm21.pos = 0;
	fsm21.rcnt = 0;
	fsm21.errmsg = NULL;

	while(fsm12.stat != STATE_T || fsm21.stat != STATE_T) {
		if (fsm12.stat == STATE_E) {
			fsm_drive(&fsm12);
			continue;
		}
		if (fsm21.stat == STATE_E) {
			fsm_drive(&fsm21);
			continue;
		}

		FD_ZERO(&rset);
		FD_ZERO(&wset);
		
		if (fsm12.stat == STATE_R)
			FD_SET(fd1, &rset);
		else if (fsm12.stat == STATE_W)
			FD_SET(fd2, &wset);
		if (fsm21.stat == STATE_R)
			FD_SET(fd2, &rset);
		else if (fsm21.stat == STATE_W)
			FD_SET(fd1, &wset);

		while (select((fd1 > fd2 ? fd1:fd2) + 1, &rset, &wset, NULL, NULL) == -1) {
			if (errno == EINTR) {
				continue;
			}
			perror("select()");
			exit(1);
		}

		if ((FD_ISSET(fd1, &rset) || FD_ISSET(fd2, &wset)) && fsm12.stat != STATE_T) {
			printf("fd1 ready to read\n");
			printf("fd2 ready to write\n");
			fsm_drive(&fsm12);	
		}
		if ((FD_ISSET(fd2, &rset) || FD_ISSET(fd1, &wset)) && fsm21.stat != STATE_T) {
			printf("fd2 ready to read\n");
			printf("fd1 ready to write\n");
			fsm_drive(&fsm21);	
		}
	}

	fcntl(fd1, F_SETFL, fd1_state);
	fcntl(fd2, F_SETFL, fd2_state);
}

int main(void)
{
	int fd1, fd2;

	fd1 = open(TTY1, O_RDWR | O_NONBLOCK);
	if (fd1 < 0) {
		perror("open()");
		exit(1);
	}
	write(fd1, "[tty1]", 6);

	fd2 = open(TTY2, O_RDWR);
	if (fd2 < 0) {
		close(fd1);
		perror("open()");
		exit(1);
	}
	write(fd2, "[tty2]", 6);

	fsm_create(fd1, fd2);

	exit(0);
}

