#include <iostream>

struct CHAR_INFO{
    char character;
    int code_decimo;    // 为了方便，01的编码用21来代替
    std::string code;
};

struct NODE{
    bool is_leaf;
    CHAR_INFO char_info;    // 是叶子节点时该项才有意义
    int times;  // 出现次数
    NODE* next; // 单链表时用到,制作成Huffman树之后应该置空
    NODE* l;    // huffman树要用到，制作之前应该置空
    NODE* r;    // huffman树要用到，制作之前应该置空
};

void printHuffmanTree(NODE* root){
    if (root!=nullptr){ // 前序
        if (root->is_leaf){
            std::cout<<"[leaf]char: "<<root->char_info.character;
        }
        std::cout<<" times: "<<root->times;
        if (root->l!=nullptr){
            std::cout<<" l_times: "<<root->l->times;
        }
        if (root->r!=nullptr){
            std::cout<<" r_times: "<<root->r->times;
        }
        std::cout<<std::endl;
        printHuffmanTree(root->l);
        printHuffmanTree(root->r);
    }
}

void printLeafLink(NODE* ptr_for_view, bool has_info=false){
    while (ptr_for_view->next!=nullptr){
        std::cout<<ptr_for_view->char_info.character<<": "<<ptr_for_view->times<<" --is_leaf="<<ptr_for_view->is_leaf;
        if (has_info){
            std::cout<<" code: "<<ptr_for_view->char_info.code_decimo<<" | "<<ptr_for_view->char_info.code;
        }
        std::cout<<std::endl;
        ptr_for_view = ptr_for_view->next;
    }
    if (has_info){
        std::cout<<ptr_for_view->char_info.character<<": "<<ptr_for_view->times<<" --is_leaf="<<ptr_for_view->is_leaf;
        std::cout<<" code: "<<ptr_for_view->char_info.code_decimo<<" | "<<ptr_for_view->char_info.code;
        std::cout<<std::endl;
    }
}

void setLeafNodeAndCreateLink(NODE* &headptr ,NODE* node, int code_dec){
    // next在设置Huffman树的时候必须设置nullptr因为要对森林处理，现在可以利用next重建link
    if (node->is_leaf){
        node->char_info.code_decimo = code_dec;
        node->next = headptr;
        headptr = node;
    }
    else{
        setLeafNodeAndCreateLink(headptr, node->l, code_dec*10+2);
        setLeafNodeAndCreateLink(headptr, node->r, code_dec*10+1);
    }
}

std::string encodeHuffman(NODE* info_link, std::string data){
    std::string result = "";
    for (int i=0;i<data.length();++i){
        NODE* roarptr = info_link;
        while (roarptr->char_info.character!=data[i]&&roarptr!=nullptr){
            roarptr = roarptr->next;
        }
        result = result + roarptr->char_info.code;
    }
    return result;
}

std::string decodeHuffman(NODE* info_link, std::string data){
    int current_char_start_pos = 0;
    std::string result = "";
    // std::cout<<"encoded data length: "<<data.length()<<std::endl;
    while (current_char_start_pos<data.length()){
        int len = 1;
        while (true){
            std::string code = data.substr(current_char_start_pos,len);
            bool code_found = false;
            std::string character = "";
            NODE* roarptr = info_link;    
            while (roarptr!=nullptr){
                if (roarptr->char_info.code==code){
                    code_found = true;
                    character = roarptr->char_info.character;
                    break;
                }
                else{
                    roarptr = roarptr->next;
                }
            }
            if (code_found){
                result += character;
                current_char_start_pos += len;
                break;
            }
            else{
                ++len;
            }
        }
    }
    return result;
}

