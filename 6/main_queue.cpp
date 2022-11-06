#include <iostream>
#include <cstdlib>
#include <time.h>

#define LENGTH 8

struct QUEUE {
    int cap;
    int * queue;
    int head;
    int tail;
    int count;
};

void pushQueue(QUEUE & q, int data){
    if (q.count==q.cap){
        std::cout<<"queue full."<<std::endl;
    }
    else{
        q.tail = (q.tail+1)%q.cap;
        q.queue[q.tail] = data;
        if (q.count==0){
            q.head = (q.head+1)%q.cap;
        }
        ++q.count;
    }
}

int popQueue(QUEUE & q){
    if (q.count==0){
        throw true;
    }
    else{
        int data = q.queue[q.head];
        q.queue[q.head] = NULL;
        if (q.count!=1){
            q.head = (q.head+1)%q.cap;            
        }
        --q.count;
        return data;
    }
}

void popQueueAndPrint(QUEUE & q){
    try{
        std::cout<<popQueue(q)<<std::endl;
    }
    catch(...){
        std::cout<<"empty queue does not allow pop."<<std::endl;
    }
}


int main(void){
    QUEUE q{LENGTH,nullptr,0,0,0};
    q.queue = new int[q.cap];
    // [head, ..., ..., ..., tail, 0, 0]
    // 先空队列pop
    popQueueAndPrint(q);
    // 填3个弹4个
    pushQueue(q,333);
    pushQueue(q,666);
    pushQueue(q,999);
    popQueueAndPrint(q);
    popQueueAndPrint(q);
    popQueueAndPrint(q);
    popQueueAndPrint(q);
    // 填9个
    pushQueue(q,1);
    pushQueue(q,2);
    pushQueue(q,3);
    pushQueue(q,4);
    pushQueue(q,5);
    pushQueue(q,6);
    pushQueue(q,7);
    pushQueue(q,8);
    pushQueue(q,9); // 填不进，会提示queue full.
    popQueueAndPrint(q); // 弹1个
    pushQueue(q,10);    // 填进
    // 全部弹出直到弹空
    popQueueAndPrint(q);
    popQueueAndPrint(q);
    popQueueAndPrint(q);
    popQueueAndPrint(q);
    popQueueAndPrint(q);
    popQueueAndPrint(q);
    popQueueAndPrint(q);
    popQueueAndPrint(q);
    popQueueAndPrint(q);





    delete q.queue;
}