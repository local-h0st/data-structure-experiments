#include <iostream>
#include <stdlib.h>
#include <time.h>
#define DELETED 9999

struct TRIPLE{
    int row;
    int column;
    int data;
};

class Matrix;

class TripleArr{
public:
    TripleArr(const Matrix &matrix);
    ~TripleArr();
    void printArr();
    void reverso();
    TRIPLE * p;
    int length;
private:
    int findRowMin();
};

class Matrix{
public:
    Matrix(int r,int c){
        this->none0count = 0;
        this->rows = r;
        this->columns = c;
        this->p = new int*[this->rows];
        for (int i=0;i<this->rows;++i)
            this->p[i] = new int[this->columns];
    }
    ~Matrix(){
        for (int i=0;i<this->rows;++i){
            delete []this->p[i];
        }
        delete []this->p;
    }
    void countNoneZero(){
        none0count = 0;
        for (int i=0;i<rows;++i){
            for (int j=0;j<columns;++j){
                if (p[i][j]!=0){
                    ++none0count;
                }
            }
        }
    }
    void generateSparseMatrix(){
        int flag = 0;
        for (int i=0;i<this->rows;++i){
            for (int j=0;j<this->columns;++j){
                flag = rand()%1000;
                if (flag<50){   // flag 控制稀疏度
                    this->p[i][j] = rand()%100;
                }
                else{
                    this->p[i][j] = 0;
                }
            }
        }
        this->countNoneZero();
    }
    void printMatrix(){
        std::cout<<"# start matrix"<<std::endl;
        for (int i=0;i<this->rows;++i){
            for (int j=0;j<this->columns;++j){
                std::cout<<this->p[i][j]<<"\t";
            }
            std::cout<<std::endl;
        }
        std::cout<<"# end matrix"<<std::endl;
    }
    void rebuildFromTripleArr(TripleArr & arr){
        for (int i=0;i<this->rows;++i){
            for (int j=0;j<this->columns;++j){
                this->p[i][j] = 0;
            }
        }
        for (int i=0;i<arr.length;++i){
            this->p[arr.p[i].row][arr.p[i].column] = arr.p[i].data;
        }
        this->countNoneZero();
        std::cout<<"rebuilt from triple arr."<<std::endl;
    }
    int rows;
    int columns;
    int **p;
    int none0count;
};



TripleArr::TripleArr(const Matrix &matrix){
    this->length = matrix.none0count;
    this->p = new TRIPLE[this->length];
    TRIPLE * current = this->p;
    for (int i=0;i<matrix.rows;++i){
        for (int j=0;j<matrix.columns;++j){
            if (matrix.p[i][j]!=0){
                *current = TRIPLE{i,j,matrix.p[i][j]};
                ++current;
            }
        }
    }
    current = nullptr;
}
TripleArr::~TripleArr(){
    delete []this->p;
}
void TripleArr::printArr(){
    std::cout<<"# start to print triple array."<<std::endl;
    for (int i=0;i<this->length;++i){
        std::cout<<"{ position: ("<<p[i].row<<", "<<p[i].column<<")\tdata: "<<p[i].data<<" }"<<std::endl;
    }
    std::cout<<"# print triple array ended."<<std::endl;
}
void TripleArr::reverso(){
    // 先交换
    for (int i=0;i<this->length;++i){
        int tmp = this->p[i].row;
        this->p[i].row = this->p[i].column;
        this->p[i].column = tmp; 
    }
    // 再排序
    TRIPLE * tmp = new TRIPLE[this->length];
    TRIPLE * current = tmp;
    int to_sort = this->findRowMin();
    while (to_sort!=DELETED) {
        for (int i=0;i<this->length;++i){
            if (this->p[i].row==to_sort){
                *current = TRIPLE{this->p[i].row, this->p[i].column, this->p[i].data};
                ++current;
                this->p[i].row = DELETED;
            }
        }
        to_sort = this->findRowMin();
    } 
    current = nullptr;
    delete []this->p;
    this->p = tmp;
    std::cout<<"triple array reversed."<<std::endl;
}


int TripleArr::findRowMin(){
    int min = this->p[0].row;
    for (int i=1;i<this->length;++i){
        if (this->p[i].row<min){
            min = this->p[i].row;
        }
    }
    return min;
}   // 仅辅助函数



