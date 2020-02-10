#include <stdlib.h>
#include <string.h>

#include "stack.h"

stack_t *stack_init(int size, int maxnmemb)
{
	stack_t *s;

	s = malloc(sizeof(stack_t));
	if (NULL == s)
		return NULL;
	s->base = calloc(maxnmemb, size);
	s->top = s->base;
	s->size = size;
	s->maxnmemb = maxnmemb;

	return s;
}

// 入
int stack_push(stack_t *s, const void *data)
{
	if (stack_isfull(s))
		return -1;
	memcpy(s->top, data, s->size);
	s->top = (char *)s->top+s->size;
	return 0;
}

// 出
int stack_pop(stack_t *s, void *data)
{
	if (stack_isempty(s))
		return -1;
	s->top = (char *)s->top - s->size;	
	memcpy(data, s->top, s->size);
	return 0;
}

// 是否空栈
int stack_isempty(const stack_t *s)
{
	return s->base == s->top;
}

// 是否满
int stack_isfull(const stack_t *s)
{
	return ((char *)s->top - (char *)s->base) / s->size == s->maxnmemb;
}

// 销毁
void stack_destroy(stack_t *t)
{
	free(t->base);
	free(t);
}
