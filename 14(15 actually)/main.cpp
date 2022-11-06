#include <iostream>
#include <cstdlib>
#include <time.h>

struct NODE{
    int data;
    NODE* l;
    NODE* r;
};

bool insertNode(NODE* root, int data){
    if (data<root->data){
        if (root->l==nullptr){
            root->l = new NODE{data, nullptr, nullptr};
            return true;
        }
        else{
            return insertNode(root->l, data);
        }
    }
    else if (data>root->data){
        if (root->r==nullptr){
            root->r = new NODE{data, nullptr, nullptr};
            return true;
        }
        else{
            return insertNode(root->r, data);
        }
    }
    else{
        // already exists, insert not allowed
        return false;
    }
}

void printTree(NODE* root){
    if (root==nullptr){

    }
    else{
        printTree(root->l);
        std::cout<<root->data<<" ";
        printTree(root->r);
    }
}

struct NODE_FIND_RESULT{
    bool found;
    int data;
    NODE* parent;
    NODE* pos;
};

NODE_FIND_RESULT findNode(NODE* root, int data_to_search){  // 这里用递归也能写
    NODE* parent_node = nullptr;
    NODE* current_node = root;
    while (true){
        if (current_node->data==data_to_search){
            return NODE_FIND_RESULT{true, data_to_search, parent_node, current_node};
        }
        else if (data_to_search<current_node->data){
            if (current_node->l==nullptr){
                return NODE_FIND_RESULT{false, data_to_search, nullptr, nullptr};
            }
            else{
                parent_node = current_node;
                current_node = current_node->l;
            }
        }
        else{
            if (current_node->r==nullptr){
                return NODE_FIND_RESULT{false, data_to_search, nullptr, nullptr};
            }
            else{
                parent_node = current_node;
                current_node = current_node->r;
            }
        }
    }
}

int deleteNode(NODE* &node, NODE* parent_node){
    int data_poped = node->data;
    if (node->l==nullptr&&node->r==nullptr){
        if (parent_node!=nullptr){
            if (parent_node->l==node){
                parent_node->l = nullptr;
            }
            else if (parent_node->r==node){
                parent_node->r = nullptr;
            }
        }
        delete node;
        if (parent_node==nullptr){
            node = nullptr;
        }
    }
    else if (node->l!=nullptr){ // 左非空
        NODE* parent = node;
        NODE* max_in_left = node->l;
        while (max_in_left->r!=nullptr){
            parent = max_in_left;
            max_in_left = max_in_left->r;
        }
        node->data = deleteNode(max_in_left, parent);
    }
    else{   // 左空右非空
        NODE* parent = node;
        NODE* min_in_right = node->r;
        while (min_in_right->l!=nullptr){
            parent = min_in_right;
            min_in_right = min_in_right->l;
        }
        node->data = deleteNode(min_in_right, parent);
    }
    return data_poped;
}

int main(void){
    srand((unsigned)time(NULL));
    int length = 16 + rand()%50;
    int list[length];
    for (int i=0; i<length; ++i){
        list[i] = -1;
    }
    for (int i=0; i<length; ++i){
        int data_to_insert;
        while (true){
            data_to_insert = rand()%100;
            bool already_exists = false;
            for (int i=0; list[i]!=-1; ++i){
                if (list[i]==data_to_insert){
                    already_exists = true;
                    break;
                }
            }
            if (already_exists){
                continue;   // 如果随机范围比length小那么一定会死循环，原因是代数层面而非代码层面
            }
            else{
                break;
            }
        }
        list[i] = data_to_insert;
    }
    // list随机生成完毕
    NODE* BSTroot = new NODE{list[0], nullptr, nullptr};
    for (int i=1; i<length; ++i){
        insertNode(BSTroot, list[i]);
    }
    // 输出list
    for (int i=0; i<length; ++i){
        std::cout<<list[i]<<" ";
    }
    std::cout<<std::endl;
    // 按照list生成BST完成
    printTree(BSTroot); // 输出
    std::cout<<"\n删除:\n";
    // while (BSTroot!=nullptr){
    //     std::cout<<deleteNode(BSTroot, nullptr)<<" ";
    // }
    // std::cout<<std::endl;
    for (int i=0; i<length; ++i){
        NODE_FIND_RESULT to_delete = findNode(BSTroot,list[i]);
        std::cout<<deleteNode(to_delete.pos, to_delete.parent)<<" ";
    }
}

// ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
// Author: redh3t
// TimeStamp: 2022/11/6
// 这次写的个人感觉逻辑明确，思路清晰
// 是一次对所学知识很优雅的实践
// Nice!
// ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;