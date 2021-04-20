#include <cstdio>
#include <iostream>
#include <queue>

struct node {
    int data;
    struct node* lchild;
    struct node* rchild;
};

typedef struct node node;

int N;

int *postO;
int *inO;
node* head;

// 利用在两个序列中的下标，在堆上构建二叉树。
node* construct(int inOl, int inOr, int postOl, int postOr) {
    if (inOl > inOr) {
        return nullptr;
    }
    if (postOl > postOr) {
        return nullptr;
    }
    
    node* head = new node;
    head->data = postO[postOr];
    int ind = -1;
    for(int i=inOl;i<=inOr;i++) {
        if (inO[i] == head->data) {
            ind = i;
            break;
        }
    }
    if (ind == -1) {
        printf("err");
        return nullptr;
    }
    // 左右子树的总长度，所以除去根节点
    int len = postOr - postOl + 1 - 1;
    int lLen = ind - inOl; // 左子树长度
    // int rLen = len - lLen; // 右
    head->lchild = construct(inOl, ind-1, postOl, postOl + lLen-1);
    head->rchild = construct(ind+1, inOr, postOl+lLen, postOr-1);
    return head;
}

void BFS(node* head) {
    std::queue<node*> que;

    printf("%d", head->data);
    que.push(head);
    while(!que.empty()) {
        node* front = que.front();
        if (front->lchild) {
            printf(" %d", front->lchild->data);
            que.push(front->lchild);
        }
        if (front->rchild) {
            printf(" %d", front->rchild->data);
            que.push(front->rchild);
        }

        que.pop();
    }
}

int main () {
    std::cin >> N;
    postO = new int[N];
    inO = new int[N];

    for (int i=0;i<N;i++) {
        std::cin >> postO[i];
    }

    for (int i=0;i<N;i++) {
        std::cin >> inO[i];
    }

    head = construct(0,N-1,0,N-1);

    BFS(head);

    return 0;
}