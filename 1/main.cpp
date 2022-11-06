#include <iostream>
#include <cstdlib>
#include <time.h>

int main(void){
    std::srand((unsigned)time(NULL));
    int size = rand()%31 + 20;
    int* arr_ptr = new int[size];
    for (size_t i = 0; i < size; i++)
    {
        arr_ptr[i] = rand()%101;
        std::cout<<arr_ptr[i]<<" ";
    }
    std::cout<<std::endl;
    std::cout<<"changing the order..."<<std::endl;
    for (size_t i = 0; i < size/2; i++)
    {
        int tmp = 0;
        tmp = arr_ptr[i];
        arr_ptr[i] = arr_ptr[size-1-i];
        arr_ptr[size-1-i] = tmp;
    }
    for (size_t i = 0; i < size; i++)
    {
        std::cout<<arr_ptr[i]<<" ";
    }

    


    delete []arr_ptr;
}