#include <cstdio>
#include <iostream>
#include <stack>

// L o a D i n g
// B e i n g
// 首先找到两个末尾，然后反向一一比较字符即可。
// 用stack保存每个节点用于之后反向遍历。

struct node {
    char data;
    int next;
};

struct node mem[100001] = {0};

int head1_addr, head2_addr, node_count;

void fill_stack(int head, std::stack<int>& sta) {
    while (head != -1) {
        sta.push(head);
        head = mem[head].next;
    }
}

bool top_eq(std::stack<int>& sta1, std::stack<int>& sta2) { // 这样比较反而不对
    int top1 = sta1.top();
    int top2 = sta2.top();
    if (top1 == top2) {
        return true;
    } else if (mem[top1].data == mem[top2].data) {
        return true;
    }
    return false;
}

int main () {
    std::cin >> head1_addr >> head2_addr >> node_count;
    int count = node_count;
    while(count --) {
        int addr ,next;
        char data;
        scanf("%d %c %d", &addr, &data, &next);
        mem[addr].data = data;
        mem[addr].next = next;
    }

    std::stack<int> sta1, sta2;
    fill_stack(head1_addr, sta1);
    fill_stack(head2_addr, sta2);

    // compare
    int substr_addr = -1;
    bool last_eq;
    while ( (!sta1.empty()) && (!sta2.empty()) && (sta1.top() == sta2.top()) ) {
        substr_addr = sta1.top();
        sta1.pop();
        sta2.pop();
    }
    if (substr_addr >= 0) {
        printf("%05d", substr_addr);
    } else {
        printf("%d", substr_addr);
    }
    
    
    return 0;
}