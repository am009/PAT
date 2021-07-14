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
        if (in < 0) {in = - in;}
        int old = imap[in]++;
        if (old) {count++;}
    }
    printf("%d\n", count);

    return 0;
}