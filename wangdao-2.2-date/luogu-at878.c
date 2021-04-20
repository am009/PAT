#include <stdio.h>

#define YEAP(x) (x % 100 != 0 && x % 4 == 0 || x % 400 == 0)

int mondays[2][12] = {{31,28,31,30,31,30,31,31,30,31,30,31}, {31,29,31,30,31,30,31,31,30,31,30,31}};

int getoffset (int year, int mon, int day)
{
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
    year--;
    while (year >= 0) {
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
    int year, mon, day;
    scanf("%d", &year);
    scanf("%d", &mon);
    scanf("%d", &day);
    int delta = getoffset(2014,5,17);
    // int current_yeap = YEAP(year) ? 1 : 0;
    // printf("%d\n", current_yeap);
    int delta2 = getoffset(year,mon,day);
    // printf("%d\n", delta2);
    if (delta2 > delta) {
        printf("%d\n", delta2 - delta);
    }else {
        printf("%d\n", delta- delta2);
    }
}

int debug(){
    int last;
    last = getoffset(1999,12,31);
    for(int i=2000;i<2014;i++)
    {
        int current_yeap = YEAP(i) ? 1 : 0;
        for(int j=0;j<12;j++)
        {
            for(int k=0;k<mondays[current_yeap][j];k++)
            {
                int current = getoffset(i, j+1, k+1);
                if (current - last != 1) {
                    printf("%d %d %d\n",i,j,k);
                }
                last = current;
            }
        }
    }
}
/* 
2000 0 0
2001 0 0
2004 0 0
2005 0 0
2008 0 0
2009 0 0
2012 0 0
2013 0 0
*/