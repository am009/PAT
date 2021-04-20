#include <cstdio>
#include <iostream>
#include <vector>

using std::vector;using  std::cin;

struct node {
    double data;
    vector<int> childs;
    bool is_leaf;
    int product_num;
};

typedef struct node node;

int COUNT;
double unit_price, rate;
node* nodes;
double final_sale = 0;

void traverse_set_data(double price, int root_ind) {
    nodes[root_ind].data = price;
    vector<int> vec = nodes[root_ind].childs;
    if(!vec.empty()) {
        vector<int>::iterator it;
        for(it = vec.begin(); it != vec.end(); it++) {
            traverse_set_data(price*rate, *it);
        }
    } else {
        if (! nodes[root_ind].is_leaf) {
            printf("#err1#");
        }
        final_sale += price * nodes[root_ind].product_num;
    }
}

int main () {
    std::cin >> COUNT >> unit_price >> rate;
    rate = rate / 100.0 + 1.0;
    nodes = new node[COUNT];
    for (int i=0;i<COUNT;i++) {
        nodes[i].data = 3.141; // error num
        nodes[i].is_leaf = false;
        nodes[i].product_num = -1;
        // read childs
        int count;
        cin >> count;
        if (count == 0) {
            nodes[i].is_leaf = true;
            cin >> nodes[i].product_num;
        } else {
            for (int j=0;j<count;j++) {
                int tmp;
                cin >> tmp;
                nodes[i].childs.push_back(tmp);
            }
        }
    }

    // 遍历设置data，同时计算结果
    traverse_set_data(unit_price, 0);

    printf("%.1lf", final_sale);

    return 0;
}