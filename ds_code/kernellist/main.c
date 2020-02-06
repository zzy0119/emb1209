#include <stdio.h>
#include <stdlib.h>

#include "kernellist.h"

struct data_st {
	int num;
	struct list_head node;
};

int main(void)
{
	struct data_st *data;
	struct list_head *pos;

	LIST_HEAD(head);

	for (int i = 1; i < 10; i++) {
		data = malloc(sizeof(struct data_st));	
		// if error
		data->num = i;
		list_add_tail(&data->node, &head);
	}

	list_for_each(pos, &head) {
		data = list_entry(pos, struct data_st, node);
		printf("%d\n", data->num);
	}

	return 0;
}
