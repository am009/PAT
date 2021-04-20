#include <cstdio>
#include <iostream>
#include <vector>
#include <climits>

#ifndef ONLINE_JUDGE
#define DEBUG(X) X
#else
#define DEBUG(X) 
#endif

int Capacity, num_stations, target;
int* bike_nums;

struct road
{
    int to;
    int dist;
};
using road = struct road;

std::vector<road> *edges;

// dij
bool* visited;
int* distance;

std::vector<int> *dij_prev;

void dij_init() {
    for(int i=0;i<num_stations;i++) {
        visited[i] = false;
        if (i == 0) {
            distance[i] = 0;
        } else {
            distance[i] = INT_MAX;
        }
    }
}
// 访问传入的节点（是距离最近的），优化一遍路径，并搜索一遍最近未访问节点。
int dij_main(int root) {
    if (visited[root] == true) { 
        DEBUG(printf("#err1#");)
    }
    visited[root] = true;
    // traverse root's edge
    for(road& n: edges[root]) {
        int new_dist = distance[root] + n.dist;
        if (new_dist < distance[n.to]) {
            distance[n.to] = new_dist;
            dij_prev[n.to].clear();
            dij_prev[n.to].push_back(root);
        } else if (new_dist == distance[n.to]) {
            dij_prev[n.to].push_back(root);
        }
    }
    int min_dist = INT_MAX;
    int min_ind = -1;
    for (int i=0;i<num_stations;i++) {
        if (visited[i]) continue;
        if (distance[i] < min_dist) {
            min_dist = distance[i];
            min_ind = i;
        }
    }
    return min_ind;
}

// dfs

std::vector<int> c_path, best_path;
int best_bring = INT_MAX;
int best_left = INT_MAX;
void traverse(int root) {
    if (root == 0) {
        // 计算整个路径的参数，然后和最好参数比较即可。
        // adj最终为一开始带的自行车数量，left_bike为最后剩下的自行车数量。
        int adj = 0;
        int left_bike = 0;
        for (auto i = c_path.rbegin(); i != c_path.rend(); ++i) {
            int n = (*i);
            left_bike += (bike_nums[n] - Capacity);
            if (left_bike < adj) {
                adj = left_bike;
            }
        }
        adj = -adj;
        left_bike += adj;
        // 判断是否更优
        // 目标是一开始带的少，最后带回去的也少。
        if (adj < best_bring) {
            best_path = c_path;
            best_bring = adj;
            best_left = left_bike;
        } else if (adj == best_bring) {
            if (left_bike < best_left) {
                best_path = c_path;
                best_bring = adj;
                best_left = left_bike;
            }
        }

        return;
    }
    c_path.push_back(root);
    // 继续深入
    for(int &item: dij_prev[root]) {
        traverse(item);
    }
    c_path.pop_back();
}

int main () {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    #endif
    int edge_count;
    std::cin >> Capacity >> num_stations >> target >> edge_count;
    num_stations ++; // for center
    Capacity = Capacity / 2;
    bike_nums = new int[num_stations];
    for(int i=1;i<num_stations;i++) { // skip center
        std::cin >> bike_nums[i];
    }
    edges = new std::vector<road>[num_stations];
    for(int i=0;i<edge_count;i++) {
        int from, to, dist;
        std::cin >> from >> to >> dist;
        road r = {to, dist};
        edges[from].push_back(r);
        r.to = from;
        edges[to].push_back(r); // 无向边
    }

    // dij
    visited = new bool[num_stations];
    distance = new int[num_stations];
    dij_prev = new std::vector<int>[num_stations];
    dij_init();
    int ind = 0;
    while(ind != -1) {
        ind = dij_main(ind);
    }

    // for(int i=0;i<num_stations;i++) {
    //     printf("%d ",distance[i]);
    //     printf("#%d: ");
    //     for(int &j: dij_prev[i]) {
    //         printf("%d ", j);
    //     }
    //     printf("\n");
    // }

    // traverse for best road
    // 倒过来当作一棵树，然后深度优先遍历吧，不动态规划了。
    traverse(target);

    printf("%d 0", best_bring);
    for(auto i=best_path.rbegin(); i!= best_path.rend(); ++i) {
        printf("->%d", (*i));
    }
    printf(" %d\n", best_left);
    


    return 0;
}