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
    while(!sta.empty()) sta.pop();
    sta.push(1);
    int pushed = 1; //已经push的最大数字
    for(int i=0;i<seqlen;i++) {
        int current;
        scanf("%d", &current);
        // 如果数字比较大，就继续push到它，然后pop
        if (current > pushed) {
        	
            while(current != sta.top()) {
                { pushed ++; sta.push(pushed); }
                // check capa
                { if (sta.size() > capa) { 
                    // printf("capa#%d#", current);
                    read_n(seqlen - i - 1);
                    return false;
                } }
            }
            // pop 后如果是empty，则下一步必定是push。
            { sta.pop(); if (sta.empty()) { pushed ++; sta.push(pushed); } }
            continue;
        } else { // 否则只能pop栈顶的。
            if (current == sta.top()) {
                // pop 后如果是empty，则下一步必定是push。
                { sta.pop(); if (sta.empty()) { pushed ++; sta.push(pushed); } }
                continue;
            } else {
                // printf("#%d#", current);
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
