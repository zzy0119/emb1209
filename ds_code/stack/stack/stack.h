#ifndef __STACK_H
#define __STACK_H

// ADT
typedef struct {
	void *base;// 栈底地址	
	void *top;// 栈顶地址
	int size; // 每个数据字节个数
	int maxnmemb; // 栈的容量
}stack_t;

// 接口
stack_t *stack_init(int size, int maxnmemb);

// 入
int stack_push(stack_t *s, const void *data);

// 出
int stack_pop(stack_t *s, void *data);

// 是否空栈
int stack_isempty(const stack_t *s);

// 是否满
int stack_isfull(const stack_t *s);

// 销毁
void stack_destroy(stack_t *t);

#endif

