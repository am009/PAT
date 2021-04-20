#include <cstdio>
#include <iostream>

struct node {
    int data;
    int child_count;
    int* childs;
};
typedef struct node node;

// 总节点个数
int COUNT;
node* nodes;
int* leaf_counts;
int max_depth = 0;

// 深度优先遍历，维护深度，计算叶子节点数量
// 访问时只处理当前节点，而不是访问前处理
void DFS(int root_ind, int depth) {
    int count = nodes[root_ind].child_count;
    int *childs = nodes[root_ind].childs;
    if (depth > max_depth) {
        max_depth = depth;
    }
    if (count == 0) {
        leaf_counts[depth] ++;
    } else {
        for(int i=0;i<count;i++) {
            DFS(childs[i], depth+1);
        }
    }
}

int main () {
    std::cin >> COUNT;
    nodes = new node[COUNT];
    leaf_counts = new int[COUNT];
    for (int i=0;i<COUNT;i++) {
        nodes[i].child_count = 0;
        nodes[i].childs = nullptr;
        nodes[i].data = -1;
        leaf_counts[i] = 0;
    }

    // 非叶子节点个数，即读入次数
    int count;
    std::cin >> count;
    for(int i=0;i<count;i++) {
        int id, count2;
        std::cin >> id >> count2;
        id -= 1;
        node* current = &nodes[id];
        current->child_count = count2;
        current->childs = new int[count2];
        for (int j=0;j<count2;j++) {
            int child_id;
            std::cin >> child_id;
            child_id --;
            current->childs[j] = child_id;
        }
    }

    DFS(0,0);
    printf("%d", leaf_counts[0]);
    for(int i=1;i<=max_depth;i++) {
        printf(" %d", leaf_counts[i]);
    }


    return 0;
}