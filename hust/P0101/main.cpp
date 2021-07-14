#include <cstdio>
#include <iostream>
#include <algorithm>

// define ONLINE_JUDGE

#ifndef ONLINE_JUDGE
#define DEBUG(X) X
#else
#define DEBUG(X) 
#endif

using namespace std;

struct ball{
    int coor;
    int v;
    int index;
    bool operator <(ball& other) const {
        return this->coor < other.coor;
    }
};

struct ind_sort {
    bool operator ()(ball& one, ball& other) {
        return one.index < other.index;
    }
};

int main () {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    setbuf(stdout, NULL);
    #endif
    int n, L, t;
    cin >> n >> L >> t;
    ball* bs = new ball[n];
    for(int i=0;i<n;i++) {
        cin >> bs[i].coor;
        bs[i].v = 1;
        bs[i].index = i;
    }

    for(int ti = t;ti>0;ti--) {
        // 碰撞
        sort(bs, bs+n);
        for(int i=0;i<n;i++) {
            if (bs[i].coor == 0 || bs[i].coor == L) {
                bs[i].v = - bs[i].v;
            }

            if (bs[i].coor == bs[i+1].coor) {
                bs[i].v = - bs[i].v;
                bs[i+1].v = - bs[i+1].v;
                i+=1;
            }
        }
        // 运动
        for(int i=0;i<n;i++) {
            bs[i].coor += bs[i].v;
        }
    }

    sort(bs, bs+n, ind_sort());
    for(int i=0;i<n;i++){
        if (i != n-1) printf("%d ", bs[i].coor);
        else printf("%d\n", bs[i].coor);
    }
    return 0;
}