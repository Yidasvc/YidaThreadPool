#include <stdio.h>
#include <pthread.h>
#include "yida_queue.h"
#define N_PRODUCER 1000
#define QUEUE_LEN 1
pthread_t producer_thread[N_PRODUCER];
pthread_t customer_thread;
int numbers[N_PRODUCER];
Queue* queue;

void* my_customer(void* arg){
    int* a;
    while(1){
        a = queue_pop_fast(queue);
        printf("This message from producer int address %p, #%d\n",a,*a);
    }
}

void* my_producer(void* producer_id){
    queue_push(queue,producer_id);
}

int main(){
    queue = queue_init(QUEUE_LEN,sizeof(int));
    for(int i=0;i<N_PRODUCER;i++){
        numbers[i] = i;
    }
    pthread_create(&customer_thread,NULL,my_customer,NULL);
    for(int i=0;i<N_PRODUCER;i++){
        pthread_create(producer_thread+i,NULL,my_producer,numbers+i);
    }
    for(int i=0;i<N_PRODUCER;i++){
        pthread_join(producer_thread[i],NULL);
    }
    // sleep(1);
}