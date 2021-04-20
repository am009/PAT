#include <cstdio>
#include <iostream>
#include <vector>
#include <queue>
typedef std::vector<int> vec;
typedef std::vector<int>::iterator vit;

int num_cities;
std::vector<int>* edges;
int avoid;

bool* is_in_queue;

void bfs_init() {
    for (int i=0;i<num_cities;i++) {
        is_in_queue[i] = false;
    }
}

int get_unvisit() {
    for (int i=0;i<num_cities;i++) {
        if (i == avoid) continue;
        if(is_in_queue[i] == false) return i;
    }
    return -1;
}

void bfs_traverse(int ind) {
    if (ind == avoid) {
        #ifndef ONLINE_JUDGE
        printf("#err1#");
        #endif
    }
    is_in_queue[ind] = true;
    std::queue<int> que;
    que.push(ind);
    while(!que.empty()) {
        int front = que.front();
        vec &ve = edges[front];
        vit it;
        for(it=ve.begin();it!=ve.end();it++) {
            if ((*it) == avoid) continue;
            if (!is_in_queue[(*it)]) { 
                is_in_queue[(*it)] = true; 
                que.push((*it));
            }
        }
        que.pop();
    }
}

int main () {
    int num_edge, num_queries;
    std::cin >> num_cities >> num_edge >> num_queries;
    edges = new std::vector<int>[num_cities];
    is_in_queue = new bool[num_cities];

    for(int i=0;i<num_edge;i++) {
        int a, b;
        std::cin >> a >> b; a--;b--;

        edges[a].push_back(b);
        edges[b].push_back(a);
    }


    for(int i=0;i<num_queries;i++) {
        std::cin >> avoid; avoid--;
        bfs_init();
        int ind = get_unvisit();
        int count = 0;
        while(ind != -1) {
            count ++;
            bfs_traverse(ind);
            ind = get_unvisit();
        }
        printf("%d\n", count-1);
    }
    return 0;
}