int main(void){
    int size = 32;
    char str[size] = "helloreeeddeddhhh3hellllllh3ttt";
    // 统计所有字符以及出现次数，它们是将来的叶子节点
    NODE* forest = new NODE{false,CHAR_INFO{},NULL,nullptr,nullptr,nullptr};
    for (int i=0; str[i]!='\0'; ++i){
        char current_char = str[i];
        std::cout<<"current char: "<<current_char<<std::endl;
        bool has_been_recorded = false;
        NODE* tmp = forest;
        while (tmp->next!=nullptr){
            if (tmp->char_info.character==current_char){
                std::cout<<"char "<<current_char<<": "<<tmp->times<<" -> ";
                has_been_recorded = true;
                ++tmp->times;
                std::cout<<tmp->times<<std::endl;
                break;
            }
            tmp = tmp->next;
        }
        if (!has_been_recorded){
            std::cout<<"adding "<<current_char<<"..."<<std::endl;
            forest = new NODE{true,CHAR_INFO{current_char,NULL},1,forest,nullptr,nullptr};
        }
    }
    // 输出一下结果看看对不对
    printLeafLink(forest);
    
    // 开始制作Huffman树
    while (forest->next->next!=nullptr){   // 森林只剩下一棵树
        NODE* min_1 = nullptr;
        NODE* min_2 = nullptr;
        NODE* tmp = nullptr;
        // 两次遍历forest找最小的，存了之后记得把链表重新连上
        min_1 = forest;
        tmp = forest;
        while (tmp->next!=nullptr){
            if (tmp->times<min_1->times){
                min_1 = tmp;
            }
            tmp = tmp->next;
        }
        std::cout<<"min_1 times: "<<min_1->times<<std::endl;
        if (min_1==forest){
            forest = forest->next;
            min_1->next = nullptr;
        }
        else{
            tmp = forest;
            while (tmp->next!=min_1){
                tmp = tmp->next;
            }
            tmp->next = min_1->next;
            min_1->next = nullptr;
        }
        std::cout<<"---- delete min_1 ----"<<std::endl;
        printLeafLink(forest);
        min_2 = forest;
        tmp = forest;
        while (tmp->next!=nullptr){
            if (tmp->times<min_2->times){
                min_2 = tmp;
            }
            tmp = tmp->next;
        }
        std::cout<<"min_2 times: "<<min_2->times<<std::endl;
        if (min_2==forest){
            forest = forest->next;
            min_2->next = nullptr;
        }
        else{
            tmp = forest;
            while (tmp->next!=min_2){
                tmp = tmp->next;
            }
            tmp->next = min_2->next;
            min_2->next = nullptr;
        }
        std::cout<<"---- delete min_1 ----"<<std::endl;
        printLeafLink(forest);
        // 制作新的NODE并添加到forest
        forest = new NODE{false,CHAR_INFO{},min_1->times+min_2->times,forest,min_1,min_2};
        std::cout<<"---- new forest ----"<<std::endl;
        printLeafLink(forest);
        std::cout<<std::endl;
    }
    printHuffmanTree(forest);
    // 经过验证Huffman树生成正确

    NODE* info_link = nullptr;
    setLeafNodeAndCreateLink(info_link, forest, 0);
    // 输出一下看看
    printLeafLink(info_link, true);
    // 结果正确！接下来把int类型的code_decimo转换成string类型的编码code
    NODE* tmp = info_link;
    while (tmp!=nullptr){
        int decimo = tmp->char_info.code_decimo;
        while (decimo!=0){
            if (decimo%2==0){
                tmp->char_info.code = "0" + tmp->char_info.code;
            }
            else{
                tmp->char_info.code = "1" + tmp->char_info.code;
            }
            decimo = decimo/10;
        }
        tmp = tmp->next;
    }
    printLeafLink(info_link, true);
    // 结果正确，现在可以拿info_link来编码和解码信息了
    std::string data(str);
    std::cout<<"original data: "<<data<<std::endl;
    std::string encoded_data = encodeHuffman(info_link,data);
    std::cout<<"encoded code: "<<encoded_data<<std::endl;
    std::string decoded_data = decodeHuffman(info_link,encoded_data);
    std::cout<<"decoded data: "<<decoded_data<<std::endl;
    // 成功实现编码和解码！
}

// ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
// Author: redh3t
// TimeStamp: 2022/11/1-2 凌晨
// 感慨良多，虽然看似简单，但是要处理
// 的细节问题实在太多，比如叶子节点的
// 生成，比如用叶子节点构建Huffman树
// 再根据Huffman树进行编码并记录对应
// 规则，最后实现编码和解码。细节问题
// 太多，需要很小心，比如哪里什么时候
// 哪里为空，这步操作完成之后链表会变
// 成什么样子等等等等......
// 不过最终还是完整实现了，很爽哈哈哈
// ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;