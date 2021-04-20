// 依然极其简单的进制转换

#include<cstdio>

int main() {
    int num1[3];
    int num2[3];
    scanf("%d.%d.%d", &num1[0], &num1[1], &num1[2]);
    scanf("%d.%d.%d", &num2[0], &num2[1], &num2[2]);

    int res[3];
    int carry = 0;
    carry = num1[2] + num2[2];
    res[2] = carry % 29;
    carry /= 29;

    carry += num1[1] + num2[1];
    res[1] = carry % 17;
    carry /= 17;

    res[0] = num1[0] + num2[0] + carry;

    printf("%d.%d.%d", res[0], res[1], res[2]);


}