#include <stdio.h>

#include "llist.h"

#define NAMESIZE	32

struct stu_st {
	int id;
	char name[NAMESIZE];
};

static void pri_stu(const void *data)
{
	const struct stu_st *d = data;
	printf("%d %s\n", d->id, d->name);
}

int main(void)
{
	llisthead_t *head;
	struct stu_st stu;

	head = llisthead_init(sizeof(struct stu_st));
	if (head == NULL)
		return 1;

	for (int i = 1; i < 10; i++) {
		stu.id = i;	
		snprintf(stu.name, NAMESIZE, "stu%d", i);
		llist_insert(head, &stu, INSERT_TAIL);
	}

	llist_traval(head, pri_stu);

	return 0;
}

