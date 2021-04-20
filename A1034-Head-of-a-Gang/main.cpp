#include <cstdio>
#include <iostream>
#include <map>
#include <string>
#include <queue>
#include <algorithm>



int weight_matrix[2001][2001];
int pweight[2001];

int N, threthold;

std::map<std::string, int> name_map;
typedef std::map<std::string, int>::iterator mit;
int ID_count = 0;
// std::string *index2name[2001];
int name2index(const char* name) {
    std::string s(name);
    name_map.find(s);
    mit it = name_map.find(s);
    if (it != name_map.end()) {
        return (*it).second;
    } else {
        name_map.insert(std::pair<std::string, int>(s, ID_count));
        ID_count++;
        return ID_count-1;
    }
}

std::string index2name(int ind) {
    mit it;
    for(it = name_map.begin();it!=name_map.end();it++) {
        if ((*it).second == ind) {
            return (*it).first;
        }
    }
    return std::string("");
}

bool *visited;
int *from_node;
void bfs_init() {
    for(int i=0;i<ID_count;i++) {
        visited[i] = false;
        from_node[i] = -1;
    }
}
int get_unvisit() {
    for(int i=0;i<ID_count;i++) {
        if (visited[i] == false) return i;
    }
    return -1;
}

struct bfs_result {
    int comp_weight;
    int mem_count;
    int bellwether;
};

struct bfs_result bfs_visit(int start) {
    std::queue<int> que;
    struct bfs_result ret = {0,0,0};
    from_node[start] = start;
    visited[start] = true;
    ret.mem_count ++;
    ret.bellwether = start;
    ret.comp_weight = 0;
    que.push(start);
    while(!que.empty()) {
        int front = que.front();
        for(int i=0;i<ID_count;i++) {
            if (weight_matrix[front][i] == -1 && weight_matrix[i][front] == -1) continue;
            if (i == front) continue;
            if (weight_matrix[front][i] != -1) ret.comp_weight += weight_matrix[front][i];
            if (weight_matrix[i][front] != -1) ret.comp_weight += weight_matrix[i][front];
            if (i == from_node[front]) continue;
            if (visited[i] == true) continue;
            from_node[i] = front;
            visited[i] = true;
            ret.mem_count ++;
            if (pweight[i] > pweight[ret.bellwether]) {
                ret.bellwether = i;
            }
            que.push(i);
        }
        que.pop();
    }
    return ret;
}

std::vector<struct bfs_result> result_vec;

int main () {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    #endif
    for(int i=0;i<2001;i++) {
        for(int j=0;j<2001;j++) {
            weight_matrix[i][j] = -1;
        }
        pweight[i] = 0;
    }
    std::cin >> N >> threthold;

    // if (N<=1) {
    //     printf("0\n");
    //     return 0;
    // }

    // 读入,把名字映射到下标，计算每个人的总边权。
    // 使用map保存名字到下标，顺序分配下标
    // 使用邻接表保存边关系，那就需要成员是一个结构体了（目标，权重）
    // 这次还是用邻接矩阵
    // 输入的时候同时计算每个人的总边权。
    for(int i=0;i<N;i++) {
        char buf1[6];
        char buf2[6];
        int weight;
        scanf("%s%s%d",buf1, buf2, &weight);
        int ind1 = name2index(buf1);
        int ind2 = name2index(buf2);
        weight_matrix[ind1][ind2] = weight;
        // weight_matrix[ind2][ind1] = weight;
        pweight[ind1] += weight;
        pweight[ind2] += weight;
    }

    // 图遍历，得到每个连通块的总边权，边权最大的人，人的数量
    // 使用一个bool数组保存是否访问过。

    visited = new bool[ID_count];
    from_node = new int[ID_count];
    bfs_init(); // init bool array
    int next = get_unvisit();
    int comp_count = 0;
    while (next != -1) {
        // printf("#%d\n", next);
        comp_count ++;
        struct bfs_result ret = bfs_visit(next); // 返回权重最大的人，人数量，以及连通块的总权重
        if (ret.comp_weight > 2*threthold && ret.mem_count > 2) {
            result_vec.push_back(ret);
        }
        next = get_unvisit();
    }

    std::sort(result_vec.begin(), result_vec.end(), [](struct bfs_result a, struct bfs_result b) { 
        return index2name(a.bellwether) < index2name(b.bellwether); 
    });

    printf("%d\n", result_vec.size());

    std::vector<struct bfs_result>::iterator it;
    for(it = result_vec.begin(); it != result_vec.end();++it) {
        printf("%s %d\n", index2name((*it).bellwether).c_str(), (*it).mem_count);
        // printf("%s %d %d\n", index2name((*it).bellwether).c_str(), (*it).mem_count, (*it).comp_weight);
    }

    return 0;
}