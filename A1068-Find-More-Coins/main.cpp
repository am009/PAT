#include <cstdio>
#include <iostream>
#include <algorithm>
#include <functional>

#ifndef ONLINE_JUDGE
#define DEBUG(X) X
#else
#define DEBUG(X) 
#endif

int bp_volume;
int bp_item_count;
int *item_weights;

int *values;

bool* choice_area;
bool** choice;

int main () {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    #endif
    std::cin >> bp_item_count >> bp_volume;

    item_weights = new int[bp_item_count];
    for(int i=0;i<bp_item_count;i++) {
        std::cin >> item_weights[i];
    }

    std::sort(item_weights, item_weights+bp_item_count, std::greater<int>());
    // for(int i=0;i<bp_item_count;i++) {
    //     printf("%d ", item_weights[i]);
    // }

    // dp
    // 
    // choice_area = new bool[bp_item_count * (bp_volume+1)];
    choice = new bool*[bp_item_count];
    for(int i=0;i<bp_item_count;i++) {
        choice[i] = new bool[(bp_volume+1)];
        for(int j=0;j<=bp_volume;j++) {
            // choice_area[i*(bp_volume+1)+j] = false;
            choice[i][j] = false;
        }
    }

    values = new int[bp_volume+1];
    for(int i=0;i<=bp_volume;i++) {
        values[i] = 0;
    }
    for(int i=0;i<bp_item_count;i++) {
        for(int v=bp_volume;v>=item_weights[i];v--) {
            // 保证v-item_weights[i]是合法下标
            int new_value = values[v-item_weights[i]] + item_weights[i];
            if(new_value >= values[v]) {
                choice[i][v] = true;
                values[v] = new_value;
            }
        }
        // if (i == bp_item_count-1) {
            for(int v=0;v<=bp_volume;v++) {
                DEBUG(printf("%d ", values[v]);)
            }
            DEBUG(printf("\n");)
        // }
    }

    for(int i=0;i<bp_item_count;i++) {
        for(int j=0;j<=bp_volume;j++) {
            // choice_area[i*(bp_volume+1)+j] = false;
            DEBUG(printf("%d ", choice[i][j]);)
        }
        DEBUG(printf("\n");)
    }
    if (values[bp_volume] != bp_volume) {
        printf("No Solution");
        return 0;
    }
    // 倒着获取结果。
    int value = bp_volume;
    bool init =true;
    for(int i=bp_item_count-1;i>=0 && value > 0;i--) {
        if (choice[i][value]) {
            // 选了
            value -= item_weights[i];
            // printf("select: %d, cur_val: %d, item_weight: %d \n", i, value, item_weights[i]);
            if (init) {
                init = false;
                printf("%d", item_weights[i]);
            } else {
                printf(" %d", item_weights[i]);
            }
            
        } else {
            // 没选
        }
    }



    return 0;
}