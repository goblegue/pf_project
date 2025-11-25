#ifndef CHAR_HPP
#define CHAR_HPP

inline int lengthOfCharArray(const char arr[]){
    int length = 0;
    while (arr[length] != '\0'){
        length++;
    }
    return length;
};

inline void charToString(const char c,char str[2]){
    str[0] = c;
    str[1] = '\0';
}

#endif 