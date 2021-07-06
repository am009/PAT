#include <algorithm>
#include <string>
#include <cstdio>
#include <vector>
#include <iostream>
#include <map>
#include <unordered_map>

using namespace std;

struct node
{
    string s;
    int n;
};

bool cmp(node&a, node&b) {
    if(a.n != b.n) {
        return a.n > b.n;
    } else {
        return a.s < b.s;
    }
}

int main () {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    #endif
    int n,m;
    // scanf("%d%d", &n, &m);
    cin >> n >> m;
    vector<node> vec(n);
    for(int i=0;i<n;i++) {
        cin >>vec[i].s >> vec[i].n;
    }
    for(int i=0;i<m;i++) {
        node que; cin >> que.n >> que.s;
        int nt = 0;
        vector<node> ans;
        printf("Case %d: %d %s\n", i+1, que.n, que.s.c_str());
        if(que.n == 1) {
            for(auto &e : vec) {
                if (e.s[0] == que.s[0]) {
                    ans.push_back({e.s, e.n});
                }
            }
        } else if (que.n == 2) {
            int ns = 0;
            for(auto &e: vec) {
                // printf("#%s#%s#\n", e.s.substr(1, 3).c_str(), que.s.c_str());
                if(e.s.substr(1,3) == que.s) {
                    nt++;
                    ns+=e.n;
                }
            }
            if(nt != 0) {
                printf("%d %d\n",nt, ns);
            }
        } else {
            // date find
            // site -> rearrange sum nt
            unordered_map<string, int> amap;
            for(auto &e: vec) {
                if(e.s.substr(4,6) == que.s) {
                    amap[e.s.substr(1,3)] ++;
                }
            }
            for(auto &e: amap) {
                ans.push_back({e.first, e.second});
            }
        }
        sort(ans.begin(), ans.end(), cmp);
        for(auto &e:ans) {
            printf("%s %d\n", e.s.c_str(), e.n);
        }
        if ((que.n == 2 && nt == 0) || (que.n != 2 && ans.size() == 0)) {
            printf("NA\n");
        }

    }
}