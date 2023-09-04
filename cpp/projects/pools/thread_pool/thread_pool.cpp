/** 多线程池化 实践*/
// 1. 任务队列
// 2. 线程池
// 基础组件 像轮子, api

#include <process.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

/** Macro Definition */
// 双向链表的item插入 macro
#define LL_INSERT(item, list)                                                  \
  do {                                                                         \
    item->prev = NULL;                                                         \
    item->next = list;                                                         \
    if (list != NULL)                                                          \
      list->prev = item;                                                       \
  } while (0)

// 双向链表的item删除 macro
// 主要关注头节点, 尾节点单向
#define LL_REMOVE(item, list)                                                  \
  do {                                                                         \
    if (item->prev != NULL)                                                    \
      item->prev->next = item->next;                                           \
    if (item->next != NULL)                                                    \
      item->next->prev = item->prev;                                           \
    if (list == item)                                                          \
      list = item->next;                                                       \
    item->prev = item->next = NULL;                                            \
  } while (0)

/** 数据结构定义 */
// Worker 消费队列
struct NWORKER {
  pthread_t id;

  struct NMANAGER *pool;

  struct NWORKER *prev;
  struct NWORKER *next;
};

// Task 任务队列
struct NTASK {
  void *task_data;
  void (*task_func)(void *arg);

  struct NTASK *prev;
  struct NTASK *next;
};

// Manager 线程池数据结构
struct NMANAGER {
  struct NTASK *tasks;
  pthread_mutex_t mtx; // 互斥锁

  struct NWORKER *workers; // 执行队列
  pthread_cond_t cond;     // 条件锁
};

/** 函数定义 */
// static entry's callback 调用
static void *thread_callback(void *arg) {
  // 取任务
  // 执行队列
  struct NWORKER *worker = (struct NWORKER *)arg;
  while (1) {
    // 加锁
    pthread_mutex_lock(&worker->pool->mtx);
    while (worker->pool->tasks == NULL) {
      // 条件等待
      pthread_cond_wait(&worker->pool->cond, &worker->pool->mtx);
    }

    struct NTASK *task = worker->pool->tasks;
    if (task) {
      LL_REMOVE(task, worker->pool->tasks);
    }
    pthread_mutex_unlock(&worker->pool->mtx);

    // 执行函数
    task->task_func(task);
  }
}

// create thread_pool
int thread_pool_create(struct NMANAGER *pool, int nthread) {
  // 如果空池就返回
  if (pool == NULL) {
    return -1;
  }
  // 池的大小定义, default=1
  if (nthread < 1) {
    nthread = 1;
  }

  memset(pool, 0, sizeof(struct NMANAGER));

  pthread_mutex_t blank_mtx = PTHREAD_MUTEX_INITIALIZER;
  // 尽可能采用内存拷贝的方式赋值, 可以对比这个
  memcpy(&pool->mtx, &blank_mtx, sizeof(blank_mtx));

  pthread_cond_t blank_cond = PTHREAD_COND_INITIALIZER;
  memcpy(&pool->cond, &blank_cond, sizeof(blank_cond));

  int idx = 0;
  for (idx = 0; idx < nthread; idx++) {
    struct NWORKER *worker = (struct NWORKER *)malloc(sizeof(struct NWORKER));
    if (worker == NULL) {
      perror("malloc");
      exit(1);
    }

    memset(worker, 0, sizeof(struct NWORKER));
    worker->pool = pool;

    int ret = pthread_create(&worker->id, NULL, thread_callback, worker);
    if (ret) { // 创建失败
      perror("pthread_create");
      free(worker);
      exit(1);
    }

    // 键入池中
    LL_INSERT(worker, pool->workers);
  }

  return 0;
}

// push
int thread_pool_push(struct NMANAGER *pool, struct NTASK *task) {
  struct NWORKER *worker;
  pthread_mutex_lock(&worker->pool->mtx);
  LL_INSERT(task, pool->tasks);
  pthread_cond_signal(&worker->pool->cond);
  pthread_mutex_unlock(&worker->pool->mtx);
}

// destroy
