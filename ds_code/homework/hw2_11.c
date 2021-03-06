#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <stack.h>
#include <queue.h>

char *midToAft(const char *mid);
int cal_aft(const char *aft);
int main(int argc, char *argv[])
{
	if (argc < 2)
		return 1;
	// argv[1]
	char *aft = midToAft(argv[1]);
	if (aft == NULL) {
		printf("不符合正确的十以内四则运算\n");
		return 1;
	} else {
		puts(aft);
	}

	printf("%d\n", cal_aft(aft));

	return 0;
}

static int is_operator(char ch)
{
	return ch == '+' || ch == '-' || ch == '*' || ch == '/';
}

static int is_digital(char ch)
{
	return ch >= '0' && ch <= '9';
}

static int accociaty(char ch)
{
	int level = 0;
	if (ch == '+' || ch == '-')
		level = 1;
	else if (ch == '*' || ch == '/')
		level = 2;

	return level;
}

// 中缀表达式---->后缀表达式
char *midToAft(const char *mid)
{
	stack_t *s;
	queue_t *q;
	char top;
	char *res;
	int i;
	int len;

	len = strlen(mid);

	res = calloc(1, len+1);
	if (NULL == res)
		return NULL;
		
	s = stack_init(sizeof(char), len);
	q = queue_init(sizeof(char), len);

	while (*mid) {
		if (is_operator(*mid)) {
			if (stack_isempty(s))
				stack_push(s, mid);
			else {
				// 获取栈顶 比较优先级
				while (!stack_pop(s, &top)) {
					if (accociaty(*mid) <= accociaty(top)) {
						queue_enq(q, &top);
					} else {
						stack_push(s, &top);	
						break;
					}
				}
				stack_push(s, mid);
			}
		} else if (is_digital(*mid)) {
			queue_enq(q, mid);
		} else if (*mid == '(') {
			stack_push(s, mid);	
		} else if (*mid == ')') {
			while (1) {
				if (stack_pop(s, &top) != 0) {
					goto ERROR;
				}
				if (top == '(')
					break;
				queue_enq(q, &top);
			}	
		} else {
			goto ERROR;
		}
		mid ++;
	}

	while (!stack_isempty(s)) {
		stack_pop(s, &top);
		queue_enq(q, &top);
	}
	i = 0;
	while (!queue_isempty(q)) {
		queue_deq(q, &top);
		res[i++] = top;
	}
	res = realloc(res, i+1);
	
	stack_destroy(s);
	queue_destroy(q);
	return res;
ERROR:
	stack_destroy(s);
	queue_destroy(q);
	free(res);
	return NULL;
}

int cal2num(int left, int right, char ch)
{
	int res;

	switch (ch) {
		case '+':
			res = left + right;
			break;
		case '-':
			res = left - right;
			break;
		case '*':
			res = left * right;
			break;
		case '/':
			res = left / right;
			break;
		default:
			break;
	}
	return res;
}

// 后缀表达式--->计算结果
int cal_aft(const char *aft)
{
	int len;
	stack_t *s;
	int res;
	int l, r;
	int push;

	len = strlen(aft);
	s = stack_init(sizeof(int), len);
	
	while (*aft) {
		if (is_digital(*aft)) {
			push = *aft-'0';
			stack_push(s, &push);
		} else if (is_operator(*aft)) {
			stack_pop(s, &r);
			stack_pop(s, &l);
			res = cal2num(l, r, *aft);		
			stack_push(s, &res);
		} else 
			goto ERROR;
		aft ++;
	}
	stack_pop(s, &res);
	if (!stack_isempty(s))
		goto ERROR;

	stack_destroy(s);
	return res;
ERROR:
	stack_destroy(s);
	printf("ERROR\n");
	return -1; 
}




