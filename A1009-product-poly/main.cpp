// %.1f
// no rear space

// 拆分成

#include <cstdio>

#include <map>

typedef std::map<int, float> mymap;
typedef std::map<int, float>::iterator myit;
typedef std::map<int, float>::reverse_iterator myrit;
typedef std::pair<int, float> mypair;


void plus_poly(mymap& res, int exp, float coef){
    if(coef == 0) {
        return;
    }
    
    std::pair<myit, bool> ret;
    ret = res.insert(mypair(exp, coef));
    if (ret.second == false) {
        // already exists
        float tmp = ret.first->second;
        tmp += coef;
        if (tmp) {
            res[exp] = tmp;
        } else {
            res.erase(exp);
        }
        
    }
}

int main () {
    int count;
    scanf("%d", &count);
    mymap orig;
    mymap res;
    while(count--) {
        int exp;
        float tmp;
        scanf("%d%f",&exp, &tmp);
        if(tmp) {
            orig[exp] = tmp;
        }
    }

    scanf("%d", &count);
    while(count--) {
        int exp;
        float tmp;
        scanf("%d%f",&exp, &tmp);
        // res += current * orig
        myit it;
        for(it = orig.begin(); it != orig.end(); ++it) {
            plus_poly(res, it->first + exp, it->second * tmp);
        }
    }
    printf("%d", res.size());
    myrit it;
    for(it = res.rbegin(); it != res.rend(); ++it) {
        printf(" %d %.1f", it->first, it->second);
    }

}

