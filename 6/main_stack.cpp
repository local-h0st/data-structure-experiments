#include <iostream>
#include <cstdlib>
#include <time.h>

#define LENGTH 16

struct STACK_ELEM {
    int data;
    STACK_ELEM * next;
};

void stackPush(STACK_ELEM * &topptr, int data){
    topptr->data = data;
    topptr = new STACK_ELEM{NULL,topptr};
}

int stackPop(STACK_ELEM * &topptr){
    if (topptr->next==nullptr){ // 就剩最后一个节点了，而且是空的节点，是top也是base
        delete topptr;
        topptr = nullptr;
        throw true; // 表示stack base也被删除
    }
    else{
        STACK_ELEM * to_delete = topptr->next;
        int data = to_delete->data;
        topptr->next = to_delete->next;
        delete to_delete;
        return data;
    }

}

int main(void){
    srand((unsigned)time(NULL));
    STACK_ELEM * base = new STACK_ELEM{NULL,nullptr};
    STACK_ELEM * top = base;
    for (int i = 0; i < LENGTH; ++i){
        int data = rand()%100;
        stackPush(top, data);
        std::cout<<data<<" pushed in."<<std::endl;
    }
    std::cout<<std::endl;
    while (true){
        try {
            int data = stackPop(top);
            std::cout<<data<<" poped out."<<std::endl;
        }
        catch(bool){
            break;
        }
    }
    // 弹完了base现在指向的地方是野指针
    if (top==nullptr){
        base = nullptr;
        std::cout<<"successfully poped all the data and delete the stack."<<std::endl;
    }
    
}