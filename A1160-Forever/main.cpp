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
        // printf("%d %% %d = %d\n", big, small, tmp);
        big = small;
        small = tmp;
    }
    return big;
}

bool is_prime_2(int a) {
    if (a <= 0) {
        DEBUG(printf("#err3#");)
        return false;
    }
    if (a == 1) {
        return false;
    }
    if (a == 2) {
        return false;
    }
    for(int i=2;i*i<=a;i++) {
        if (a % i == 0) {
            return false;
        }
    }
    return true;
}

void print_vec(std::vector<int> & vec) {

    for (std::vector<int>::reverse_iterator rit = vec.rbegin(); rit != vec.rend(); rit++) {
        printf("%d", (*rit));
    }
    printf("\n");
}

bool is_printed = false;

std::vector<int> arrange_vec;
int arrange_n;
bool arrange_init = false;
void arrange(int num_count,int sum) {
    if (num_count == 0) {
        if (sum != 0) {
            return;
        }
        printf("%d ",arrange_n);
        print_vec(arrange_vec); is_printed = true;
        // printf("\n");
    } else if (num_count == 1) {
        // 最后一位（最高位）不能是0，
        if (sum < 1 || sum > 9) {
            return;
        }
        arrange_vec.push_back(sum);
        arrange(num_count-1, 0);
        arrange_vec.pop_back();
    } else {
        // not in possible range 剪枝
        if (sum < 1 || sum > (9*num_count)) {
            return;
        }
        for(int i=9;i>=0;i--) {
            // 第一次不是9
            if (i == 9 && arrange_init) {
                arrange_init = false;
                continue;
            }
            arrange_vec.push_back(i);
            arrange(num_count-1, sum-i);
            arrange_vec.pop_back();
        }
    }
}

// 1, 8, 17 26 35 44 53 62 71
int primes[][10] = {{0}, {0}, {1, 17}, {1, 13}, {2, 5, 7}, {1, 11}, {1, 53}, {1, 31}, {1, 71}};
 // [9]

int main () {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    #endif
    int count;
    std::cin >> count;
    for(int round=1;round <= count;round++) {
        printf("Case %d\n",round); is_printed = false;

        int digit_num, digit_sum;
        std::cin >> digit_num >> digit_sum;
        int num_of_9 = (digit_sum+1)/9;
        std::vector<int> init; for(int i=0;i<num_of_9;i++) init.push_back(9);
        for(int sum2=(digit_sum+1)%9;sum2<=digit_sum+1;sum2+=9,num_of_9--,init.pop_back()) {
            if(num_of_9 > digit_num) {
                // DEBUG(printf("bad num_of_9");)
                continue;
            }
            int g = gcd(digit_sum, sum2);
            DEBUG(printf("m: %d n(sum2: %d, #of9: %d, gcd: %d\n", digit_sum, sum2, num_of_9, g);)
            // 看gcd是否是对应素数。
            if (!is_prime_2(g)) {
                DEBUG(printf("prime skip: 0\n"););
                continue;
            }
            
            int rest_num_count = digit_num - num_of_9;
            // 还需要安排 rest_num_count个数字，其中开头不能是0，末尾不能是9。
            // 和是sum2。
            
            arrange_vec = init;
            arrange_n = sum2;
            arrange_init = true;
            arrange(rest_num_count, digit_sum - 9 * num_of_9);
        }
        if (!is_printed) {
            printf("No Solution\n");
        }
    }

    return 0;
}