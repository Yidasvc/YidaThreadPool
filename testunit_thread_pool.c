#include <stdio.h>
#include "yida_thread_pool.h"
#define N_THREADS_IN_POOL 10
#define N_THREADS_REALLY_USE 50

int testFunc(void* arg){
    thread* t = (thread*)arg;
    int sum = 0;
    for(int i=0;i<100000000;i++){
        sum=(sum+1)%1000000007;
    }
    printf("Hello Yida thread pool! I am thread #%d, sum=%d\n",t->tid,sum);
    // sleep(1);
}

int main(){
    Thread_Pool* pool = create_pool(N_THREADS_IN_POOL);
    if(pool==NULL){
        printf("线程池创建失败！\n");
        return 1;
    }

    for(int i=0;i<N_THREADS_REALLY_USE;i++){
        if(alloc_thread(pool,testFunc,NULL,1)==-1){
            printf("线程创建失败！\n");
        }
    }
    for(int i=0;i<N_THREADS_IN_POOL;i++){
        join_thread(i+1,pool);
    }
}