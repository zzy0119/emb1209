#ifndef __PROTO_H
#define __PROTO_H

#define RCV_PORT	1144
#define RCV_IP		"192.168.1.36"
#define MSGSIZE		1024

typedef struct {
	char msg[MSGSIZE];
}msg_t;

#endif

