#include <stdio.h>

#include "../stack/stack/stack.h"
#include "../queue/queue/queue.h"

static int ball_is_seq(queue_t *q);
int main(void)
{
	stack_t *one_min, *five_min, *one_hour;
	queue_t *ball;
	int pop_ball;
	int tmp_ball;
	int days = 0;

	one_min = stack_init(sizeof(int), 4);
	five_min = stack_init(sizeof(int), 11);
	one_hour = stack_init(sizeof(int), 11);

	ball = queue_init(sizeof(int), 27);
	
	for (int i = 1; i <= 27; i ++) {
		queue_enq(ball, &i);	
	}

	while (1) {
		queue_deq(ball, &pop_ball);
		if (!stack_isfull(one_min))	{
			stack_push(one_min, &pop_ball);
		} else {
			// 1分钟栈满
			while (!stack_isempty(one_min)) {
				stack_pop(one_min, &tmp_ball);
				queue_enq(ball, &tmp_ball);
			}
			if (!stack_isfull(five_min)) {
				stack_push(five_min, &pop_ball);
			} else {
				while (!stack_isempty(five_min)) {
					stack_pop(five_min, &tmp_ball);
					queue_enq(ball, &tmp_ball);
				}
				if (!stack_isfull(one_hour)) {
					stack_push(one_hour, &pop_ball);
				} else {
					while (!stack_isempty(one_hour)) {
						stack_pop(one_hour, &tmp_ball);
						queue_enq(ball, &tmp_ball);
					}
					queue_enq(ball, &pop_ball);
					// 12h 所有的球都在队列
					days ++;		
					if (ball_is_seq(ball)) {
						break;
					}
				}
			}
		}
	}

	printf("%d\n", days / 2);

	stack_destroy(one_min);
	stack_destroy(five_min);
	stack_destroy(one_hour);
	queue_destroy(ball);

	return 0;
}

static int ball_is_seq(queue_t *q)
{
	int tmp[27] = {};
	int prev, cur;
	int i = 0;
	int res = 1;

	prev = 0;
	while (!queue_isempty(q)) {
		queue_deq(q, &cur);
		tmp[i++] = cur;
		if (res == 1 && cur < prev) {
			res = 0;
		}
		prev = cur;
	}
	for (int h = 0; h < i; h++) {
		queue_enq(q, tmp+h);	
	}

	return res;
}

