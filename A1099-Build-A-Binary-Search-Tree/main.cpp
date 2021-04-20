#include <cstdio>
#include <iostream>
#include <algorithm>
#include <queue>

struct node
{
    int data;
    int l;
    int r;
};
typedef struct node node;

int count;
node* arr;
int* datas;

void inO_fill(int root) {
    static int ind = 0;
    if (root == -1) {
        return;
    }
    inO_fill(arr[root].l);
    arr[root].data = datas[ind++];
    inO_fill(arr[root].r);
}

int main () {
    
    std::cin >> count;
    arr = new node[count];
    datas = new int[count];
    for (int i=0;i<count;i++) {
        std::cin >> arr[i].l;
        std::cin >> arr[i].r;
    }

    for (int i=0;i<count;i++) {
        std::cin >> datas[i];
    }
    std::sort(datas, datas+count);

    inO_fill(0);

    std::queue<int> que;
    que.push(0);
    printf("%d", arr[0].data);
    while(!que.empty()) {
        int front = que.front();
        if(arr[front].l != -1) {
            printf(" %d", arr[arr[front].l].data);
            que.push(arr[front].l);
        }
        if(arr[front].r != -1) {
            printf(" %d", arr[arr[front].r].data);
            que.push(arr[front].r);
        }
        que.pop();
    }

    return 0;
}