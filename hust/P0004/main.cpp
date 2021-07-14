#include <cstdio>
#include <iostream>
#include <unordered_map>

// define ONLINE_JUDGE

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
    int N;
    cin >> N;
    unordered_map<int,int> imap;
    int count = 0;
    for(int i=0;i<N;i++) {
        int in; cin>>in;
        imap[in]++;
        int t1 = imap[in+1];
        if (t1) {count ++;}
        int t2 = imap[in-1];
        if (t2) {count ++;}
    }
    printf("%d\n", count);

    return 0;
}