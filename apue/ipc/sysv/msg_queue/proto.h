#ifndef __PROTO_H
#define __PROTO_H

#define MSGSIZE	1024

#define PATHNAME	"/etc/passwd"
#define PRO_ID		'a'

struct msg_st {
	long mtype;
	char msg[MSGSIZE];
};

#endif

