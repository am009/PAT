#include <cstdio>
#include <iostream>
#include <set>

#define assert(X) do { if (!(X)) {printf("Error!");} } while(0);

struct node {
    int data;
    int next;
};

struct node mem[100001] = {0};

int head_addr;
int dup_head_addr = -1;
int dup_end_addr = -1;
int node_count;

void insert_to_dup(int addr) {
    // init
    if (dup_head_addr == -1) {
        dup_head_addr = addr;
        dup_end_addr = addr;
    } else {
        assert(mem[dup_end_addr].next == -1);
        mem[dup_end_addr].next = addr;
        dup_end_addr = addr;
    }

    
}

int main () {
    std::cin >> head_addr >> node_count;
    int count = node_count;
    while(count --) {
        int addr, data ,next;
        std::cin >> addr >> data >> next;
        mem[addr].data = data;
        mem[addr].next = next;
    }
    
    
    std::set<int> included;
    int prev = -1;
    int current = head_addr;
    while(current != -1) {
        int data = mem[current].data;
        if (data < 0) { data = - data; }
        if (included.find(data) == included.end()) {
            included.insert(data);
        } else {
            insert_to_dup(current);
            // skip
            int tmp = current;
            current = mem[current].next;
            mem[tmp].next = -1;
            if (prev != -1) {
                mem[prev].next = current;
            } else {
                printf("error");
                head_addr = current;
            }
            continue;
        }
        prev = current;
        current = mem[current].next;
    }

    count = node_count;
    current = head_addr;
    while(count -- && current >= 0) {
        if (mem[current].next >= 0) {
            printf("%05d %d %05d\n",current, mem[current].data, mem[current].next);
        } else {
            printf("%05d %d %d\n",current, mem[current].data, mem[current].next);
        }
        current = mem[current].next;
    }

    count = node_count;
    current = dup_head_addr;
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