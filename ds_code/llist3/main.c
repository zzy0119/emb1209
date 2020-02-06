#include <stdio.h>
#include <stdlib.h>

#include "llist.h"

#define NAMESIZE	32

struct stu_st {
	int id;
	char name[NAMESIZE];
	node_t node;
};

int main(void)
{
	node_t head;
	struct stu_st *p;
	node_t *cur;

	llisthead_init(&head);

	for (int i = 1; i <= 10; i++) {
		p = malloc(sizeof(struct stu_st));	
		// if error
		p->id = i; 
		snprintf(p->name, NAMESIZE, "stu%d", i);
		// llist_insert_head(&head, &p->node);
		llist_insert_tail(&head, &p->node);
	}	

	for (cur = head.next; cur != &head; cur = cur->next) {
		p = (char *)cur - (int)&((struct stu_st *)0)->node;
		printf("%d %s\n", p->id,p->name);
	}	

	return 0;
}

