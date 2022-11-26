#include <iostream>
#include <cstdlib>
#include <time.h>
#include <vector>
#include <iterator>
#include <algorithm>
#define N 16

struct Vertix{
    int data;
    bool tag;   // to label if in group U
};
struct EDGE{
    int weight;
    bool tag;   // to label connectivity
    int Vi,Vj;
};

bool checkConn(EDGE* GraphMatrix, int size){
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
                if(GraphMatrix[i*size+j].tag){
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
bool setVal(EDGE* arr, int size, int row, int line, EDGE e){
    arr[row*size+line].weight = e.weight;
    arr[row*size+line].tag = e.tag;
    return true;
}


bool deleteElemFromVector(std::vector<int> &V, int elem){
    std::vector<int>::iterator i = std::find(V.begin(),V.end(),elem);
    if(i==V.end()){
        std::cout<<"failed to delete because not found.\n";
        return false;
    }
    else{
        V.erase(i);
        return true;
    }
}

int main(void){
    srand((unsigned)time(NULL));
    int size = N;
    EDGE GMatr[size*size];   // 含权图
    for(int i=0;i<size;++i){
        for(int j=0;j<size;++j){
            GMatr[i*size+j] = EDGE{NULL,false,i,j};
        }
    }
    for(int i=0;i<size;++i){
        setVal(GMatr,size,i,i,EDGE{0,true,i,i});
    }
    while(!checkConn(GMatr,size)){
        int row = rand()%size;
        int line = rand()%size;
        int weight = rand()%100;
        setVal(GMatr,size,row,line,EDGE{weight,true,row,line});
        setVal(GMatr,size,line,row,EDGE{weight,true,line,row});
        // 无向图必定对称矩阵
    }
    // 输出一下边
    for(int i=0;i<size;++i){
        for(int j=0;j<size;++j){
            EDGE e = GMatr[i*size+j];
            std::cout<<"weight: "<<e.weight<<" has_edge: "<<e.tag<<" two_Vs: "<<e.Vi<<"&"<<e.Vj<<std::endl;
        }
    }
    // 边生成完成，图已经连通
    Vertix vList[size];
    for(auto &v : vList){
        v.data = rand()%100;
        v.tag = false;
    }
    // 顶点数据随机生成完毕
    std::vector<int> U;
    std::vector<int> V;
    std::vector<EDGE> MSTedges;
    for(int i=0;i<size;++i){
        V.push_back(i);
    }
    int index = rand()%size;
    U.push_back(index);
    deleteElemFromVector(V,index);
    while(!V.empty()){
        EDGE current_min_weight_edge = EDGE{9999,false,-1,-1};
        for(auto e : GMatr){
            if(e.Vi!=e.Vj&&e.tag==true){
                if(
                    (std::find(U.begin(),U.end(),e.Vi)!=U.end()&&std::find(V.begin(),V.end(),e.Vj)!=V.end())||
                    (std::find(U.begin(),U.end(),e.Vj)!=U.end()&&std::find(V.begin(),V.end(),e.Vi)!=V.end())
                ){
                    if(e.weight<current_min_weight_edge.weight){
                        current_min_weight_edge = e;
                    }
                }            
            }
        }
        MSTedges.push_back(current_min_weight_edge);
        if(std::find(U.begin(),U.end(),current_min_weight_edge.Vi)!=U.end()){
            U.push_back(current_min_weight_edge.Vj);
            deleteElemFromVector(V,current_min_weight_edge.Vj);
        }
        else{
            U.push_back(current_min_weight_edge.Vi);
            deleteElemFromVector(V,current_min_weight_edge.Vi);
        }        
    }

    std::cout<<"MST Edges:\n";
    for(auto e : MSTedges)
        std::cout<<"weight: "<<e.weight<<" has_edge: "<<e.tag<<" two_Vs: "<<e.Vi<<"&"<<e.Vj<<std::endl;



}
// ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
// Author: redh3t
// TimeStamp; 2022/11/27 3:04 A.M.
// 半夜边看比赛边写的代码
// 也挺爽的，虽然有点困
// ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;