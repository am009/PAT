#include <cstdio>
#include <iostream>
#include <vector>

// Disjoint Set Union
typedef std::vector<int>::iterator vit;
typedef std::vector<int> vec;

int num_cities;
std::vector<int>* edges;

int* parents;
int* represents;

void dsu_init() {
    for(int j=0;j<num_cities;j++) {
        parents[j] = j;
        represents[j] = 0;
    }
}

int dsu_find(int ind) {
    int orig = ind;
    while(parents[ind] != ind) {
        ind = parents[ind];
    }
    while(orig != ind) {
        int next = parents[orig];
        parents[orig] = ind;
        orig = next;
    }
    return ind;
}

void dsu_union(int ind1, int ind2) {
    int p1 = dsu_find(ind1);
    int p2 = dsu_find(ind2);
    if(p1 != p2) {
        parents[p1] = p2;
    }
}

void dsu_calc_represents(int skip) {
    for(int i=0;i<num_cities;i++) {
        if (i == skip) continue;
        represents[dsu_find(i)] ++;
    }

}

int main () {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    #endif
    int num_edge, num_queries;
    std::cin >> num_cities >> num_edge >> num_queries;
    edges = new std::vector<int>[num_cities];
    parents = new int[num_cities];
    represents = new int[num_cities];
    for(int i=0;i<num_edge;i++) {
        int a, b;
        std::cin >> a >> b; a--;b--;
        edges[a].push_back(b);
        
        // edges[b].push_back(a); // 并查集里边可以只保存一半
    }

    for(int i=0;i<num_queries;i++) {
        int ind;std::cin >> ind; ind--;
        dsu_init();
        // 去除有两种情况
        for(int j=0;j<num_cities;j++) {
            if (j == ind) {
                continue;
            }
            vit it;
            vec & ve = edges[j];
            for(it=ve.begin(); it!=ve.end();it++) {
                if ((*it) != ind) {
                    dsu_union((*it),j);
                }
            }
        }
        dsu_calc_represents(ind);
        int count = 0;
        for(int j=0;j<num_cities;j++) {
            if (j == ind) continue;
            if (represents[j] != 0) {
                count++;
            }
        }
        printf("%d\n", count-1);
    }
    return 0;
}