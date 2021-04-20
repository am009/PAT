#include <cstdio>
#include <iostream>
#include <algorithm>

struct node {
    int data;
    struct node* l;
    struct node* r;
    int height;
};
typedef struct node node;

node* head = nullptr;

int get_height(node* root) {
    if(root == nullptr) {
        return 0;
    }
    return root->height;
}

void update_height(node* root) {
    root->height = std::max<int>(get_height(root->l), get_height(root->r)) + 1;
}

int get_balance_factor(node* root) {
    return get_height(root->l) - get_height(root->r);
}

//  旋转方向的记忆：以下方节点为中心（虽然调用的时候参数是上方节点）
// 左旋是从左上到左下，右旋是从右上到右下。
// 注意维护高度
void rotate_left1(node* &root) {
    if (root->r == nullptr) {
        printf("#error5#");
    }
    // 初始状态是向右的　`\` 心中有一个`>`形
    node* middle = root->r->l;
    node* tmp = root->r;
    //形成`M`形
    root->r = middle;
    //篡位
    tmp->l = root;
    root = tmp;
    update_height(root->l);
    update_height(root);
}

void rotate_left(node* &root) {
    // `>`
    node* tmp = root->r;
    root->r = tmp->l;
    tmp->l = root;
    update_height(root); // lower
    update_height(tmp);
    root = tmp;
}

void rotate_right(node* &root) {
    if (root->l == nullptr) {
        printf("#error6#");
    }
    node* middle = root->l->r;
    node* tmp = root->l;
    //形成`M`形
    root->l = middle;
    //篡位
    tmp->r = root;
    root = tmp;
    update_height(root->r);
    update_height(root);
}

void insert(node* &head, int data) {
    if (head == nullptr) {
        head = new node;
        head->l = nullptr;
        head->r = nullptr;
        head->height = 1; // 对
        head->data = data;
        return;
    }

    if (data < head->data) { // left
        insert(head->l, data);
        update_height(head);
        int balance = get_height(head->l) - get_height(head->r);
        if (balance == 2) { // 向左子树插入后就一定是2，否则不用平衡
            int c_balance = get_balance_factor(head->l);
            if(c_balance == 1) { // LL `/`
                rotate_right(head);
            } else if(c_balance == -1) { // LR `<`
                rotate_left(head->l);
                rotate_right(head);
            } else {
                puts("#ERR1#");
            }
        } else if(balance>2 || balance <= -2 ) {puts("#ERR2#");}
    }else { // right
        insert(head->r, data);
        update_height(head);
        int balance = get_height(head->l) - get_height(head->r);
        if (balance == -2) { // 向右子树插入后就一定是2，否则不用平衡
            int c_balance = get_balance_factor(head->r);
            if(c_balance == -1) { // RR `\`
                rotate_left(head);
            } else if(c_balance == 1) { // RL `>`
                rotate_right(head->r);
                rotate_left(head);
            } else {
                puts("#ERR1#");
            }
        } else if(balance>=2 || balance < -2 )  {
            puts("#ERR4#");
        }
    }

}

int main () {
    #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    #endif
    int count;
    std::cin >> count;
    for(int i=0;i<count;i++) {
        int data;
        std::cin >> data;
        insert(head, data);
    }

    printf("%d", head->data);

    return 0;
}
