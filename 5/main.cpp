#include <iostream>
#include <cstdlib>
#include <time.h>


struct Node{
    Node * prev;
    Node * next;
    int data;
};

int getRandomNum(){
    return rand()%10000;
}

void printList(Node * startptr){
    if (startptr==nullptr){
        std::cout<<"empty list without head node."<<std::endl;
    }
    else{
       std::cout<<"#list[ ";
        Node * p = startptr;
        do{
            if (p->data!=NULL){
                std::cout<<p->data<<" ";
            }
            p = p->next;
        } while (p!=startptr);
        std::cout<<"]"<<std::endl;     
    }

}

void deleteList(Node * ptr){
    Node * to_delete = ptr;
    if (ptr==nullptr){
        return;
    }
    Node * p = ptr->next;
    while (p!=ptr){
        delete to_delete;
        to_delete = p;
        p = p->next;
    }
    delete to_delete;
}

int main(void){
    srand((unsigned)time(NULL));
    int total = 0;
    std::cin >> total;
    Node * p = nullptr;
    // with head node
    Node * headptr = new Node{nullptr,nullptr,NULL};
    headptr->next = headptr;
    headptr->prev = headptr;
    for (size_t i = 0; i < total; i++){
        p = headptr->next;
        Node * new_node = new Node{nullptr,nullptr,getRandomNum()};
        while (true){
            if (p->data>new_node->data||p==headptr){
                new_node->next = p;
                p->prev->next = new_node;
                new_node->prev = p->prev;
                p->prev = new_node;
                break;
            }
            else{
                p = p->next;
            }
        }
    }
    p = nullptr;
    printList(headptr);
    // without head node
    Node * nodeptr = nullptr;
    for (size_t i = 0; i < total; i++){
        if (nodeptr==nullptr){
            nodeptr = new Node{nullptr,nullptr,getRandomNum()};
            nodeptr->prev = nodeptr;
            nodeptr->next = nodeptr;
        }
        else{
            p = nodeptr;
            Node * new_node = new Node{nullptr,nullptr,getRandomNum()};
            do{
                if (p->data>new_node->data){
                    new_node->next = p;
                    p->prev->next = new_node;
                    new_node->prev = p->prev;
                    p->prev = new_node;
                    if (p==nodeptr){
                        nodeptr = new_node;
                    }
                    break;
                }
                else{
                    p = p->next;
                }
            } while (p!=nodeptr);
            if (p==nodeptr){
                new_node->next = p;
                p->prev->next = new_node;
                new_node->prev = p->prev;
                p->prev = new_node;
            }
        }
    }
    p = nullptr;
    printList(nodeptr);

    
    // delete
    deleteList(headptr);
    deleteList(nodeptr);
    return 0;

    // 不带头节点实在是太麻烦啦QaQ！以后我一定写头节点！
    // ;;;;;;;;;;;;;;;;;;;;;;;;
    // By redh3t ( Ni Zhezhen )
    // ;;;;;;;;;;;;;;;;;;;;;;;;
}