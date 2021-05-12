#include <cstdio>
#include <iostream>

#ifndef ONLINE_JUDGE
#define DEBUG(X) X
#else
#define DEBUG(X) 
#endif

int digit_num;
char* buf;


bool is_prime(int prime) {
    for(int i=2;i * i < prime;i++) {
        if(prime % i == 0) {
            return false;
        }
    }
    return true;
}

int main () {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    #endif
    int count;
    std::cin >> count >> digit_num;
    buf = new char[count + digit_num + 2];
    std::cin.getline(buf, count+4); // empty
    std::cin.getline(buf, count+4);
    // printf("%s", buf);

    
    for(int i=digit_num; buf[i-1];i++) {
        char tmp = buf[i];
        buf[i] = '\x00';
        int integer;
        sscanf(buf+i-digit_num,"%d",&integer);
        // printf("%d\n", integer);
        if (is_prime(integer)) {
            printf("%0*d\n", digit_num, integer);
            exit(0);
        }
        buf[i] = tmp;
    }

    printf("404\n");

    return 0;
}