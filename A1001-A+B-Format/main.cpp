

#include <cstdio>
#include <cstring>

char buf[100];

int main () {
    int a,b;
    scanf("%d%d", &a, &b);
    sprintf(buf, "%d", a+b);
    int len = strlen(buf);
    int count = len;
    int start = 0;
    if (buf[0] == '-') {
        count -= 1;
        start = 1;
        putchar('-');
    }
    for(int i=start;i<len;i++) {
        putchar(buf[i]);
        count -= 1;
        if (count % 3 == 0 && count != 0) {
            putchar(',');
        }
    }

    return 0;
}