
// 
// 指数部分用%d读入

#include <cstdio>
#include <cstring>
#include <algorithm>


char digits[11000] = {0};
int dig_count = 0;
int dot = 0;

bool is_num(char c) {
    return c <= '9' && c >= '0';
}

int mymin(int a, int b) {
    return std::min<int>(a, b);
}

int mymax(int a, int b) {
    return std::max<int>(a, b);
}

int main () {
    char c;
    bool init = true;
    while (1) {
        c = getchar();
        if (c == EOF) {break;}
        // minus
        if (init) {
            init = false;
            if (c == '-') {
                // 转化
                putchar('-');
            } else if (c == '+') {
                continue;
            }
        }
        if (is_num(c)) {
            digits[dig_count] = c;
            dig_count ++;
        }
        if (c == '.') {
            dot = dig_count;
        }
        if (c == 'E') {
            break;
        }
    }

    int exp;
    scanf("%d", &exp);
    dot += exp;
    for(int i=(mymin(0, dot));i<(mymax(dig_count, dot));i++) {
        if (i == dot) {
            if (i <= 0) {
                putchar('0');
            }
            putchar('.');
        }
        
        if (i < 0 || i >= dig_count) {
            putchar('0');
            continue;
        }
        putchar(digits[i]);

    }


}