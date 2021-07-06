#include <cstdio>
#include <iostream>

#ifndef ONLINE_JUDGE
#define DEBUG(X) X
#else
#define DEBUG(X) 
#endif

using namespace std;

int arr[9] = {-1, 0, 0, 3, 3, 3, 7, 8, 9};

int lower_bound(int left, int right, int target) {
    while(left < right) { // 左闭右开性质：相等时区间为零
        int mid = left + (right - left) / 2; // 防溢出
        if (arr[mid] < target) { // 选择的点在目标（3）左边
            left = mid + 1; // 左闭，所以要多向右一点
        } else { // 选择的点在3中间或者右边
            right = mid; // 右开，所以mid不包含
        }
    }
    return left; // 记得返回值
}
        // if (arr[mid] <= target) {

int arr2[10] = {9, 8, 7, 7, 3, 3, 3, 0, 0, -1};

int lower_bound2(int left, int right, int target) {
    while(left < right) { // 左闭右开性质：相等时区间为零
        int mid = left + (right - left) / 2; // 防溢出
        if (arr2[mid] > target) { // 选择的点在目标（3）左边
            left = mid + 1; // 左闭，所以要多向右一点
        } else { // 选择的点在3中间或者右边
            right = mid; // 右开，所以mid不包含
        }
    }
    return left; // 记得返回值
}

int main () {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    #endif
    int count;
    std::cin >> count;
    int lb = lower_bound(0, 9, 3); 
    printf("result: %d -> %d\n", lb, arr[lb]);
    lb = lower_bound2(0, 10, 3); 
    printf("result: %d -> %d\n", lb, arr2[lb]);

    return 0;
}