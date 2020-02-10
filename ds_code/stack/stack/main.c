#include <stdio.h>

#include "stack.h"

int main(void)
{
	stack_t *stack;
	int pop;

	stack = stack_init(sizeof(int), 10);

	for (int i = 0; i < 20; i++) {
		stack_push(stack, &i);	
	}

	while (stack_pop(stack, &pop) == 0) {
		printf("%d\n", pop);	
	}

	stack_destroy(stack);

	return 0;
}
