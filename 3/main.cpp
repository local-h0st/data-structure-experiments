// ;;;;;;;;;;;;;;;;;;;;;;;;
// By Zhezhen Ni, 2022.9.15
// ;;;;;;;;;;;;;;;;;;;;;;;;

#include <iostream>
#include <cstdlib>
#include <time.h>
#include <math.h>


bool isPrime(int n){
    int i = 2;
    while (i<(int)sqrt(n)+1){
        if (n%i==0){
            return false;
        }
        ++i;
    }
    return true;
}

int getPrime(int index){
    if (index<1){
        return -1;
    }
    int count = 0;
    int number = 2;
    while (true){
        if (isPrime(number)){
            ++count;
            if (count==index){
                return number;
            }
        }
        ++number;
    }
    
}

int howManyPrimes(int range){
    int count = 0;
    for (size_t i = 2; i < range+1; i++)
    {
        if (isPrime(i)){
            ++count;
        }
    }
    return count;
}

typedef struct LINK_LIST
{
    int data;
    LINK_LIST* nextptr;
};

/*
int getRandomPrime(){
    while (true){
        int rst = rand()%1000;
        if (isPrime(rst)){
            return rst;
        }
    }
}
*/

int main(void){
    // srand((unsigned)time(NULL));
    // 初始化链表，质数填充
    int range = 0;
    std::cout<<"input your prime num range here: ";
    std::cin>>range;
    LINK_LIST* listptr = new LINK_LIST{NULL,nullptr};
    for (size_t i = 1; i < howManyPrimes(range)+1; i++){
        listptr = new LINK_LIST{getPrime(i),listptr};
    }

    // 遍历链表输出data
    int count = 0;
    LINK_LIST* p = listptr;
    while (p->nextptr!=nullptr){
        std::cout<<p->data<<" ";
        p = p->nextptr;
        ++count;
    }
    std::cout<<std::endl;
    std::cout<<count<<" primes in total."<<std::endl;

    // delete释放空间
    if (listptr->nextptr==nullptr){
        delete listptr;
    } 
    else{
        p = listptr->nextptr;
        while (p!=nullptr){
            delete listptr;
            listptr = p;
            p = p->nextptr;
        }
        delete listptr;
    }
    return 0;
}