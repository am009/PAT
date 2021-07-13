#include <stdio.h>
#include <string.h>

int check_newline() {
    int c = getchar();
    int ret = 1;
    if (c == ' ') {
        ret = 0;
    }
    ungetc(c, stdin);
    return ret;
}

int main() {
    freopen("input.txt", "r", stdin);
    int success = 1;
    long long sum = 0;
    do {
        long long tmp;
        success = scanf("%lld", &tmp);
        if (success <= 0) break;
        if (check_newline()) {
            sum += tmp;
            printf("%lld\n", sum);
            sum = 0;
            continue;
        } else {
            sum += tmp;
        }
        // printf("%d\n", success);
    } while(success > 0);
    return 0;
}
