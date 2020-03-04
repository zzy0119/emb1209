#ifndef __POOL_H
#define __POOL_H

#include "queue.h"

// 任务类型
typedef struct {
	void *(*job)(void *arg);
	void *arg;
}theadpool_task_t;

enum {
	THR_BUSY,
	THR_FREE
};

typedef struct {
	// 任务队列	
	queue_t *task_queue;  
	pthread_t *threads; // 处理任务线程
	pthread_t admin_tid;// 管理线程池　线程
	pthread_mutex_t lock; // 队列锁
	pthread_cond_t task_queue_not_full; // 任务队列没满
	pthread_cond_t task_queue_not_empty; // 任务队列不空

	// 线程池属性
	int max_thr_num; // 最大容纳的线程个数
	int min_thr_num; // 最少线程数
	int cur_live_thr_num; // 池中现有线程
	int busy_thr_num; // 正在处理任务中的线程

	int queue_max_size;// 任务队列能容纳任务个数
	
	// 线程池状态
	int shutdown; // 1关闭　0
}threadpool_t;

#endif

