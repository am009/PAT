#include <cstdio>
#include <iostream>
#include <vector>
#include <climits>
#include <stack>

#ifndef ONLINE_JUDGE
#define D(X) X
#else
#define D(X) 
#endif

struct edge {
    int to;
    int dist;
    int cost;
};
typedef struct edge edge;

int num_cities, start, destination;
std::vector<edge> *edges;

// dij
bool* dij_visited;
int* dij_distants;
int dij_start;

int *dij_prev;
int *dij_cost;

void dij_init(int s) {
    dij_start = s;
    for(int i=0;i<num_cities;i++) {
        if (i == dij_start) {
            dij_distants[i] = 0;
            dij_cost[i] = 0;
        } else {
            dij_distants[i] = INT_MAX;
            dij_cost[i] = INT_MAX;
        }
        dij_prev[i] = -1;
        dij_visited[i] = false;
    }
}

int dij_main(int to_visit) {
    dij_visited[to_visit] = true;
    for(edge &e: edges[to_visit]) {
        int new_dist = dij_distants[to_visit] + e.dist;
        int new_cost = dij_cost[to_visit] + e.cost;
        if (new_dist < dij_distants[e.to]) {
            dij_distants[e.to] = new_dist;
            dij_prev[e.to] = to_visit;
            dij_cost[e.to] = new_cost;
        } else if (new_dist == dij_distants[e.to]) {
            // 比较两个路径的边权
            if (new_cost < dij_cost[e.to]) {
                dij_distants[e.to] = new_dist; // 可以不加
                dij_prev[e.to] = to_visit;
                dij_cost[e.to] = new_cost;
            }
        }
    }
    // 找最小距离返回
    int min_dist = INT_MAX;
    int min_ind = -1;
    for(int i=0;i<num_cities;i++) {
        if (dij_visited[i]) continue;
        if (dij_distants[i] < min_dist) {
            min_dist = dij_distants[i];
            min_ind = i;
        }
    }
    return min_ind;
}

int main () {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    #endif
    int edge_count;
    std::cin >> num_cities >> edge_count >> start >> destination;
    edges = new std::vector<edge>[num_cities];
    for(int i=0;i<edge_count;i++) {
        int c1,c2,dist,cost;
        std::cin >> c1 >> c2 >> dist >> cost;
        edge tmp = {c2, dist, cost};
        // 无向边
        edges[c1].push_back(tmp);
        tmp.to = c1;
        edges[c2].push_back(tmp);
    }

    dij_visited = new bool[num_cities];
    dij_distants = new int[num_cities];
    dij_prev = new int[num_cities];
    dij_cost = new int[num_cities];
    dij_init(start);
    int tmp = start;
    while(tmp != -1) {
        tmp = dij_main(tmp);
    }

    // for(int i=0;i<num_cities;i++) {
    //     printf("%d ",dij_distants[i]);
    // }
    std::stack<int> sta;
    tmp = destination;
    sta.push(tmp);
    while(tmp != start){
        tmp = dij_prev[tmp];
        sta.push(tmp);
    }

    printf("%d", sta.top());
    sta.pop();
    while(!sta.empty()) {
        printf(" %d", sta.top());
        sta.pop();
    }

    printf(" %d %d\n",dij_distants[destination], dij_cost[destination]);

    return 0;
}