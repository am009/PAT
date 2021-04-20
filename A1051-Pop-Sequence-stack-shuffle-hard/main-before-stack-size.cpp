#include <cstdio>
#include <stack>

int capa, seqlen;
std::stack<int> sta;


void read_n(int n) {
    int tmp;
    for (int i=0;i<n;i++) {
        scanf("%d", &tmp);
    }
}

bool solve() {
    sta.empty();
    sta.push(1);
    int pushed = 1;
    for(int i=0;i<seqlen;i++) {
        int current;
        scanf("%d", &current);
        if (current > pushed) {
        	
            while(current != sta.top()) {
                
                { pushed ++; sta.push(pushed); }
            }
            { sta.pop(); if (sta.empty()) { pushed ++; sta.push(pushed); } }
            continue;
        } else {
            if (current == sta.top()) {
                { sta.pop(); if (sta.empty()) { pushed ++; sta.push(pushed); } }
                continue;
            } else {
                printf("#%d#", current);
                read_n(seqlen - i - 1);
                return false;
            }
        }
    }
    return true;

}

int main () {
    scanf("%d%d", &capa, &seqlen);
    int count;
    scanf("%d", &count);

    while(count --) {
        if (solve()) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
    }

    return 0;
}
