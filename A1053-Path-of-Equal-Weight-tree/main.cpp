#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>

struct node {
    int weight;
    int child_count;
    int *childs;
    int path_w;
};
typedef struct node node;

int COUNT;
int WEIGHT;

node* nodes;

std::vector<std::vector<int>> paths;

std::vector<int> DFS_weight_path;
// visit and calc weight
void DFS(int root_ind, int prev_weight) {
    node* current = &nodes[root_ind];

    DFS_weight_path.push_back(current->weight);

    int current_weight = prev_weight + current->weight;
    int count = current->child_count;
    int* childs = current->childs;
    if (count > 0) { // non leaf
        if (current_weight < WEIGHT) { // cut
            for (int i=0;i<count;i++) {
                DFS(childs[i], current_weight);
            }
        } 
    } else { // leaf
        if (current_weight == WEIGHT) {
            // save a copy of path
            paths.push_back(DFS_weight_path);
        }
    }

    DFS_weight_path.pop_back();
}

int main () {
    int count;
    std::cin >> COUNT >> count >> WEIGHT;
    nodes = new node[COUNT];
    // line 2 and init nodes
    for(int i=0;i<COUNT;i++) {
        nodes[i].child_count = 0;
        nodes[i].path_w = -1;
        nodes[i].childs = nullptr;
        std::cin >> nodes[i].weight;
    }
    // `count` lines
    for (int i=0;i<count;i++) {
        int id, count2;
        std::cin >>id >> count2;
        node* current = &nodes[id];
        current->child_count = count2;
        current->childs = new int[count2];
        for(int j=0;j<count2;j++) {
            std::cin >> current->childs[j];
        }
    }

    DFS(0, 0);
    
    std::sort(paths.begin(), paths.end(), [](std::vector<int> v1, std::vector<int> v2) {
        std::vector<int>::iterator it1, it2;
        for(it1=v1.begin(),it2=v2.begin();*it1 == *it2 && it1 != v1.end() && it2 != v2.end();it1++,it2++) { // 我的玄学！！
            ;
        }
        if(it1 == v1.end() && it2 == v2.end()) {
            return false;
        }
        if (it1 == v1.end()) {
            // return -1 > *it2;
            return false;
        }
        if(it2 == v2.end()) {
            // return *it1 > -1;
            return true;
        }
        return *it1 > *it2;
    });
    // std::sort(paths.begin(), paths.end(), [](std::vector<int> a, std::vector<int> b) {
    //     	if(a.empty() || b.empty()){
	// 	return a.empty();
	// }
	// int minL = std::min(a.size(), b.size());
	// for(int i = 0; i < minL; i++){
	// 	if(a[i] != b[i]) return a[i] > b[i]; // 关键在这里的大于号 
	// }
	// return false; // 我的天！！玄学 
    // });

    std::vector<std::vector<int>>::iterator it;
    for (it = paths.begin();it != paths.end();it++) {
        std::vector<int>::iterator it1;
        int init = true;
        for(it1=(*it).begin(); it1 != (*it).end();it1++ ) {
            if(init) {
                init = false;
                printf("%d", *it1);
            } else {
                printf(" %d", *it1);
            }
        }
        printf("\n");
    }

    return 0;
}