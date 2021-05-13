#include <cstdio>
#include <iostream>
#include <stack>

#ifndef ONLINE_JUDGE
#define DEBUG(X) X
#else
#define DEBUG(X) 
#endif

struct node {
    int data;
    int next;
};
typedef struct node node;

node nodes[100001];

int head1,head2;
std::stack<int> l1;
std::stack<int> l2;
int count1 = 0, count2 = 0;


// 先把两个链表都放到栈里，找到短的那个。
// 然后正常遍历长的，不断pop短的。

int main () {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    #endif
    int count;
    std::cin >> head1 >> head2 >> count;
    for(int i=0;i<count;i++) {
        int addr,data,next;
        std::cin >> addr >> data >>next;
        nodes[addr].data = data;
        nodes[addr].next = next;
    }

    int current = head1;
    while(current != -1) {
        l1.push(current);
        count1++;
        current = nodes[current].next;
    }

    current = head2;
    while(current != -1) {
        l2.push(current);
        count2++;
        current = nodes[current].next;
    }
    DEBUG(printf("len1: %d len2: %d\n", count1, count2);)

    // current points to longest
    std::stack<int> *shorter;
    if (count1 > count2) {
        current = head1;
        shorter = &l2;
    } else {
        current = head2;
        shorter = &l1;
    }

    int prev = -1;
    while(!(*shorter).empty()) {
        int top = (*shorter).top();

        prev = current;
        current = nodes[current].next;
        if (current == -1) {
            DEBUG(printf("#err1#\n");)
        }
        prev = current;
        current = nodes[current].next;
        if (current == -1) {
            DEBUG(printf("#err1#\n");)
        }
        // int tmp = nodes[prev].next;
        nodes[prev].next = top;
        nodes[top].next = current;

        (*shorter).pop();
    }

    // final print
    if (count1 > count2) {
        current = head1;
    } else {
        current = head2;
    }
    while(current != -1) {
        if (nodes[current].next < 0) {
            printf("%05d %d %d\n", current, nodes[current].data, nodes[current].next);
        } else {
            printf("%05d %d %05d\n", current, nodes[current].data, nodes[current].next);
        }
        current = nodes[current].next;
    }

    return 0;
}