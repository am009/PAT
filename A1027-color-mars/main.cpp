// 极其简单的进制转换。

#include <cstdio>

char tod(int i) {
    if (i < 10) {
        return '0' + i;
    }else {
        i -= 10;
        return 'A' + i;
    }
}

int main () {
    int c[3];
    scanf("%d%d%d", &c[0], &c[1],&c[2]);

    printf("#");
    for(int i=0;i<3;i++) {
        int d2 = c[i] % 13;
        int d1 = c[i] / 13;
        printf("%c%c",tod(d1), tod(d2));
    }
}