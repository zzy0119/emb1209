#include <stdlib.h>

// 任务类型
typedef struct {
	job_t job;
	void *arg;
}threadpool_task_t;

threadpool_t *threadpool_init(int queue_max_size, int min_thr_num, int max_thr_num)
{
	threadpool_t *mypool = NULL;
	
	// 开辟池
	if ((mypool = malloc(sizeof(threadpool_t))) == NULL)
	{
		fprintf(stderr, "malloc() failed\n");
		return NULL;
	}

	// 初始化任务队列
	mypool->queue_max_size = queue_max_size;	
	mypool->task_queue = queue_init(sizeof(threadpool_task_t), queue_max_size);
	// 任务线程数组
	mypool->threads = calloc(max_thr_num, sizeof(pthread_t));
	if (NULL == mypool->threads) {
		queue_destroy(mypool->task_queue);
		free(mypool);	
		return NULL;
	}

	pthread_mutex_init(&mypool->lock, NULL);
	pthread_cond_init(&mypool->task_queue_not_full, NULL);
	pthread_cond_init(&mypool->task_queue_not_empty, NULL);

	mypool->min_thr_num = min_thr_num;
	mypool->max_thr_num = max_thr_num;
	mypool->busy_thr_num = 0;
	mypool->cur_live_thr_num = min_thr_num;
	mypool->wait_exit_thr_num = 0;

	mypool->shutdown = 1;

	// 启动min_thr_num线程
	for (int i = 0; i < min_thr_num; i ++) {
		err = pthread_create(mypool->threads+i, NULL, threadpool_job, (void *)pool);
		if (err) {
			fprintf(stderr, "pthread_create():%s\n", strerror(err));
			queue_destroy(mypool->task_queue);
			free(mypool->threads);
			free(mypool);	
			return NULL;	
		}
	}

	// 管理线程池
	pthread_create(&mypool->admin_tid, NULL, admin_thread, (void*)mypool);

	return mypool;
}
