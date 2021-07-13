#include <stdio.h>

#ifndef ONLINE_JUDGE
#define DEBUG(X) X
#else
#define DEBUG(X) 
#endif

int main () {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    setbuf(stdout, NULL);
    #endif
    int count;
    scanf("%d", &count);

    return 0;
}