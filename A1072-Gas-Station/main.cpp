#include <cstdio>
#include <iostream>
#include <vector>
#include <climits>
#include <cmath>

#ifndef ONLINE_JUDGE
#define DEBUG(X) X
#else
#define DEBUG(X) 
#endif

int num_houses, num_gases, srv_range, node_count;


// 节点编号，从0~numhouces是房子，num_houses~num_houses+numgases是加油站
char buf[0x100];
// 读入的时候如果以G开头，则加上num_houses
int read_ind() {
    scanf("%s", buf);
    int ind;
    if(buf[0] == 'G') {
        sscanf(buf+1, "%d", &ind);
        ind --;
        ind += num_houses;
    } else {
        sscanf(buf, "%d", &ind);
        ind --;
    }
    return ind;
}

struct edge
{
    int to;
    int dist;
};

std::vector<edge> *edges;

// dij
bool* dij_visited;
int* dij_distances;
int dij_start;

void dij_init(int s) {
    dij_start = s;
    for(int i=0;i<node_count;i++) {
        if (i == s) {
            dij_distances[i] = 0;
        } else {
            dij_distances[i] = INT_MAX;
        }
        dij_visited[i] = false;
    }
}

int dij_main(int to_visit) {
    dij_visited[to_visit] = true;
    for(edge &e: edges[to_visit]) {
        // printf("%d %d ",e.to, e.dist);
        int new_dist = dij_distances[to_visit] + e.dist;
        if (new_dist < dij_distances[e.to]) {
            dij_distances[e.to] = new_dist;
        } else if (new_dist == dij_distances[e.to]) {
            ;
        }
    }

    int min_distance = INT_MAX;
    int min_ind = -1;
    for(int i=0;i<node_count;i++) {
        if (dij_visited[i]) continue;
        if (dij_distances[i] < min_distance) {
            min_distance = dij_distances[i];
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
    std::cin >> num_houses >> num_gases >> edge_count >> srv_range;
    node_count = num_houses + num_gases;
    edges = new std::vector<edge>[node_count];
    for(int i=0;i<edge_count;i++) {
        int i1 = read_ind();
        int i2 = read_ind();
        int dist;
        std::cin >> dist;
        edge tmp = {i2, dist};
        // printf("%d %d %d\n", i1, i2, dist);
        edges[i1].push_back(tmp);
        tmp.to = i1;
        edges[i2].push_back(tmp);
    }

    dij_distances = new int[node_count];
    dij_visited = new bool[node_count];
    // 对每个gas，调用dij，计算标尺，记录其中标尺最好的。不需要路径
    int max_min_dist = -1;
    double min_arv_dist = INT_MAX;
    int best_ind = -1;
    for(int gind=0; gind <num_gases;gind++) {
        dij_init(num_houses + gind);
        int tmp = num_houses + gind;
        while( tmp != -1) {
            tmp = dij_main(tmp);
        }
        // 检查标尺 
        // 判断是否在服务范围内
        // 顺便计算最小距离 计算平均距离
        bool valid = true;
        int min_dist = INT_MAX;
        double dist_sum = 0;
        for(int i=0;i<num_houses;i++) {
            // printf("%d ", dij_distances[i]);
            if (dij_distances[i] > srv_range) {
                valid = false;
                break;
            }
            if (dij_distances[i] < min_dist) {
                min_dist = dij_distances[i];
            }
            dist_sum += dij_distances[i];
        }
        // printf("\n");
        // if (valid) {
        //     printf("%d %d %lf\n", gind, min_dist, dist_sum);
        // } else { puts("invalid"); }
        if (valid) {
            // 进一步判断
            dist_sum = dist_sum / (double)num_houses;
            // 先看最小距离最大值
            if (max_min_dist < min_dist) {
                max_min_dist = min_dist;
                min_arv_dist = dist_sum;
                best_ind = gind;
            } else if (max_min_dist == min_dist) {
                // 再看平均距离最小
                if (dist_sum < min_arv_dist) {
                    max_min_dist = min_dist;
                    min_arv_dist = dist_sum;
                    best_ind = gind;
                } else if(dist_sum == min_arv_dist) {
                    // 再看index最小
                    if (gind < best_ind) {
                        max_min_dist = min_dist;
                        min_arv_dist = dist_sum;
                        best_ind = gind;
                    }
                }
            }
        }
    }

    if (best_ind == -1) {
        printf("No Solution\n");
    } else {
        printf("G%d\n%d.0 %.1lf\n", best_ind+1, max_min_dist, round(min_arv_dist * 10.0) / 10.0);
    }

    return 0;
}