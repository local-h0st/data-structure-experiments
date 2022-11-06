#include <iostream>

#define STR_NOT_FOUND -1
#define STR_EMPTY_INPUT -2

int strpos(char * pattern, char * strr){
    if (*pattern=='\0'||*strr=='\0')
        return STR_EMPTY_INPUT;
    int pos = 0;
    while (*strr!='\0'){
        char * p = pattern;
        char * s = strr;
        while (true){
            if (*p!=*s){
                break;
            }
            else{
                ++p;
                ++s;
                if (*s=='\0'&&*p!='\0')
                    return STR_NOT_FOUND;
                else if (*s!='\0'&&*p!='\0')
                    continue;
                else    // found and return
                    return pos;
            }
        }
        ++strr;
        ++pos;
    }
    return STR_NOT_FOUND;  // haven't found in loop
}

void printRst(char * pattern, char * strr){
    int index = 0;
    index = strpos(pattern,strr);
    if (index==STR_EMPTY_INPUT)
        std::cout<<"pattern or string empty."<<std::endl;
    else if (index==STR_NOT_FOUND)
        std::cout<<"\""<<pattern<<"\" cannot be found in string \""<<strr<<"\"."<<std::endl;
    else
        std::cout<<"\""<<pattern<<"\" was found at "<<index<<" in string \""<<strr<<"\"."<<std::endl;
}

int main(void){
    char strr[] = "Hello redh3t, welcome to fiki's data structure class!";
    printRst("redh3t",strr);
    printRst("fiki",strr);
    printRst("H",strr);
    printRst("!",strr);
    printRst("bad",strr);
    printRst("",strr);
    printRst("yeah","yea");

}