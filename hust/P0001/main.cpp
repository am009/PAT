#include <cstdio>
#include <iostream>
#include <unordered_map>

#ifndef ONLINE_JUDGE
#define DEBUG(X) X
#else
#define DEBUG(X) 
#endif

using namespace std;

int main () {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    setbuf(stdout, NULL);
    #endif
    int count;
    std::cin >> count;
    unordered_map<int,int> imap;
    int mcnt = 0, mnum = -1;
    for(int i=0;i<count;i++) {
        int n1; cin >> n1;
        int cnt = ++imap[n1];
        if ((cnt > mcnt) || (cnt == mcnt && n1 < mnum)) {
            mcnt = cnt;
            mnum = n1;
        }
        // printf("%d\n", cnt);
    }
    printf("%d\n", mnum);

    return 0;
}