#include <cstdio>
#include <iostream>
#include <cstring>
#include <queue>

int count;
char buf[11];

struct node {
    int data;
    int lchild;
    int rchild;
};

typedef struct node node;

node* nodes = nullptr;
bool* isRoot = nullptr;

void in_order_traverse(int root_ind) {
    static bool first = true;
    if (root_ind == -1) {
        return;
    }
    in_order_traverse(nodes[root_ind].lchild);
    if (first) {
        first = false;
        printf("%d", nodes[root_ind].data);
    } else {
        printf(" %d", nodes[root_ind].data);
    }
    in_order_traverse(nodes[root_ind].rchild);
}

int main () {
    std::cin >> count;
    nodes = new node[count];
    isRoot = new bool[count];
    for (int i=0;i<count;i++) {
        isRoot[i] = true;        
    }
    for(int i=0;i<count;i++) {
        nodes[i].data = i;
        // 直接先读r再读到l，在读入的时候反转。
        scanf("%s",buf);
        if (buf[0] == '-') {
            nodes[i].rchild = -1;
        } else {
            int tmp = atoi(buf);
            nodes[i].rchild = tmp;
            if (tmp < count && tmp >= 0) {
                isRoot[tmp] = false;
            } else {
                printf("#err#");
            }
        }
        scanf("%s",buf);
        if (buf[0] == '-') {
            nodes[i].lchild = -1;
        } else {
            int tmp = atoi(buf);
            nodes[i].lchild = tmp;
            if (tmp < count && tmp >= 0) {
                isRoot[tmp] = false;
            } else {
                printf("#err#");
            }
        }
    }

    int root_ind = -1;
    for (int i=0;i<count;i++) {
        if (isRoot[i]) {
            if (root_ind != -1) {
                printf("#err2#"); // multiple root
            }
            root_ind = i;
        }
    }
    if (root_ind == -1) {
        printf("#err3#");
        return 0;
    }

    // printf("ind : %d\n", root_ind);
    // level-order
    std::queue<int> que;
    printf("%d", nodes[root_ind].data);
    que.push(root_ind);
    while(!que.empty()) {
        int front = que.front();
        int child = nodes[front].lchild;
        if (child != -1) {
            printf(" %d", nodes[child].data);
            que.push(child);
        }
        child = nodes[front].rchild;
        if (child != -1) {
            printf(" %d", nodes[child].data);
            que.push(child);
        }
        que.pop();
    }
    printf("\n");
    // in-order

    in_order_traverse(root_ind);


    return 0;
}