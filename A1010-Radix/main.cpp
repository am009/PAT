#include <cstdio>
#include <iostream>
#include <string>
#include <algorithm>

#ifndef ONLINE_JUDGE
#define DEBUG(X) X
#else
#define DEBUG(X) 
#endif

using namespace std;

unsigned long long char2num(char a) {
    if (a >= 'a') {
        return 10 + a - 'a';
    } else {
        return a - '0';
    }
}

unsigned long long decode(const char* s, unsigned long long radix) {
    // DEBUG(printf("Decode: %s, %I64u. ", s, radix);)
    unsigned long long ret = 0;
    while((*s) != 0) {
        ret *= radix;
        ret += char2num((*s));
        s++;
        // printf("xxx%I64uxxx\n", ret);
    }
    // DEBUG(printf("result: %I64d\n", ret);)
    return ret;
}

int smallest_radix(const char* s) {
    int ret = 2;
    while((*s) != 0) {
        int rad = char2num((*s)) + 1;
        // printf("xxx%dxxx\n", rad);
        if (rad>ret) {
            ret = rad;
        }
        s++;
    }
    return ret;
}

int main () {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    #endif
    string n1, n2;
    int tag, radix;
    cin >> n1 >> n2 >> tag >> radix;
    if(tag == 2) {
        string tmp = n2;
        n2 = n1;
        n1 = tmp;
    }
    // n1 + radix -> num
    // n2 + iter radix
    // 上下限，然后判断过大还是过小。
    unsigned long long real_n1 = decode(n1.c_str(), radix);
    DEBUG(printf("real_n1:      %I64u\n", real_n1);)
    // return 0;
    unsigned long long decode_n2 = 0; 
    unsigned long long left = smallest_radix(n2.c_str()); 
    unsigned long long right = max(real_n1, left) + 1;
    unsigned long long null_mark = right;
    DEBUG(printf("null: %I64u\n", null_mark);)
    while( left < right ) { // guess_radix <= 36 &&
        unsigned long long mid = left + (right - left) / 2;
        decode_n2 = decode(n2.c_str(), mid);
        DEBUG(printf("#guess_radix: %I64u. decoded: %I64u.$\n",mid, decode_n2);)
        if (decode_n2 < real_n1) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    if (left == null_mark || decode(n2.c_str(), left) != real_n1) {
        printf("Impossible\n");
    } else {
        printf("%I64u\n", left);
    }
    return 0;
}
