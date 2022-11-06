#include <iostream>
#include <time.h>
#include <cstdlib>

#define MAX_RANDOM_INT 10000

int randomNumBiggerThanOrEqualTo(int num){
    int rst = 0;
    while (true){
        rst = rand()%MAX_RANDOM_INT;
        if (num==NULL){
            return rst%20;
        }
        else if(rst>=num&&rst-num<50)    // 差距不要太大就行
            return rst;
    }
}

struct Node
{
    int data;
    Node* next;
};

Node * generateList(int length){
    Node * headptr = new Node{NULL,nullptr};
    for (int i = 0;i<length;++i){
        headptr = new Node{randomNumBiggerThanOrEqualTo(headptr->data),headptr};
    }
    return headptr;
}

void printList(Node * headptr){
    std::cout<<"[list][ ";
    Node * p = headptr;
    while (p->next!=nullptr){
        std::cout<<p->data<<" ";
        p = p->next;
    }
    std::cout<<"]"<<std::endl;
}

void deleteList(Node* p){
    Node * node_to_delete = p;
    Node *head_node = p->next;
    while (head_node!=nullptr){
        delete node_to_delete;
        node_to_delete  = head_node;
        head_node = head_node->next;
    }
    delete node_to_delete;
}

Node * mergeTwoLists(Node * a,Node * b){
    Node * headptr = new Node{NULL,nullptr};
    Node * tail = headptr;
    // 这里必须要尾插法了，头插法会变成单增
    while (a->next!=nullptr&&b->next!=nullptr){
        if(a->data>b->data){
            tail->next = a;
            tail = tail->next;
            a = a->next;
        }
        else{
            tail->next = b;
            tail = tail->next;
            b = b->next;
        }
    }
    if (a->next==nullptr){
        delete a;
        tail->next = b;
    }
    else{
        delete b;
        tail->next = a;
    }
    tail = nullptr;
    // 到这里链表就会变成有两个头节点：开始的地方data=NULL，next指向第一个数据，结尾的地方最后一个是头节点，data=NULL，next=nullptr
    // 为了输出方便现在需要把第一个头节点删了
    Node * head_to_delete = headptr;
    headptr = headptr->next;
    delete head_to_delete;
    head_to_delete = nullptr;
    return headptr;
}



int main(void){
    // 头插入法创建链表单调递减，后插入的一定在前面，最后插入的一定是链表最开始的指针，因此最终链表的顺序必定和创建时给出的数据顺序相反
    // 由于要填充数据并合并，如果只是填12345678的话太无聊了，我就选择填充随机数了
    srand((unsigned)time(NULL));
    int len_a = 0,len_b = 0;
    std::cout<<"input length of list a: ";
    std::cin>>len_a;
    std::cout<<"input length of list b: ";
    std::cin>>len_b;
    std::cout<<"generating two lists..."<<std::endl;
    Node * list_a = generateList(len_a);
    Node * list_b = generateList(len_b);
    printList(list_a);
    printList(list_b);
    std::cout<<"merging into one list..."<<std::endl;
    Node * merged_list = mergeTwoLists(list_a,list_b);
    printList(merged_list);

    deleteList(merged_list);
}
