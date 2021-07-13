#include <stdio.h>

#ifndef ONLINE_JUDGE
#define DEBUG(X) X
#else
#define DEBUG(X) 
#endif

char N1_buf[32];
char N2_buf[32];

unsigned long long tag, radix;

unsigned long long chr2num(char c) {
    if (c >= 'a' && c <= 'z') {
        return c-'a'+10;
    } else if(c >='0' && c <= '9') {
        return c - '0';
    } else if (c >= 'A' && c <= 'Z') {
        return c-'A'+10;
    }else {
        DEBUG(puts("#err1#");)
    }
    return 0;
}

unsigned long long interpreter(char* buf, unsigned long long radix, unsigned long long* lower_boud) {
    unsigned long long ret = 0;
    if (lower_boud != NULL) {
        (*lower_boud) = 1;
    }
    while((*buf) != 0) {
        ret *= radix;
        unsigned long long tmp = chr2num((*buf));
        ret += tmp;
        // find biggest digit
        if (lower_boud != NULL) {
            if (tmp > (*lower_boud)) {
                (*lower_boud) = tmp;
            }
        }
        buf ++;
    }
    return ret;
}

int main () {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    setbuf(stdout, NULL);
    #endif
    scanf("%s%s%I64u%I64u", N1_buf, N2_buf, &tag, &radix);
    char* N1 = N1_buf;
    char* N2 = N2_buf;
    if (tag == 2) {
        N1 = N2_buf;
        N2 = N1_buf;
    }
    unsigned long long lb;
    unsigned long long real_N1 = interpreter(N1, radix, NULL);
    interpreter(N2, 2, &lb); lb++;
    unsigned long long old_lb = lb;
    unsigned long long ub = real_N1 + 1;
    while(lb < ub) {
        unsigned long long mid = lb + (ub - lb) / 2;
        unsigned long long guess = interpreter(N2, mid, NULL);
        if (guess < real_N1) {
            lb = mid + 1;
            
        } else {
            ub = mid;
        }
    }
    // 边界 
    if(lb == real_N1+1) {
        printf("Impossible\n");
        return 0;
    }
    unsigned long long ans = interpreter(N2, lb, NULL);
    if(ans == real_N1) {
        printf("%I64u\n", lb);DEBUG(fflush(stdout);)
    } else {
        printf("Impossible\n");
    }

    return 0;
}