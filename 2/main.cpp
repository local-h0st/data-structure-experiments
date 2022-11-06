#include <iostream>
#include <cstdlib>
#include <time.h>

typedef struct LIST
{
    int* p;
    int length;
    int cap;
};

void printList(const std::string &name,const LIST &l){
    std::cout<<"(LIST "+name+") = [ ";
    for (size_t i = 0; i < l.length; i++)
    {
        if (l.p[i]<10)
        {
            std::cout<<" ";
        }
        
        std::cout<<l.p[i]<<" ";
    }
    std::cout<<"]"<<std::endl;
}

void bubbleSort(LIST &l){
    for (size_t i = 0; i < l.length; i++)
    {
        for (size_t j = i+1; j < l.length; j++)
        {
            if(l.p[j]<l.p[i]){
                int tmp = l.p[i];
                l.p[i] = l.p[j];
                l.p[j] = tmp;
            }
        }
        
    }
    
}


int main(void){
    LIST list_a{nullptr,0,64};
    LIST list_b{nullptr,0,8};
    srand((unsigned)time(NULL));
    list_a.p = new int[list_a.cap];
    list_b.p = new int[list_b.cap];
    if(list_a.p==nullptr||list_b.p==nullptr){
        if(list_a.p!=nullptr){
            delete []list_a.p;
        }
        if(list_b.p!=nullptr){
            delete []list_b.p;
        }
    }
    
    std::cout<<"Generating LISTs..."<<std::endl;
    for (size_t i = 0; i < 8; i++)
    {
        list_a.p[i]=rand()%100;
        ++list_a.length;
    }
    for (size_t i = 0; i < list_b.cap; i++)
    {
        list_b.p[i]=rand()%100;
        ++list_b.length;
    }
    printList("A",list_a);
    printList("B",list_b);
    std::cout<<std::endl;

    std::cout<<"Bubble sorting..."<<std::endl;
    bubbleSort(list_a);
    bubbleSort(list_b);
    printList("A",list_a);
    printList("B",list_b);
    std::cout<<std::endl;

    std::cout<<"Uniting into LIST C..."<<std::endl;
    LIST list_c{nullptr,0,list_a.length+list_b.length};
    list_c.p = new int[list_c.cap];
    int a_index = 0,b_index = 0,c_index = 0;
    while(a_index!=list_a.length&&b_index!=list_b.length){
        if(list_a.p[a_index]<list_b.p[b_index]){
            list_c.p[c_index] = list_a.p[a_index];
            ++a_index;
        }
        else{
            list_c.p[c_index] = list_b.p[b_index];
            ++b_index;
        }
        ++list_c.length;
        ++c_index;
    }
    if(a_index==list_a.length){
        while (b_index<list_b.length)
        {
            list_c.p[c_index] = list_b.p[b_index];
            ++list_c.length;
            ++b_index;
            ++c_index;
        }
    }
    else{
        while (a_index<list_a.length)
        {
            list_c.p[c_index] = list_a.p[a_index];
            ++list_c.length;
            ++a_index;
            ++c_index;
        }
    }
    printList("C",list_c);
    std::cout<<std::endl;



    std::cout<<"Uniting into A self..."<<std::endl;
    std::cout<<"# Original LIST A and B :"<<std::endl;
    printList("A",list_a);
    printList("B",list_b);
    a_index = list_a.length-1;
    b_index = list_b.length-1;
    list_a.length = list_a.length + list_b.length;
    int index = list_a.length-1;
    while(a_index!=-1&&b_index!=-1){
        if(list_a.p[a_index]>list_b.p[b_index]){
            list_a.p[index] = list_a.p[a_index];
            --a_index;
        }
        else{
            list_a.p[index] = list_b.p[b_index];
            --b_index;
        }
        --index;
    }
    if(a_index==-1){
        while(b_index!=-1){
            list_a.p[index] = list_b.p[b_index];
            --b_index;
            --index;
        }
    }
    else{
        while(a_index!=-1){
            list_a.p[index] = list_a.p[a_index];
            --a_index;
            --index;
        }
    }




    std::cout<<"# Current LIST A :"<<std::endl;
    printList("A",list_a);



    delete []list_a.p;
    delete []list_b.p;
    delete []list_c.p;
    list_a.p = nullptr;
    list_b.p = nullptr;
    list_c.p = nullptr;
    return 0;
}