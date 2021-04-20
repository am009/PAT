#include <cstdio>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

typedef std::vector<int> myvec;
typedef std::vector<int>::iterator vit;

int N;
myvec* edges;
myvec distal;

int* parents;
int* dsu_count;
int *distants;
int *from_node;

void dsu_init() {
    parents = new int[N];
    dsu_count = new int[N];
    for(int i=0;i<N;i++) {
        parents[i] = i;
        dsu_count[i] = 0;
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

int dsu_union(int ind1, int ind2) {
    int p1 = dsu_find(ind1);
    int p2 = dsu_find(ind2);
    if (p1 != p2) {
        parents[p1] = p2;
    }
}

void init_dist() {
    for(int i=0;i<N;i++) {
        distants[i] = -1;
        from_node[i] = -1;
    }
}

// 从root开始遍历，返回最大距离。通过distants维护距离，通过from_node维护来向。
int BFS1(int root) {
    distants[root] = 0;
    from_node[root] = root;
    std::queue<int> que;
    que.push(root);
    int max_dist = 0;
    while(!que.empty()) {
        int front = que.front();
        myvec& vec = edges[front];
        vit it;
        for(it = vec.begin();it!=vec.end();it++) {
            // 对于边from_node[front] -> front -> *it
            if ((*it) == from_node[front]) continue; // 来的路。
            if((*it) == front) continue; // 自己走向自己
            // printf("#%d %d %d\n", from_node[front], front, (*it) );
            if (distants[(*it)] != -1 || from_node[(*it)] != -1) {
                #ifndef ONLINE_JUDGE
                printf("#err1#");
                #endif
            }
            from_node[(*it)] = front;
            distants[(*it)] = distants[from_node[(*it)]] + 1;
            if(distants[(*it)] > max_dist) {
                max_dist = distants[(*it)];
                // printf("#2#%d\n", max_dist);
            }
            que.push((*it));
        }
        que.pop();
    }
    return max_dist;
}

int main () {
    #ifndef ONLINE_JUDGE
        freopen("input.txt", "r", stdin);
    #endif
    std::cin >> N;
    edges = new myvec[N];
    dsu_init();
    for(int i=0;i<N-1;i++) {
        int a,b;
        std::cin >>a >> b; a--; b--;
        edges[a].push_back(b);
        edges[b].push_back(a);
        // 用并查集计算节点数量
        dsu_union(a, b);
    }
    for(int i=0;i<N;i++) {
        dsu_count[dsu_find(i)] ++;
    }
    int comp_count = 0;
    for(int i=0;i<N;i++) {
        if (dsu_count[i] != 0) {
            comp_count ++;
        }
    }
    if (comp_count != 1) {
        printf("Error: %d components\n", comp_count);
        return 0;
    }
    // 第一次遍历。
    distants = new int[N];
    from_node = new int[N];

    init_dist();
    int mdist = BFS1(0);
    for(int i=0;i<N;i++) {
        if (distants[i] == mdist) {
            distal.push_back(i);
        }
    }
    int random = distal[0];

    init_dist();
    mdist = BFS1(random);
    for(int i=0;i<N;i++) {
        if (distants[i] == mdist && std::find(distal.begin(), distal.end(), i) == distal.end()) {
            distal.push_back(i);
        }
    }

    std::sort(distal.begin(), distal.end());
    vit it;
    for(it = distal.begin();it != distal.end();++it) {
        printf("%d\n", (*it)+1);
    }


    return 0;
}