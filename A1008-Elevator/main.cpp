#include <cstdio>
#include <iostream>

#ifndef ONLINE_JUDGE
#define DEBUG(X) X
#else
#define DEBUG(X) 
#endif

int go(int a) {
    if (a < 0) return (-a) * 4;
    return a*6;
}

int main () {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    #endif
    int count;
    std::cin >> count;
    int time = 0;
    int current_floor = 0;
    for(int i=0;i<count;i++) {
        int floor;
        std::cin >> floor;
        time += 5 + go(floor - current_floor);
        current_floor = floor;
    }
    printf("%d\n", time);

    return 0;
}