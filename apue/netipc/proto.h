#ifndef __PROTO_H

#define RCV_IP		"192.168.1.36"
#define RCVPORT		1234

#define NAMESIZE	32

typedef struct {
	int8_t id;
	char name[NAMESIZE];
}msg_t;

#endif
