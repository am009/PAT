#include <cstdio>
#include <iostream>

#ifndef ONLINE_JUDGE
#define DEBUG(X) X
#else
#define DEBUG(X) 
#endif

int * statements;
bool * lies;

int main () {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    #endif
    int count;
    std::cin >> count;
    statements = new int[count+1];
    for(int i=1;i<=count;i++) {
        std::cin >> statements[i];
        // if (statements[i] > 0) {
        //     statements[i] --;
        // } else {
        //     statements[i] ++;
        // }
    }
    DEBUG(for(int i=1;i<=count;i++) { printf("%d ", statements[i]); } printf("\n"); )
    
    lies = new bool[count+1];
    for(int l1=1;l1<=count;l1++) {
        for(int l2=l1+1;l2 <= count;l2++) {
            // l1 和 l2 说谎
            // 枚举说谎情况。记录说谎的人数
            int lie_count = 0;
            for(int i=1;i<=count;i++) {
                bool result;
                if (statements[i] > 0) {
                    if (statements[i] != l1 && statements[i] != l2) {
                        result = true; // 指对了好人
                    } else {
                        result = false; lie_count ++; // 指错了好人
                    }
                } else {
                    int stat = - statements[i];
                    if (stat != l1 && stat != l2) {
                        result = false; lie_count ++; // 指错了坏人
                    } else {
                        result = true; // 指对了坏人
                    }
                }
                lies[i] = result;
            }
            DEBUG(printf("%d %d\n", l1, l2);)
            DEBUG(for(int i=1;i<=count;i++) { printf("%d ", lies[i]); } printf("\n"); )
            if (lie_count != 2) {
                continue;
            }
            // 是否狼人只有一个说谎。
            if (lies[l1] == lies[l2]) {
                continue;
            }
            printf("%d %d\n", l1, l2);
            
            exit(0);
        }
    }

    printf("No Solution\n");

    return 0;
}