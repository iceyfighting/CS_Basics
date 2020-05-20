#include "threadpool.h"
#include <fstream>
#include<iostream>
using namespace std;

const int THREAD_COUNT = 3;

int main(){

    ThreadPool::threadpool_create(THREAD_COUNT);
    
    ThreadPool::threadpool_release();

    cout << endl << " 程序结束 " << endl;

}
