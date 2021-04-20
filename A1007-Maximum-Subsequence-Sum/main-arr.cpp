#include <cstdio>
#include <iostream>
#include <climits>

#ifndef ONLINE_JUDGE
#define DEBUG(X) X
#else
#define DEBUG(X) 
#endif

int *nums;

int *sums; // 以i结尾的最大sum。必须包含nums[i]
int *start_inds;

int main () {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    #endif
    int count;
    std::cin >> count;
    nums = new int[count];
    
    for(int i=0;i< count;i++) {
        std::cin >> nums[i];
    }
    bool all_negative = true;
    for(int i=0;i<count;i++) {
        if (nums[i] >= 0) {
            all_negative = false;
            break;
        }
    }
    if (all_negative) {
        printf("0 %d %d\n", nums[0], nums[count-1]);
        return 0;
    }

    sums = new int[count];
    start_inds = new int[count];

    int max_ind = -1;
    int max_sum = INT_MIN;
    for(int i=0;i<count;i++) {
        // 以nums[i]结尾的最大子序列，要么是自己独立成序列的，要么是和前面的连在一起的。
        if (i == 0) {
            sums[i] = nums[i];
            start_inds[i] = i;
            goto end;
        }
        if (sums[i-1] < 0) { // 有和为0 的子列就和前面的连到一起。
            sums[i] = nums[i];
            start_inds[i] = i;
        } else {
            sums[i] = sums[i-1] + nums[i];
            start_inds[i] = start_inds[i-1];
        }
end:
        if (sums[i] > max_sum) { // 等于的时候不更新
            max_sum = sums[i];
            max_ind = i;
        }
    }

    DEBUG(printf("%d %d\n", start_inds[max_ind], max_ind);)
    printf("%d %d %d\n", max_sum, nums[start_inds[max_ind]], nums[max_ind]);


    return 0;
}