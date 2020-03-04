#ifndef __POOL_H
#define __POOL_H

#include "queue.h"
#include <pthread.h>

#define MIN_FREE_THR		5
#define DEFAULT_ADD_THR_NUM	3
#define DEFAULT_DESTROY_NUM	3

typedef void *(*job_t)(void *arg);

typedef struct {
	// 任务队列	
	queue_t *task_queue;  
	pthread_t *threads; // 处理任务线程
	pthread_t admin_tid;// 管理线程池　线程
	pthread_mutex_t lock; // 队列锁
	pthread_mutex_t busy_lock;
	pthread_cond_t task_queue_not_full; // 任务队列没满
	pthread_cond_t task_queue_not_empty; // 任务队列不空

	// 线程池属性
	int max_thr_num; // 最大容纳的线程个数
	int min_thr_num; // 最少线程数
	int cur_live_thr_num; // 池中现有线程
	int busy_thr_num; // 正在处理任务中的线程
	int wait_exit_thr_num; // 等待终止的线程个数

	int queue_size; // 队列中当前任务个数
	int queue_max_size;// 任务队列能容纳任务个数
	
	// 线程池状态
	int shutdown; // 1关闭　0
}threadpool_t;

// 接口
/*
   创建线程池
 */
threadpool_t *threadpool_init(int queue_max_size, int min_thr_num, int max_thr_num);

/*
 添加任务
 */
int threadpool_add_task(threadpool_t *pool, job_t job, void *arg);

/*
   销毁
 */
void threadpool_destroy(threadpool_t *pool);

#endif

