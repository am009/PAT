#include <cstdio>
#include <iostream>
#include <vector>
#include <limits.h>

int debug = 0;

struct road {
    int target;
    int value;
};
typedef struct road road;

int num_cities, current_city, target_city;
int* weights;
std::vector<road> *edges;

// Dijkstra
bool* dij_visited;
int* dij_distants;
int dij_target;
int *shortest_num;
int *num_people;

void dij_init(int from, int to) {
    for(int i=0;i<num_cities;i++) {
        if(i == current_city) {
            dij_distants[i] = 0;
            shortest_num[i] = 1;
            num_people[i] = weights[i];
        } else {
            dij_distants[i] = INT_MAX;
            shortest_num[i] = 0;
            num_people[i] = 0;
        }
        dij_visited[i] = false;
    }
}

// 访问传入的节点，并通过改节点优化一遍距离，返回最近的节点号。
int dij_visit(int closest) {
    // 访问该节点
    dij_visited[closest] = true;
    // 优化距离
    std::vector<road> &vec = edges[closest];
    for(const road& r: vec) {
        if (dij_visited[r.target]) continue;
        int dist = dij_distants[closest] + r.value;
        if (dist < dij_distants[r.target]) {
            dij_distants[r.target] = dist;
            
            shortest_num[r.target] = shortest_num[closest];

            num_people[r.target] = num_people[closest] + weights[r.target];
        } else if(dist == dij_distants[r.target]){
            shortest_num[r.target] += shortest_num[closest];

            int tmp_num_people = num_people[closest] + weights[r.target];
            if (tmp_num_people > num_people[r.target]) { num_people[r.target] = tmp_num_people; }
        }
    }
    // 找最近节点返回，如果全部被访问过返回-1
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
    int num_roads;
    std::cin >> num_cities >> num_roads >> current_city >> target_city;
    weights = new int [num_cities];
    for(int i=0;i<num_cities;i++) {
        std::cin >> weights[i];
    }
    edges = new std::vector<road>[num_cities];
    for(int i=0;i<num_roads;i++) {
        int from, to, value;
        std::cin >> from >>to >>value;
        road tmp = {.target = to, .value=value};
        edges[from].push_back(tmp);
        tmp.target = from;
        edges[to].push_back(tmp);
    }

    dij_visited = new bool[num_cities];
    dij_distants = new int[num_cities];
    shortest_num = new int[num_cities];
    num_people = new int[num_cities];
    dij_init(current_city, target_city);

    int current = current_city;
    while (current != -1) {
        current = dij_visit(current);
    }

    printf("%d %d\n", shortest_num[target_city], num_people[target_city]);

    return 0;
}