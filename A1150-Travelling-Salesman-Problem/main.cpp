#include <cstdio>
#include <iostream>
#include <set>
#include <map>

#ifndef ONLINE_JUDGE
#define DEBUG(X) X
#else
#define DEBUG(X) 
#endif

// cities are numbered from 1 to N
int node_count;
struct edge {
    int to;
    int dist;
};
typedef struct edge edge;
std::map<int, edge>* edges;

struct path {
    int ind, dist;
    bool is_cycle, is_simple, is_all_visited;
};

void init_path(struct path &p) {
    p.ind = -1;
    p.dist = 0;
    p.is_cycle = true;
    p.is_simple = true;
    p.is_all_visited = true;
}

int main () {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    #endif
    int edge_count;
    std::cin >> node_count >> edge_count;
    edges = new std::map<int, edge>[node_count];
    for(int i=0;i<edge_count;i++) {
        int n1, n2, dist;
        std::cin >>n1 >>n2 >>dist; n1--; n2--;
        edge e;
        e.dist = dist;
        e.to = n2;
        edges[n1].emplace(n2, e);
        e.to = n1;
        edges[n2].emplace(n1, e);
    }

    int pcount;
    std::cin >> pcount;
    struct path best;
    init_path(best);
    for(int i=1;i<=pcount;i++) {
        struct path current;
        init_path(current);
        current.ind = i;
        int ncount;
        std::cin >> ncount;
        bool* visited = new bool[node_count];
        int * nodes = new int[ncount];
        // 数量初筛
        // if (ncount <= node_count) {
        //     current.is_all_visited = false;
        //     goto last;
        // }
        // read and init
        for(int j=0;j<ncount;j++) {
            std::cin >> nodes[j]; nodes[j]--;
        }
        for (int j=0;j<node_count;j++) {
            visited[j] = false;
        }
        // 是否闭合
        // if (nodes[0] != nodes[ncount-1]) {
        //     current.is_cycle = false;
        //     goto last;
        // }

        int current_visit = nodes[0];
        for(int j=1;j<ncount;j++) {
            int next_visit = nodes[j];
            // 确保有路 current -> next
            auto it = edges[current_visit].find(next_visit);
            if (it == edges[current_visit].end()) {
                current.is_cycle = false;
                current.dist = -1;
                DEBUG(printf("#err1: no such path from %d to %d.#\n", current_visit+1, next_visit+1);)
                goto last;
            }
            current.dist += (*it).second.dist;
            if (visited[next_visit] == true) {
                current.is_simple = false;
            }
            visited[next_visit] = true;
            current_visit = next_visit;
        }

        // check all visited
        for(int j=0;j<node_count;j++) {
            if (visited[j] == false) {
                DEBUG(printf("#%d not visited#\n", j+1);)
                current.is_all_visited = false;
            }
        }
    
    last:
        if (current.dist == -1) {
            printf("Path %d: %s ", current.ind, "NA");
        } else {
            printf("Path %d: %d ", current.ind, current.dist);
        }
        // todo NA
        if(current.is_cycle && current.is_all_visited) {
            if (current.is_simple) {
                printf("(TS simple cycle)\n");
            } else {
                printf("(TS cycle)\n");
            }
            if (best.ind == -1 || current.dist < best.dist) {
                best = current;
            }
        } else {
            // DEBUG(printf("#is_cycle: %d, is_all_visited: %d#\n", current.is_cycle, current.is_all_visited);)
            printf("(Not a TS cycle)\n");
        }

    }

    printf("Shortest Dist(%d) = %d\n", best.ind, best.dist);

    return 0;
}