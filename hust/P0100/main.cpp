#include <cstdio>
#include <iostream>

// define ONLINE_JUDGE

#ifndef ONLINE_JUDGE
#define DEBUG(X) X
#else
#define DEBUG(X) 
#endif

using namespace std;

// 黄 -> 红 -> 绿
int settings[3];

int main () {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    setbuf(stdout, NULL);
    #endif
    cin >> settings[1] >> settings[0] >>settings[2];
    int mod = settings[0] + settings[1] + settings[2];
    int green = settings[0] + settings[1];
    int count;
    cin >> count;
    int time = 0;
    for(int i=0;i<count;i++) {
        int ty, ttime; cin >> ty >> ttime;
        if (ty == 0) {
            time += ttime;
        } else {
            
            if (ty == 2) {ty = 1;}
            else if (ty == 1) {ty = 2;}
            // 1 -> 黄 2-> 红
            int state = 0;
            for(int i=0;i<ty-1;i++) {
                state += settings[i];
            }
            state += (settings[ty-1] - ttime);
            // 红绿灯出发时状态
            state += time;
            state = state % mod;
            // 红绿灯到达时状态
            if(state < green) {
                time += green - state;
            }
        }
    }
    printf("%d\n", time);
    return 0;
}