#include <cstdio>
#include <iostream>
#include <queue>

struct Player {
    unsigned int weight;
    int round_out;
};

std::queue<unsigned int> q1;
std::queue<unsigned int> q2;

struct Player* plas;
int* dist; 

typedef std::queue<unsigned int> myque;

int main () {
    unsigned int player_num, grp_num;
    std::cin >> player_num >> grp_num;
    plas = new struct Player[player_num];
    dist = new int[player_num];

    // 1. 读入
    for(int i=0;i<player_num;i++) {
        struct Player* current = &plas[i];
        current->round_out = -1;
        std::cin >> current->weight;
        dist[i] = 0;
    }
    // 2. 打乱顺序
    for(int i=0;i<player_num;i++) {
        unsigned int seq;
        std::cin >> seq;
        // 之后直接根据pop作为index取
        q1.push(seq);
    }
    // 3. 不断进行每一轮，在两个队列里相互倒
    myque* source = &q1;
    myque* dest = &q2;
    myque* tmp;
    unsigned int current_round = 0;

    // 是否所有轮结束了
    while (source->size() != 1) {
        
        // 每一轮倒一次
        while(!source->empty()) {
            int max_ind = -1;
            int current_ind;
            // 进行一轮
            for(int i=0;i<grp_num;i++) {
                current_ind = source->front();
                if (max_ind == -1) { max_ind = current_ind; }
                else if (plas[current_ind].weight > plas[max_ind].weight) {
                    plas[max_ind].round_out = current_round; // 淘汰者设置轮数
                    max_ind = current_ind;
                    dist[current_round] ++;
                } else { // 不会相等，肯定小于
                    plas[current_ind].round_out = current_round; // 淘汰者设置轮数
                    dist[current_round] ++;
                }
                { // pop 时检测empty
                    source->pop();
                    if (source->empty()) { break; }
                }
            }
            // 本轮结果留到下一轮
            dest->push(max_ind);
        }

        current_round ++;
        { tmp = source; source = dest; dest = tmp; }
    }
    int winner_ind = source->front();
    plas[winner_ind].round_out = current_round; dist[current_round] ++;
    current_round ++;
    source->pop();
    
    // dist是第i轮被淘汰的人数。 实在是没考虑到，写完了才发现名次计算不对。
    // 4. 根据轮数输出排名
    int rank = 0;

    for(int i=current_round-1;i>=0;i--) {
        int tmp = dist[i];
        dist[i] = rank+1;
        rank += tmp;
        // dist[i] = rank;
    }

    for(int i=0;i<player_num;i++) {
        if (i == 0) {
            printf("%d", dist[plas[i].round_out]);
        } else {
            printf(" %d", dist[plas[i].round_out]);
        }
    }

    return 0;
}