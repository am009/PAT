// 突然意识到致命的一点：当前四个节点，的下一个节点，在下一轮翻转后会到末尾！！每次翻转还需要修正前一个节点的下一个节点。

#include <cstdio>
#include <iostream>
#include <queue>

struct node {
    int data;
    int next;
};

struct node mem[100001] = {0};

int head_addr, node_count, rev_count;

bool first_rev = true;

int do_rev_last_end;
int do_rev_last_end_next;

int do_rev(std::queue<int>& que, int next_addr) {
    int prev = que.front();

    do_rev_last_end_next = prev;
    
    mem[prev].next = next_addr;
    que.pop();
    while(!que.empty()) {
        int current = que.front();

        mem[current].next = prev;
        
        prev = current;
        que.pop();
    }
    if (first_rev) {
        head_addr = prev;
        first_rev = false;
        do_rev_last_end = do_rev_last_end_next;
    } else { // 修正prev node
        mem[do_rev_last_end].next = prev;
        do_rev_last_end = do_rev_last_end_next;
    }
}

int main () {
    std::cin >> head_addr >> node_count >> rev_count;
    int count = node_count;
    while(count --) {
        int addr, data ,next;
        std::cin >> addr >> data >> next;
        mem[addr].data = data;
        mem[addr].next = next;
    }

    // 正式开始逆转。使用一个队列保存当前遍历的node地址，
    // 满了rev_count个就整理过来。
    // 满了就找到队列开头的那个元素指向下一个元素，
    // 接着pop队列，不断指向之前的元素。
    // 第一次reverse的队列末尾是头元素
    std::queue<int> que;
    int current_addr = head_addr;
    do {
        que.push(current_addr);
        int next_addr = mem[current_addr].next;
        if (que.size() >= rev_count) { //  || next_addr == -1
            do_rev(que, next_addr); // 会改变mem[current_addr]
        }
        current_addr = next_addr;
    } while(current_addr != -1);


    // 输出链表
    count = node_count;
    int current = head_addr;
    while(count -- && current >= 0) {
        if (mem[current].next >= 0) {
            printf("%05d %d %05d\n",current, mem[current].data, mem[current].next);
        } else {
            printf("%05d %d %d\n",current, mem[current].data, mem[current].next);
        }
        current = mem[current].next;
    }



    return 0;
}