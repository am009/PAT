#include <cstdio>
#include <iostream>

#ifndef ONLINE_JUDGE
#define DEBUG(X) X
#else
#define DEBUG(X) 
#endif

int block_num;
int head;
int head2 = -1;

struct node {
    int data;
    int next;
};

typedef struct node node;

node nodes[100001];

int main () {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    #endif
    int count;
    std::cin >> head >> count >> block_num;
    for(int i=0;i<count;i++) {
        int addr,data,next;
        std::cin >> addr >> data >> next;
        nodes[addr].data = data;
        nodes[addr].next = next;
    }

    int current_block_head;
    int prev = -1;
    int current = head;
    // int current_block_tail;
    // int next_block_head;
    do {
        current_block_head = current;
        for(int i=0;i<block_num && current != -1;i++) {
            prev = current;
            current = nodes[current].next;
        }
        // current是next_block_head prev是current_block_tail
        // if (current != -1) {
        //     int tmp = head2;
        //     head2 = current_block_head;
        //     nodes[prev].next = tmp;
        // } else {
        //     // 块数不够了。此时current是-1;
        //     int tmp = head2;
        //     head2 = current_block_head;
        //     nodes[prev].next = tmp;
        // }
        int tmp = head2;
        head2 = current_block_head;
        nodes[prev].next = tmp;

    } while(current != -1); // next_block_head != -1

    current = head2;
    while(current != -1) {
        if (nodes[current].next >= 0) {
            printf("%05d %d %05d\n", current, nodes[current].data, nodes[current].next);
        } else {
            printf("%05d %d %d\n", current, nodes[current].data, nodes[current].next);
        }
        current = nodes[current].next;
    }

    return 0;
}