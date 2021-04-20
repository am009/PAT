#include <stdio.h>

#define YEAP(x) (x % 100 != 0 && x % 4 == 0 || x % 400 == 0)

int mondays[2][12] = {{31,28,31,30,31,30,31,31,30,31,30,31}, {31,29,31,30,31,30,31,31,30,31,30,31}};

int getoffset ()
{
    int year, mon, day;
    scanf("%4d%2d%2d", &year, &mon, &day);
    mon -= 1;
    day -= 1;
    if (mon >= 12 || mon < 0) {
        return -1;
    }
    int delta1 = 0;
    if (year > 400) {
        int times = year / 400;
        year %= 400;
        delta1 += times * (400 * 365 + 100 - 4 + 1);
    }
    int current_yeap = YEAP(year) ? 1 : 0;
    while (year > 0) {
        if (YEAP(year)) {
            delta1 += 366;
        } else {
            delta1 += 365;
        }
        year--;
    }
    int max_days = mondays[current_yeap][mon];
    if (day >= max_days || day < 0) {
        return -1;
    }
    mon --;
    while (mon >= 0) {
        delta1 += mondays[current_yeap][mon];
        mon--;
    }
    delta1 += day;
    return delta1;
}

int main ()
{
    int delta = getoffset();
    // printf("%d", delta);
    int delta2 = getoffset();
    printf("%d", delta2 - delta);
}