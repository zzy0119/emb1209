#ifndef __PROTO_H
#define __PROTO_H

#define SUN_PATH 	"./socket_txt"

#define NAMESIZE	32

typedef struct {
	int id;
	char name[NAMESIZE];
}msg_t;

#endif

