#include <stdio.h>

#include "list.h"

static void pri_num(const void *data)
{
	const int *d = data;	
	printf("%d\n", *d);
}

static int cmp_num(const void *data, const void *key)
{
	const int *d = data;
	const int *k = key;

	return *d - *k;
}

int main(void)
{
	int arr[] = {3,2,1,6,7,9,8};
	head_t *head = NULL;

	if (listhead_init(sizeof(int), &head) != 0)
		return 1;
	
	for (int i = 0; i < sizeof(arr)/sizeof(*arr); i++) {
		list_insert(head, arr+i, TAIL_INSERT);
	}
	list_traval(head, pri_num);

	printf("******************************\n");
	int delnum = 3;
	list_delete(head, &delnum, cmp_num);
	list_traval(head, pri_num);

	printf("******************************\n");
	delnum = 8;
	list_delete(head, &delnum, cmp_num);
	list_traval(head, pri_num);

	printf("******************************\n");
	delnum = 6;
	list_delete(head, &delnum, cmp_num);

	list_traval(head, pri_num);

	return 0;
}


