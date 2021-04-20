#include <cstdio>

const char* out[] = {"Case #%d: false", "Case #%d: true"};

int cases() {
    long long int a, b, c, tmp;
    scanf("%I64d%I64d%I64d", &a, &b, &c);
    tmp = a + b;
    if (tmp <= 0 && a>0 && b > 0){
        return 1;
    }
    if (tmp >=0 && a<0 && b <0)
    {
        return 0;
    }
    if(tmp > c) {
        return 1;
    } else {
        return 0;
    }
}

int main () {
    int count;
    scanf("%d", &count);
    
    for(int i=1;i<=count;i++){
        int res = cases();
        printf(out[res], i);
        puts("");
    }
}