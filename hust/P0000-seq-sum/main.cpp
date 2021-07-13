#include <cstdio>
#include <string>
#include <iostream>
#include <sstream>
#include <stack>

#ifndef ONLINE_JUDGE
#define DEBUG(X) X
#else
#define DEBUG(X) 
#endif

using namespace std;

#define NUM_T __int128

void print_num(NUM_T num) {
    stack<char> sta;
    bool minus = false;
    if (num < 0) {
        minus = true;
        num = -num;
    }
    while(num > 0) {
        int digit = num % 10;
        num /= 10;
        sta.push(digit+'0');
    }
    if (minus) {sta.push('-');}
    while(!sta.empty()) {
        putchar(sta.top());
        sta.pop();
    }
    putchar('\n');
}

int main () {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    setbuf(stdout, NULL);
    #endif
    while(!cin.eof()) {
        NUM_T sum = 0;
        string line;
        getline(cin, line);
        stringstream ss;
        ss.str(line);
        long long tmp = 0;
        int count = 0;
        while (ss) {
            sum += tmp;
            count ++;
            ss >> tmp;
        }
        if (count > 1) {
            print_num(sum);
        }
    }
    return 0;
}
