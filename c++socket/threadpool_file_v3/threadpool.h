#ifndef THREADPOOL
#define THREADPOOL

#include<pthread.h>
#include<string>
#include<queue>
#include<iostream>
#include<fstream>
using namespace std;


class ThreadPool{
    public:
        static pthread_t producer;          // 生产者线程
        static pthread_t *consumer;         // 用于创建消费者线程个数
        static pthread_mutex_t lock;        // 互斥锁，线程互斥
        static int thread_count;            // 线程数目
        static bool shutdown;                // 是否关闭，默认 false 不关闭
        static int line_of_count;           // 文件行数
        static queue<string> MessageQueue;  // 消息队列

    public:
        static int threadpool_create(int _thread_count);
        static void threadpool_add(string _str);
        static void *threadpool_consumer(void *args);
        static void *threadpool_producer(void *args);
        static void threadpool_release();
};

#endif
