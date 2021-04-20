#include <cstdio>
#include <iostream>
#include <vector>
#include <climits>
#include <stack>

#ifndef ONLINE_JUDGE
#define DEBUG(X) X
#else
#define DEBUG(X) 
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

std::vector<int> *dij_prev;

void dij_init(int s) {
    dij_start = s;
    for(int i=0;i<num_cities;i++) {
        if (i == dij_start) {
            dij_distants[i] = 0;
        } else {
            dij_distants[i] = INT_MAX;
        }
        dij_visited[i] = false;
    }
}

int dij_main(int to_visit) {
    dij_visited[to_visit] = true;
    for(edge &e: edges[to_visit]) {
        int new_dist = dij_distants[to_visit] + e.dist;
        if (new_dist < dij_distants[e.to]) {
            dij_distants[e.to] = new_dist;
            dij_prev[e.to].clear();
            dij_prev[e.to].push_back(to_visit);
        } else if (new_dist == dij_distants[e.to]) {
            dij_prev[e.to].push_back(to_visit);
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

// dfs
std::vector<int> dfs_tmp, best;
int min_cost = INT_MAX;

int get_edge_cost(int from, int to) {
    for(edge &e: edges[from]) {
        if (e.to == to) {
            return e.cost;
        }
    }
    DEBUG(printf("#ERR1#");)
    return INT_MAX - 10000;
}

void DFS(int to_visit) {
    if (to_visit == start) {
        int from = -1;
        int to = start;
        int cost = 0;
        for(auto it=dfs_tmp.rbegin();it != dfs_tmp.rend();++it ) {
            from = to;
            to = (*it);
            cost += get_edge_cost(from, to);
        }
        if (cost < min_cost) {
            min_cost = cost;
            best = dfs_tmp;
        }

        return;
    }
    dfs_tmp.push_back(to_visit);
    for(int &i: dij_prev[to_visit]) {
        DFS(i);
    }
    dfs_tmp.pop_back();
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
    dij_prev = new std::vector<int>[num_cities];
    dij_init(start);
    int tmp = start;
    while(tmp != -1) {
        tmp = dij_main(tmp);
    }

    // for(int i=0;i<num_cities;i++) {
    //     printf("%d ",dij_distants[i]);
    // }

    DFS(destination);

    printf("%d", start);
    while(!best.empty()) {
        printf(" %d", best.back());
        best.pop_back();
    }

    printf(" %d %d\n",dij_distants[destination], min_cost);

    return 0;
}