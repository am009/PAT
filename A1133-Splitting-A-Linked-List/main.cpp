#include <cstdio>
#include <iostream>
#include <stack>

#ifndef ONLINE_JUDGE
#define DEBUG(X) X
#else
#define DEBUG(X) 
#endif


int K;
int head;
int head2 = -1;

struct node {
    int data;
    int next;
};

typedef struct node node;

node nodes[100001];

struct node_info {
    int addr;
    int data;
};
typedef struct node_info node_info;

int main () {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    #endif
    int count;
    std::cin >> head >> count >> K;
    for(int i=0;i<count;i++) {
        int addr, data, next;
        std::cin >> addr >> data >> next;
        nodes[addr].data = data;
        nodes[addr].next = next;
    }
    std::stack<node_info> que;

    int current = head;
    while(current != -1) {
        node_info n = {current, nodes[current].data};
        que.push(n);
        current = nodes[current].next;
    }

    // 遍历插入到node2.
    std::stack<node_info> que2 = que;
    while(!que2.empty()) {
        node_info front = que2.top();
        if (front.data > K) {
            int tmp = head2;
            head2 = front.addr;
            nodes[front.addr].next = tmp;
        }
        que2.pop();
    }

    que2 = que;
    while(!que2.empty()) {
        node_info front = que2.top();
        if (front.data <= K && front.data >= 0) {
            int tmp = head2;
            head2 = front.addr;
            nodes[front.addr].next = tmp;
        }
        que2.pop();
    }

    que2 = que;
    while(!que2.empty()) {
        node_info front = que2.top();
        if (front.data < 0) {
            int tmp = head2;
            head2 = front.addr;
            nodes[front.addr].next = tmp;
        }
        que2.pop();
    }

    // print
    current = head2;
    while(current != -1) {
        if(nodes[current].next < 0) {
            printf("%05d %d %d\n", current, nodes[current].data, nodes[current].next);
        } else {
            printf("%05d %d %05d\n", current, nodes[current].data, nodes[current].next);
        }
        current = nodes[current].next;
    }


    return 0;
}