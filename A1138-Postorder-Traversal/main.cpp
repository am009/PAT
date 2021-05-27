#include <cstdio>
#include <iostream>

#ifndef ONLINE_JUDGE
#define DEBUG(X) X
#else
#define DEBUG(X) 
#endif

int N;
int *pre_o;
int *in_o;

struct node {
    int data;
    struct node* left;
    struct node* right;
};
typedef struct node node;

node* head = nullptr;

void build_tree(int inl, int inr, int prel, int prer, node* &head) {
    if(inl > inr || prel > prer) {
        return;
    }
    int root = pre_o[prel];
    int root_in_ind = -1;
    for(int i=inl;i <= inr; i ++) {
        if (in_o[i] == root) {
            root_in_ind = i;
            break;
        }
    }
    head = new node;
    head->data = root;
    head->left = nullptr;
    head->right = nullptr;
    int left_node_count = root_in_ind - 1 - inl + 1;
    int right_node_count = inr - (root_in_ind+1) +1;
    DEBUG(printf("root: %d, left: %d, right %d\n",root, left_node_count, right_node_count);)
    build_tree(inl, root_in_ind-1, prel+1, prel + 1 + left_node_count - 1, head->left);
    build_tree(root_in_ind+1, inr, prel + 1 + left_node_count,prer, head->right);
}

void traverse(node* root) {
    if(root->left != nullptr) {
        traverse(root->left);
    }
    if(root->right != nullptr) {
        traverse(root->right);
    }
    printf("%d\n", root->data);
    exit(0);
}

int main () {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    #endif
    std::cin >> N;
    pre_o = new int[N];
    for(int i=0;i<N;i++) {
        std::cin >> pre_o[i];
    }

    in_o = new int[N];
    for(int i=0;i<N;i++) {
        std::cin >> in_o[i];
    }

    build_tree(0, N-1, 0,N-1, head);
    traverse(head);

    return 0;
}