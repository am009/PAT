#include <cstdio>
#include <iostream>
#include <algorithm>

int* sorted;
int* level_order_arr;
int count;

// index 比原来多1
int current = 0;
void fill(int root) {
    if (root > count) { return; }
    fill(2*root);
    level_order_arr[root - 1] = sorted[current++];
    fill(2*root +1);
}

int main () {
    std::cin >> count;
    sorted = new int[count];
    level_order_arr = new int[count];
    for(int i=0;i<count;i++) {
        std::cin >> sorted[i];
        level_order_arr[i] = 0;
    }
    std::sort(sorted, sorted + count);

    fill(1);

    for(int i=0;i<count;i++) {
        if (i==0){
            printf("%d",level_order_arr[i]);
        } else {
            printf(" %d",level_order_arr[i]);
        }
    }

    return 0;
}