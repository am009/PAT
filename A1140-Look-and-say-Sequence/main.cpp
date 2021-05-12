#include <cstdio>
#include <iostream>
#include <queue>

#ifndef ONLINE_JUDGE
#define DEBUG(X) X
#else
#define DEBUG(X) 
#endif

std::queue<char> buf1;
std::queue<char> buf2;
char num_buf[50];

void push_str(std::queue<char> &to, char* buf) {
    int ind = 0;
    while(buf[ind] != '\x00') {
        to.push(buf[ind]);
        ind ++;
    }
}

void look_and_say(std::queue<char> &from, std::queue<char> &to) {
    if (!to.empty()) {
        DEBUG(printf("#err2#");)
    }
    while(!from.empty()) {
        char front = from.front();
        int calc = 1;
        from.pop();
        while(!from.empty() && from.front() == front) { // !!!!STL真的得好好供着！！如果是empty 的时候调用front还会segfault！！
            calc ++;
            from.pop();
        }
        // from.front() != front
        to.push(front);
        snprintf(num_buf, 50, "%d", calc);
        push_str(to, num_buf);
    }
}

void print_queue(std::queue<char> &que) {
    while(!que.empty()) {
        putchar(que.front());
        que.pop();
    }
}

int main () {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    #endif
    int start, generation;
    std::cin >> start >> generation;
    if (start > 9 || start < 0) {
        DEBUG(printf("#err1#");)
    }
    buf1.push('0'+ start);

    std::queue<char> *from = &buf1;
    std::queue<char> *to = &buf2;
    for(int i=1;i<generation;i++) {
        look_and_say(*from, *to);
        std::queue<char> *tmp = from;
        from = to;
        to = tmp;
    }

    print_queue(*from);

    return 0;
}