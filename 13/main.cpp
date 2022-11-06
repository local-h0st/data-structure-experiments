#include <iostream>
#include <cstdlib>
#include <time.h>

int* randomlyGenerateCompleteBinaryTree(const int &size){
    int* root = new int[size];
    for (int i=0; i<size; ++i){
        root[i] = rand()%100;
    }
    return root;
}

void sortTheHeap(int* heap, const int &size, int mode){
    bool complete_flag = false;
    while (!complete_flag){
        complete_flag = true;
        for (int i=1; i<size; ++i){
            if (mode==0){   // 最小堆
                if (i%2==1){    // i = 2n + 1
                    if (heap[i]<heap[(i-1)/2]){ // 比父节点小则交换
                        complete_flag = false;
                        int tmp = heap[i];
                        heap[i] = heap[(i-1)/2];
                        heap[(i-1)/2] = tmp;
                    }
                }
                else{   //  i = 2n + 2
                    if (heap[i]<heap[(i-2)/2]){ // 比父节点小则交换
                        complete_flag = false;
                        int tmp = heap[i];
                        heap[i] = heap[(i-2)/2];
                        heap[(i-2)/2] = tmp;
                    }
                }
            }
            else{   // 最大堆
                if (i%2==1){    // i = 2n + 1
                    if (heap[i]>heap[(i-1)/2]){ // 比父节点大则交换
                        complete_flag = false;
                        int tmp = heap[i];
                        heap[i] = heap[(i-1)/2];
                        heap[(i-1)/2] = tmp;
                    }
                }
                else{   //  i = 2n + 2
                    if (heap[i]>heap[(i-2)/2]){ // 比父节点大则交换
                        complete_flag = false;
                        int tmp = heap[i];
                        heap[i] = heap[(i-2)/2];
                        heap[(i-2)/2] = tmp;
                    }
                }
            }
        }
    }
}

void printHeap(int* heap, const int &size){
    std::cout<<"######### heap info #########"<<std::endl;
    for (int i=0; i<size; ++i){
        std::cout<<"node index: "<<i<<" node data: "<<heap[i]<<" ";
        if ((2*i+1)<size){
            std::cout<<"left child data: "<<heap[2*i+1]<<" ";
        }
        if ((2*i+2)<size){
            std::cout<<"left child data: "<<heap[2*i+2]<<" ";
        }
        std::cout<<std::endl;
    }
    std::cout<<"######### heap info #########"<<std::endl;
}


int main(void){
    srand((unsigned)time(NULL));
    const int size = rand()%100;
    int* heap = randomlyGenerateCompleteBinaryTree(size);
    printHeap(heap, size);
    sortTheHeap(heap, size, 0); // 最小堆
    printHeap(heap, size);
    sortTheHeap(heap, size, 1); // 最大堆
    printHeap(heap, size);
    delete []heap;
}

// ;;;;;;;;;;;;;;;;;;;;;;;;;;;;
// Author: redh3t
// TimeStamp: 2022/10/31
// 完全二叉树可以不用二叉链表存储
// 所以堆也不用，nice！
// 如果和子节点比较，那么最下面那
// 一层会越界，而采用和父节点比较
// 只有0号有特殊情况，更容易处理
// ;;;;;;;;;;;;;;;;;;;;;;;;;;;;
