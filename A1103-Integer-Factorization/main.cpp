#include <cstdio>
#include <iostream>

// K个槽，P次方等于N
int N,K,P;

// 当前递归状态。
int* nums;
int* answer;
int* powers;
int ans_fac_sum = -1;

// 每个槽的基本范围是从1到根号N。大于根号N的时候就必定结束
// 当前的和大于根号N的时候也可以剪枝
// 由对称性，我们可以让N个槽的数递减或相等。这样恰好字典序最大
int current_sum = 0;
int prev_num = 0;

int my_pow(int x, unsigned int p)
{
  if (p == 0) return 1;
  if (p == 1) return x;
  
  int tmp = my_pow(x, p/2);
  if (p%2 == 0) return tmp * tmp;
  else return x * tmp * tmp;
}

void save_ans() {
    for (int i=0;i<K;i++) {
        answer[i] = nums[i];
    }
}

void insp_nums() {
    for (int i=0;i<K;i++) {
        printf("%d#", nums[i]);
    }
    puts("");
}


// 递归深度用来判断是否结束。range表示当前可选的数字的范围
void search(int index, int range, int current_sum, int fac_sum) {
    if (index == K) {
        // check answer
        // insp_nums();
        if (current_sum == N) {
            
            if (fac_sum >= ans_fac_sum) {
                ans_fac_sum = fac_sum;
                save_ans();
            }
        }
        return;
    } // index < K
    // i是当前选的数字。
    for(int i=1;current_sum + powers[i-1] <= N && i <= range; i++) {
        nums[index] = i;
        // 后面的数字小于等于i，current_sum增加i方，fac_sum累加。
        search(index+1, i, current_sum + powers[i-1], fac_sum + i);
    }
}


int main () {
    std::cin >> N >> K >> P;
    nums = new int[K];
    answer = new int[K];
    powers = new int[N];
    for (int i=0;i<K;i++) {
        nums[i] = 0;
        answer[i] = 0;
        
    }
    for (int i=0;i<N;i++) {
        // i+1 的P次方。
        powers[i] = my_pow(i+1, P);
    }
    search(0, N, 0, 0);

    // ----print--- 
    if (ans_fac_sum == -1) {
        printf("Impossible");
    } else {
        printf("%d = %d^%d", N, answer[0], P);
        for(int i=1;i<K;i++) {
            printf(" + %d^%d", answer[i], P);
        }
    }


    return 0;
}