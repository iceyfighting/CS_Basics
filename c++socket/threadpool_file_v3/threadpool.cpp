
#include "threadpool.h"
#include<unistd.h>

pthread_t ThreadPool::producer;
pthread_t *ThreadPool::consumer;
pthread_mutex_t ThreadPool::producer_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t ThreadPool::consumer_lock = PTHREAD_MUTEX_INITIALIZER;
queue<string> ThreadPool::MessageQueue ;
int ThreadPool::thread_count = 0;
bool ThreadPool::shutdown = false;
int ThreadPool::line_of_count = 0;

// 线程池初始化
int ThreadPool::threadpool_create(int _thread_count)
{
    int result = pthread_create(&producer, NULL, threadpool_producer, NULL);
    if(result != 0)
    {
        cout << " 生产者线程创建出错!" << endl;
    }
    else
    {
        cout << " 生产者线程创建成功!" << endl;
    }

    consumer = (pthread_t*)malloc(sizeof(pthread_t)*_thread_count);

    thread_count = 0;
    shutdown = false;
    line_of_count = 0;

    for(int i = 0; i < _thread_count; ++i)
    {
        // ret == 0 代表线程创建成功
        int result = pthread_create(&consumer[i], NULL, threadpool_consumer, NULL);
        if(result != 0){
            cout << " 消费者线程创建出错 " << endl;
        }
        else{
            cout << " 消费者线程 " << i << " 创建成功!" << endl;
        }
        thread_count++;
    }

    cout << " threadpool_create successful " << endl;
    return 0;
}

// 往线程池中添加任务
void ThreadPool::threadpool_add(string _str)
{    
    cout << "测试2..." << endl;
    //这个锁是不是和消费者的锁冲突了？
    pthread_mutex_lock(&producer_lock);
    
    cout << "测试2..." << endl;
    MessageQueue.push(_str);
    pthread_mutex_unlock(&producer_lock);
}

void *ThreadPool::threadpool_consumer(void *args)
{
    cout << " 消费者开始执行 " << endl;
    while(true)
    {
        pthread_mutex_lock(&consumer_lock);
        if(MessageQueue.size() != 0)
        {
            string str = MessageQueue.front();
            cout << pthread_self() << " " << str << endl;
            // 对这一行数据进行处理 xxx
            MessageQueue.pop();
        } //队列为空且线程池关闭说明任务执行完了
        else if(MessageQueue.size() == 0 && shutdown == true)
        {
            break;
        }
        else // 为空，但是生产者还没结束，消息队列里面以后可能还有数据
        {
            usleep(300000); // 300ms
        }
        pthread_mutex_unlock(&consumer_lock);        
    }
    pthread_mutex_unlock(&consumer_lock);        
}

void *ThreadPool::threadpool_producer(void *args)
{
    cout << " 生产者开始执行 " << endl;
    const char *file_name = "./a.txt";
    ifstream ifs(file_name);
    string line;
    while(getline(ifs, line))
    {
        ++line_of_count;
        
        cout << "测试....." << endl;
        //因为生产者只有一个，不用加锁
        ThreadPool::threadpool_add(line);

        cout << "测试....." << endl;
    }
    // 线程池关闭
    shutdown = true;
    cout << " 文件行数是: " << line_of_count << endl << endl;
    cout << " 生产者执行结束 " << endl;
}

void ThreadPool::threadpool_release(){
    cout << endl << " 进入 threadpool_release " << endl;

    void *retval;
    int result = pthread_join(producer, &retval);
    if(result == 0)
    {
        cout << endl << " producer 释放成功 " << endl;
    }
    else
    {
        cout << endl << " producer 释放失败 " << endl;
    }

    for(int i=0; i < thread_count; i++)
    {
        int result = pthread_join(consumer[i], &retval);
        if(result == 0)
        {
            cout << endl << " consumer[" << i << "] 释放成功 " << endl;
        }
        else
        {
            cout << endl << " consumer[" << i << "] 释放失败 " << endl;
        }
    }
}
