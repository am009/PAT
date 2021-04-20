#include <cstdio>
#include <iostream>

struct node {
    int child_count;
    int* childs;
};

typedef struct node node;

node* nodes;
// 每层的数量
int * gene_counts;
int COUNT;

void traverse(int root_ind, int depth) {
    if (root_ind >= COUNT || root_ind < 0) {
        printf("#err#");
    }
    gene_counts[depth] ++;
    int count = nodes[root_ind].child_count;
    int* childs = nodes[root_ind].childs;
    for(int i=0;i<count;i++){
        traverse(childs[i], depth + 1);
    }
}

int main () {
    std::cin >> COUNT;
    nodes = new node[COUNT];
    gene_counts = new int[COUNT];
    for(int i=0;i<COUNT;i++) {
        nodes[i].child_count = -1;
        nodes[i].childs = nullptr;
        gene_counts[i] = 0;
    }

    int count;
    std::cin >> count;
    for(int i=0;i<count;i++) {
        int id,count2;
        std::cin >> id >> count2;
        id -= 1;
        nodes[id].child_count = count2;
        nodes[id].childs = new int[count2];
        for (int j=0;j<count2;j++) {
            std::cin >> nodes[id].childs[j];
            nodes[id].childs[j] -= 1;
        }
    }

    traverse(0, 0);

    int max_ind = 0;
    int max_count = gene_counts[0];
    for(int i=1;i<COUNT;i++) {
        if(gene_counts[i] > max_count) {
            max_count = gene_counts[i];
            max_ind = i;
        }
    }

    printf("%d %d", max_count, max_ind+1);

    return 0;
}