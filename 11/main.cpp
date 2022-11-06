#include <iostream>
#include <cstdlib>
#include <time.h>
#define DEPTH 6

struct TREENODE{
    int data;
    TREENODE *l;
    TREENODE *r;
};
void createTree(TREENODE *node, int depth){
    node->l = new TREENODE{rand()%100,nullptr,nullptr};
    node->r = new TREENODE{rand()%100,nullptr,nullptr};  
    if (depth>2){
        createTree(node->l,depth-1);
        createTree(node->r,depth-1);
    }
    // 递归生成满二叉树
}
void printTree(TREENODE *node, int mode){
    if (node->l==nullptr&&node->r==nullptr){
        std::cout<<node->data<<" ";
    }
    else{
        if (mode==0){
            std::cout<<node->data<<" ";
            printTree(node->l, 0);
            printTree(node->r, 0);
        }
        else if (mode==2){
            printTree(node->l, 2);
            printTree(node->r, 2);
            std::cout<<node->data<<" ";
        }
        else{
            printTree(node->l, 1);
            std::cout<<node->data<<" ";
            printTree(node->r, 1);
        }
    }
}
void deleteTree(TREENODE *node){
    if (node->l->l==nullptr){
        delete node->l;
        delete node->r;
    }
    else{
        deleteTree(node->l);
        deleteTree(node->r);
    }
    delete node;
}



struct STACKELEM{
    TREENODE *nodeptr;
    STACKELEM *next;
    int flag;
};
void pushElem(STACKELEM* &top, TREENODE *p){
    top = new STACKELEM{p, top};
}
TREENODE* popElem(STACKELEM* &top){
    if (top==nullptr){
        return nullptr;
    }
    TREENODE *p = top->nodeptr;
    STACKELEM *to_del = top;
    top = top->next;
    delete to_del;
    return p;
}

void printTreeUsingStack(TREENODE *node, int mode){
    STACKELEM *base = new STACKELEM{nullptr,nullptr};
    STACKELEM *top = base;
    if (mode==0){   // 前序遍历
        while (node!=nullptr||top!=base){
            while (node!=nullptr){
                std::cout<<node->data<<" ";
                pushElem(top, node);
                node = node->l;
            }
            node = top->nodeptr->r;
            popElem(top);
        }
    }
    else if (mode==1){  // 中序遍历
        while (node!=nullptr||top!=base){
            while (node!=nullptr){
                pushElem(top, node);
                node = node->l;
            }
            std::cout<<popElem(top)->data<<" "; // 左
            if (top->nodeptr==nullptr){ // 最后一个节点
                break;
            }
            else{
                node = top->nodeptr->r;
                std::cout<<popElem(top)->data<<" "; // 中    
            }
        }
    }
    else{   // 后序遍历
        while (true){
            while (node!=nullptr){
                pushElem(top,node);
                top->flag = false;  // false表示当前节点的右子树尚未被访问过
                node = node->l;
            }
            std::cout<<popElem(top)->data<<" "; // 左
            if (top->flag==true){   // 左右都已经被访问了，现在访问中
                std::cout<<popElem(top)->data<<" ";
                if (top->nodeptr==nullptr){
                    break;
                }
                if (top->flag==false){
                    node = top->nodeptr->r;
                    top->flag = true;
                }
                else{
                    // node这时候刚好就是nullptr
                }
            }
            else{   // 访问右子树，并更新flag状态为true
                if (top->nodeptr==nullptr){
                    break;
                }
                node = top->nodeptr->r;
                top->flag = true;
            }

        }
    }

    while (top!=nullptr){   // 删除栈
        popElem(top);
    }
}

int main(void){
    srand((unsigned)time(NULL));
    TREENODE *root = new TREENODE{1,nullptr,nullptr};
    root->l = new TREENODE{11,nullptr,nullptr};
    root->r = new TREENODE{12,nullptr,nullptr};
    root->l->l = new TREENODE{111,nullptr,nullptr};
    root->l->r = new TREENODE{112,nullptr,nullptr};
    root->r->l = new TREENODE{121,nullptr,nullptr};
    root->r->r = new TREENODE{122,nullptr,nullptr};

    std::cout<<"前序"<<std::endl;
    printTree(root, 0);
    std::cout<<std::endl;
    printTreeUsingStack(root, 0);
    std::cout<<std::endl;

    std::cout<<"中序"<<std::endl;
    printTree(root, 1);
    std::cout<<std::endl;
    printTreeUsingStack(root, 1);
    std::cout<<std::endl;

    std::cout<<"后序"<<std::endl;
    printTree(root, 2);
    std::cout<<std::endl;
    printTreeUsingStack(root, 2);
    std::cout<<std::endl;

    deleteTree(root);
    root = nullptr;



    std::cout<<"随机生成完全树，后序遍历"<<std::endl;
    root = new TREENODE{16,nullptr,nullptr};
    createTree(root,DEPTH);
    printTree(root, 2);
    std::cout<<std::endl;
    printTreeUsingStack(root, 2);
    std::cout<<std::endl;

    deleteTree(root);
    root = nullptr;
}

// ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
// Author: redh3t
// TimeStamp: 2022/10/22
// 当逻辑复杂的时候代码总是很难优雅起来...
// 逻辑一复杂就很容易猪脑过载...
// （尽管最终能够符合预期地输出）
// ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;