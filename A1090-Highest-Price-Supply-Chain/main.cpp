#include <cstdio>
#include <iostream>
#include <vector>



struct node {
    double data;
    int parent;
    std::vector<int> childs;
};

typedef struct node node;

node* nodes;
int nodes_root = -1;

int COUNT;
double unit_price, rate;


int final_depth = 0;
double final_price = 0.0;
int final_count = 1;

void traverse(int root_ind, double price, int depth) {
    if (depth > final_depth) {
        final_depth = depth;
        final_price = price;
        final_count = 1;
    } else if (depth == final_depth) {
        final_count ++;
    }
    std::vector<int>& vec = nodes[root_ind].childs;
    std::vector<int>::iterator it;
    for(it = vec.begin(); it != vec.end(); it++) {
        traverse(*it, price * rate, depth + 1);
    }
}

int main () {
    int count;
    std::cin >> COUNT >> unit_price >> rate;
    rate = rate / 100.0 + 1.0;

    nodes = new node[COUNT];

    for (int i=0;i<COUNT;i++) {
        int parent;
        std::cin >> parent;
        nodes[i].parent = parent;
        if (parent == -1) {
            if (nodes_root != -1) {
                printf("#err1#");
            }
            nodes_root = i;
        } else {
            nodes[parent].childs.push_back(i);
        }

    }
    if (nodes_root == -1) {
        printf("#err2#");
    }

    // 遍历
    traverse(nodes_root, unit_price, 1);


    printf("%.2lf %d", final_price, final_count);

    return 0;
}