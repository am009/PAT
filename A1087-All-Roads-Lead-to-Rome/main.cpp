#include <cstdio>
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <climits>
#include <stack>

#ifndef ONLINE_JUDGE
#define DEBUG(X) X
#else
#define DEBUG(X) 
#endif

int num_cities;
std::map<std::string, int> name2ind;
std::vector<std::string> ind2name;
int ind_counter = 0;
int ROM_IND = -1;
int get_ind(std::string s) {
    auto it = name2ind.find(s);
    if (it != name2ind.end()) {
        return (*it).second;
    } else {
        int ind = ind_counter; ind_counter ++;
        name2ind.insert(std::pair<std::string, int>(s, ind));
        if (ind2name.size() != ind) {
            DEBUG(printf("#err1#");)
        }
        if (ind >= num_cities) {
            DEBUG(printf("#err4#");)
        }
        if (s == std::string("ROM")) {
            ROM_IND = ind;
        }
        ind2name.push_back(s);
        return ind;
    }
}

int *happiness;

struct road
{
    int to;
    int cost;
};
std::vector<road> *edges;

// dij
bool* dij_visited;
int *dij_distances;
int dij_start;

//
int *dij_route_count;
int *dij_prev;
int *dij_happ;
int *dij_node_count;

void dij_init(int s) {
    dij_start = s;
    for(int i=0;i<num_cities;i++) {
        dij_visited[i] = false;
        dij_prev[i] = -1;
        dij_happ[i] = 0;
        
        if(i == dij_start) {
            dij_distances[i] = 0;
            dij_route_count[i] = 1;
            dij_node_count[i] = 0;
        } else {
            dij_distances[i] = INT_MAX;
            dij_route_count[i] = 0;
            dij_node_count[i] = INT_MAX;
        }
    }
}

int dij_main(int to_visit) {
    dij_visited[to_visit] = true;

    for(road &r: edges[to_visit]) {
        int new_dist = dij_distances[to_visit] + r.cost;
        int new_happ = dij_happ[to_visit] + happiness[r.to];
        int new_node_count = dij_node_count[to_visit] + 1;
        if (new_dist < dij_distances[r.to]) {
            dij_distances[r.to] = new_dist;
            dij_prev[r.to] = to_visit;
            dij_route_count[r.to] = dij_route_count[to_visit];
            dij_happ[r.to] = new_happ;
            dij_node_count[r.to] = new_node_count;
        } else if (new_dist == dij_distances[r.to]) { // 之后可以不更新distance。
            dij_route_count[r.to] += dij_route_count[to_visit];
            // 之后的标尺不影响最短路径条数的计算
            if (dij_happ[r.to] < new_happ) { // happ 最大
                dij_prev[r.to] = to_visit;
                dij_happ[r.to] = new_happ;
                dij_node_count[r.to] = new_node_count;
            } else if(dij_happ[r.to] == new_happ) {
                if(new_node_count < dij_node_count[r.to]) { // node_count 最小
                    dij_prev[r.to] = to_visit;
                    dij_node_count[r.to] = new_node_count;
                }
            }

        }
    }

    int min_dist = INT_MAX;
    int min_ind = -1;
    for(int i=0;i<num_cities;i++) {
        if (dij_visited[i]) continue;
        if(dij_distances[i] < min_dist) {
            min_dist = dij_distances[i];
            min_ind = i;
        }
    }

    return min_ind;
}

int main () {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    #endif
    int road_count;
    std::cin >> num_cities >> road_count;
    std::string s;
    std::cin >> s;
    int start = get_ind(s);
    if(start != 0) {
        DEBUG(printf("#err2#");)
    }
    happiness = new int[num_cities];
    happiness[0] = 0;
    for(int i=1;i<num_cities;i++) {
        int hap;
        std::cin >> s >> hap;
        int ind = get_ind(s);
        if (ind != i) {
            DEBUG(printf("#err3#");)
        }
        happiness[i] = hap;
        // printf("%s %d\n", s.c_str(), hap);
    }
    edges = new std::vector<road>[num_cities];
    for(int i=0;i<road_count;i++) {
        std::string from, to;
        int cost;
        std::cin >> from >> to >> cost;
        int f_ind = get_ind(from);
        int to_ind = get_ind(to);
        road tmp = {to_ind, cost};
        edges[f_ind].push_back(tmp);
        tmp.to = f_ind;
        edges[to_ind].push_back(tmp);
    }

    dij_distances = new int [num_cities];
    dij_visited = new bool[num_cities];
    dij_route_count = new int[num_cities];
    dij_prev = new int[num_cities];
    dij_happ = new int[num_cities];
    dij_node_count = new int[num_cities];
    // 标尺：cost--> happiness -> 经过的节点数量
    dij_init(0);
    int tmp = 0;
    while(tmp != -1) {
        tmp = dij_main(tmp);
    }

    // printf("%d", ROM_IND);
    // for(int i=0;i<num_cities;i++) {
    //     printf("%s %d\n", ind2name[i].c_str(), dij_distances[i]);
    // }
    printf("%d %d %d %d\n", dij_route_count[ROM_IND], dij_distances[ROM_IND], dij_happ[ROM_IND], dij_happ[ROM_IND]/dij_node_count[ROM_IND]);
    std::stack<int> sta;
    tmp = ROM_IND;
    sta.push(tmp);
    while(tmp != 0) {
        tmp = dij_prev[tmp];
        sta.push(tmp);
    }
    
    printf("%s", ind2name[sta.top()].c_str());
    sta.pop();
    while(!sta.empty()) {
        printf("->%s", ind2name[sta.top()].c_str());
        sta.pop();
    }


    return 0;
}