int main(void){
    srand((unsigned)time(NULL));
    Matrix matrix(16,16);
    matrix.generateSparseMatrix();
    matrix.printMatrix();
    TripleArr matrix_arr(matrix);
    matrix_arr.printArr();
    matrix_arr.reverso();
    matrix_arr.printArr();
    matrix.rebuildFromTripleArr(matrix_arr);
    matrix.printMatrix();
}

/*
class Matrix{
public:
    Matrix(int r,int c){
        this->none0count = 0;
        this->rows = r;
        this->columns = c;
        this->p = new int*[this->rows];
        for (int i=0;i<this->rows;++i)
            this->p[i] = new int[this->columns];
    }
    ~Matrix(){
        for (int i=0;i<this->rows;++i){
            delete []this->p[i];
        }
        delete []this->p;
    }
    void countNoneZero(){
        none0count = 0;
        for (int i=0;i<rows;++i){
            for (int j=0;j<columns;++j){
                if (p[i][j]!=0){
                    ++none0count;
                }
            }
        }
    }
    void generateSparseMatrix(){
        int flag = 0;
        for (int i=0;i<this->rows;++i){
            for (int j=0;j<this->columns;++j){
                flag = rand()%1000;
                if (flag<50){   // flag 控制稀疏度
                    this->p[i][j] = rand()%100;
                }
                else{
                    this->p[i][j] = 0;
                }
            }
        }
        this->countNoneZero();
    }
    void printMatrix(){
        std::cout<<"# start matrix"<<std::endl;
        for (int i=0;i<this->rows;++i){
            for (int j=0;j<this->columns;++j){
                std::cout<<this->p[i][j]<<"\t";
            }
            std::cout<<std::endl;
        }
        std::cout<<"# end matrix"<<std::endl;
    }
    void rebuildFromTripleArr(TripleArr & arr){
        for (int i=0;i<this->rows;++i){
            for (int j=0;j<this->columns;++j){
                this->p[i][j] = 0;
            }
        }
        for (int i=0;i<arr.length;++i){
            this->p[arr.p[i].row][arr.p[i].column] = arr.p[i].data;
        }
        this->countNoneZero();
        std::cout<<"rebuilt from triple arr."<<std::endl;
    }
    int rows;
    int columns;
    int **p;
    int none0count;
};

struct TRIPLE{
    int row;
    int column;
    int data;
};

class TripleArr{
public:
    TripleArr(const Matrix &matrix){
        this->length = matrix.none0count;
        this->p = new TRIPLE[this->length];
        TRIPLE * current = this->p;
        for (int i=0;i<matrix.rows;++i){
            for (int j=0;j<matrix.columns;++j){
                if (matrix.p[i][j]!=0){
                    *current = TRIPLE{i,j,matrix.p[i][j]};
                    ++current;
                }
            }
        }
        current = nullptr;
    }
    ~TripleArr(){
        delete []this->p;
    }
    void printArr(){
        std::cout<<"# start to print triple array."<<std::endl;
        for (int i=0;i<this->length;++i){
            std::cout<<"{ position: ("<<p[i].row<<", "<<p[i].column<<")\tdata: "<<p[i].data<<" }"<<std::endl;
        }
        std::cout<<"# print triple array ended."<<std::endl;
    }
    void reverso(){
        // 先交换
        for (int i=0;i<this->length;++i){
            int tmp = this->p[i].row;
            this->p[i].row = this->p[i].column;
            this->p[i].column = tmp; 
        }
        // 再排序
        TRIPLE * tmp = new TRIPLE[this->length];
        TRIPLE * current = tmp;
        int to_sort = this->findRowMin();
        while (to_sort!=DELETED) {
            for (int i=0;i<this->length;++i){
                if (this->p[i].row==to_sort){
                    *current = TRIPLE{this->p[i].row, this->p[i].column, this->p[i].data};
                    ++current;
                    this->p[i].row = DELETED;
                }
            }
            to_sort = this->findRowMin();
        } 
        current = nullptr;
        delete []this->p;
        this->p = tmp;
        std::cout<<"triple array reversed."<<std::endl;
    }
    TRIPLE * p;
    int length;
private:
    int findRowMin(){
        int min = this->p[0].row;
        for (int i=1;i<this->length;++i){
            if (this->p[i].row<min){
                min = this->p[i].row;
            }
        }
        return min;
    }   // 仅辅助函数
};
*/