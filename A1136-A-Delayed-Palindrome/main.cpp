#include <cstdio>
#include <iostream>
#include <cstring>

#ifndef ONLINE_JUDGE
#define DEBUG(X) X
#else
#define DEBUG(X) 
#endif

char bufA[1010];
char bufB[1010];
char bufC[1010];


int chr2dig (char c) {
    if ( c < '0' || c > '9' ) {
        DEBUG(printf("#err1#");)
    }
    return c - '0';
}

bool is_pali(char* str) {
    int len = strlen(str);
    for(int i=0;i<=len/2;i++) {
        if (str[i] != str[len-1-i]) {
            return false;
        }
    }
    return true;
}

void num_rev(char* from, char* to) {
    int len = strlen(from);
    if (len > 1004) {
        DEBUG(printf("#err2#");)
    }
    for(int i=0;i<len;i++) {
        // from[i]
        to[len-1-i] = from[i];
    }
}

void rev_print(char* s) {
    int len = strlen(s);
    for(int i=0;i<len;i++){
        putchar(s[len-1-i]);
    }
}

// 加完后低位在前，高位在后。需要倒着打印。
void pali_add(char* from , char* to) {
    int len = strlen(from);
    int upcount = 0;
    for(int i=0; i<len;i++) {
        int dig_a = chr2dig(from[i]);
        int dig_b = chr2dig(from[len-1-i]);
        int result = upcount + dig_a + dig_b;
        upcount = result / 10;
        to[i] = result % 10 + '0';
    }
    if (upcount != 0) {
        to[len] = upcount+'0';
    }
}


int main () {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    #endif
    std::cin >> bufA;
    
    char* from = bufA;
    char* rev = bufB;
    char* to = bufC;

    // num_rev(bufA, bufB);
    // pali_add(bufA, bufC);
    // std::cout << bufC;
    if (is_pali(from)) { // !!!!! 无语
        printf("%s is a palindromic number.\n", from);
        return 0;
    }
    for(int round=0;round<10;round++) {
        std::cout << from;
        printf(" + ");
        rev_print(from);
        printf(" = ");
        pali_add(from, to);
        // rev_print(to);
        num_rev(to, from);
        std::cout << from << std::endl;
        if (is_pali(from)) {
            printf("%s is a palindromic number.\n", from);
            return 0;
        }
    }
    printf("Not found in 10 iterations.\n");

    return 0;
}