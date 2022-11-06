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
    TripleArr(int len);
    ~TripleArr();
    void printArr();
    void reversoWithOriginalMatrix(Matrix & m);
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
        this->none0countAtColumn = new int[this->columns];
        this->cpot = new int[this->columns];
        this->clear();
    }
    ~Matrix(){
        for (int i=0;i<this->rows;++i){
            delete []this->p[i];
        }
        delete []this->p;
        delete this->none0countAtColumn;
        delete this->cpot;
    }
    void generateSparseMatrix(int degree=50){
        int flag = 0;
        for (int i=0;i<this->rows;++i){
            for (int j=0;j<this->columns;++j){
                flag = rand()%1000;
                if (flag<degree){   // flag 控制稀疏度
                    this->p[i][j] = rand()%100;
                }
                else{
                    this->p[i][j] = 0;
                }
            }
        }
        this->prepare();
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
        this->prepare();
        std::cout<<"rebuilt from triple arr."<<std::endl;
    }
    void prepare(){
        // total and every column count and cpot
        this->none0count = 0;
        for (int c=0;c<this->columns;++c){
            int count = 0;
            bool flag = true;
            for (int r=0;r<this->rows;++r){
                if (this->p[r][c]!=0){
                    ++count;
                    ++this->none0count;
                    if (flag){
                        this->cpot[c] = this->none0count - 1;
                        flag = false;
                    }
                }
            }
            this->none0countAtColumn[c] = count;
        }
    }
    void clear(){
        for (int i=0;i<this->rows;++i){
            for (int j=0;j<this->columns;++j){
                this->p[i][j] = 0;
            }
        }
    }
    int rows;
    int columns;
    int **p;
    int none0count;
    int *none0countAtColumn;
    int *cpot;
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
TripleArr::TripleArr(int len){
    this->length = len;
    this->p = new TRIPLE[this->length];
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
void TripleArr::reversoWithOriginalMatrix(Matrix & m){
    TRIPLE * tmp = new TRIPLE[this->length];
    for (int i=0;i<this->length;++i){
        tmp[m.cpot[this->p[i].column]] = TRIPLE{this->p[i].column,this->p[i].row,this->p[i].data};
        ++m.cpot[this->p[i].column];
    }
    delete []this->p;
    this->p = tmp;
    m.prepare();
}

// 单独实现矩阵乘法，结果返回Matrix
Matrix matrixMult(const Matrix & a, const Matrix & b){
    // a * b
    Matrix result(a.rows,b.columns);
    for (int row=0;row<a.rows;++row){
        for (int col=0;col<b.columns;++col){
            int sum = 0;
            for (int i=0;i<a.columns;++i){
                sum += a.p[row][i]*b.p[i][col];
            }
            result.p[row][col] = sum;
        }
    }
    result.prepare();
    return result;
}

int main(void){
    srand((unsigned)time(NULL));
    // 测试快速转置算法
    Matrix matrix(16,16);
    matrix.generateSparseMatrix();
    matrix.printMatrix();
    TripleArr mt_arr = TripleArr(matrix);
    mt_arr.printArr();
    mt_arr.reversoWithOriginalMatrix(matrix);
    mt_arr.printArr();
    matrix.rebuildFromTripleArr(mt_arr);
    matrix.printMatrix();
    
    std::cout<<std::endl;

    // 实现矩阵乘法
    Matrix m1(5,6);
    Matrix m2(6,5);
    m1.generateSparseMatrix(300);
    m2.generateSparseMatrix(300);
    m1.printMatrix();
    m2.printMatrix();
    std::cout<<"multiply.."<<std::endl;
    matrixMult(m1,m2).printMatrix();
}

// ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
// Author: redh3t
// TimeStamp: 2022/10/13
// 相对上一次作业，本次作业我实现了快速转置算法
// 见TripleArr类的reversoWithOriginalMatrix方法
// 还设置了稀疏度的控制，默认是生成稀疏矩阵
// 当generate函数给定0-999的参数时就可以控制稀疏度，例如我测试的时候给了300
// 同时我实现了两个Matrix的乘法运算，返回的结果也是Matrix类的一个对象
// ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;