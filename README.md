# YidaThreadPool
Copyright (c) 2022 李易达 All rights reserved.

// 对外接口，用于创建线程池。参数为线程池容量，返回线程池，失败时返回NULL.

Thread_Pool* create_pool(int n_threads);


// 对外接口，在线程池中申请线程，返回线程在这个线程池中的tid号，从1开始。

// startNow参数置0就暂不启动，置1就立即启动。对于可预知线程入口的情况，预设置入口可以进一步加速。

int alloc_thread(Thread_Pool* pool,int (*function)(thread*),void* params, int startNow);


// 对外接口，启动一个线程。用于申请线程时没启动的情况。

int start_thread(int tid, Thread_Pool* pool);


// 对外接口，等待线程结束。

int join_thread(int tid, Thread_Pool* pool);
