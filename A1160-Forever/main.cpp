#include <cstdio>
#include <iostream>
#include <vector>

#ifndef ONLINE_JUDGE
#define DEBUG(X) X
#else
#define DEBUG(X) 
#endif

int gcd(int a, int b) {
    int big = a;
    int small = b;
    if (b > a) {
        big = b;
        small = a;
    }
    int tmp;
    while(small > 0) {
        tmp = big % small; // tmp < small
        printf("%d %% %d = %d\n", big, small, tmp);
        big = small;
        small = tmp;
    }
    return big;
}

std::vector<int> arrange_vec;
int arrange_sum;
void arrange(int num_count,int sum) {
    if (num_count == 0) {
        if (sum != 0) {
            return;
        }
        printf("%d ",arrange_sum);
        // print_vec(arrange_vec);
        printf("\n");
    } else if (num_count == 1) {
        // 不能是0，
    } else {
        // not in possible range 剪枝
        if (sum < 1 || sum > (9*num_count)) {
            return;
        }
        for(int i=0;i<9;i++) {
            arrange_vec.push_back(i);
            arrange(num_count-1, sum-i);
            arrange_vec.pop_back();
        }
    }
}

int main () {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    #endif
    int count;
    std::cin >> count;
    for(int round=1;round <= count;round++) {
        printf("Case %d\n",round);
        int digit_num, digit_sum;
        std::cin >> digit_num >> digit_sum;
        int num_of_9 = (digit_sum+1)/9;
        std::vector<int> init; for(int i=0;i<num_of_9;i++) init.push_back(9);
        for(int sum2=(digit_sum+1)%9;sum2<=digit_sum+1;sum2+=9,num_of_9--,init.pop_back()) {

            int rest_num_count = digit_num - num_of_9;
            // 还需要安排 rest_num_count个数字，其中开头不能是0，末尾不能是9。
            // 和是sum2。
            DEBUG(printf("sum2: %d, num_of_9: %d, \n",sum2, num_of_9);)
            if(num_of_9 > digit_num) {
                DEBUG(printf("bad num_of_9");)
                continue;
            }
            if (gcd(sum2, digit_sum) <= 2) {
                DEBUG(printf("bad gcd");)
                continue;
            }
            
            arrange_vec = init;
            arrange_sum = sum2;
            arrange(rest_num_count, sum2);
        }
    }

    return 0;
}