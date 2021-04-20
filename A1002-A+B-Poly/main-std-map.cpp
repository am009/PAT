// 将存在的项放入set中。

#include <cstdio>

#include <map>

int main () {
    int count;
    std::map<int, float> exps;
    scanf("%d", &count);
    while(count --) {
        int exp;
        float tmp;
        scanf("%d", &exp);
        scanf("%f", &tmp);
        if (tmp) {
            exps.insert(std::pair<int, float>(exp, tmp));
        }
    }
    // ----
    scanf("%d", &count);
    while(count --) {
        int exp;
        float tmp;
        float orig = 0.0f;
        scanf("%d", &exp);
        scanf("%f", &tmp);

        // 原来有项的情况
        std::map<int, float>::iterator it = exps.find(exp);
        if (it != exps.end()) {
            orig = it->second;
        }
        orig += tmp;
        if (orig == 0.0f) {
            exps.erase(exp);
        } else {
            exps[exp] = orig;
        }
    }
    // -----
    printf("%d", exps.size());

    std::map<int, float>::reverse_iterator it;
    for(it = exps.rbegin(); it!=exps.rend(); ++it) {
        printf(" %d %.1f", it->first, it->second);
    }

}