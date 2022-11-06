#include <iostream>
#define END_OF_NEXT_ARR -1
#define PATTERN_NOT_FOUND -2

void generateNextArr(char * pattern, int * next){
    int i = 1;
    next[0] = 0;
    while (pattern[i]!='\0'){
        int index_to_compair = next[i-1];
        while (true){
            if (pattern[i]==pattern[index_to_compair]){
                next[i] = index_to_compair + 1;
                break;
            }
            else{
                if (index_to_compair==0){
                    next[i] = 0;
                    break;
                }
                else{
                    index_to_compair = next[index_to_compair-1];
                }
            }
        }
        ++i;
    }
    next[i] = END_OF_NEXT_ARR;
}

int matchStr(char * strr, char * pattern, int * next){
    int to_compair = 0;
    int i = 0;
    while (strr[i]!='\0'){
        if (strr[i]!=pattern[to_compair]){
            if (pattern[to_compair]=='\0'){
                std::string tmp(pattern);
                return i - tmp.length();
            }
            else if (to_compair!=0){
                to_compair = next[to_compair-1];
            }
            else{
                ++i;
            }
        }
        else{
            ++i;
            ++to_compair;
        }

    }
    return PATTERN_NOT_FOUND;
}

int main(void){
    char pattern[] = "aacacaacacc";
    int next[18];
    // 生成并输出next arr
    generateNextArr(pattern,next);
    int * n = next;
    std::cout<<"[next arr][ ";
    while (*n!=END_OF_NEXT_ARR){
        std::cout<<*n<<" ";
        ++n;
    }
    std::cout<<"]"<<std::endl;

    char strr[] = "dfffuyfyaacacaacaccdfghgtc";
    std::cout<<"pattern '"<<pattern<<"' at index "<<matchStr(strr,pattern,next)<<" in string '"<<strr<<"'"<<std::endl;
}























// ;;;;;;;;;;;;;;
// KMP 
// Author: redh3t
// ;;;;;;;;;;;;;;