#include <cstdio>
#include <iostream>
#include <queue>


int M,N,L,T;
// MxNxL threshold
// map[L][M][N]
short map[60][1286][128];
bool met[60][1286][128];
int answer = 0;

int dN[6] = {0,0,0,0,1,-1};
int dM[6] = {0,0,1,-1,0,0};
int dL[6] = {1,-1,0,0,0,0};


struct Coor {
    int l;
    int m;
    int n;

    short get_map() {
        return map[this->l][this->m][this->n];
    }

    bool get_met() {
        return met[this->l][this->m][this->n];
    }

    void set_met() {
        met[this->l][this->m][this->n] = true;
    }
};
typedef struct Coor Coor;

bool valid_coor(int l, int m, int n) {
    return l>=0 && l<L && m>=0 && m<M && n>=0 && n<N;
}

void BFS(int l, int m, int n) {
    met[l][m][n] = true;
    std::queue<Coor> que;
    // 进队列前必定是map为1
    que.push(Coor{l,m,n}); // 进队列前met 设为true，并增加完volume。
    int current_volume = 1;
    while(!que.empty()) {
        Coor front = que.front();
        // 四周加入队列，
        for(int i=0;i<6;i++) {
            Coor next = {front.l + dL[i], front.m + dM[i], front.n + dN[i]};
            // 越界
            if (!valid_coor(next.l, next.m, next.n)) {
                continue;
            }
            // 是0且没有访问过
            if ((next.get_map()) && next.get_met() == false) {
                next.set_met();
                current_volume ++;
                que.push(next);
            }
        }
        que.pop();
    }
    if (current_volume >= T) {
        answer += current_volume;
    }
}

int main () {
    std::cin >> M >> N >> L >> T;
    for(int i=0;i<L;i++) {
        for (int j=0;j<M;j++) {
            for(int k=0;k<N;k++) {
                std::cin >> map[i][j][k];
            }
        }
    }
    for(int i=0;i<L;i++) {
        for (int j=0;j<M;j++) {
            for(int k=0;k<N;k++) {
                // 没被访问过并且不是0。
                if ((map[i][j][k]) && met[i][j][k] == false) {
                    // 搜索结束的时候判断
                    BFS(i,j,k);

                }
            }
        }
    }

    printf("%d", answer);
    
    return 0;
}