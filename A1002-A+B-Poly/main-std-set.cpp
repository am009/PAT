// 将存在的项放入set中。

#include <cstdio>

#include <set>


float coefficients[1001];

int main () {
    int count;
    std::set<int> exps;
    scanf("%d", &count);
    while(count --) {
        int exp;
        scanf("%d", &exp);
        scanf("%f", &coefficients[exp]);
        if (coefficients[exp]) {
            exps.insert(exp);
        }
    }
    // ----
    scanf("%d", &count);
    while(count --) {
        int exp;
        float tmp;
        scanf("%d", &exp);
        scanf("%f", &tmp);

        // 转化为原来有项的情况
        if (!(coefficients[exp])) {
            exps.insert(exp);
        }
        coefficients[exp] += tmp;
        if (!(coefficients[exp])) {
            exps.erase(exp);
        }
    }
    // -----
    printf("%d", exps.size());

    std::set<int>::reverse_iterator it;
    for(it = exps.rbegin(); it!=exps.rend(); ++it) {
        printf(" %d %.1f", *it, coefficients[*it]);
    }

}