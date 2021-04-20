#include <cstdio>
#include <cstring>

char buf[20] = {0};
bool init = true;

bool is_num(char c) {
    return c >= '0' && c <= '9';
}

void put_dig(char c) {
    if (init) {
        init = false;
    } else {
        putchar(' ');
    }
    static const char* eng[] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    printf(eng[c-'0']);
}

int main () {
    char c;
    int sum = 0;
    while (1) {
        c = getchar();
        if (c == EOF) { break; }
        if (is_num(c)) {
            sum += (c - '0');
        }
    }

    sprintf(buf, "%d", sum);
    int len = strlen(buf);
    for(int i=0;i<len;i++) {
        put_dig(buf[i]);
    }

}