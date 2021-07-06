#include <cstdio>
#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <cmath>

#ifndef ONLINE_JUDGE
#define DEBUG(X) X
#else
#define DEBUG(X) 
#endif

using namespace std;
struct node {
    string id;
    int a;
    int c;
    int m;
    int e;
};
typedef struct node node;

bool cmp(int a, int b) {
    return a > b;
}

int M, N;

int get_rank(int* arr, int target) {
    int left = 0; int right = M;
    while(left < right) {
        int mid = left + (right - left) / 2;
        if((arr[mid] > target)) {
            // printf("%d < %d: left = %d\n", arr[mid], target, mid+1);
            left = mid + 1;
        } else {
            // printf("%d >= %d: right = %d\n", arr[mid], target, mid);
            right = mid;
        }
    }
    return left;
}

int main () {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    #endif
    cin >> M >> N;
    // printf("%d %d\n", M, N);
    // node* nodes = new node[M];
    map<string, node> node_map;

    int* arank = new int[M];
    int* crank = new int[M];
    int* mrank = new int[M];
    int* erank = new int[M];
    for(int i=0;i<M;i++) {
        string id; cin >> id;
        int c,m,e; cin >> c >> m >> e;
        int a = round((c+m+e)/3.0);
        node_map[id] = (node){id, a, c, m, e};
        // nodes[i].id = id; nodes[i].a = round((c+m+e)/3.0);
        // nodes[i].c = c; nodes[i].m = m; nodes[i].e = e;

        arank[i] = a;
        crank[i] = c;
        mrank[i] = m;
        erank[i] = e;
    }
    sort(arank, arank+M, cmp);
    sort(crank, crank+M, cmp);
    sort(mrank, mrank+M, cmp);
    sort(erank, erank+M, cmp);
    // for(int i=0;i<M;i++) {
    //     printf("%d ",crank[i]);
    // }
    // printf("\n");

    for(int i=0;i<N;i++) {
        DEBUG(printf("====stu %d ====\n", i);)
        string id; cin >> id;
        node & stu = node_map[id];
        if (stu.id != id) {
            printf("N/A\n");
            continue;
        }
        // printf("tmp\n");
        char rank_chr = 'A';
        int highest_rank = get_rank(arank, stu.a);
        DEBUG(printf("getrank A %d: %d\n",stu.a, highest_rank);)
        int crk = get_rank(crank, stu.c);
        DEBUG(printf("getrank C %d: %d\n",stu.c, crk);)
        if (crk < highest_rank) {
            highest_rank = crk;
            rank_chr = 'C';
        }
        int mrk = get_rank(mrank, stu.m);
        if (mrk < highest_rank) {
            highest_rank = mrk;
            rank_chr = 'M';
        }
        int erk = get_rank(erank, stu.e);
        if (erk < highest_rank) {
            highest_rank = erk;
            rank_chr = 'E';
        }
        printf("%d %c\n", highest_rank+1, rank_chr);
    }



    return 0;
}