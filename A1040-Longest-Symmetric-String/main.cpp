#include <cstdio>
#include <iostream>
#include <cstring>

#ifndef ONLINE_JUDGE
#define DEBUG(X) X
#else
#define DEBUG(X) 
#endif

char buf[1002]; // !!! 1001就过不了！！！

int symstr[1010][1010];

int main () {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    #endif
    std::cin.getline(buf, 1001);
    int length = strlen(buf);
    if (length == 0) {
        printf("0\n");
        return 0;
    }
    
    DEBUG(printf("len: %d\n", length);)

    int ans = 1;
    for(int i=0;i<length;i++) {
        for(int j=0;j<length-i;j++) { // j+i保证是合法下标
            if(i == 0) {
                symstr[j][j+i] = 1;
                continue;
            }
            if (i == 1) {
                if (buf[j] == buf[j+i]) {
                    symstr[j][j+i] = 1;
                    ans = i+1;
                }
                continue;
            }
            if (buf[j] == buf[j+i] && symstr[j+1][j+i-1]) {
                symstr[j][j+i] = 1;
                ans = i+1;
            } else {
                symstr[j][j+i] = 0;
            }
        }

    }

    printf("%d",ans);


    return 0;
}