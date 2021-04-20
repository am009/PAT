#include <cstdio>
#include <iostream>
#include <stack>
#include <cstring>

struct node {
    int data;
    struct node* lchild;
    struct node* rchild;
};

typedef struct node node;

node* head;

int N;
char buf[11];
int * preO;
int *inO;

// 先序和中序构建树，包含端点
node* construct(int inOl, int inOr, int preOl, int preOr) {
    if (inOl > inOr || preOl > preOr) {
        return nullptr;
    }
    // 初始化
    node* head = new node;
    head->data = preO[preOl];
    // 计算位置
    int ind = -1;
    for(int i=inOl;i<=inOr;i++) {
        if (inO[i] == head->data) {
            ind = i;
            break;
        }
    }
    if (ind == -1) {
        // printf("#err1#");
        return nullptr;
    }
    int lLen = ind - inOl;
    // 递归构建
    head->lchild = construct(inOl, ind-1, preOl+1, preOl+lLen);
    head->rchild = construct(ind+1, inOr, preOl+1+lLen, preOr);
    return head;
}


void postVisit(node* head) {\
    static bool first = true;
    if (head == nullptr) {
        return;
    }
    postVisit(head->lchild);
    postVisit(head -> rchild);
    if(first) {
        printf("%d", head->data);
        first = false;
    } else {
        printf(" %d", head->data);
    }
}

int main () {
    std::cin >> N;
    preO = new int[N];
    inO = new int[N];

    std::stack<int> que_tmp;
    int tmp;
    int push_ind = 0;
    int pop_ind = 0;
    for (int i=0;i<2*N;i++) {
        scanf("%10s", buf);
        if (!strcmp(buf, "Push")) {
            std::cin >> tmp;
            que_tmp.push(tmp);
            preO[push_ind] = tmp;
            push_ind ++;
            // printf("push %d\n", tmp);
        } else if(!strcmp(buf, "Pop")) {
            inO[pop_ind] = que_tmp.top();
            pop_ind ++;
            // printf("pop %d\n", que_tmp.top());
            que_tmp.pop();
        } else {
            // printf("#err#");
        }
    }
    if(push_ind != N && pop_ind != N) {
        printf("!%d %d\n", push_ind, pop_ind);
    }
    
    head = construct(0, N-1, 0, N-1);

    postVisit(head);

    return 0;
}