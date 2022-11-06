#include <iostream>
#include <cstdlib>
#include <time.h>
#define DEPTH 5

struct NODE{
    int data;
    bool l_is_link;
    bool r_is_link;
    NODE* l;
    NODE* r;
};

void deleteTree(NODE* node, bool has_thread = false){   //递归传递根，线索传递第一个
    if (has_thread){
        NODE* start = node;
        if (start==nullptr){
        }
        else{
            // 查找next
            NODE* next = nullptr;
            if (start->r_is_link){  // 无右子树
                next = start->r;
            }
            else{
                next = start->r;
                if (next!=nullptr){
                    while (next->l_is_link==false){
                        next = next->l;
                    }        
                }
            }
            deleteTree(next,true);
            delete start;
        }
    
    }
    else{
        if (node!=nullptr){
            deleteTree(node->l);
            deleteTree(node->r);
            delete node;
        }
    }

}

int countLayers(NODE* root){
    if (root==nullptr){
        return 0;
    }
    else{
        int l_count = countLayers(root->l);
        int r_count = countLayers(root->r);
        if (l_count>=r_count){
            return 1 + l_count;
        }
        else{
            return 1 + r_count;
        }
    }
}

void randomGenerate(NODE* &root, int depth){
    NODE* p_pre;
    NODE* p;
    while (countLayers(root)<=depth){
        p_pre = root;
        p = root;
        if (rand()%2==0){
            p = p->l;
        }
        else{
            p = p->r;
        }
        while (p!=nullptr){
            if (rand()%2==0){
                p_pre = p;
                p = p->l;
            }
            else{
                p_pre = p;
                p = p->r;
            }
        }
        if (p_pre->l==nullptr&&p_pre->r==nullptr){
            if (rand()%2==0){
                p_pre->l = new NODE{rand()%100, false, false, nullptr, nullptr};
            }
            else{
                p_pre->r = new NODE{rand()%100, false, false, nullptr, nullptr};
            }
        }
        else if (p_pre->l==nullptr){
            p_pre->l = new NODE{rand()%100, false, false, nullptr, nullptr};
        }
        else{
            p_pre->r = new NODE{rand()%100, false, false, nullptr, nullptr};
        }  
    }
    if (p_pre->l!=nullptr){
        delete p_pre->l;
        p_pre->l = nullptr;
    }
    else{
        delete p_pre->r;
        p_pre->r = nullptr;
    }
}

void printTreeWithThread(NODE* start, bool start_from_right=false){
    if (start_from_right){
        if (start==nullptr){
            std::cout<<"done"<<std::endl;
        }
        else{
            std::cout<<start->data<<" ";
            // 查找next
            NODE* next = nullptr;
            if (start->l_is_link){  // 无左子树
                next = start->l;
            }
            else{
                next = start->l;
                if (next!=nullptr){
                    while (next->r_is_link==false){
                        next = next->r;
                    }        
                }
            }
            printTreeWithThread(next,true);
        }
    }
    else{
        if (start==nullptr){
            std::cout<<"done"<<std::endl;
        }
        else{
            std::cout<<start->data<<" ";
            // 查找next
            NODE* next = nullptr;
            if (start->r_is_link){  // 无右子树
                next = start->r;
            }
            else{
                next = start->r;
                if (next!=nullptr){
                    while (next->l_is_link==false){
                        next = next->l;
                    }        
                }
            }
            printTreeWithThread(next);
        }
    }
}

void printNode(NODE* node){
    std::cout<<"addr: "<<node<<" data: "<<node->data<<" l_is_link: "<<node->l_is_link<<" r_is_link: "<<node->r_is_link<<" left: "<<node->l<<" right: "<<node->r<<std::endl;
}

NODE* getHaed(NODE* root){
    if (root->l!=nullptr){
        return getHaed(root->l);
    }
    else{
        return root;
    }
}

NODE* getTail(NODE* root){
    if (root->r==nullptr){
        return root;
    }
    else{
        return getTail(root->r);
    }
}

NODE* pre = nullptr;
void process(NODE* p){
    if (p==nullptr){
        return;
    }
    process(p->l);
    if (p->l==nullptr){
        p->l_is_link = true;
        p->l = pre;
    }
    if (pre!=nullptr){
        if (pre->r==nullptr&&pre->r_is_link==false){
            pre->r_is_link = true;
            pre->r = p;
        }
    }
    pre = p;
    process(p->r);
}

int main(void){
    srand((unsigned)time(NULL));
    NODE* root = new NODE{1, false, false, nullptr, nullptr};
    root->l = new NODE{11, false, false, nullptr, nullptr};
    root->r = new NODE{12, false, false, nullptr, nullptr};
    root->l->l = new NODE{111, false, false, nullptr, nullptr};
    root->r->l = new NODE{121, false, false, nullptr, nullptr};
    root->r->l->r = new NODE{1212, false, false, nullptr, nullptr};
    process(root);
    printNode(root);
    printNode(root->l);
    printNode(root->r);
    printNode(root->l->l);
    printNode(root->r->l);
    printNode(root->r->l->r);
    printTreeWithThread(root->l->l);
    printTreeWithThread(root->r,true);
    deleteTree(root, true);


    root = new NODE{1, false, false, nullptr, nullptr};
    randomGenerate(root, DEPTH);
    NODE* start = getHaed(root);
    NODE* end = getTail(root);
    pre = nullptr;
    process(root);
    printTreeWithThread(start);
    printTreeWithThread(end,true);
    deleteTree(root, true);
}
// ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
// Author: redh3t
// 我真服了全是坑，，调了两个下午才调出来结果
// 各种地方指针一不注意就乱，if顺序一改就不对
// 以及那个pre指针，，忘记置空了，查了很久的
// 代码才反应过来是pre的锅，，可恶
// 调试太痛苦了，好在终于是全部写下来了，
// 细节问题算是都搞清楚了。
// ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;