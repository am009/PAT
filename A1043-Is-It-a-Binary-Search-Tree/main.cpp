#include <cstdio>
#include <iostream>

struct node {
    int data;
    struct node* l;
    struct node* r;
};

typedef struct node node;
node* HEAD = nullptr;

int *seqs;


node* new_node(int data) {
    node* tmp = new node;
    tmp->data = data;
    tmp->l = nullptr;
    tmp->r = nullptr;
    return tmp;
}

// head只有在HEAD为null的时候才能为null
void insert(node* head, int data) {
    if (head == nullptr) {
        HEAD = new_node(data);
        return;
    }

    if (data < head->data) {
        // 插入左子树
        if (head->l == nullptr) {
            head->l = new_node(data);
            return;
        } else {
            insert(head->l, data);
            return;
        }
    } else {
        // 右
        if (head -> r == nullptr) {
            head->r = new_node(data);
            return;
        } else {
            insert(head->r, data);
            return;
        }
    }
}


bool is_preo(node* head) {
    static int count = 0;
    if (head == nullptr) {
        return true;
    }
    if (head->data == seqs[count]) {
        count ++;
        return is_preo(head->l) && is_preo(head->r);
    } else {
        return false;
    }
}

bool is_preo_mirror(node* head) {
    static int count = 0;
    if (head == nullptr) {
        return true;
    }
    if (head->data == seqs[count]) {
        count ++;
        return is_preo_mirror(head->r) && is_preo_mirror(head->l);
    } else {
        return false;
    }
}

void postO_print(node* head) {
    static bool init = true;
    if (head == nullptr) {
        return ;
    }
    postO_print(head->l);
    postO_print(head->r);
    if (init) {
        init =false;
        printf("YES\n%d", head->data);
    } else {
        printf(" %d", head->data);
    }
}

void postO_print_mirror(node* head) {
    static bool init = true;
    if (head == nullptr) {
        return ;
    }
    postO_print_mirror(head->r);
    postO_print_mirror(head->l);
    if (init) {
        init =false;
        printf("YES\n%d", head->data);
    } else {
        printf(" %d", head->data);
    }
}

int main () {
    int count;
    std::cin >> count;
    seqs = new int[count];
    for(int i=0;i<count;i++) {
        std::cin >> seqs[i];
        insert(HEAD, seqs[i]);
    }

    if (is_preo(HEAD)) {
        postO_print(HEAD);
        return 0;
    }

    if (is_preo_mirror(HEAD)) {
        postO_print_mirror(HEAD);
        return 0;
    }
    printf("NO");
    return 0;
}