#include <cstdio>
#include <iostream>
#include <queue>
#include <algorithm>
#include <vector>

// define ONLINE_JUDGE

#ifndef ONLINE_JUDGE
#define DEBUG(X) X
#else
#define DEBUG(X) 
#endif

using namespace std;

struct sum {
    int sum;
    int aind;
    int bind;
};

struct cmp {
    bool operator ()(sum&a, sum&b) {
        return a.sum > b.sum;
    }
};

int main () {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    setbuf(stdout, NULL);
    #endif
    int N;
    scanf("%d",&N);
    int * arra = new int[N];
    int * arrb = new int[N];
    for(int i=0;i<N;i++) {
        scanf("%d", &arra[i]);
    }
    for(int i=0;i<N;i++) {
        scanf("%d", &arrb[i]);
    }
    // bind 小于 level[aind] 的都已经加入队列了。
    int *level = new int[N];
    for(int i=0;i<N;i++) {
        level[i] = 0;
    }
    // bool ** pushed = new bool*[N];
    // for(int i=0;i<N;i++) {
    //     pushed[i] = new bool[N];
    //     for(int j=0;j<N;j++) {
    //         pushed[i][j] = true;
    //     }
    // }

    // print aux
    sort(arra, arra+N);
    sort(arrb, arrb+N);

    // priority_queue<sum, vector<sum>, cmp> q;
    // q.push({arra[0]+arrb[0], 0 ,0});
    //  level[0] = 1;

    bool init = true;
    int count = 0;

    // while(!q.empty()) {
    //     if (count >= N) {
    //         break;
    //     }
    //     sum top = q.top();
    //     q.pop();
        
    //     if(init) {
    //         init = false;
    //         printf("%d", top.sum);
    //     }else {
    //         printf(" %d", top.sum);
    //     }
    //     count ++;
    //     if(top.aind + 1 < N && ) {
    //         sum tmp1 = {arra[top.aind+1]+arrb[top.bind], top.aind+1, top.bind};
    //         q.push(tmp1);
    //         // pushed[top.aind+1][top.bind] = false;
    //     }
    //     if(top.bind + 1 < N && pushed[top.aind][top.bind+1] ) {
    //         sum tmp2 = {arra[top.aind]+arrb[top.bind+1], top.aind, top.bind+1};
    //         q.push(tmp2);
    //         // pushed[top.aind][top.bind+1] = false;
    //     }
    // }

    // int top = 2*(N-1);
    // priority_queue<pair<int,int>, std::vector<pair<int,int>>, cmp> lst;
    priority_queue<int> lst;
    for(int i=0;i<N;i++) {
        lst.push(arra[0]+arrb[i]);
    }
    for(int i=1;i<N;i++) {
        for(int j=0;j<N;j++) {
            int tmp = arra[i] + arrb[j];
            if (tmp < lst.top()) {
                lst.pop();
                lst.push(tmp);
            } else {
                break;
            }
        }
    }

    // int border = arrb[N-1] + arra[0];
    // int border2 = arra[N-1] + arrb[0];

    // for(int sum=0;sum<=top;sum++) {
    //     for(int i=0;i<=sum;i++) {
    //         if (i >= N || (sum-i) >= N) {
    //             continue;
    //         }
    //         // printf("arra[%d]+arrb[%d]\n", i, sum-i);
    //         int tmp = arra[i]+arrb[sum-i];
    //         if (tmp > border || tmp > border2) {
    //             continue;
    //         }
    //         lst.push(tmp);
    //     }
    // }

    int * sta = new int[N];
    count = 0;
    while(!lst.empty()) {
        if(count >= N) {
            break;
        }
        int out = lst.top();
        sta[count] = out;
        lst.pop();
        count ++;
    }
    for(int i=0;i<N;i++) {
        int out = sta[N-i-1];
        if (init) {
            init = false;
            printf("%d", out);
        } else{
            printf(" %d", out);
        }
    }
    return 0;
}