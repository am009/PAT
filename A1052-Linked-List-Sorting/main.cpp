// 没有考虑特判 0 -1 的情况

#include <cstdio>
#include <iostream>


struct node {
    int data;
    int next;
};

struct node mem[100001] = {0};

int head_addr;
int node_count;
int sorted = -1;
int unsorted = -1;

bool bigger(int ind1, int ind2) {
    return mem[ind1].data > mem[ind2].data;
}

int main () {
    std::cin >> node_count >> head_addr;
    int count = node_count;
    while(count --) {
        int addr, data ,next;
        std::cin >> addr >> data >> next;
        mem[addr].data = data;
        mem[addr].next = next;
    }

    if(head_addr < 0) {
        printf("0 -1");
        return 0;
    }

    unsorted = head_addr;

    
    node_count = 0;
    while (unsorted != -1) {
        node_count ++;
        // 拿出一个节点到current
        int current = unsorted;
        unsorted = mem[unsorted].next;

        // debug
        // if (mem[current].data == -1) {
        //     printf("#");
        // }

        // 找到该插入的位置的前后两个节点。
        int p = -1;
        int p2 = sorted;
        while (p2 != -1 && bigger(current, p2)) {
            p = p2;
            p2 = mem[p2].next;
        }
        // 插入
        if (p == -1) {
            // 插入到第一个节点之前
            int tmp = sorted;
            sorted = current;
            mem[current].next = tmp;
        } else {
            int tmp = mem[p].next;
            mem[p].next = current;
            mem[current].next = tmp;
        }
    }

    // print
    printf("%d %05d", node_count, sorted);
    int current = sorted;
    while(node_count -- && current >= 0) {
        if (mem[current].next >= 0) {
            printf("\n%05d %d %05d", current, mem[current].data, mem[current].next);
        } else {
            printf("\n%05d %d %d", current, mem[current].data, mem[current].next);
        }
        current = mem[current].next;
    }

    return 0;
}