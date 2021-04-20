// 就是简单计算乘积吧。

#include <cstdio>

char cc[3] = {'W', 'T', 'L'};

int main () {
    // float arr[3];
    float max[3];
    char seq[3];
    for(int i=0;i<3;i++) {
        max[i] = 0;
        for(int j=0;j<3;j++) {
            float tmp;
            scanf("%f", &tmp);
            if (tmp > max[i]) {
                max[i] = tmp;
                seq[i] = cc[j];
            }
        }
    }

    float res = max[0] * max[1] * max[2] * 0.65f - 1;
    printf("%c %c %c %.2f", seq[0], seq[1], seq[2], res * 2);
}