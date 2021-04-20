// 判断任意进制的回文数
// 忘了边界数据
// 麻了，No打成了NO。tmd
#include <cstdio>

bool palin(int* digits, int front, int end)
{
    if (front >= end) {
        return true;
    }
    return digits[front] == digits[end] && palin(digits, front+1, end-1);
}

bool palin(int* digits, int len)
{
    for(int i=0;i<len/2;i++) {
        if (digits[i] != digits[len-1-i]) {
            return false;
        }
    }
    return true;
}

int main()
{
    int num, base;
    scanf("%d%d", &num, &base);
    int digits[50];
    int tmp = num;
    int dig_count = 0;
    if(tmp == 0) {
        digits[0] = 0;
        dig_count = 1;
    }
    while (tmp != 0) {
        digits[dig_count] = tmp % base;
        tmp = tmp / base;
        dig_count ++;
    }
    printf("%s\n", palin(digits, dig_count)? "Yes":"No" );
    bool init = true;
    while(--dig_count >= 0) {
        if (init) {
            printf("%d", digits[dig_count]);
            init = false;
        } else {
            printf(" %d", digits[dig_count]);
        }
    }
}