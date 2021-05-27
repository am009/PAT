#include <cstdio>
#include <iostream>
#include <set>

#ifndef ONLINE_JUDGE
#define DEBUG(X) X
#else
#define DEBUG(X) 
#endif

int node_count, edge_count;

std::set<int>* edges;

bool has(std::set<int> vec, int ele) {
    return vec.find(ele) != vec.end();
}

bool finder(int count, int* query, int ele) {
    for(int i=0;i<count;i++) {
        if(query[i] == ele) {
            return true;
        }
    }
    return false;
}

void solve(int count, std::set<int> query) {
    for(auto it=query.begin();it!=query.end();++it) {
        auto it2=it;
        ++it2;
        for(;it2!=query.end();++it2) {
            // *it 能连到*it2
            if(edges[(*it)].find(*it2) == edges[(*it)].end()) {
                printf("Not a Clique\n");
                return;
            }
        }
    }
    // DEBUG(printf("-----\n");)
    // return;
    // // 是否存在非团内节点，能联通所有节点。
    for(int i=0;i<node_count;i++) {
        if (query.find(i) != query.end()) {continue;}
        bool connected = true;
        for(auto it=query.begin();it!=query.end();++it) {
            if (edges[i].find(*it) == edges[i].end()) {
                connected = false;
                break;
            }
        }
        if (connected) {
            printf("Not Maximal\n");
            return;
        }
    }

    printf("Yes\n");
    return;
}

int main () {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    #endif
    std::cin >> node_count >> edge_count;
    edges = new std::set<int>[node_count];
    for(int i=0;i<edge_count;i++) {
        int from, to;
        std::cin >> from >> to; from--;to--;
        edges[from].insert(to);
        edges[to].insert(from);
    }

    int count;
    std::cin >> count;
    for(int i=0;i<count;i++) {
        std::set<int> query;
        if (!query.empty()) {DEBUG(printf("#err3#\n");)}
        int c2; std::cin >> c2;
        for(int j=0;j<c2;j++) {
            int q;
            std::cin >> q; q--;
            query.insert(q);
        }
        solve(c2, query);
    }


    return 0;
}