// 结果：第六个测试项目	Presentation Error
// 把每次输出和前面的空格配对后就ac了。


// special case: all 0 print 0?
// %.1f
// no rear space

#include <cstdio>

float coefficients[1001];

int main () {
    int count;
    int xiangshu = 0;
    scanf("%d", &count);
    while(count --) {
        int exp;
        scanf("%d", &exp);
        scanf("%f", &coefficients[exp]);
        if (coefficients[exp]) {
            xiangshu += 1;
        }
    }
    // ----
    scanf("%d", &count);
    while(count --) {
        int exp;
        float tmp;
        scanf("%d", &exp);
        scanf("%f", &tmp);
        // // 原来没有 之后有了
        // if( (!(coefficients[exp])) && (tmp)) {
        //     xiangshu += 1;
        //     coefficients[exp] += tmp;
        //     continue;
        // }
        // tmp += coefficients[exp];
        // // 原来有，之后没了
        // if ((coefficients[exp]) && tmp == 0)
        // {
        //     xiangshu -= 1;
        // }
        // ---
        // 转化为原来有项的情况
        if (!(coefficients[exp])) {
            xiangshu += 1;
        }
        coefficients[exp] += tmp;
        if (!(coefficients[exp])) {
            xiangshu -= 1;
        }
    }
    // -----
    printf("%d", xiangshu);
    for(int i=1000;i>=0;i--) {
        if (coefficients[i]) {
            xiangshu --;
            if (xiangshu != 0) {
                printf(" %d %.1f", i, coefficients[i]);
            } else {
                printf(" %d %.1f", i, coefficients[i]);
                // printf("#");
                // puts("");
            }
        }
    }

}