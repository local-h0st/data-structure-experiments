#include <iostream>
#include <cstdlib>
#include <time.h>
#define N 16

bool checkConn(bool* GraphMatrix, int size){
    bool VsThatInConnectedPart[size];
    for(int i=0;i<size;++i){
        VsThatInConnectedPart[i] = false;
    }
    VsThatInConnectedPart[0] = true;
    for(int thisVarIsNotImportant=0;thisVarIsNotImportant<size;++thisVarIsNotImportant){
        // 按列遍历
        for(int j=0;j<size;++j){
            for(int i=0;i<size;++i){
                // 邻接矩阵的i行j列，对应Vi到Vj的边的情况
                if(GraphMatrix[i*size+j]){
                    if(VsThatInConnectedPart[j]&&!VsThatInConnectedPart[i]){
                        // 不在已知的连通部分但是有边连到该部分
                        VsThatInConnectedPart[i] = true;
                    }
                }
            }
        }
    }
    for(int i=0;i<size;++i){
        if(!VsThatInConnectedPart[i])
            return false;
    }
    return true;
}

bool setVal(bool* arr, int size, int row, int line, bool value){
    arr[row*size+line] = value;
    return true;
}

struct Vertix{
    int data;
    bool tag;
};

void DFSvisit(Vertix* Vlist, bool* GMatr, int size, int index){
    if(Vlist[index].tag){   // visited already
        return;
    }
    std::cout<<Vlist[index].data<<" ";
    Vlist[index].tag = true;
    for(int j=0;j<size;++j){
        if(GMatr[index*size+j])
            DFSvisit(Vlist,GMatr,size,j);
    }
}

class InTEGER_QUEUE{
public:
    InTEGER_QUEUE(){
        this->qHead = new queueNameIsNotImportant{-1,nullptr};
        this->qTail = qHead;
    }
    ~InTEGER_QUEUE(){
        queueNameIsNotImportant *cnt = this->qHead;
        queueNameIsNotImportant *nxt = this->qHead->nxt;
        while(nxt!=nullptr){
            delete cnt;
            cnt = nxt;
            nxt = nxt->nxt;
        }
        delete cnt;
    }
    void inQ(int v){
        this->qTail->nxt = new queueNameIsNotImportant{v,nullptr};
        this->qTail = this->qTail->nxt;
    }
    int outQ(){
        if(qHead->nxt==nullptr){
            return 0; // queue is empty
        }
        int popedOut = qHead->nxt->data;
        if(qTail==qHead->nxt){
            qTail = qHead;
        }
        queueNameIsNotImportant *tmp = qHead->nxt->nxt;
        delete qHead->nxt;
        qHead->nxt = tmp;
        return popedOut;
    }
    bool isEmpty(){
        if(qHead->nxt==nullptr)
            return true;
        else
            return false;
    }
    void printHeadAndTail(){
        std::cout<<"headptr: "<<qHead<<" nxt: "<<qHead->nxt<<" tailptr: "<<qTail<<std::endl;
    }
private:
    struct queueNameIsNotImportant{
        int data;
        queueNameIsNotImportant *nxt;
    } *qHead, *qTail;
};

void BFSvisit(Vertix* Vlist, bool* GMatr, int size, InTEGER_QUEUE &q){
    if(q.isEmpty()){
        // std::cout<<"queue is empty.\n";
        return;
    }
    int index = q.outQ();
    if(Vlist[index].tag){
        // std::cout<<"index "<<index<<" has been visited.\n";
    }
    else{
        std::cout<<Vlist[index].data<<" ";
        Vlist[index].tag = true;
        for(int j=0;j<size;++j){
            if(GMatr[index*size+j]){
                q.inQ(j);
            }
        }
    }
    BFSvisit(Vlist,GMatr,size,q);
}

int main(void){
    srand((unsigned)time(NULL));
    int size = N;
    bool GMatr[size*size];
    for(auto &i : GMatr)
        i = false;
    for(int i=0;i<size;++i){
        setVal(GMatr,size,i,i,true);
    }
    while(!checkConn(GMatr,size)){
        int row = rand()%size;
        int line = rand()%size;
        setVal(GMatr,size,row,line,true);
        setVal(GMatr,size,line,row,true);
        // 无向图必定对称矩阵
    }
    // 边生成完成，图已经连通
    Vertix vList[size];
    for(auto &v : vList){
        v.data = rand()%100;
        v.tag = false;
    }
    // 顶点数据随机生成完毕
    std::cout<<"vert 0 - "<<size-1<<std::endl;
    for(auto v : vList)
        std::cout<<v.data<<" ";
    std::cout<<"\nDFS:\n";
    DFSvisit(vList,GMatr,size,rand()%size);
    std::cout<<"\nBFS:\n";
    for(auto &v : vList){
        v.tag = false;
    }
    InTEGER_QUEUE q;
    q.inQ(rand()%size);
    BFSvisit(vList,GMatr,size,q);
}

// ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
// Author: redh3t
// TimeStamp: 2022/11/27 1:35 A.M.
// 半夜写代码，有点小饿
// 正在考虑要不要来一桶泡面
// 写BFS时候顺带写了个int类型的队列
// ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;