#include <cstdio>
#include <iostream>
#include <vector>
#include <queue>

typedef std::vector<int>::iterator vit;
typedef std::vector<int> myvec;

int NUM ,LEVEL;
std::vector<int>* edges;

bool* visited;
// int* from; 单向边，不用from。
int *depth;
void bfs_init () {
    for(int i=0;i<NUM;i++) {
        visited[i] = false;
        depth[i] = -1;
    }
}

// 深度最多Level 返回数量
int bfs_visit(int root) {
    std::queue<int> que;
    visited[root] = true;
    depth[root] = 0;
    que.push(root);
    int count = 0;
    while(!que.empty()) {
        int front = que.front();
        vit it;
        myvec& vec = edges[front];
        for(it=vec.begin(); it!= vec.end();it++) {
            // front -> *it
            if(visited[(*it)]) continue;
            visited[(*it)] = true;
            depth[(*it)] = depth[front] + 1;
            count ++;
            if(depth[(*it)] < LEVEL) { // depth = LEVEL的边不用继续遍历
                que.push((*it));
            }
        }
        que.pop();
    }
    return count;
}

int main () {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    #endif
    std::cin >> NUM >> LEVEL;
    edges = new std::vector<int>[NUM];
    for(int i=0;i<NUM;i++) {
        int count;
        std::cin >> count;
        for (int j=0;j<count;j++) {
            int target;
            std::cin >> target; target--;
            edges[target].push_back(i); // 反向边
        }
    }

    visited = new bool[NUM];
    depth = new int[NUM];

    int count;
    std::cin >> count;
    for(int i=0;i<count;i++) {
        int root;
        std::cin >> root; root--;
        bfs_init();
        int count = bfs_visit(root);
        printf("%d\n", count);
    }

    return 0;
}