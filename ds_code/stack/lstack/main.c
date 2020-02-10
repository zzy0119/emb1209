
#include <stdio.h>

#include "lstack.h"

int main(void)
{
	int arr[] = {6,1,2,8,9,3,7,4,5};
	lstack_t *s;
	int pop;
	
	s = lstack_init(sizeof(int));
	// if error

	for (int i = 0; i < sizeof(arr) / sizeof(*arr); i++) {
		lstack_push(s, arr+i);	
	}

	while (!lstack_isempty(s)) {
		lstack_pop(s, &pop);
		printf("%d\n", pop);
	}

	lstack_destroy(s);

	return 0;
}

