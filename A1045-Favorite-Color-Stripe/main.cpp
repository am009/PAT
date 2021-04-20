#include <cstdio>
#include <iostream>
#include <vector>

#ifndef ONLINE_JUDGE
#define DEBUG(X) X
#else
#define DEBUG(X) 
#endif

int *color2ind; // 以color作为下标。如果color取出来是-1，则表示不是喜欢的颜色，如果是正数，则是对应的下标。

int main () {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    #endif
    // for(int i=0;i<201;i++) {
    //     color2ind[i] = -1;
    // }
    int num_color;
    std::cin >> num_color;
    color2ind = new int[num_color+1];
    for(int i=0;i<=num_color;i++) {
        color2ind[i] = -1;
    }

    int seq_count;
    std::cin >> seq_count;
    for(int i=0;i<seq_count;i++) {
        int color;
        std::cin >> color;
        color2ind[color] = i;
    }

    // 输入的同时把不喜欢的颜色去掉，把喜欢的颜色转换成对应的下标
    std::vector<int> stripe;
    int count;
    std::cin >> count;
    for(int i=0;i<count;i++) {
        int color;
        std::cin >> color;
        int ind = color2ind[color];
        if(ind != -1) {
            stripe.push_back(ind);
        }
    }

    // 在stripe上做普通的最大子列和。
    int length = stripe.size();
    int *lens = new int[length];
    for(int i=0;i<length;i++) {
        lens[i] = 1;
    }
    for(int i=0;i<length;i++) {
        bool alone = true;
        for(int j=0;j<i;j++) {
            if(stripe[j] > stripe[i]) { continue; }
            else {
                alone = false;
                // 保证lens[i]最大
                if(lens[j]+1 > lens[i]) {
                    lens[i] = lens[j] + 1;
                }
            }
        }
        // if (alone) { lens[i] = 1; }
    }

    int max_len = -1;
    int max_ind = -1;
    for(int i=0;i<length;i++) {
        if(lens[i] > max_len) {
            max_len = lens[i];
            max_ind = i;
        }
    }

    printf("%d\n", max_len);

    return 0;
}